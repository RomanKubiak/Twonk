#include "../JuceLibraryCode/JuceHeader.h"
#include "../UI/MainHostWindow.h"
#include "PluginGraph.h"
#include "InternalPlugins.h"
#include "../UI/GraphEditorPanel.h"
#include "Twonk.h"

//==============================================================================
PluginGraph::PluginGraph (AudioPluginFormatManager& fm, GraphDocumentComponent &_documentOwner, TwonkPlayHead &_twonkPlayHead)
    : FileBasedDocument (getFilenameSuffix(),
                         getFilenameWildcard(),
                         "Load a graph",
                         "Save a graph"),
      formatManager (fm), documentOwner(_documentOwner), twonkPlayHead(_twonkPlayHead)
{
    newDocument();
    graph.addListener (this);
	graph.setPlayHead(&twonkPlayHead);
}

PluginGraph::~PluginGraph()
{
    graph.removeListener (this);
    graph.removeChangeListener (this);
    graph.clear();
}

PluginGraph::NodeID PluginGraph::getNextUID() noexcept
{
    return PluginGraph::NodeID (++(lastUID.uid));
}

//==============================================================================
void PluginGraph::changeListenerCallback (ChangeBroadcaster*)
{
    changed();

    for (int i = activePluginWindows.size(); --i >= 0;)
        if (! graph.getNodes().contains (activePluginWindows.getUnchecked(i)->node))
            activePluginWindows.remove (i);
}

AudioProcessorGraph::Node::Ptr PluginGraph::getNodeForName (const String& name) const
{
    for (auto* node : graph.getNodes())
        if (auto p = node->getProcessor())
            if (p->getName().equalsIgnoreCase (name))
                return node;

    return nullptr;
}

void PluginGraph::addPlugin (const PluginDescription& desc, Point<double> pos)
{
    formatManager.createPluginInstanceAsync (desc,
                                             graph.getSampleRate(),
                                             graph.getBlockSize(),
                                             [this, pos] (std::unique_ptr<AudioPluginInstance> instance, const String& error)
                                             {
                                                 addPluginCallback (std::move (instance), error, pos);
                                             });
}

void PluginGraph::addPluginCallback (std::unique_ptr<AudioPluginInstance> instance,
                                     const String& error, Point<double> pos)
{
    if (instance == nullptr)
    {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          TRANS("Couldn't create plugin"),
                                          error);
    }
    else
    {
        instance->enableAllBuses();
		instance->setPlayHead(&twonkPlayHead);

        if (auto node = graph.addNode (std::move (instance)))
        {
            node->properties.set ("x", pos.x);
            node->properties.set ("y", pos.y);
            changed();
        }
    }
}

void PluginGraph::setNodePosition (NodeID nodeID, Point<double> pos)
{
    if (auto* n = graph.getNodeForId (nodeID))
    {
        n->properties.set ("x", jlimit (0.0, 1.0, pos.x));
        n->properties.set ("y", jlimit (0.0, 1.0, pos.y));
    }
}

Point<double> PluginGraph::getNodePosition (NodeID nodeID) const
{
    if (auto* n = graph.getNodeForId (nodeID))
        return { static_cast<double> (n->properties ["x"]),
                 static_cast<double> (n->properties ["y"]) };

    return {};
}

//==============================================================================
void PluginGraph::clear()
{
    closeAnyOpenPluginWindows();
    graph.clear();
    changed();
}

PluginWindow* PluginGraph::getOrCreateWindowFor (AudioProcessorGraph::Node* node, PluginWindow::Type type)
{
    jassert (node != nullptr);

    for (auto* w : activePluginWindows)
        if (w->node.get() == node && w->type == type)
            return w;

    if (auto* processor = node->getProcessor())
    {
        if (auto* plugin = dynamic_cast<AudioPluginInstance*> (processor))
        {
            auto description = plugin->getPluginDescription();

            if (description.pluginFormatName == "Internal")
            {
                getCommandManager().invokeDirectly (CommandIDs::showAudioSettings, false);
                return nullptr;
            }
        }
        return activePluginWindows.add (new PluginWindow (node, type, activePluginWindows, *this));
    }

    return nullptr;
}

bool PluginGraph::closeAnyOpenPluginWindows()
{
    bool wasEmpty = activePluginWindows.isEmpty();
    activePluginWindows.clear();
    return ! wasEmpty;
}

//==============================================================================
String PluginGraph::getDocumentTitle()
{
    if (! getFile().exists())
        return "Program.generic.twonk";

    return getFile().getFileNameWithoutExtension().upToFirstOccurrenceOf(".", false, true);
}

void PluginGraph::newDocument()
{
    clear();
    setFile (GET_TWONK_PROGRAM_DIR().getChildFile("Program.generic.twonk"));

    graph.removeChangeListener (this);

    InternalPluginFormat internalFormat;

    addPlugin (internalFormat.audioInDesc,  { 0.5,  0.1 });
    addPlugin (internalFormat.midiInDesc,   { 0.25, 0.1 });
    addPlugin (internalFormat.audioOutDesc, { 0.5,  0.9 });

    MessageManager::callAsync ([this] () {
        setChangedFlag (false);
        graph.addChangeListener (this);
    } );
}

Result PluginGraph::loadDocument (const File& file)
{
    if (auto xml = parseXMLIfTagMatches (file, "FILTERGRAPH"))
    {
        graph.removeChangeListener (this);
        restoreFromXml (*xml);

        MessageManager::callAsync ([this]
        {
            setChangedFlag (false);
            graph.addChangeListener (this);
        });

		setFile(file);
        return Result::ok();
    }

    return Result::fail ("Not a valid graph file");
}

Result PluginGraph::saveDocument (const File& file)
{
    auto xml = createXml();

    if (! xml->writeTo (file, {}))
        return Result::fail ("Couldn't write to the file");

    return Result::ok();
}

File PluginGraph::getSuggestedSaveAsFile (const File &defaultFile)
{
	return (GET_TWONK_PROGRAM_DIR().getChildFile(defaultFile.getFileName()));
}

File PluginGraph::getLastDocumentOpened()
{
    RecentlyOpenedFilesList recentFiles;
    recentFiles.restoreFromString (getAppProperties().getUserSettings()
                                        ->getValue ("recentFilterGraphFiles"));

    return recentFiles.getFile (0);
}

void PluginGraph::setLastDocumentOpened (const File& file)
{
    RecentlyOpenedFilesList recentFiles;
    recentFiles.restoreFromString (getAppProperties().getUserSettings()
                                        ->getValue ("recentFilterGraphFiles"));

    recentFiles.addFile (file);

    getAppProperties().getUserSettings()
        ->setValue ("recentFilterGraphFiles", recentFiles.toString());
}

static void readBusLayoutFromXml (AudioProcessor::BusesLayout& busesLayout, AudioProcessor& plugin,
                                  const XmlElement& xml, bool isInput)
{
    auto& targetBuses = (isInput ? busesLayout.inputBuses
                                 : busesLayout.outputBuses);
    int maxNumBuses = 0;

    if (auto* buses = xml.getChildByName (isInput ? "INPUTS" : "OUTPUTS"))
    {
        forEachXmlChildElementWithTagName (*buses, e, "BUS")
        {
            const int busIdx = e->getIntAttribute ("index");
            maxNumBuses = jmax (maxNumBuses, busIdx + 1);

            // the number of buses on busesLayout may not be in sync with the plugin after adding buses
            // because adding an input bus could also add an output bus
            for (int actualIdx = plugin.getBusCount (isInput) - 1; actualIdx < busIdx; ++actualIdx)
                if (! plugin.addBus (isInput))
                    return;

            for (int actualIdx = targetBuses.size() - 1; actualIdx < busIdx; ++actualIdx)
                targetBuses.add (plugin.getChannelLayoutOfBus (isInput, busIdx));

            auto layout = e->getStringAttribute ("layout");

            if (layout.isNotEmpty())
                targetBuses.getReference (busIdx) = AudioChannelSet::fromAbbreviatedString (layout);
        }
    }

    // if the plugin has more buses than specified in the xml, then try to remove them!
    while (maxNumBuses < targetBuses.size())
    {
        if (! plugin.removeBus (isInput))
            return;

        targetBuses.removeLast();
    }
}

static XmlElement* createBusLayoutXml (const AudioProcessor::BusesLayout& layout, const bool isInput)
{
    auto& buses = isInput ? layout.inputBuses
                          : layout.outputBuses;

    auto* xml = new XmlElement (isInput ? "INPUTS" : "OUTPUTS");

    for (int busIdx = 0; busIdx < buses.size(); ++busIdx)
    {
        auto& set = buses.getReference (busIdx);

        auto* bus = xml->createNewChildElement ("BUS");
        bus->setAttribute ("index", busIdx);
        bus->setAttribute ("layout", set.isDisabled() ? "disabled" : set.getSpeakerArrangementAsString());
    }

    return xml;
}

static XmlElement* createNodeXml (AudioProcessorGraph::Node* const node) noexcept
{
    if (auto* plugin = dynamic_cast<AudioPluginInstance*> (node->getProcessor()))
    {
        auto e = new XmlElement ("FILTER");
        e->setAttribute ("uid", (int) node->nodeID.uid);
        e->setAttribute ("x", node->properties ["x"].toString());
        e->setAttribute ("y", node->properties ["y"].toString());

        for (int i = 0; i < (int) PluginWindow::Type::numTypes; ++i)
        {
            auto type = (PluginWindow::Type) i;

            if (node->properties.contains (PluginWindow::getOpenProp (type)))
            {
                e->setAttribute (PluginWindow::getLastXProp (type), node->properties[PluginWindow::getLastXProp (type)].toString());
                e->setAttribute (PluginWindow::getLastYProp (type), node->properties[PluginWindow::getLastYProp (type)].toString());
				e->setAttribute (PluginWindow::getLastWidthProp (type), node->properties[PluginWindow::getLastWidthProp (type)].toString());
				e->setAttribute (PluginWindow::getLastHeightProp (type), node->properties[PluginWindow::getLastHeightProp (type)].toString());
                e->setAttribute (PluginWindow::getOpenProp (type),  node->properties[PluginWindow::getOpenProp (type)].toString());
				e->setAttribute (PluginWindow::getLastStickyProp (type), node->properties[PluginWindow::getLastStickyProp (type)].toString());
            }
        }

        {
            PluginDescription pd;
            plugin->fillInPluginDescription (pd);
            e->addChildElement (pd.createXml().release());
        }

        {
            MemoryBlock m;
            node->getProcessor()->getStateInformation (m);
            e->createNewChildElement ("STATE")->addTextElement (m.toBase64Encoding());
        }

        auto layout = plugin->getBusesLayout();

        auto layouts = e->createNewChildElement ("LAYOUT");
        layouts->addChildElement (createBusLayoutXml (layout, true));
        layouts->addChildElement (createBusLayoutXml (layout, false));

        return e;
    }

    jassertfalse;
    return nullptr;
}

void PluginGraph::createNodeFromXml (const XmlElement& xml)
{
    PluginDescription pd;

    forEachXmlChildElement (xml, e)
    {
        if (pd.loadFromXml (*e))
            break;
    }

    String errorMessage;

    if (auto instance = formatManager.createPluginInstance (pd, graph.getSampleRate(),
                                                            graph.getBlockSize(), errorMessage))
    {
        if (auto* layoutEntity = xml.getChildByName ("LAYOUT"))
        {
            auto layout = instance->getBusesLayout();

            readBusLayoutFromXml (layout, *instance, *layoutEntity, true);
            readBusLayoutFromXml (layout, *instance, *layoutEntity, false);

            instance->setBusesLayout (layout);
        }

        if (auto node = graph.addNode (std::move (instance), NodeID ((uint32) xml.getIntAttribute ("uid"))))
        {
            if (auto* state = xml.getChildByName ("STATE"))
            {
                MemoryBlock m;
                m.fromBase64Encoding (state->getAllSubText());

                node->getProcessor()->setStateInformation (m.getData(), (int) m.getSize());
            }

            node->properties.set ("x", xml.getDoubleAttribute ("x"));
            node->properties.set ("y", xml.getDoubleAttribute ("y"));

            for (int i = 0; i < (int) PluginWindow::Type::numTypes; ++i)
            {
                auto type = (PluginWindow::Type) i;

                if (xml.hasAttribute (PluginWindow::getOpenProp (type)))
                {
                    node->properties.set (PluginWindow::getLastXProp (type), xml.getIntAttribute (PluginWindow::getLastXProp (type)));
                    node->properties.set (PluginWindow::getLastYProp (type), xml.getIntAttribute (PluginWindow::getLastYProp (type)));
					node->properties.set (PluginWindow::getLastWidthProp (type), xml.getIntAttribute (PluginWindow::getLastWidthProp (type)));
					node->properties.set (PluginWindow::getLastHeightProp (type), xml.getIntAttribute (PluginWindow::getLastHeightProp (type)));
                    node->properties.set (PluginWindow::getOpenProp  (type), xml.getIntAttribute (PluginWindow::getOpenProp (type)));
					node->properties.set (PluginWindow::getLastStickyProp  (type), xml.getIntAttribute (PluginWindow::getLastStickyProp (type)));
					//DBG("PluginGraph::createNodeFromXml lastSticky:" + String(xml.getIntAttribute (PluginWindow::getLastStickyProp (type))));
					if (node->properties[PluginWindow::getOpenProp (type)])
                    {
                        jassert (node->getProcessor() != nullptr);

                        if (auto w = getOrCreateWindowFor (node, type))
                            w->toFront (true);
                    }
                }
            }
        }
    }
}

std::unique_ptr<XmlElement> PluginGraph::createXml() const
{
    auto xml = std::make_unique<XmlElement> ("FILTERGRAPH");

    for (auto* node : graph.getNodes())
        xml->addChildElement (createNodeXml (node));

    for (auto& connection : graph.getConnections())
    {
        auto e = xml->createNewChildElement ("CONNECTION");

        e->setAttribute ("srcFilter", (int) connection.source.nodeID.uid);
        e->setAttribute ("srcChannel", connection.source.channelIndex);
        e->setAttribute ("dstFilter", (int) connection.destination.nodeID.uid);
        e->setAttribute ("dstChannel", connection.destination.channelIndex);
    }

    return xml;
}

void PluginGraph::restoreFromXml (const XmlElement& xml)
{
    clear();

    forEachXmlChildElementWithTagName (xml, e, "FILTER")
    {
        createNodeFromXml (*e);
        changed();
    }

    forEachXmlChildElementWithTagName (xml, e, "CONNECTION")
    {
        graph.addConnection ({ { NodeID ((uint32) e->getIntAttribute ("srcFilter")), e->getIntAttribute ("srcChannel") },
                               { NodeID ((uint32) e->getIntAttribute ("dstFilter")), e->getIntAttribute ("dstChannel") } });
    }

    graph.removeIllegalConnections();
}

File PluginGraph::getDefaultGraphDocumentOnMobile()
{
    auto persistantStorageLocation = File::getSpecialLocation (File::userApplicationDataDirectory);
    return persistantStorageLocation.getChildFile ("state.twonk");
}

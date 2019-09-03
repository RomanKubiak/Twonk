#include "Document.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Filters/InternalPlugins.h"
#include "MainHostWindow.h"
#include "TwonkToolBar.h"
#include "TwonkToolBarButton.h"
#include "TwonkProgramMenu.h"
#include "Twonk.h"
#include "TwonkProgramList.h"
#include "TwonkTransport.h"
#include "TwonkFilterPopupProperties.h"
#include "PluginGraph.h"

/*
 * GraphDocumentComponent
 */
Document::Document (AudioPluginFormatManager& fm, AudioDeviceManager& dm, KnownPluginList& kpl)
        : deviceManager (dm),
          pluginList (kpl),
          graphPlayer (getAppProperties().getUserSettings()->getBoolValue ("doublePrecisionProcessing", false)),
          twonkPlayHead(dm),
          graph (new PluginGraph (fm, *this, twonkPlayHead))
{
    init();

    deviceManager.addChangeListener (graphPanel.get());
    deviceManager.addAudioCallback (&graphPlayer);
    deviceManager.addMidiInputDeviceCallback ({}, &graphPlayer.getMidiMessageCollector());
}

void Document::init()
{
    graphPanel.reset (new Editor (*graph, deviceManager, twonkPlayHead));
    addAndMakeVisible (graphPanel.get());

    graphPlayer.setProcessor (&graph->graph);
    graphPanel->updateComponents();
}

Document::~Document()
{
    releaseGraph();
}

void Document::resized()
{
    graphPanel->setBounds (getLocalBounds());
}

void Document::createNewPlugin (const PluginDescription& desc, Point<int> pos)
{
    graphPanel->createNewPlugin (desc, pos);
}

void Document::releaseGraph()
{
    deviceManager.removeAudioCallback (&graphPlayer);
    deviceManager.removeMidiInputDeviceCallback ({}, &graphPlayer.getMidiMessageCollector());

    if (graphPanel != nullptr)
    {
        deviceManager.removeChangeListener (graphPanel.get());
        graphPanel = nullptr;
    }

    graphPlayer.setProcessor (nullptr);
    graph = nullptr;
}

bool Document::isInterestedInDragSource (const SourceDetails& details)
{
    return ((dynamic_cast<ListBox*> (details.sourceComponent.get()) != nullptr)
            && details.description.toString().startsWith ("PLUGIN"));
}

void Document::itemDropped (const SourceDetails& details)
{
    auto pluginTypeIndex = details.description.toString()
            .fromFirstOccurrenceOf ("PLUGIN: ", false, false)
            .getIntValue();

    // must be a valid index!
    jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

    createNewPlugin (pluginList.getTypes()[pluginTypeIndex], details.localPosition);
}

void Document::setDoublePrecision (bool doublePrecision)
{
    graphPlayer.setDoublePrecisionProcessing (doublePrecision);
}

bool Document::closeAnyOpenPluginWindows()
{
    return graphPanel->graph.closeAnyOpenPluginWindows();
}

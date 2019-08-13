/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphEditorPanel.h"
#include "../Filters/InternalFilters.h"
#include "MainHostWindow.h"
#include "GraphDocument.h"
#include "TwonkFilterComponent.h"
#include "TwonkFilterConnector.h"

struct GraphEditorPanel::PluginListBoxModel : public ListBoxModel,
	public ChangeListener,
	public MouseListener
{
	PluginListBoxModel (ListBox& lb, KnownPluginList& kpl)
		: owner (lb),
		knownPlugins (kpl)
	{
		knownPlugins.addChangeListener (this);
		owner.addMouseListener (this, true);
	}

	int getNumRows() override
	{
		return knownPlugins.getNumTypes();
	}

	void paintListBoxItem (int rowNumber, Graphics& g,
		int width, int height, bool rowIsSelected) override
	{
		g.fillAll (rowIsSelected ? Colour (0xff42A2C8)
			: Colour (0xff263238));

		g.setColour (rowIsSelected ? Colours::black : Colours::white);
		g.setFont(Font("Liberation Sans", 20.0f, Font::plain));
		knownPlugins.sort(KnownPluginList::sortAlphabetically, true);
		if (rowNumber < knownPlugins.getNumTypes())
			g.drawFittedText (knownPlugins.getType (rowNumber)->name,
				{ 0, 0, width - 4, height - 2 },
				Justification::centredRight,
				1);

		g.setColour (Colours::black.withAlpha (0.4f));
		g.drawRect (0, height - 1, width, 1);
	}

	var getDragSourceDescription (const SparseSet<int>& selectedRows) override
	{
		if (!isOverSelectedRow)
			return var();

		return String ("PLUGIN: " + String (selectedRows[0]));
	}

	void changeListenerCallback (ChangeBroadcaster*) override
	{
		owner.updateContent();
	}

	void mouseDown (const MouseEvent& e) override
	{
		isOverSelectedRow = owner.getRowPosition (owner.getSelectedRow(), true)
			.contains (e.getEventRelativeTo (&owner).getMouseDownPosition());
	}

	ListBox& owner;
	KnownPluginList& knownPlugins;

	bool isOverSelectedRow = false;
};

GraphEditorPanel::GraphEditorPanel (AudioPluginFormatManager& _formatManager,
	AudioDeviceManager& _deviceManager,
	KnownPluginList& _pluginList,
	TwonkPlayHead &_twonkPlayHead)
	: graph (new FilterGraph (formatManager, _twonkPlayHead)),
	twonkPlayHead(_twonkPlayHead),
	pluginList(_pluginList),
	deviceManager(_deviceManager),
	formatManager(_formatManager)
{
	toolBar.reset(new TwonkTitleBarComponent(*this));
	toolBar->setAlwaysOnTop(true);
	toolBar->setTopLeftPosition(32, 32);
	addAndMakeVisible(toolBar.get());
    graph->addChangeListener (this);
    setOpaque (false);
	bgImage = ImageCache::getFromMemory(BinaryData::hexagon_png, BinaryData::hexagon_pngSize);

	deviceManager.addChangeListener (this);
	deviceManager.addAudioCallback (&graphPlayer);
	deviceManager.addMidiInputCallback (String(), &graphPlayer.getMidiMessageCollector());
}

GraphEditorPanel::~GraphEditorPanel()
{
	releaseGraph();
	draggingConnector = nullptr;
	connectors.clear();
}

void GraphEditorPanel::releaseGraph()
{
	deviceManager.removeAudioCallback (&graphPlayer);
	deviceManager.removeMidiInputCallback (String(), &graphPlayer.getMidiMessageCollector());
	deviceManager.removeChangeListener (this);
	graphPlayer.setProcessor (nullptr);
	graph = nullptr;
}

void GraphEditorPanel::init()
{
	graphPlayer.setProcessor (&graph->graph);
	audioSettingsComponent.reset(new AudioDeviceSelectorComponent (deviceManager, 1, 8, 1, 8, true, true, true, false));
	updateComponents();

	if (isOnTouchDevice())
	{
		pluginListBoxModel.reset (new PluginListBoxModel (pluginListBox, pluginList));
		pluginListBox.setModel (pluginListBoxModel.get());
		pluginListBox.setRowHeight (28);

		auto deadMansPedalFile = getAppProperties().getUserSettings()
			->getFile().getSiblingFile ("RecentlyCrashedPluginsList");

		pluginListComponent.reset(new PluginListComponent (formatManager, pluginList, deadMansPedalFile, getAppProperties().getUserSettings(), true));
	}
}

bool GraphEditorPanel::closeAnyOpenPluginWindows()
{
	return graph->closeAnyOpenPluginWindows();
}

void GraphEditorPanel::paint (Graphics& g)
{
	g.drawImageWithin(bgImage, 0, 0, getWidth(), getHeight(), RectanglePlacement::fillDestination, false);
}

void GraphEditorPanel::mouseDown (const MouseEvent& e)
{
    if (isOnTouchDevice())
    {
        originalTouchPos = e.position.toInt();
        startTimer (750);
    }

    if (e.mods.isPopupMenu())
        showPopupMenu (e.position.toInt());

}

void GraphEditorPanel::mouseDoubleClick(const MouseEvent &e)
{
	showPopupMenu (e.position.toInt());
}

void GraphEditorPanel::mouseUp (const MouseEvent&)
{
    if (isOnTouchDevice())
    {
        stopTimer();
        //callAfterDelay (250, []() { PopupMenu::dismissAllActiveMenus(); });
    }
}

void GraphEditorPanel::mouseDrag (const MouseEvent& e)
{
    if (isOnTouchDevice() && e.getDistanceFromDragStart() > 5)
        stopTimer();

}

void GraphEditorPanel::createNewPlugin (const PluginDescription& desc, Point<int> position)
{
    graph->addPlugin (desc, position.toDouble() / Point<double> ((double) getWidth(), (double) getHeight()));
}

TwonkFilterComponent* GraphEditorPanel::getComponentForFilter (AudioProcessorGraph::NodeID nodeID) const
{
    for (auto* fc : nodes)
       if (fc->pluginID == nodeID)
            return fc;

    return nullptr;
}

TwonkFilterConnector* GraphEditorPanel::getComponentForConnection (const AudioProcessorGraph::Connection& conn) const
{
    for (auto* cc : connectors)
        if (cc->connection == conn)
            return cc;

    return nullptr;
}

TwonkFilterComponentPinWrapper* GraphEditorPanel::findPinAt (Point<float> pos) const
{
    for (auto* fc : nodes)
    {
        // NB: A Visual Studio optimiser error means we have to put this Component* in a local
        // variable before trying to cast it, or it gets mysteriously optimised away..
        auto* comp = fc->getComponentAt (pos.toInt() - fc->getPosition());

        if (auto* pin = dynamic_cast<TwonkFilterComponentPinWrapper*> (comp))
            return pin;
    }

    return nullptr;
}

void GraphEditorPanel::resized()
{
    updateComponents();
}

void GraphEditorPanel::changeListenerCallback (ChangeBroadcaster*)
{
    updateComponents();
}

void GraphEditorPanel::updateComponents()
{
    for (int i = nodes.size(); --i >= 0;)
        if (graph->graph.getNodeForId (nodes.getUnchecked(i)->pluginID) == nullptr)
            nodes.remove (i);

    for (int i = connectors.size(); --i >= 0;)
        if (! graph->graph.isConnected (connectors.getUnchecked(i)->connection))
            connectors.remove (i);

    for (auto* fc : nodes)
        fc->update();

    for (auto* cc : connectors)
        cc->update();

    for (auto* f : graph->graph.getNodes())
    {
        if (getComponentForFilter (f->nodeID) == nullptr)
        {
            auto* comp = nodes.add (new TwonkFilterComponent (*this, f->nodeID));
            addAndMakeVisible (comp);
            comp->update();
        }
    }

    for (auto& c : graph->graph.getConnections())
    {
        if (getComponentForConnection (c) == nullptr)
        {
            auto* comp = connectors.add (new TwonkFilterConnector (*this));
            addAndMakeVisible (comp);

            comp->setInput (c.source);
            comp->setOutput (c.destination);
        }
    }
}

void GraphEditorPanel::showPopupMenu (Point<int> mousePos)
{
    menu.reset (new PopupMenu);

    if (auto* mainWindow = findParentComponentOfClass<MainHostWindow>())
    {
        mainWindow->addPluginsToMenu (*menu);

        menu->showMenuAsync ({},
                             ModalCallbackFunction::create ([this, mousePos] (int r)
		{
			DBG("GraphEditorPanel::showPopupMenu r=" + String(r));
			if (r == 0)
				return;

			if (auto* mainWin = findParentComponentOfClass<MainHostWindow>())
			{
				const PluginDescription* desc = mainWin->getChosenType(r);
				
				if (desc)
				{
					DBG("GraphEditorPanel::showPopupMenu createNewPlugin desc:"+desc->descriptiveName);
					createNewPlugin (*desc, mousePos);
				}
			}
		}));
	}
}

void GraphEditorPanel::beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                                           AudioProcessorGraph::NodeAndChannel dest,
                                           const MouseEvent& e)
{
    auto* c = dynamic_cast<TwonkFilterConnector*> (e.originalComponent);
    connectors.removeObject (c, false);
    draggingConnector.reset (c);

    if (draggingConnector == nullptr)
        draggingConnector.reset (new TwonkFilterConnector (*this));

    draggingConnector->setInput (source);
    draggingConnector->setOutput (dest);

    addAndMakeVisible (draggingConnector.get());
    draggingConnector->toFront (false);

    dragConnector (e);
}

void GraphEditorPanel::dragConnector (const MouseEvent& e)
{
    auto e2 = e.getEventRelativeTo (this);

    if (draggingConnector != nullptr)
    {
        draggingConnector->setTooltip ({});

        auto pos = e2.position;

        if (auto* pin = findPinAt (pos))
        {
            auto connection = draggingConnector->connection;

            if (connection.source.nodeID == AudioProcessorGraph::NodeID() && ! pin->isInput())
            {
                connection.source = pin->getPin();
            }
            else if (connection.destination.nodeID == AudioProcessorGraph::NodeID() && pin->isInput())
            {
                connection.destination = pin->getPin();
            }

            if (graph->graph.canConnect (connection))
            {
                pos = (pin->getParentComponent()->getPosition() + pin->getBounds().getCentre()).toFloat();
                draggingConnector->setTooltip (pin->getTooltip());
            }
        }

        if (draggingConnector->connection.source.nodeID == AudioProcessorGraph::NodeID())
            draggingConnector->dragStart (pos);
        else
            draggingConnector->dragEnd (pos);
    }
}

void GraphEditorPanel::endDraggingConnector (const MouseEvent& e)
{
    if (draggingConnector == nullptr)
        return;

    draggingConnector->setTooltip ({});

    auto e2 = e.getEventRelativeTo (this);
    auto connection = draggingConnector->connection;

    draggingConnector = nullptr;

    if (auto* pin = findPinAt (e2.position))
    {
        if (connection.source.nodeID == AudioProcessorGraph::NodeID())
        {
            if (pin->isInput())
                return;

            connection.source = pin->getPin();
        }
        else
        {
            if (! pin->isInput())
                return;

            connection.destination = pin->getPin();
        }

        graph->graph.addConnection (connection);
    }
}

void GraphEditorPanel::timerCallback()
{
    // this should only be called on touch devices
    jassert (isOnTouchDevice());

    stopTimer();
    showPopupMenu (originalTouchPos);
}

bool GraphEditorPanel::isInterestedInDragSource (const SourceDetails& details)
{
	return ((dynamic_cast<ListBox*> (details.sourceComponent.get()) != nullptr)
		&& details.description.toString().startsWith ("PLUGIN"));
}

void GraphEditorPanel::itemDropped (const SourceDetails& details)
{
	auto pluginTypeIndex = details.description.toString()
		.fromFirstOccurrenceOf ("PLUGIN: ", false, false)
		.getIntValue();

	// must be a valid index!
	jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

	createNewPlugin (*pluginList.getType (pluginTypeIndex), details.localPosition);
}
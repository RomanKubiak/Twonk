/*
  ==============================================================================

    GraphDocument.cpp
    Created: 5 Jun 2019 5:47:06pm
    Author:  rkubiak

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphEditorPanel.h"
#include "../Filters/InternalFilters.h"
#include "MainHostWindow.h"
#include "GraphDocument.h"
#include "../TwonkPlayHead.h"
#include "../UI/TwonkTitleBarComponent.h"
#include "Filters/FilterGraph.h"
//==============================================================================
struct GraphDocumentComponent::PluginListBoxModel : public ListBoxModel,
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

//==============================================================================
GraphDocumentComponent::GraphDocumentComponent (AudioPluginFormatManager& fm, AudioDeviceManager& dm, KnownPluginList& kpl, TwonkPlayHead &_twonkPlayHead)
	: graph (new FilterGraph (fm, _twonkPlayHead)),
		deviceManager (dm),
		pluginList (kpl),
		formatManager(fm),
		twonkPlayHead(_twonkPlayHead)
{
	init();
	bg = ImageCache::getFromMemory(BinaryData::hexagon_png, BinaryData::hexagon_pngSize);

	deviceManager.addChangeListener (graphPanel.get());
	deviceManager.addAudioCallback (&graphPlayer);
	deviceManager.addMidiInputCallback (String(), &graphPlayer.getMidiMessageCollector());
}

void GraphDocumentComponent::init()
{
	graphPanel.reset (new GraphEditorPanel (*this));
	addAndMakeVisible (graphPanel.get());
	graphPlayer.setProcessor (&graph->graph);

	audioSettingsComponent.reset(new AudioDeviceSelectorComponent (deviceManager, 1, 8, 1, 8, true, true, true, false));

	graphPanel->updateComponents();

	if (isOnTouchDevice())
	{
		pluginListBoxModel.reset (new PluginListBoxModel (pluginListBox, pluginList));
		pluginListBox.setModel (pluginListBoxModel.get());
		pluginListBox.setRowHeight (28);

		pluginListSidePanel.setContent (&pluginListBox, false);

		auto deadMansPedalFile = getAppProperties().getUserSettings()
			->getFile().getSiblingFile ("RecentlyCrashedPluginsList");

		pluginListComponent.reset(new PluginListComponent (formatManager, pluginList, deadMansPedalFile, getAppProperties().getUserSettings(), true));

		settingsTab.reset(new TabbedComponent(TabbedButtonBar::TabsAtBottom));
		settingsTab->addTab("Audio Settings", Colours::black, audioSettingsComponent.get(), false);
		settingsTab->addTab("Plugins", Colours::black, pluginListComponent.get(), false);

		mobileSettingsSidePanel.setContent (settingsTab.get(), false);

		if (isOnTouchDevice())
		{
			addAndMakeVisible (pluginListSidePanel);
			addAndMakeVisible (mobileSettingsSidePanel);
		}
	}
}

GraphDocumentComponent::~GraphDocumentComponent()
{
	mobileSettingsSidePanel.setLookAndFeel(nullptr);
	pluginListSidePanel.setLookAndFeel(nullptr);
	//releaseGraph();
}

void GraphDocumentComponent::releaseGraph()
{
	deviceManager.removeAudioCallback (&graphPlayer);
	deviceManager.removeMidiInputCallback (String(), &graphPlayer.getMidiMessageCollector());

	if (graphPanel != nullptr)
	{
		deviceManager.removeChangeListener (graphPanel.get());
		graphPanel = nullptr;
	}

	graphPlayer.setProcessor (nullptr);
	graph = nullptr;
}

void GraphDocumentComponent::resized()
{
	auto r = getLocalBounds();
	graphPanel->setBounds (r);
}

void GraphDocumentComponent::createNewPlugin (const PluginDescription& desc, Point<int> pos)
{
	graphPanel->createNewPlugin (desc, pos);
}

bool GraphDocumentComponent::isInterestedInDragSource (const SourceDetails& details)
{
	return ((dynamic_cast<ListBox*> (details.sourceComponent.get()) != nullptr)
		&& details.description.toString().startsWith ("PLUGIN"));
}

void GraphDocumentComponent::itemDropped (const SourceDetails& details)
{
	auto pluginTypeIndex = details.description.toString()
		.fromFirstOccurrenceOf ("PLUGIN: ", false, false)
		.getIntValue();

	// must be a valid index!
	jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

	createNewPlugin (*pluginList.getType (pluginTypeIndex), details.localPosition);
}

bool GraphDocumentComponent::closeAnyOpenPluginWindows()
{
	return graphPanel->graph->closeAnyOpenPluginWindows();
}

void GraphDocumentComponent::paint (Graphics& g)
{
	g.drawImageWithin(bg, 0, 0, getWidth(), getHeight(), RectanglePlacement::fillDestination, false);
}
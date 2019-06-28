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

	deviceManager.addChangeListener (graphPanel.get());
	deviceManager.addAudioCallback (&graphPlayer);
	deviceManager.addMidiInputCallback (String(), &graphPlayer.getMidiMessageCollector());
}

void GraphDocumentComponent::init()
{
	graphPanel.reset (new GraphEditorPanel (*graph));
	addAndMakeVisible (graphPanel.get());
	graphPlayer.setProcessor (&graph->graph);

	audioSettingsComponent.reset(new AudioDeviceSelectorComponent (deviceManager, 1, 8, 1, 8, true, true, true, false));

	keyState.addListener (&graphPlayer.getMidiMessageCollector());
	keyboardComp.reset(new MidiKeyboardComponent(keyState, MidiKeyboardComponent::horizontalKeyboard));
	keyboardComp->setKeyWidth(40);
	addAndMakeVisible(keyboardComp.get());

	graphPanel->updateComponents();

	if (isOnTouchDevice())
	{
		if (isOnTouchDevice())
		{
			titleBarComponent.reset (new TwonkTitleBarComponent (*this));
			twonkPlayHead.addClockListener(titleBarComponent.get());
			addAndMakeVisible (titleBarComponent.get());
		}

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

	mobileSettingsSidePanel.setLookAndFeel(&sidePanelLF);
	pluginListSidePanel.setLookAndFeel(&sidePanelLF);
}

GraphDocumentComponent::~GraphDocumentComponent()
{
	mobileSettingsSidePanel.setLookAndFeel(nullptr);
	pluginListSidePanel.setLookAndFeel(nullptr);
	releaseGraph();

	keyState.removeListener (&graphPlayer.getMidiMessageCollector());
}

void GraphDocumentComponent::resized()
{
	auto r = getLocalBounds();
	const int titleBarHeight = TITLEBAR_HEIGHT;
	const int keysHeight = keyboardComp->isVisible() ? 100 : 0;

	if (isOnTouchDevice())
		titleBarComponent->setBounds (r.removeFromTop(titleBarHeight));

	graphPanel->setBounds (r);
	keyboardComp->setBounds (r.removeFromBottom (keysHeight));
	checkAvailableWidth();
}

void GraphDocumentComponent::createNewPlugin (const PluginDescription& desc, Point<int> pos)
{
	graphPanel->createNewPlugin (desc, pos);
}

void GraphDocumentComponent::unfocusKeyboardComponent()
{
	keyboardComp->unfocusAllComponents();
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
	keyboardComp = nullptr;
	settingsTab = nullptr;
	pluginListComponent = nullptr;
	audioSettingsComponent = nullptr;
	graphPlayer.setProcessor (nullptr);
	graph = nullptr;
}

bool GraphDocumentComponent::isInterestedInDragSource (const SourceDetails& details)
{
	return ((dynamic_cast<ListBox*> (details.sourceComponent.get()) != nullptr)
		&& details.description.toString().startsWith ("PLUGIN"));
}

void GraphDocumentComponent::itemDropped (const SourceDetails& details)
{
	// don't allow items to be dropped behind the sidebar
	if (pluginListSidePanel.getBounds().contains (details.localPosition))
		return;

	auto pluginTypeIndex = details.description.toString()
		.fromFirstOccurrenceOf ("PLUGIN: ", false, false)
		.getIntValue();

	// must be a valid index!
	jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

	createNewPlugin (*pluginList.getType (pluginTypeIndex), details.localPosition);
}

void GraphDocumentComponent::showSidePanel (bool showSettingsPanel)
{
	if (showSettingsPanel)
		mobileSettingsSidePanel.showOrHide (true);
	else
		pluginListSidePanel.showOrHide (true);

	checkAvailableWidth();

	lastOpenedSidePanel = showSettingsPanel ? &mobileSettingsSidePanel
		: &pluginListSidePanel;
}

void GraphDocumentComponent::hideLastSidePanel()
{
	if (lastOpenedSidePanel != nullptr)
		lastOpenedSidePanel->showOrHide (false);

	if (mobileSettingsSidePanel.isPanelShowing())    lastOpenedSidePanel = &mobileSettingsSidePanel;
	else if (pluginListSidePanel.isPanelShowing())        lastOpenedSidePanel = &pluginListSidePanel;
	else                                                  lastOpenedSidePanel = nullptr;
}

void GraphDocumentComponent::checkAvailableWidth()
{
	if (mobileSettingsSidePanel.isPanelShowing() && pluginListSidePanel.isPanelShowing())
	{
		if (getWidth() - (mobileSettingsSidePanel.getWidth() + pluginListSidePanel.getWidth()) < 150)
			hideLastSidePanel();
	}
}

bool GraphDocumentComponent::closeAnyOpenPluginWindows()
{
	return graphPanel->graph.closeAnyOpenPluginWindows();
}

void GraphDocumentComponent::showMidiKeyboardComponent()
{
	keyboardComp.get()->setVisible(!keyboardComp.get()->isVisible());
}

void GraphDocumentComponent::stop()
{
	twonkPlayHead.stop();
}
void GraphDocumentComponent::play(const bool isPlaying)
{
	twonkPlayHead.play(isPlaying);
}
void GraphDocumentComponent::toggleSync(const bool shouldBeSynced)
{
	twonkPlayHead.setExternalSync(shouldBeSynced);
}

void GraphDocumentComponent::setTempo(const double bpm)
{
	twonkPlayHead.setTempo(bpm);
}

void GraphDocumentComponent::setLoopLength(const int _loopLength)
{
	twonkPlayHead.setLoopLength(_loopLength);
}
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

//==============================================================================
class GraphDocumentComponent::TitleBarComponent : public Component,
	private Button::Listener
{
public:
	TitleBarComponent (GraphDocumentComponent& graphDocumentComponent)
		: owner (graphDocumentComponent)
	{
		static const unsigned char pluginListPathData[]
			= { 110,109,193,202,222,64,80,50,21,64,108,0,0,48,65,0,0,0,0,108,160,154,112,65,80,50,21,64,108,0,0,48,65,80,
				50,149,64,108,193,202,222,64,80,50,21,64,99,109,0,0,192,64,251,220,127,64,108,160,154,32,65,165,135,202,
				64,108,160,154,32,65,250,220,47,65,108,0,0,192,64,102,144,10,65,108,0,0,192,64,251,220,127,64,99,109,0,0,
				128,65,251,220,127,64,108,0,0,128,65,103,144,10,65,108,96,101,63,65,251,220,47,65,108,96,101,63,65,166,135,
				202,64,108,0,0,128,65,251,220,127,64,99,109,96,101,79,65,148,76,69,65,108,0,0,136,65,0,0,32,65,108,80,
				77,168,65,148,76,69,65,108,0,0,136,65,40,153,106,65,108,96,101,79,65,148,76,69,65,99,109,0,0,64,65,63,247,
				95,65,108,80,77,128,65,233,161,130,65,108,80,77,128,65,125,238,167,65,108,0,0,64,65,51,72,149,65,108,0,0,64,
				65,63,247,95,65,99,109,0,0,176,65,63,247,95,65,108,0,0,176,65,51,72,149,65,108,176,178,143,65,125,238,167,65,
				108,176,178,143,65,233,161,130,65,108,0,0,176,65,63,247,95,65,99,109,12,86,118,63,148,76,69,65,108,0,0,160,
				64,0,0,32,65,108,159,154,16,65,148,76,69,65,108,0,0,160,64,40,153,106,65,108,12,86,118,63,148,76,69,65,99,
				109,0,0,0,0,63,247,95,65,108,62,53,129,64,233,161,130,65,108,62,53,129,64,125,238,167,65,108,0,0,0,0,51,
				72,149,65,108,0,0,0,0,63,247,95,65,99,109,0,0,32,65,63,247,95,65,108,0,0,32,65,51,72,149,65,108,193,202,190,
				64,125,238,167,65,108,193,202,190,64,233,161,130,65,108,0,0,32,65,63,247,95,65,99,101,0,0 };

		{
			settingsIcon.reset(Drawable::createFromImageData(BinaryData::Settings_svg, BinaryData::Settings_svgSize));
			settingsButton.setImages(settingsIcon.get());
		}

		{
			Path p;
			p.loadPathFromData (pluginListPathData, sizeof (pluginListPathData));
			pluginButton.setShape (p, true, true, false);
		}
		{
			midiKeyboardIcon.reset(Drawable::createFromImageData(BinaryData::PianoKeyboard_svg, BinaryData::PianoKeyboard_svgSize));
			midiKeysButton.setImages(midiKeyboardIcon.get());
		}

		pluginButton.addListener (this);
		addAndMakeVisible (pluginButton);

		midiKeysButton.addListener(this);
		addAndMakeVisible (midiKeysButton);

		settingsButton.addListener(this);
		addAndMakeVisible (settingsButton);

		setOpaque (true);
	}

private:
	void paint (Graphics& g) override
	{
		auto titleBarBackgroundColour = getLookAndFeel().findColour (ResizableWindow::backgroundColourId).darker();

		g.setColour (titleBarBackgroundColour);
		g.fillRect (getLocalBounds());
	}

	void resized() override
	{
		auto r = getLocalBounds();

		settingsButton.setBounds (r.removeFromLeft (40).withSizeKeepingCentre (32, 32));
		pluginButton.setBounds (r.removeFromRight (40).withSizeKeepingCentre (32, 32));
		midiKeysButton.setBounds(r.removeFromRight(72).withSizeKeepingCentre(32, 32));
	}

	void buttonClicked (Button* b) override
	{
		if (b == &settingsButton)
		{
			owner.showSidePanel(true);
		}

		if (b == &pluginButton)
		{
			owner.showSidePanel(false);
		}

		if (b == &midiKeysButton)
		{
			owner.showMidiKeyboardComponent();
		}
	}

	GraphDocumentComponent& owner;
	std::unique_ptr<Drawable> midiKeyboardIcon;
	std::unique_ptr<Drawable> settingsIcon;
	ShapeButton pluginButton{ "pluginButton", Colours::lightgrey, Colours::lightgrey, Colours::white };
	DrawableButton midiKeysButton{ "midiKeysButton", DrawableButton::ImageFitted };
	DrawableButton settingsButton{ "settingsButton", DrawableButton::ImageFitted };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBarComponent)
};

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
GraphDocumentComponent::GraphDocumentComponent (AudioPluginFormatManager& fm,
	AudioDeviceManager& dm,
	KnownPluginList& kpl)
	: graph (new FilterGraph (fm)),
	deviceManager (dm),
	pluginList (kpl),
	formatManager(fm)
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

	audioSettingsComponent.reset(new AudioDeviceSelectorComponent (deviceManager, 0, 2, 0, 2, true, true, true, false));

	keyState.addListener (&graphPlayer.getMidiMessageCollector());
	keyboardComp.reset(new MidiKeyboardComponent(keyState, MidiKeyboardComponent::horizontalKeyboard));
	keyboardComp->setKeyWidth(40);
	addAndMakeVisible(keyboardComp.get());

	graphPanel->updateComponents();

	if (isOnTouchDevice())
	{
		if (isOnTouchDevice())
		{
			titleBarComponent.reset (new TitleBarComponent (*this));
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
	const int titleBarHeight = 32;
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
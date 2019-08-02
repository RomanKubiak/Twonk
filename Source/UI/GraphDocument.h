/*
  ==============================================================================

    GraphDocument.h
    Created: 5 Jun 2019 5:47:06pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "Twonk.h"
#include "../Filters/FilterGraph.h"
#include "../UI/GraphEditorPanel.h"


class TwonkPlayHead;
class TwonkTitleBarComponent;

class SidePanelLookAndFeel : public LookAndFeel_V4
{
	public:
		SidePanelLookAndFeel()
		{
			font = getDefaultTwonkSansFont();
		}
		Font getSidePanelTitleFont(SidePanel &)
		{
			return (font);
		}
	private:
		Font font;
};

//==============================================================================
/**
	A panel that embeds a GraphEditorPanel with a midi keyboard at the bottom.

	It also manages the graph itself, and plays it.
*/
class GraphDocumentComponent : public Component,
	public DragAndDropTarget,
	public DragAndDropContainer
{
public:
	GraphDocumentComponent (AudioPluginFormatManager& formatManager,
		AudioDeviceManager& deviceManager,
		KnownPluginList& pluginList,
		TwonkPlayHead &_twonkPlayHead);

	~GraphDocumentComponent() override;

	//==============================================================================
	void createNewPlugin (const PluginDescription&, Point<int> position);
	bool closeAnyOpenPluginWindows();

	//==============================================================================
	std::unique_ptr<FilterGraph> graph;

	void resized() override;
	void unfocusKeyboardComponent();
	void releaseGraph();
	void paint (Graphics& g);
	//==============================================================================
	bool isInterestedInDragSource (const SourceDetails&) override;
	void itemDropped (const SourceDetails&) override;

	//==============================================================================
	std::unique_ptr<GraphEditorPanel> graphPanel;
	std::unique_ptr<MidiKeyboardComponent> keyboardComp;
	MidiKeyboardState keyState;
	void showMidiKeyboardComponent();
	void stop();
	void play(const bool isPlaying);
	void toggleSync(const bool shouldBeSynced);
	void setTempo(const double bpm);
	void setLoopLength(const int _loopLength);
	//==============================================================================
	void showSidePanel (bool isSettingsPanel);
	void hideLastSidePanel();
	BurgerMenuComponent burgerMenu;

private:
	//==============================================================================
	AudioDeviceManager& deviceManager;
	KnownPluginList& pluginList;
	TwonkPlayHead &twonkPlayHead;
	AudioProcessorPlayer graphPlayer;
	std::unique_ptr<PluginListComponent> pluginListComponent;
	//==============================================================================
	struct PluginListBoxModel;
	AudioPluginFormatManager &formatManager;
	std::unique_ptr<PluginListBoxModel> pluginListBoxModel;
	std::unique_ptr<AudioDeviceSelectorComponent> audioSettingsComponent;
	ListBox pluginListBox;
	Image bg;
	SidePanel mobileSettingsSidePanel{ "Settings", 300, true };
	SidePanel pluginListSidePanel{ "Plugins", 300, false };
	std::unique_ptr<TabbedComponent> settingsTab;
	SidePanel* lastOpenedSidePanel = nullptr;
	SidePanelLookAndFeel sidePanelLF;
	//==============================================================================
	void init();
	void checkAvailableWidth();

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphDocumentComponent)
};
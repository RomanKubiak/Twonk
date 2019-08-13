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

class GraphEditorPanel;
class TwonkPlayHead;
class TwonkTitleBarComponent;

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
	void releaseGraph();
	void paint (Graphics& g);
	//==============================================================================
	bool isInterestedInDragSource (const SourceDetails&) override;
	void itemDropped (const SourceDetails&) override;

	//==============================================================================
	std::unique_ptr<GraphEditorPanel> graphPanel;
	AudioProcessorPlayer &getGraphPlayer() { return (graphPlayer); }
	//==============================================================================
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
	//==============================================================================
	void init();

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphDocumentComponent)
};
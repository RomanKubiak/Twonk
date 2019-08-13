#pragma once

#include "../Filters/FilterGraph.h"
#include "TwonkTitleBarComponent.h"
#include "TwonkMidiKeyboard.h"

class MainHostWindow;
class TwonkFilterComponent;
class TwonkFilterConnector;
class TwonkFilterComponentPinWrapper;
class FilterGraph;

class GraphEditorPanel   : public Component,
                           public ChangeListener,
                           private Timer,
							public DragAndDropTarget,
							public DragAndDropContainer
{
public:
    GraphEditorPanel (AudioPluginFormatManager& formatManager,
		AudioDeviceManager& deviceManager,
		KnownPluginList& pluginList,
		TwonkPlayHead &_twonkPlayHead);
    ~GraphEditorPanel() override;

    void createNewPlugin (const PluginDescription&, Point<int> position);

    void paint (Graphics&) override;
    void resized() override;

    void mouseDown (const MouseEvent&) override;
    void mouseUp   (const MouseEvent&) override;
    void mouseDrag (const MouseEvent&) override;
	void mouseDoubleClick(const MouseEvent &) override;
    void changeListenerCallback (ChangeBroadcaster*) override;
    void updateComponents();
    void showPopupMenu (Point<int> position);
    void beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                             AudioProcessorGraph::NodeAndChannel dest,
                             const MouseEvent&);
    void dragConnector (const MouseEvent&);
    void endDraggingConnector (const MouseEvent&);
	void timerCallback() override;
	bool closeAnyOpenPluginWindows();
	TwonkFilterComponent* getComponentForFilter (AudioProcessorGraph::NodeID) const;
	TwonkFilterConnector* getComponentForConnection (const AudioProcessorGraph::Connection&) const;
	TwonkFilterComponentPinWrapper* findPinAt (Point<float>) const;
	bool isInterestedInDragSource (const SourceDetails&) override;
	void itemDropped (const SourceDetails&) override;
	void releaseGraph();
	std::unique_ptr<FilterGraph> graph;

private:
	std::unique_ptr<TwonkMidiKeyboard> twonkMidiKeyboard;
	MidiKeyboardState keyState;
    OwnedArray<TwonkFilterComponent> nodes;
    OwnedArray<TwonkFilterConnector> connectors;
	std::unique_ptr <TwonkFilterConnector> draggingConnector;
    std::unique_ptr<PopupMenu> menu;
	std::unique_ptr<TwonkTitleBarComponent> toolBar;
	AudioProcessorPlayer graphPlayer;
	AudioDeviceManager &deviceManager;
	KnownPluginList &pluginList;
	TwonkPlayHead &twonkPlayHead;
	AudioPluginFormatManager &formatManager;
	struct PluginListBoxModel;
	std::unique_ptr<PluginListBoxModel> pluginListBoxModel;
	std::unique_ptr<PluginListComponent> pluginListComponent;
	ListBox pluginListBox;
	std::unique_ptr<AudioDeviceSelectorComponent> audioSettingsComponent;
	Image bgImage;
    Point<int> originalTouchPos;
	void init();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphEditorPanel)
};
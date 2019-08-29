#pragma once

#include "../Filters/PluginGraph.h"
#include "TwonkProgramList.h"
class MainHostWindow;
class TwonkToolBar;
class TwonkToolBarButton;
class TwonkToolBarController;
class TwonkFileMenu;

/**
    A panel that displays and edits a PluginGraph.
*/
class GraphEditorPanel   : public Component,
                           public ChangeListener,
                           private Timer,
						   public FileBrowserListener
{
public:
    GraphEditorPanel (PluginGraph& graph, AudioDeviceManager &_dm);
    ~GraphEditorPanel() override;

    void createNewPlugin (const PluginDescription&, Point<int> position);

    void paint (Graphics&) override;
    void resized() override;

    void mouseDown (const MouseEvent&) override;
    void mouseUp   (const MouseEvent&) override;
    void mouseDrag (const MouseEvent&) override;

    void changeListenerCallback (ChangeBroadcaster*) override;

    //==============================================================================
    void updateComponents();

    //==============================================================================
    void showPopupMenu (Point<int> position);
	Path getHexagonPath(Rectangle<int> area);
    //==============================================================================
    void beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                             AudioProcessorGraph::NodeAndChannel dest,
                             const MouseEvent&);
    void dragConnector (const MouseEvent&);
    void endDraggingConnector (const MouseEvent&);
	void toggleProgramMenu();
	void selectionChanged();
	void fileClicked(const File &file, const MouseEvent &e);
	void fileDoubleClicked(const File &file);
	void browserRootChanged(const File &newRoot) {}
	void updateTwonkDocuments() { directoryContentsList.refresh(); }
	AudioDeviceManager &getAudioDeviceManager() { return (dm); }
    //==============================================================================
    PluginGraph& graph;
	enum FilterType
	{
		InternalAudioInput,
		InternalAudioOutput,
		InternalMidiInput,
		InternalMidiOutpout,
		InternalEffect,
		InternalSynth,
		PluginAudioEffect,
		PluginMidiEffect,
		PluginSynth,
		PluginSynthWithInput,
		FuckIfIKnow
	};
	
private:
    struct PluginComponent;
    struct ConnectorComponent;
    struct PinComponent;

    OwnedArray<PluginComponent> nodes;
    OwnedArray<ConnectorComponent> connectors;
    std::unique_ptr<ConnectorComponent> draggingConnector;
    std::unique_ptr<PopupMenu> menu;
	std::unique_ptr<TwonkToolBar> toolBar;
    PluginComponent* getComponentForPlugin (AudioProcessorGraph::NodeID) const;
    ConnectorComponent* getComponentForConnection (const AudioProcessorGraph::Connection&) const;
    PinComponent* findPinAt (Point<float>) const;
	Image bgImage;
	ComponentAnimator toolBarAnimator;
	WildcardFileFilter twonkDocumentFileFilter;
	TimeSliceThread directoryListThread;
	DirectoryContentsList directoryContentsList;
	TwonkProgramListWrapper twonkProgramListWrapper;
	AudioDeviceManager &dm;
    //==============================================================================
    Point<int> originalTouchPos;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphEditorPanel)
};


/**
    A panel that embeds a GraphEditorPanel with a midi keyboard at the bottom.

    It also manages the graph itself, and plays it.
*/
class GraphDocumentComponent  : public Component,
                                public DragAndDropTarget,
                                public DragAndDropContainer
{
public:
    GraphDocumentComponent (AudioPluginFormatManager& formatManager,
                            AudioDeviceManager& deviceManager,
                            KnownPluginList& pluginList);

    ~GraphDocumentComponent() override;
    void createNewPlugin (const PluginDescription&, Point<int> position);
    void setDoublePrecision (bool doublePrecision);
    bool closeAnyOpenPluginWindows();
    std::unique_ptr<PluginGraph> graph;
    void resized() override;
    void releaseGraph();
    bool isInterestedInDragSource (const SourceDetails&) override;
    void itemDropped (const SourceDetails&) override;
    std::unique_ptr<GraphEditorPanel> graphPanel;

private:
    AudioDeviceManager& deviceManager;
    KnownPluginList& pluginList;
    AudioProcessorPlayer graphPlayer;
    void init();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphDocumentComponent)
};

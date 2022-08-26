#pragma once

#include "PluginGraph.h"
#include "TwonkToolBar.h"
#include "TwonkTransport.h"
#include "TwonkProgramList.h"

class TwonkFilterPopupProperties;

class Editor : public Component, public ChangeListener, private Timer, public FileBrowserListener {
public:
    Editor(PluginGraph &graph, AudioDeviceManager &_dm, TwonkPlayHead &_twonkPlayHead);

    ~Editor() override;

    struct Processor;
    struct Connector;
    struct Pin;

    void createNewPlugin(const PluginDescription &, Point<int> position);

    void paint(Graphics &) override;

    void resized() override;

    void mouseDown(const MouseEvent &) override;

    void mouseUp(const MouseEvent &) override;

    void mouseDrag(const MouseEvent &) override;

    void changeListenerCallback(ChangeBroadcaster *) override;

    void updateComponents();

    void showPopupMenu(Point<int> position);

    void beginConnectorDrag(AudioProcessorGraph::NodeAndChannel source,
                            AudioProcessorGraph::NodeAndChannel dest,
                            const MouseEvent &);

    void dragConnector(const MouseEvent &);

    void endDraggingConnector(const MouseEvent &);

    void toggleProgramMenu();

    void selectionChanged();

    void fileClicked(const File &file, const MouseEvent &e);

    void fileDoubleClicked(const File &file);

    void showMenuForFilter(struct Editor::Processor *filter);

    void filterMoved(struct Editor::Processor *filter);

    void menuForFilterClicked(const int r);

    void browserRootChanged(const File &newRoot) {}

    void updateTwonkDocuments() { directoryContentsList.refresh(); }

    AudioDeviceManager &getAudioDeviceManager() { return (dm); }

    PluginGraph &graph;
    enum FilterType {
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
    Processor *getComponentForPlugin(AudioProcessorGraph::NodeID) const;
    Connector *getComponentForConnection(const AudioProcessorGraph::Connection &) const;
    Pin *findPinAt(Point<float>) const;
private:
    OwnedArray<Editor::Processor> nodes;
    OwnedArray<Editor::Connector> connectors;
    std::unique_ptr<Editor::Connector> draggingConnector;
    std::unique_ptr<PopupMenu> menu;
    std::unique_ptr<TwonkToolBar> toolBar;
    std::unique_ptr<TwonkTransport> twonkTransport;
    std::unique_ptr<TwonkFilterPopupProperties> filterPropertiesPopup;
    std::unique_ptr<BubbleMessageComponent> pinConnectionHint;

    Image bgImage;
    TwonkPlayHead &twonkPlayHead;
    ComponentAnimator toolBarAnimator;
    WildcardFileFilter twonkDocumentFileFilter;
    TimeSliceThread directoryListThread;
    DirectoryContentsList directoryContentsList;
    TwonkProgramListWrapper twonkProgramListWrapper;
    AudioDeviceManager &dm;
    Point<int> originalTouchPos;

    void timerCallback() override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Editor)
};

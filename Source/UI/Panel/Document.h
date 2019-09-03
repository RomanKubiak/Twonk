#pragma once

#include "Twonk.h"
#include "Filters/PluginGraph.h"
#include "TwonkProgramList.h"
#include "TwonkPlayHead.h"
class Editor;

class Document  : public Component,
                                public DragAndDropTarget,
                                public DragAndDropContainer
{
public:
    Document (AudioPluginFormatManager& formatManager,
                            AudioDeviceManager& deviceManager,
                            KnownPluginList& pluginList);

    ~Document() override;
    void createNewPlugin (const PluginDescription&, Point<int> position);
    void setDoublePrecision (bool doublePrecision);
    bool closeAnyOpenPluginWindows();
    std::unique_ptr<PluginGraph> graph;
    void resized() override;
    void releaseGraph();
    bool isInterestedInDragSource (const SourceDetails&) override;
    void itemDropped (const SourceDetails&) override;
    AudioDeviceManager& getDeviceManager() { return (deviceManager); }
    std::unique_ptr<Editor> graphPanel;

private:
    AudioDeviceManager& deviceManager;
    KnownPluginList& pluginList;
    AudioProcessorPlayer graphPlayer;
    TwonkPlayHead twonkPlayHead;
    void init();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Document)
};

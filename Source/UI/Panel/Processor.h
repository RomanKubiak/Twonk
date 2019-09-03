#pragma once

#include "JuceHeader.h"
#include "Twonk.h"
#include "PluginGraph.h"
#include "Editor.h"

class Pin;

struct Editor::Processor : public Component, public Timer, private AudioProcessorParameter::Listener
{
    Processor (Editor& p, AudioProcessorGraph::NodeID id);
    ~Processor() override;

    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    Path getHexagonPath(Rectangle<int> area);
    bool hitTest (int x, int y) override;
    FilterType getFilterType(AudioProcessorGraph::Node *node);
    Colour getColourForFilterType(FilterType type);
    Image getImageForFilter(FilterType type);
    void paint (Graphics& g) override;
    void resized() override;
    Point<float> getPinPos (int index, bool isInput) const;
    void update();
    AudioProcessor* getProcessor() const;
    void showPopupMenu();
    void testStateSaveLoad();
    void showWindow (PluginWindow::Type type);
    void timerCallback() override;
    void parameterValueChanged (int, float) override;
    void parameterGestureChanged(int, bool) override;
    void moved() override;
    void mouseEnter(const MouseEvent &e) override;
    void mouseExit(const MouseEvent &e) override;

    Editor& panel;
    PluginGraph& graph;
    const AudioProcessorGraph::NodeID pluginID;
    OwnedArray<Pin> pins;
    int numInputs = 0, numOutputs = 0;
    int pinSize = 16;
    Point<int> originalPos;
    Font font { 13.0f, Font::bold };
    int numIns = 0, numOuts = 0;
    std::unique_ptr<PopupMenu> menu;
};
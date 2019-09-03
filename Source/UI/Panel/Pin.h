#pragma once
#include "JuceHeader.h"
#include "Twonk.h"
#include "PluginGraph.h"
#include "Editor.h"

struct Editor::Pin   : public Component, public SettableTooltipClient
{
    Pin (Editor& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn);
    void paint (Graphics& g) override;
    void setText(const String &_text);
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;

    Editor& panel;
    PluginGraph& graph;
    AudioProcessorGraph::NodeAndChannel pin;
    const bool isInput;
    int busIdx = 0;
    Colour baseColour;
    Image pinImage;
    String text;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pin)
};
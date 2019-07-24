/*
  ==============================================================================

    FilterNodeBubble.h
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include "../Filters/FilterGraph.h"
#include "GraphEditorPanel.h"

class TwonkFilterComponentPin : public Component, public SettableTooltipClient
{
	public:
		TwonkFilterComponentPin (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn);
		// void paint (Graphics& g) override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		void paint(Graphics &g);
		GraphEditorPanel& panel;
		FilterGraph& graph;
		AudioProcessorGraph::NodeAndChannel pin;
		const bool isInput;
		int busIdx = 0;
		Colour currentColour;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterComponentPin)
};
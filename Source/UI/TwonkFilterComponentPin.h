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
#include "TwonkBubbleNodeComponent.h"

class TwonkFilterComponentPin : public TwonkBubbleNodeComponent, public SettableTooltipClient
{
	public:
		TwonkFilterComponentPin (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn);
		// void paint (Graphics& g) override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		GraphEditorPanel& panel;
		FilterGraph& graph;
		AudioProcessorGraph::NodeAndChannel pin;
		const bool isInput;
		int busIdx = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterComponentPin)
};
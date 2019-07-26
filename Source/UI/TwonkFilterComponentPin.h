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

class TwonkFilterComponentPin : public Component
{

};

class TwonkFilterComponentPinWrapper : public Component, public SettableTooltipClient
{
	public:
		//TwonkFilterComponentPinWrapper (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn);
		TwonkFilterComponentPinWrapper(GraphEditorPanel& _panel, AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType _pinType);
		void paint (Graphics& g) override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		void mouseEnter(const MouseEvent &e) override;
		GraphEditorPanel& panel;
		FilterGraph& graph;
		AudioProcessorGraph::NodeAndChannel pin;
		bool isInput;
		int busIdx = 0;
		Colour currentColour;
	private:
		Array <TwonkFilterComponentPin> childPins;
		AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType pinType;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterComponentPinWrapper)
};
/*
  ==============================================================================

    FilterNodeBubble.h
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include "GraphEditorPanel.h"

class TwonkFilterComponent;
class TwonkFilterComponentPin : public Component
{

};

class TwonkFilterComponentPinWrapper : public Component, public SettableTooltipClient
{
	public:
		//TwonkFilterComponentPinWrapper (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn);
		TwonkFilterComponentPinWrapper(TwonkFilterComponent &_owner, GraphEditorPanel &_panel, AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType _pinType);
		void paint (Graphics& g) override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		void mouseEnter(const MouseEvent &e) override;
		AudioProcessorGraph::NodeAndChannel getPin() { return (pin); }
		bool isInput() { return (false); }

	private:
		Colour currentColour;
		GraphEditorPanel& panel;
		AudioProcessorGraph::NodeAndChannel pin;
		TwonkFilterComponent &owner;
		Array <TwonkFilterComponentPin> childPins;
		AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType pinType;
		Path shapePath;
		Image pinImage;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterComponentPinWrapper)
};
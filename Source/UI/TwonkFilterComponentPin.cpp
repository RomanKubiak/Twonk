/*
  ==============================================================================

    FilterNodeBubble.cpp
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#include "TwonkFilterComponentPin.h"
#include "Twonk.h"
TwonkFilterComponentPinWrapper::TwonkFilterComponentPinWrapper(GraphEditorPanel& _panel, AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType _pinType)
	: panel(_panel), graph(panel.graph), pinType(_pinType)
{
	switch (pinType)
	{
		case AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode:
		case AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode:
			currentColour = Colour(NODE_COLOUR_AUDIO);
			break;
		case AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode:
		case AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode:
			currentColour = Colour(NODE_COLOUR_MIDI);
			break;
		default:
			break;
	}
	setComponentEffect(nullptr);
	setSize (NODE_SIZE, NODE_SIZE);
}

/*
TwonkFilterComponentPinWrapper::TwonkFilterComponentPinWrapper (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn)
	: panel (p), graph (p.graph), pin (pinToUse), isInput (isIn)
{
	pin.isMIDI() ? currentColour = Colours::red : currentColour = Colours::green;

	if (auto node = graph.graph.getNodeForId (pin.nodeID))
	{
		String tip;

		if (pin.isMIDI())
		{
			
			tip = isInput ? ("MIDI Input") : "MIDI Output";
		}
		else
		{
			auto& processor = *node->getProcessor();
			auto channel = processor.getOffsetInBusBufferForAbsoluteChannelIndex (isInput, pin.channelIndex, busIdx);

			if (auto* bus = processor.getBus (isInput, busIdx))
				tip = bus->getName() + ": " + AudioChannelSet::getAbbreviatedChannelTypeName (bus->getCurrentLayout().getTypeOfChannel (channel));
			else
				tip = (isInput ? "Main Input: " : "Main Output: ") + String (pin.channelIndex + 1);

		}

		setTooltip (tip);
	}
	setComponentEffect(nullptr);
	setSize (24, 24);
}
*/
void TwonkFilterComponentPinWrapper::paint (Graphics& g)
{
	Path hexagon;
	hexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.45f, float_Pi*0.5f);
	g.setColour(currentColour.withAlpha(0.8f));
	g.fillPath(hexagon);
	g.setColour(currentColour);
	g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.1f));
}

void TwonkFilterComponentPinWrapper::mouseDown (const MouseEvent& e)
{
	AudioProcessorGraph::NodeAndChannel dummy {{}, 0};
	panel.beginConnectorDrag (isInput ? dummy : pin, isInput ? pin : dummy, e);
}

void TwonkFilterComponentPinWrapper::mouseDrag (const MouseEvent& e)
{
	panel.dragConnector (e);
}

void TwonkFilterComponentPinWrapper::mouseEnter(const MouseEvent &e)
{
}

void TwonkFilterComponentPinWrapper::mouseUp (const MouseEvent& e)
{
	panel.endDraggingConnector (e);
}
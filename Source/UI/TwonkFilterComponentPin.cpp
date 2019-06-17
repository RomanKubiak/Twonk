/*
  ==============================================================================

    FilterNodeBubble.cpp
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#include "TwonkFilterComponentPin.h"

//==============================================================================
TwonkFilterComponentPin::TwonkFilterComponentPin (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn)
	: panel (p), graph (p.graph), pin (pinToUse), isInput (isIn)
{
	if (isInput)
	{
		
		stroke = Colours::blue;
	}
	else
	{
		fillColour = Colours::yellow;
		stroke = Colours::yellow;
	}

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

	setSize (32, 32);
}

/*void TwonkFilterComponentPin::paint (Graphics& g)
{
	auto w = (float)getWidth();
	auto h = (float)getHeight();

	Path p;
	p.addEllipse (w * 0.25f, h * 0.25f, w * 0.5f, h * 0.5f);
	p.addRectangle (w * 0.4f, isInput ? (0.5f * h) : 0.0f, w * 0.2f, h * 0.5f);

	auto colour = (pin.isMIDI() ? Colours::red : Colours::green);

	g.setColour (colour.withRotatedHue (busIdx / 5.0f));
	g.fillPath (p);
}*/

void TwonkFilterComponentPin::mouseDown (const MouseEvent& e)
{
	AudioProcessorGraph::NodeAndChannel dummy {{}, 0};
	panel.beginConnectorDrag (isInput ? dummy : pin, isInput ? pin : dummy, e);
}

void TwonkFilterComponentPin::mouseDrag (const MouseEvent& e)
{
	panel.dragConnector (e);
}

void TwonkFilterComponentPin::mouseUp (const MouseEvent& e)
{
	panel.endDraggingConnector (e);
}
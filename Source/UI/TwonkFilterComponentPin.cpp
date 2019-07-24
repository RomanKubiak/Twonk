/*
  ==============================================================================

    FilterNodeBubble.cpp
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#include "TwonkFilterComponentPin.h"
#include "Twonk.h"
//==============================================================================
TwonkFilterComponentPin::TwonkFilterComponentPin (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn)
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

void TwonkFilterComponentPin::paint (Graphics& g)
{
	Path hexagon;
	hexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.45f, float_Pi*0.5f);
	g.setColour(currentColour.withAlpha(0.06f));
	g.fillPath(hexagon);
	g.setColour(currentColour);
	g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.2f));
}

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
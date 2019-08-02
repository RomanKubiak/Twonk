/*
  ==============================================================================

    FilterNodeBubble.cpp
    Created: 12 Jun 2019 10:14:04pm
    Author:  atom

  ==============================================================================
*/

#include "TwonkFilterComponentPin.h"
#include "TwonkFilterComponent.h"
#include "Twonk.h"
TwonkFilterComponentPinWrapper::TwonkFilterComponentPinWrapper(TwonkFilterComponent &_owner, GraphEditorPanel &_panel, AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType _pinType)
	: pinType(_pinType), owner(_owner), panel(_panel)
{
	switch (pinType)
	{
		case AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode:
			currentColour = Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_IN);
			pinImage = ImageCache::getFromMemory(BinaryData::icon_input_32_png, BinaryData::icon_input_32_pngSize);
			break;

		case AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode:
			pinImage = ImageCache::getFromMemory(BinaryData::icon_output_32_png, BinaryData::icon_output_32_pngSize);
			currentColour = Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_OUT);
			break;

		case AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode:
			pinImage = ImageCache::getFromMemory(BinaryData::icon_input_32_png, BinaryData::icon_input_32_pngSize);
			currentColour = Colour(BUBBLE_COLOUR_INTERNAL_MIDI_IN);
			break;

		case AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode:
			pinImage = ImageCache::getFromMemory(BinaryData::icon_output_32_png, BinaryData::icon_output_32_pngSize);
			currentColour = Colour(BUBBLE_COLOUR_INTERNAL_MIDI_OUT);
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
	g.setColour(currentColour.contrasting(0.1f));
	g.drawImage(pinImage, getLocalBounds().toFloat().reduced(NODE_SIZE * 0.15f), RectanglePlacement::stretchToFit, true);
	g.setColour(currentColour.withAlpha(0.3f));
	g.fillPath(hexagon);
	g.setColour(currentColour);
	g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.1f));
}

void TwonkFilterComponentPinWrapper::mouseDown (const MouseEvent& e)
{
}

void TwonkFilterComponentPinWrapper::mouseDrag (const MouseEvent& e)
{
	owner.getPanel().dragConnector (e);
}

void TwonkFilterComponentPinWrapper::mouseEnter(const MouseEvent &e)
{
}

void TwonkFilterComponentPinWrapper::mouseUp (const MouseEvent& e)
{
	owner.getPanel().endDraggingConnector (e);
}
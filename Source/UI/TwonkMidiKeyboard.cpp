#include "TwonkMidiKeyboard.h"
#include "TwonkToolBarButton.h"
#include "Twonk.h"
#define DRAGGING_HEX_SIZE 32
TwonkMidiKeyboard::TwonkMidiKeyboard(MidiKeyboardState &state, MidiKeyboardComponent::Orientation orientation)
{
	corner.reset(new ResizableCornerComponent(this, nullptr));
	addAndMakeVisible(corner.get());
	midiKeyboardComponent.reset(new MidiKeyboardComponent(state, orientation));
	addAndMakeVisible(midiKeyboardComponent.get());

	keyHeight.reset(new Slider());
	keyHeight->setColour(Slider::trackColourId, Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_IN));
	keyHeight->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	keyHeight->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	keyHeight->setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
	keyHeight->setRange(0.0, 1.0, 0.1);
	keyHeight->addListener(this);
	keyHeight->setValue(0.5, sendNotification);

	keyWidth.reset(new Slider());
	keyWidth->setColour(Slider::trackColourId, Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_IN));
	keyWidth->setSliderStyle(Slider::SliderStyle::LinearBar);
	keyWidth->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	keyWidth->setRange(16,64);
	keyWidth->addListener(this);
	keyWidth->setValue(20, sendNotification);
	keyWidth->setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
	addAndMakeVisible(keyWidth.get());
	addAndMakeVisible(keyHeight.get());
}

TwonkMidiKeyboard::~TwonkMidiKeyboard()
{
}

void TwonkMidiKeyboard::paint (Graphics& g)
{
	g.setColour(Colours::lightgrey.withAlpha(0.5f));
	g.fillRect(Rectangle<float>(0, 0, getWidth() - 24, 22));
}

void TwonkMidiKeyboard::resized()
{
	corner->setBounds(getWidth() - 24, getHeight() - 24, 24, 24);
	midiKeyboardComponent->setBounds(0, 24, getWidth() - 24, getHeight() - 48);
	keyHeight->setBounds(getWidth() - 24, 0, 24, getHeight()-24);
	keyWidth->setBounds(0, getHeight()-24, getWidth() - 24, 24);
}

void TwonkMidiKeyboard::mouseDown(const MouseEvent &e)
{
	dragger.startDraggingComponent (this, e);
}

void TwonkMidiKeyboard::mouseDrag(const MouseEvent &e)
{
	dragger.dragComponent (this, e, nullptr);
}

void TwonkMidiKeyboard::sliderValueChanged(Slider *slider)
{
	if (slider == keyWidth.get())
	{
		midiKeyboardComponent->setKeyWidth(keyWidth->getValue());
	}

	if (slider == keyHeight.get())
	{
		midiKeyboardComponent->setBlackNoteLengthProportion(keyHeight->getValue());
	}
}
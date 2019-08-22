#include "TwonkMidiKeyboard.h"
#include "TwonkToolBarButton.h"
#include "Twonk.h"
#define DRAGGING_HEX_SIZE 32

/**
  holds the actual keyboard with resizing sliders etc
*/
TwonkMidiKeyboard::TwonkMidiKeyboard(MidiKeyboardState &state, MidiKeyboardComponent::Orientation orientation)
	: optionsVisible(false)
{
	resizeBounds.reset(new ComponentBoundsConstrainer());
	resizeBounds->setMinimumHeight(64);
	resizeBounds->setMinimumWidth(128);
	resizeBounds->setMaximumWidth(1024);
	resizeBounds->setMaximumHeight(600);

	corner.reset(new ResizableCornerComponent(this, resizeBounds.get()));
	addAndMakeVisible(corner.get());
	corner->setAlwaysOnTop(true);

	dockToBottom.reset(new TwonkToolBarButton());
	dockToBottom->setBaseColour(Colours::lightgrey);
	dockToBottom->setIcon(IMG(icon_dock_on_bottom_png));
	addAndMakeVisible(dockToBottom.get());

	positionOnKeyboard.reset(new Slider());
	positionOnKeyboard->setSliderStyle(Slider::LinearBar);
	positionOnKeyboard->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	positionOnKeyboard->setRange(0, 127, 1);
	positionOnKeyboard->setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
	positionOnKeyboard->setColour(Slider::trackColourId, Colours::aqua);
	positionOnKeyboard->setColour(Slider::thumbColourId, Colours::aquamarine);
	positionOnKeyboard->addListener(this);
	
	//addAndMakeVisible(positionOnKeyboard.get());
	midiKeyboardComponent.reset(new MidiKeyboardComponent(state, orientation));
	addAndMakeVisible(midiKeyboardComponent.get());
}

TwonkMidiKeyboard::~TwonkMidiKeyboard()
{
}

void TwonkMidiKeyboard::paint (Graphics& g)
{
	if (!optionsVisible)
	{
		{
			float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = 40.0f;
			Colour fillColour1 = Colour (0xd75a5a5a), fillColour2 = Colour (0xd7000000);
			//[UserPaintCustomArguments] Customize the painting arguments here..
			//[/UserPaintCustomArguments]
			g.setGradientFill (ColourGradient (fillColour1,
				0.0f - 0.0f + x,
				0.0f - 0.0f + y,
				fillColour2,
				0.0f - 0.0f + x,
				static_cast<float> (getHeight()) - 0.0f + y,
				false));
			g.fillRoundedRectangle (x, y, width, height, 7.000f);
		}
	}
}

void TwonkMidiKeyboard::resized()
{
	positionOnKeyboard->setBounds(0, 0, getWidth(), 32);
	corner->setBounds(getWidth() - 24, getHeight() - 24, 24, 24);
	midiKeyboardComponent->setBounds(0, 32, getWidth(), getHeight()-32);
	dockToBottom->setBounds(2, 2, 30, 30);
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
	if (slider == positionOnKeyboard.get())
	{
		midiKeyboardComponent->setLowestVisibleKey(slider->getValue());
	}
}
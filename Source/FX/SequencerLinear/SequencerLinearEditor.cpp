/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "SequencerLinearProcessor.h"
//[/Headers]

#include "SequencerLinearEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
Slider::SliderLayout SequencerLinearLook::getSliderLayout(Slider &slider)
{
	Slider::SliderLayout layout;
	layout.sliderBounds = Rectangle<int>(0, 0, slider.getWidth(), slider.getHeight());
	layout.textBoxBounds = Rectangle<int>(0,0, slider.getWidth(), slider.getHeight() * 0.1f);

	return (layout);
}

void SequencerLinearLook::drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	Colour c;
	if (button.getToggleState())
		c = Colours::aqua.withAlpha(0.7f);
	else
		c = Colours::black.withAlpha(0.2f);
	g.setColour(c);
	g.fillRect(button.getLocalBounds().reduced(2));

	g.setColour(c.brighter(0.9f));
	g.drawRect(button.getLocalBounds().reduced(1));
}

void SequencerLinearLook::drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
	g.setColour(Colours::white);
	g.setFont(owner.sliderLabelFont);
	String textToDraw;

	g.drawFittedText(textToDraw, Rectangle<int>(0, 0, width, height*0.1f), Justification::centred, 1);

	g.setColour (slider.findColour (Slider::trackColourId));
	g.fillRect (slider.isHorizontal() ?
		Rectangle<float> (x, y        , sliderPos - x, height) :
		Rectangle<float> (x, sliderPos, width        , y + (height - sliderPos))
	);


}
//[/MiscUserDefs]

//==============================================================================
SequencerLinearEditor::SequencerLinearEditor (SequencerLinearProcessor &p)
    : processor(p), AudioProcessorEditor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
	sliderLabelFont = CustomTypeface::createSystemTypefaceFor(BinaryData::terminess_ttf, BinaryData::terminess_ttfSize);
	notePosition  = previousBeat = 0;
	previousNotePosition = -1;
	lf = new SequencerLinearLook(*this);
	setLookAndFeel(lf);
	p.addListener(this);

	for (int positionIndicatorIndex = 0; positionIndicatorIndex < 16; positionIndicatorIndex++)
	{
		TextButton *positionIndicator = new TextButton (String(positionIndicatorIndex));
		addAndMakeVisible (positionIndicator);
		positionIndicator->setButtonText (String());
		positionIndicator->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
		positionIndicator->addListener (this);
		positionIndicator->setColour (TextButton::buttonColourId, Colours::red.darker(0.8f));
		positionIndicator->setBounds (24 + (positionIndicatorIndex * 36), +32, 36, 16);
		positionIndicators.set(positionIndicatorIndex, positionIndicator);
	}

	for (int sliderIndex = 0; sliderIndex < 16; sliderIndex++)
	{
		Slider *slider = new Slider (String(sliderIndex));
		addAndMakeVisible (slider);
		slider->setSliderStyle (Slider::LinearVertical);
		slider->setTextBoxStyle (Slider::NoTextBox, false, 32, 0);
		slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
		slider->addListener (this);
		slider->setBounds (24 + (sliderIndex * 36), 16 + 32, 36, 236);
		stepValues.set(sliderIndex, slider);
	}

	for (int buttonIndex = 0; buttonIndex < 16; buttonIndex++)
	{
		ToggleButton *buttonNoteState = new ToggleButton (String(buttonIndex));
		addAndMakeVisible (buttonNoteState);
		buttonNoteState->setButtonText (String());
		buttonNoteState->addListener (this);
		buttonNoteState->setBounds (24 + (buttonIndex * 36), 236 + 16 + 32, 36, 36);
		stepStates.set(buttonIndex, buttonNoteState);
		buttonNoteState->setToggleState(stepValues[buttonIndex]->getValue() > 10, dontSendNotification);
	}
    //[/Constructor_pre]

    positionLabel.reset (new Label ("new label",
                                    TRANS("00:00:00:000")));
    addAndMakeVisible (positionLabel.get());
    positionLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    positionLabel->setJustificationType (Justification::centredLeft);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (TextEditor::textColourId, Colours::black);
    positionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    positionLabel->setBounds (32, 8, 128, 16);


    //[UserPreSize]
	positionLabel->setFont(sliderLabelFont);
    //[/UserPreSize]

    setSize (600, 320);


    //[Constructor] You can add your own custom stuff here..
	startTimerHz(30);
    //[/Constructor]
}

SequencerLinearEditor::~SequencerLinearEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
	deleteAndZero(lf);
    //[/Destructor_pre]

    positionLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SequencerLinearEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff0e374c));

    {
        int x = 2, y = 2, width = 20, height = getHeight() - 4;
        Colour fillColour = Colour (0x54ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = 26, y = 2, width = getWidth() - 28, height = 28;
        Colour fillColour = Colour (0x917ab3a8);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SequencerLinearEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SequencerLinearEditor::audioProcessorParameterChanged(AudioProcessor *processor, int parameterIndex, float newValue){}
void SequencerLinearEditor::audioProcessorChanged(AudioProcessor *processor){}

void SequencerLinearEditor::sliderValueChanged(Slider *slider)
{
}
void SequencerLinearEditor::buttonClicked(Button *button)
{
}

void SequencerLinearEditor::timerCallback()
{
	AudioPlayHead::CurrentPositionInfo pos = processor.lastPosInfo;
	auto sampleRate = processor.getCurrentSampleRate();

	if (!pos.isPlaying)
	{
		previousBeat = 0;
		previousNotePosition = -1;
		notePosition = 0;
		return;
	}

	double beatLengthInSamples = 60.0 / (pos.bpm * 4) * sampleRate;
	int beatLengthMultiple = (int)pos.timeInSamples % (int)beatLengthInSamples;

	auto quarterNotes = pos.ppqPosition;
	auto quarterNotesPerBar = (pos.timeSigNumerator * 4 / pos.timeSigDenominator);
	auto beats = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * pos.timeSigNumerator;

	auto bar = ((int)quarterNotes) / quarterNotesPerBar;
	auto beat = ((int)beats);
	auto ticks = ((int)(fmod (beats, 1.0) * 960.0 + 0.5));
	positionLabel->setText(String::formatted("%02d:%02d:%f:%03d", bar, beat, pos.ppqPosition / quarterNotesPerBar, ticks), dontSendNotification);
	if (beat != previousBeat)
	{
		// increment one beat
		previousBeat = beat;

		if (positionIndicators[notePosition])
			positionIndicators[notePosition]->setColour (TextButton::buttonColourId, Colours::red);

		if (positionIndicators[previousNotePosition])
			positionIndicators[previousNotePosition]->setColour (TextButton::buttonColourId, Colours::red.darker(0.8f));

		previousNotePosition = notePosition;

		notePosition++;

		if (notePosition == 16)
			notePosition = 0;
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SequencerLinearEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public AudioProcessorListener, public Slider::Listener, public Button::Listener, public Timer"
                 constructorParams="SequencerLinearProcessor &amp;p" variableInitialisers="processor(p), AudioProcessorEditor (p),"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="320">
  <BACKGROUND backgroundColour="ff0e374c">
    <RECT pos="2 2 20 4M" fill="solid: 54ffffff" hasStroke="0"/>
    <RECT pos="26 2 28M 28" fill="solid: 917ab3a8" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="885bf34271a78587" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="32 8 128 16" edTextCol="ff000000"
         edBkgCol="0" labelText="00:00:00:000" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


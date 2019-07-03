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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "SequencerLinearProcessor.h"

class SequencerLinearEditor;

class SequencerLinearLook : public LookAndFeel_V4
{
	public:
		SequencerLinearLook(SequencerLinearEditor &_owner) : owner(_owner){}
		void drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
		void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;
		Slider::SliderLayout getSliderLayout(Slider &);

	private:
		SequencerLinearEditor &owner;
};

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SequencerLinearEditor  : public AudioProcessorEditor,
                               public AudioProcessorListener,
                               public Slider::Listener,
                               public Button::Listener,
                               public Timer
{
public:
    //==============================================================================
    SequencerLinearEditor (SequencerLinearProcessor &p);
    ~SequencerLinearEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void audioProcessorParameterChanged(AudioProcessor *processor, int parameterIndex, float newValue);
	void audioProcessorChanged(AudioProcessor *processor);
	void sliderValueChanged(Slider *slider) override;
	void buttonClicked(Button *button) override;
	void timerCallback();
	Font sliderLabelFont;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SequencerLinearProcessor &processor;
	SequencerLinearLook *lf;
	Array <Slider *> stepValues;
	Array <Button *> stepStates;
	Array <Button *> positionIndicators;
	int notePosition;
	int previousBeat;
	int previousNotePosition;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> positionLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerLinearEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
#include "../../JuceLibraryCode/JuceHeader.h"
class SequencerLinearProcessor;

class SequencerLinearLook : public LookAndFeel_V4
{
	public:
		void drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
		void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;
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
                               public Slider::Listener,
                               public Button::Listener
{
public:
    //==============================================================================
    SequencerLinearEditor (SequencerLinearProcessor &p);
    ~SequencerLinearEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SequencerLinearProcessor &processor;
	SequencerLinearLook *lf;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> slider;
    std::unique_ptr<Slider> slider2;
    std::unique_ptr<Slider> slider3;
    std::unique_ptr<Slider> slider4;
    std::unique_ptr<Slider> slider5;
    std::unique_ptr<Slider> slider6;
    std::unique_ptr<Slider> slider7;
    std::unique_ptr<Slider> slider8;
    std::unique_ptr<Slider> slider9;
    std::unique_ptr<Slider> slider10;
    std::unique_ptr<Slider> slider11;
    std::unique_ptr<Slider> slider12;
    std::unique_ptr<Slider> slider13;
    std::unique_ptr<Slider> slider14;
    std::unique_ptr<Slider> slider15;
    std::unique_ptr<ToggleButton> toggleButton;
    std::unique_ptr<ToggleButton> toggleButton2;
    std::unique_ptr<ToggleButton> toggleButton3;
    std::unique_ptr<ToggleButton> toggleButton4;
    std::unique_ptr<ToggleButton> toggleButton5;
    std::unique_ptr<ToggleButton> toggleButton6;
    std::unique_ptr<ToggleButton> toggleButton7;
    std::unique_ptr<ToggleButton> toggleButton8;
    std::unique_ptr<ToggleButton> toggleButton9;
    std::unique_ptr<ToggleButton> toggleButton10;
    std::unique_ptr<ToggleButton> toggleButton11;
    std::unique_ptr<ToggleButton> toggleButton12;
    std::unique_ptr<ToggleButton> toggleButton13;
    std::unique_ptr<ToggleButton> toggleButton14;
    std::unique_ptr<ToggleButton> toggleButton15;
    std::unique_ptr<TextButton> textButton2;
    std::unique_ptr<TextButton> textButton3;
    std::unique_ptr<TextButton> textButton4;
    std::unique_ptr<TextButton> textButton5;
    std::unique_ptr<TextButton> textButton6;
    std::unique_ptr<TextButton> textButton7;
    std::unique_ptr<TextButton> textButton8;
    std::unique_ptr<TextButton> textButton9;
    std::unique_ptr<TextButton> textButton10;
    std::unique_ptr<TextButton> textButton11;
    std::unique_ptr<TextButton> textButton12;
    std::unique_ptr<TextButton> textButton13;
    std::unique_ptr<TextButton> textButton14;
    std::unique_ptr<TextButton> textButton15;
    std::unique_ptr<TextButton> textButton16;
    std::unique_ptr<TextButton> textButton17;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerLinearEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../../JuceLibraryCode/JuceHeader.h"
#include "UI/TwonkLookAndFeel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentParametersEditor  : public Component,
                                    public Slider::Listener,
                                    public Button::Listener
{
public:
    //==============================================================================
    InstrumentParametersEditor ();
    ~InstrumentParametersEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TwonkLookAndFeel twonkLookAndFeel;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> envelopeAttack;
    std::unique_ptr<ToggleButton> toggleButton;
    std::unique_ptr<ToggleButton> toggleButton2;
    std::unique_ptr<Slider> envelopeAttack5;
    std::unique_ptr<Slider> envelopeAttack2;
    std::unique_ptr<Slider> envelopeAttack3;
    std::unique_ptr<Slider> envelopeAttack4;
    std::unique_ptr<Slider> envelopeAttack6;
    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Slider> envelopeAttack7;
    std::unique_ptr<Label> label5;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentParametersEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
class JucesamplerAudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BankEditor  : public AudioProcessorEditor,
                    public Slider::Listener,
                    public Button::Listener,
                    public ComboBox::Listener
{
public:
    //==============================================================================
    BankEditor (JucesamplerAudioProcessor &_processor);
    ~BankEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	JucesamplerAudioProcessor &processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Component> component;
    std::unique_ptr<Slider> slider;
    std::unique_ptr<Slider> slider2;
    std::unique_ptr<Slider> slider3;
    std::unique_ptr<Slider> slider4;
    std::unique_ptr<Slider> slider5;
    std::unique_ptr<TextButton> textButton;
    std::unique_ptr<TextButton> textButton2;
    std::unique_ptr<ComboBox> comboBox;
    std::unique_ptr<Component> component2;
    std::unique_ptr<Component> component3;
    std::unique_ptr<Component> component4;
    std::unique_ptr<Component> component5;
    std::unique_ptr<Component> component6;
    std::unique_ptr<Component> component7;
    std::unique_ptr<Component> component8;
    std::unique_ptr<Component> component9;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BankEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


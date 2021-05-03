/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../JuceLibraryCode/JuceHeader.h"
#include "TwonkPlayHead.h"
class TwonkToolBarButton;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkTransport  : public Component,
                        public TwonkClockListener,
                        public Button::Listener,
                        public Timer,
                        public juce::Slider::Listener
{
public:
    //==============================================================================
    TwonkTransport (TwonkPlayHead &_playHead);
    ~TwonkTransport() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo);
	void buttonClicked(Button *button);
	void timerCallback();
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseDoubleClick (const juce::MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	std::unique_ptr<ComponentDragger> dragger;
	TwonkPlayHead &playHead;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkToolBarButton> playButton;
    std::unique_ptr<TwonkToolBarButton> stopButton;
    std::unique_ptr<TwonkToolBarButton> loopButton;
    std::unique_ptr<juce::Slider> tempoSlider;
    std::unique_ptr<juce::Slider> loopLengthSlider;
    std::unique_ptr<juce::Label> timeLabel;
    std::unique_ptr<juce::Label> positionLabel;
    std::unique_ptr<juce::Label> tempoLabel;
    std::unique_ptr<juce::Label> cpuUsage;
    std::unique_ptr<juce::Label> memUsage;
    std::unique_ptr<juce::Label> juce__label;
    std::unique_ptr<juce::Label> juce__label2;
    std::unique_ptr<juce::Label> juce__label3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkTransport)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


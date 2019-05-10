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
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkMain  : public AudioAppComponent,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    //==============================================================================
    TwonkMain ();
    ~TwonkMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void prepareToPlay (int, double) override;
	void releaseResources() override;
	void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	std::unique_ptr<TimeSliceThread> uiManagerThread;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> settingsButton;
    std::unique_ptr<drow::Spectroscope> drowScope;
    std::unique_ptr<drow::TriggeredScope> drowOsc;
    std::unique_ptr<Slider> verticalZoomFactor;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkMain)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


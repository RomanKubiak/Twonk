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
#include "../TwonkPlayHead.h"
class GraphDocumentComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkTitleBarComponent  : public Component,
                                public TwonkClockListener,
                                public Button::Listener,
                                public Slider::Listener
{
public:
    //==============================================================================
    TwonkTitleBarComponent (GraphDocumentComponent &_owner);
    ~TwonkTitleBarComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	GraphDocumentComponent &owner;
	void stepIncrement(int currentStep);
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> settingsButton;
    std::unique_ptr<ImageButton> midiKeysButton;
    std::unique_ptr<ImageButton> pluginButton;
    std::unique_ptr<ImageButton> syncButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<Slider> tempoSlider;
    std::unique_ptr<Slider> positionIndicator;
    std::unique_ptr<Slider> seqLength;
    std::unique_ptr<Slider> seqFirst;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkTitleBarComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../TwonkPlayHead.h"

class GraphEditorPanel;
class TwonkToolBarButton;
class TwonkToolBarStatus;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkToolBar  : public Component,
                      public TwonkClockListener,
                      Button::Listener,
                      public Slider::Listener
{
public:
    //==============================================================================
    TwonkToolBar (GraphEditorPanel &_owner);
    ~TwonkToolBar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked (Button *);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	GraphEditorPanel &owner;
	void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo);
	void transportStopped();
	Font labelFont;
	ComponentAnimator toolbarAnimator;
	ComponentDragger toolbarDragger;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkToolBarButton> buttonConfig;
    std::unique_ptr<TwonkToolBarButton> buttonFilters;
    std::unique_ptr<TwonkToolBarButton> buttonPlay;
    std::unique_ptr<TwonkToolBarStatus> statusItem;
    std::unique_ptr<TwonkToolBarButton> buttonMidiKeyboard;
    std::unique_ptr<Slider> tempoSlider;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Label> tempoLabel;
    std::unique_ptr<Label> volumeLabel;
    std::unique_ptr<TwonkToolBarButton> buttonToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkToolBar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


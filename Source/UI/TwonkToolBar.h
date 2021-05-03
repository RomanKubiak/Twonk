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
#include "TwonkProgramMenu.h"
#include "TwonkAudioSettingsMenu.h"
class Editor;
class TwonkToolBarButton;
class TwonkToolBarStatus;
//[/Headers]

#include "TwonkToolBarHeader.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkToolBar  : public Component,
                      public TwonkClockListener,
                      Button::Listener
{
public:
    //==============================================================================
    TwonkToolBar (Editor &_owner);
    ~TwonkToolBar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked (Button *);
	void toggleMenu();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void moved() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Editor &owner;
	void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo);
	void transportStopped();
	Font labelFont;
	ComponentAnimator toolbarAnimator;
	ComponentDragger toolbarDragger;
	std::unique_ptr<TwonkProgramMenu> twonkProgramMenu;
	std::unique_ptr<TwonkAudioSettingsMenu> twonkAudioSettingsMenu;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkToolBarButton> buttonConfig;
    std::unique_ptr<TwonkToolBarButton> buttonFilters;
    std::unique_ptr<TwonkToolBarButton> buttonFile;
    std::unique_ptr<TwonkToolBarHeader> toolbarHeader;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkToolBar)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


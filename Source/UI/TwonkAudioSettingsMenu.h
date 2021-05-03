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
class Editor;
class TwonkToolBarButton;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkAudioSettingsMenu  : public Component,
                                public Button::Listener
{
public:
    //==============================================================================
    TwonkAudioSettingsMenu (Editor &_owner);
    ~TwonkAudioSettingsMenu();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked(Button *b);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Editor &owner;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkToolBarButton> settingsPlugins;
    std::unique_ptr<TwonkToolBarButton> settingsAudio;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkAudioSettingsMenu)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


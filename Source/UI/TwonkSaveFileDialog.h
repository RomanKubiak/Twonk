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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkSaveFileDialog  : public Component,
                             public Button::Listener,
                             public Label::Listener
{
public:
    //==============================================================================
    TwonkSaveFileDialog ();
    ~TwonkSaveFileDialog();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void labelTextChanged (Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	enum ProgramType
	{
		Synth,
		Effect,
		MIDI,
		General
	};
	ProgramType programType;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> saveButton;
    std::unique_ptr<TextButton> cancelButton;
    std::unique_ptr<Label> programName;
    std::unique_ptr<ImageButton> fxProgamType;
    std::unique_ptr<ImageButton> generatorProgram;
    std::unique_ptr<ImageButton> midiProgram;
    std::unique_ptr<ImageButton> generalProgram;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkSaveFileDialog)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
#include <JuceHeader.h>
#include "../Simpler/SimplerEditor.h"
class PianoKeys;
class HexagonController;
class MidiControllerProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MidiControllerEditor  : public AudioProcessorEditor
{
public:
    //==============================================================================
    MidiControllerEditor (MidiControllerProcessor &_processor);
    ~MidiControllerEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiControllerProcessor &processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ConcertinaPanel> panel;
    std::unique_ptr<ResizableCornerComponent> corner;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiControllerEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


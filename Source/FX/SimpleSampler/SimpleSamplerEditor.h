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
#include "../../../JuceLibraryCode/JuceHeader.h"
#include "SimpleSamplerProcessor.h"
#include "SamplerSoundEditor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SimpleSamplerEditor  : public AudioProcessorEditor
{
public:
    //==============================================================================
    SimpleSamplerEditor (SimpleSamplerProcessor &p);
    ~SimpleSamplerEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimpleSamplerProcessor &processor;
	std::unique_ptr<SamplerSoundEditor> sound1;
	std::unique_ptr<SamplerSoundEditor> sound2;
	std::unique_ptr<SamplerSoundEditor> sound3;
	std::unique_ptr<SamplerSoundEditor> sound4;
	std::unique_ptr<SamplerSoundEditor> sound5;
	std::unique_ptr<SamplerSoundEditor> sound6;
	std::unique_ptr<SamplerSoundEditor> sound7;
	std::unique_ptr<SamplerSoundEditor> sound8;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
class FifteenStepProcessor;
class FifteenStepHexStep;
class FifteenStepHexRow;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FifteenStepEditor  : public AudioProcessorEditor,
                           public Timer,
                           public ChangeBroadcaster
{
public:
    //==============================================================================
    FifteenStepEditor (FifteenStepProcessor &_processor);
    ~FifteenStepEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
	int lastPlayStep;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseMove (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	FifteenStepProcessor &processor;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> timeInfoLabel;
    std::unique_ptr<Viewport> rowViewport;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FifteenStepEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


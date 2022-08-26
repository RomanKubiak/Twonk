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
class FifteenStepHexStep;
class FifteenStepEditor;

#define SQRT3 1.73205080757f
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class FifteenStepHexRow  : public Component,
                           public ChangeListener
{
public:
    //==============================================================================
    FifteenStepHexRow (FifteenStepEditor &_owner);
    ~FifteenStepHexRow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setBaseColour(const Colour _baseColour);
	void changeListenerCallback (ChangeBroadcaster* source);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseMove (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	OwnedArray<FifteenStepHexStep> steps;
	Colour baseColour;
	int index;
	FifteenStepEditor &owner;
	int lastPlayStep;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FifteenStepHexRow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


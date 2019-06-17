/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

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
class TwonkBubbleComponent  : public Component
{
public:
    //==============================================================================
    TwonkBubbleComponent ();
    ~TwonkBubbleComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void mouseDown (const MouseEvent& e);
	void mouseDrag (const MouseEvent& e);
	Colour fillColour;
	Colour stroke;
	void setComponentName(const String &newName);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ComponentDragger myDragger;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> componentName;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkBubbleComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
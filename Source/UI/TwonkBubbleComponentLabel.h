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
class TwonkBubbleComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkBubbleComponentLabel  : public Component
{
public:
    //==============================================================================
    TwonkBubbleComponentLabel (TwonkBubbleComponent &_owner);
    ~TwonkBubbleComponentLabel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setText(const String &_text);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TwonkBubbleComponent &owner;
	GlowEffect glow;
	String text;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkBubbleComponentLabel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

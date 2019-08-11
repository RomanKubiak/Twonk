/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../TwonkPlayHead.h"

class GraphDocumentComponent;

class TitleBarLookAndFeel : public LookAndFeel_V4
{
	public:
		TitleBarLookAndFeel(Font _font) : font(_font)
		{
		}
		Label* createSliderTextBox (Slider& slider) override
		{
			auto* l = LookAndFeel_V2::createSliderTextBox (slider);
			l->setFont(font);
			if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
				|| slider.getSliderStyle() == Slider::LinearBarVertical))
			{

				l->setColour (Label::textColourId, Colours::black.withAlpha (0.7f));
			}

			return l;
		}
		Font font;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkTitleBarComponent  : public Component,
                                public TwonkClockListener
{
public:
    //==============================================================================
    TwonkTitleBarComponent (GraphDocumentComponent &_owner);
    ~TwonkTitleBarComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	GraphDocumentComponent &owner;
	void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo);
	void transportStopped();
	TitleBarLookAndFeel *titleBarLookAndFeel;
	Font labelFont;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkTitleBarComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

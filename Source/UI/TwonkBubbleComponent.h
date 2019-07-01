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
#include "../Filters/FilterGraph.h"
//[/Headers]

#include "TwonkBubbleComponentLabel.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkBubbleComponent  : public Component,
                              public Button::Listener
{
public:
    //==============================================================================
    TwonkBubbleComponent (FilterGraph &g, const AudioProcessorGraph::NodeID id);
    ~TwonkBubbleComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void mouseDown (const MouseEvent& e);
	void mouseDrag (const MouseEvent& e);
	Colour fillColour;
	Colour stroke;
	void setComponentName(const String &newName);
	void setBypassed(const bool isBypassed);
	void toggleOptions(const bool shouldBeVisible);
	FilterGraph& graph;
	const AudioProcessorGraph::NodeID pluginID;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ComponentDragger myDragger;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> removeButton;
    std::unique_ptr<TextButton> bypassButton;
    std::unique_ptr<TwonkBubbleComponentLabel> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkBubbleComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

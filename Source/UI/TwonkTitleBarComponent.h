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
#include "../TwonkPlayHead.h"

class GraphEditorPanel;
class TwonkTitleBarButton;
class TwonkTitleBarStatus;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkTitleBarComponent  : public Component,
                                public TwonkClockListener,
                                public Button::Listener
{
public:
    //==============================================================================
    TwonkTitleBarComponent (GraphEditorPanel &_owner);
    ~TwonkTitleBarComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked (Button *b) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	GraphEditorPanel &owner;
	void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo);
	void transportStopped();
	Font labelFont;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkTitleBarButton> buttonConfig;
    std::unique_ptr<TwonkTitleBarButton> buttonFilters;
    std::unique_ptr<TwonkTitleBarButton> buttonMinMax;
    std::unique_ptr<TwonkTitleBarButton> buttonPlay;
    std::unique_ptr<TwonkTitleBarStatus> statusItem;
    std::unique_ptr<TwonkTitleBarButton> buttonMidiKeyboard;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkTitleBarComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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
#include "../../../JuceLibraryCode/JuceHeader.h"
class SimplerEditor;
//[/Headers]

#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentButtonsPanel  : public Component
{
public:
    //==============================================================================
    InstrumentButtonsPanel (SimplerEditor &_owner);
    ~InstrumentButtonsPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	Array<InstrumentButton *> &getAllButtons() { return (buttons); }
	InstrumentButton *getButton(int index) { return (buttons[index]); }
	void deselectAll();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimplerEditor &owner;
	Array<InstrumentButton *> buttons;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<InstrumentButton> ins1;
    std::unique_ptr<InstrumentButton> ins2;
    std::unique_ptr<InstrumentButton> ins3;
    std::unique_ptr<InstrumentButton> ins4;
    std::unique_ptr<InstrumentButton> ins5;
    std::unique_ptr<InstrumentButton> ins6;
    std::unique_ptr<InstrumentButton> ins7;
    std::unique_ptr<InstrumentButton> ins8;
    std::unique_ptr<InstrumentButton> ins9;
    std::unique_ptr<InstrumentButton> ins10;
    std::unique_ptr<InstrumentButton> ins11;
    std::unique_ptr<InstrumentButton> ins12;
    std::unique_ptr<InstrumentButton> ins13;
    std::unique_ptr<InstrumentButton> ins14;
    std::unique_ptr<InstrumentButton> ins15;
    std::unique_ptr<InstrumentButton> ins16;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentButtonsPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


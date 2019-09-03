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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "FifteenStepRowHolder.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "FifteenStepHexRow.h"
#include "FifteenStepEditor.h"
//[/MiscUserDefs]

//==============================================================================
FifteenStepRowHolder::FifteenStepRowHolder (FifteenStepEditor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
	for (int i = 0; i < 4; i++)
	{
		FifteenStepHexRow * row = new FifteenStepHexRow (owner);
		rows.add(row);
		row->setBounds(0, 0 + i * (48 * sqrt(3.0)*0.5f), 588, 72);
		addAndMakeVisible(row);
	}
	rows[0]->setBaseColour(Colours::red);
	rows[1]->setBaseColour(Colours::yellow);
	rows[2]->setBaseColour(Colours::blue);
	rows[3]->setBaseColour(Colours::lightgreen);
	owner.addChangeListener(rows[0]);
	owner.addChangeListener(rows[1]);
	owner.addChangeListener(rows[2]);
	owner.addChangeListener(rows[3]);
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (588, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FifteenStepRowHolder::~FifteenStepRowHolder()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FifteenStepRowHolder::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FifteenStepRowHolder::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FifteenStepRowHolder" componentName=""
                 parentClasses="public Component" constructorParams="FifteenStepEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="588"
                 initialHeight="300">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


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

#include "FifteenStepHexRow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "UI/TwonkToolBarButton.h"
#include "FifteenStepHexStep.h"
#include "FifteenStepEditor.h"
//[/MiscUserDefs]

//==============================================================================
FifteenStepHexRow::FifteenStepHexRow (FifteenStepEditor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
	lastPlayStep = -1;
	for (int i = 0; i < 16; i++)
	{
		FifteenStepHexStep *step = new FifteenStepHexStep();
		step->setClickingTogglesState(true);
		steps.add(step);
		addAndMakeVisible(step);
	}
	setInterceptsMouseClicks(false, true);
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (768, 72);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FifteenStepHexRow::~FifteenStepHexRow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FifteenStepHexRow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FifteenStepHexRow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	const float lowerY = 48 * SQRT3 * 0.25f;
	const float size = 48;
	for (int i = 0; i < steps.size(); i++)
	{
		steps[i]->setBounds(size*i*0.75f, i%2 ? 0 : lowerY, size, size);
		if (!fmod(i,4))
			steps[i]->setHinted(true);
	}
	/*
	steps[0]->setBounds(0, 0, size, size);
	steps[0]->setVisible(true);
	steps[1]->setBounds(size * 0.75f, lowerY, size, size);
	steps[1]->setVisible(true);
	steps[2]->setBounds(size * 1.5f, 0, size, size);
	steps[2]->setVisible(true);
	steps[3]->setBounds(size * 2.25f, lowerY, size, size);
	steps[3]->setVisible(true);

	steps[4]->setBounds(size * 3.0f, 0, size, size);
	steps[4]->setVisible(true);
	steps[5]->setBounds(size * 3.75f, lowerY, size, size);
	steps[5]->setVisible(true);
	steps[6]->setBounds(size * 4.5f, 0, size, size);
	steps[6]->setVisible(true);
	steps[7]->setBounds(size * 5.25f, lowerY, size, size);
	steps[7]->setVisible(true);

	steps[8]->setBounds(size * 6.0f, 0, size, size);
	steps[8]->setVisible(true);
	steps[9]->setBounds(size * 6.75f, lowerY, size, size);
	steps[9]->setVisible(true);
	steps[10]->setBounds(size * 7.5f, 0, size, size);
	steps[10]->setVisible(true);
	steps[11]->setBounds(size * 8.25f, lowerY, size, size);
	steps[11]->setVisible(true);

	steps[12]->setBounds(size * 9.0f, 0, size, size);
	steps[12]->setVisible(true);
	steps[13]->setBounds(size * 9.75f, lowerY, size, size);
	steps[13]->setVisible(true);
	steps[14]->setBounds(size * 10.5f, 0, size, size);
	steps[14]->setVisible(true);
	steps[15]->setBounds(size * 11.25f, lowerY, size, size);
	steps[15]->setVisible(true);
	*/
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FifteenStepHexRow::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    //[/UserCode_mouseMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void FifteenStepHexRow::setBaseColour(const Colour _baseColour)
{
	baseColour = _baseColour;
	for (int i = 0; i < steps.size(); i++)
	{
		steps[i]->setBaseColour(baseColour);
	}
}

void FifteenStepHexRow::changeListenerCallback(ChangeBroadcaster *b)
{
	if (lastPlayStep != owner.lastPlayStep)
	{
		lastPlayStep = owner.lastPlayStep;
		if (steps[lastPlayStep])
		{
			steps[lastPlayStep]->setHighlited(true);
		}

		if (steps[lastPlayStep - 1])
			steps[lastPlayStep - 1]->setHighlited(false);

		if (lastPlayStep == 0)
			steps[steps.size()-1]->setHighlited(false);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FifteenStepHexRow" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="FifteenStepEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="768"
                 initialHeight="72">
  <METHODS>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


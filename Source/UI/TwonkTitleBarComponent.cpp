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

//[Headers] You can add your own extra header files here...
#include "GraphDocument.h"
//[/Headers]

#include "TwonkTitleBarComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkTitleBarComponent::TwonkTitleBarComponent (GraphDocumentComponent &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
	labelFont = CustomTypeface::createSystemTypefaceFor(BinaryData::terminess_ttf, BinaryData::terminess_ttfSize);
	titleBarLookAndFeel = new TitleBarLookAndFeel(labelFont);
	setLookAndFeel(titleBarLookAndFeel);
    //[/Constructor_pre]


    //[UserPreSize]
	tempoSlider->setValue(60.0);
	playButton->setClickingTogglesState(true);
	syncButton->setClickingTogglesState(true);
	timeLabel->setFont(labelFont);
    //[/UserPreSize]

    setSize (64, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkTitleBarComponent::~TwonkTitleBarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
	deleteAndZero(titleBarLookAndFeel);
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkTitleBarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x07ffffff));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkTitleBarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkTitleBarComponent::positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo)
{
	if (!positionInfo.isPlaying)
	{
		timeLabel->setText("00:00:00:0.0", dontSendNotification);
		return;
	}

	timeLabel->setText(String::formatted("00:00:00:%.1f", positionInfo.ppqPosition), dontSendNotification);
}

void TwonkTitleBarComponent::transportStopped()
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkTitleBarComponent" componentName=""
                 parentClasses="public Component, public TwonkClockListener" constructorParams="GraphDocumentComponent &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.33" fixedSize="1" initialWidth="64"
                 initialHeight="600">
  <BACKGROUND backgroundColour="7ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TwonkBubbleComponentLabel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "TwonkBubbleComponent.h"
//[/MiscUserDefs]

//==============================================================================
TwonkBubbleComponentLabel::TwonkBubbleComponentLabel (TwonkBubbleComponent &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
	glow.setGlowProperties(1.0f, Colours::white.withAlpha(0.5f));
	setComponentEffect(&glow);
    //[/UserPreSize]

    setSize (128, 48);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkBubbleComponentLabel::~TwonkBubbleComponentLabel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkBubbleComponentLabel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	Font f (CustomTypeface::createSystemTypefaceFor(BinaryData::_60sekuntia_ttf, BinaryData::_60sekuntia_ttfSize));
	f.setHeight(proportionOfHeight(0.4f));
	g.setFont(f);
	g.setColour(Colours::white);
	g.drawFittedText(
		text, 
		Rectangle<int>(
			proportionOfWidth(0.1f),
			proportionOfHeight(0.1f),
			proportionOfWidth(0.8f),
			proportionOfHeight(0.8f)
		),
		Justification::centred,
		1
	);
    //[/UserPaint]
}

void TwonkBubbleComponentLabel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkBubbleComponentLabel::setText(const String &_text)
{
	text = _text;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkBubbleComponentLabel"
                 componentName="" parentClasses="public Component" constructorParams="TwonkBubbleComponent &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="128"
                 initialHeight="48">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


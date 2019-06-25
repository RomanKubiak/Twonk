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

#include "TwonkBubbleNodeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkBubbleNodeComponent::TwonkBubbleNodeComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (32, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkBubbleNodeComponent::~TwonkBubbleNodeComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkBubbleNodeComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = static_cast<float> (proportionOfWidth (0.1000f)), y = static_cast<float> (proportionOfHeight (0.1000f)), width = static_cast<float> (proportionOfWidth (0.8000f)), height = static_cast<float> (proportionOfHeight (0.8000f));
        Colour fillColour = Colour (0xff2a7da5);
        Colour strokeColour = Colour (0xffadc9ff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour = fill;
    		strokeColour = fill.brighter(0.8f);
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkBubbleNodeComponent::resized()
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

<JUCER_COMPONENT documentType="Component" className="TwonkBubbleNodeComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="32" initialHeight="32">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="10% 10% 80% 80%" cornerSize="5.0" fill="solid: ff2a7da5"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffadc9ff"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


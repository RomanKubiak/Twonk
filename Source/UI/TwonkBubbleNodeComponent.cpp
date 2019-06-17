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
        float x = static_cast<float> (proportionOfWidth (0.1f)), y = static_cast<float> (proportionOfHeight (0.1f)), width = static_cast<float> (proportionOfWidth (0.8f)), height = static_cast<float> (proportionOfHeight (0.8f));
        Colour fillColour1 = Colours::red, fillColour2 = Colours::black;
        Colour strokeColour = Colour (0xff9e0000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour1 = fillColour;
    		strokeColour = stroke;
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> ((getWidth() / 2)) - static_cast<float> (proportionOfWidth (0.1f)) + x,
                                       static_cast<float> ((getHeight() / 2)) - static_cast<float> (proportionOfHeight (0.1f)) + y,
                                       fillColour2,
                                       static_cast<float> (getWidth()) - static_cast<float> (proportionOfWidth (0.1f)) + x,
                                       0.0f - static_cast<float> (proportionOfHeight (0.1f)) + y,
                                       true));
        g.fillEllipse (x, y, width, height);
        g.setColour (strokeColour);
        g.drawEllipse (x, y, width, height, 2.0f);
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
                 overlayOpacity="0.33" fixedSize="1" initialWidth="32" initialHeight="32">
  <BACKGROUND backgroundColour="0">
    <ELLIPSE pos="10% 10% 80% 80%" fill=" radial: 0C 0C, 0R 0, 0=ffff0000, 1=ff000000"
             hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ff9e0000"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

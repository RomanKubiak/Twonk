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

#include "TwonkSlider.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkSlider::TwonkSlider ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (256, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkSlider::~TwonkSlider()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkSlider::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        float x = static_cast<float> (proportionOfWidth (0.0500f)), y = static_cast<float> (proportionOfHeight (0.2500f)), width = static_cast<float> (proportionOfWidth (0.9000f)), height = static_cast<float> (proportionOfHeight (0.5000f));
        Colour fillColour1 = Colour (0xff003f8f), fillColour2 = Colour (0xff0042a3);
        Colour strokeColour = Colour (0x58000000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.5000f)) - static_cast<float> (proportionOfWidth (0.0500f)) + x,
                                       static_cast<float> (proportionOfHeight (0.5000f)) - static_cast<float> (proportionOfHeight (0.2500f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (1.0000f)) - static_cast<float> (proportionOfWidth (0.0500f)) + x,
                                       static_cast<float> (proportionOfHeight (0.5000f)) - static_cast<float> (proportionOfHeight (0.2500f)) + y,
                                       true));
        g.fillRoundedRectangle (x, y, width, height, 2.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 2.000f, 2.000f);
    }

    {
        float x = static_cast<float> (proportionOfWidth (0.4297f)), y = static_cast<float> (proportionOfHeight (0.0313f)), width = static_cast<float> (proportionOfWidth (0.1016f)), height = static_cast<float> (proportionOfHeight (0.9063f));
        Colour fillColour = Colour (0x9cffffff);
        Colour strokeColour = Colour (0xe2ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 2.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 2.000f, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkSlider::resized()
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

<JUCER_COMPONENT documentType="Component" className="TwonkSlider" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="256" initialHeight="32">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="5% 25% 90% 50%" cornerSize="2.0" fill=" radial: 50% 50%, 100% 50%, 0=ff003f8f, 1=ff0042a3"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: 58000000"/>
    <ROUNDRECT pos="42.969% 3.125% 10.156% 90.625%" cornerSize="2.0" fill="solid: 9cffffff"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: e2ffffff"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


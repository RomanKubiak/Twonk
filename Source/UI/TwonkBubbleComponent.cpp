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

#include "TwonkBubbleComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkBubbleComponent::TwonkBubbleComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (32, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkBubbleComponent::~TwonkBubbleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkBubbleComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 2.0f, y = 2.0f, width = static_cast<float> (getWidth() - 4), height = static_cast<float> (getHeight() - 4);
        Colour fillColour1 = Colour (0x00000000), fillColour2 = Colours::green;
        Colour strokeColour1 = Colour (0xff00ff0b), strokeColour2 = Colour (0x00008000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> ((getWidth() / 2)) - 2.0f + x,
                                       static_cast<float> ((getHeight() / 2)) - 2.0f + y,
                                       fillColour2,
                                       static_cast<float> ((getWidth() / 2)) - 2.0f + x,
                                       0.0f - 2.0f + y,
                                       true));
        g.fillEllipse (x, y, width, height);
        g.setGradientFill (ColourGradient (strokeColour1,
                                       static_cast<float> ((getWidth() / 2)) - 2.0f + x,
                                       static_cast<float> ((getHeight() / 2)) - 2.0f + y,
                                       strokeColour2,
                                       static_cast<float> ((getWidth() / 2)) - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (1.25f)) - 2.0f + y,
                                       true));
        g.drawEllipse (x, y, width, height, 3.0f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkBubbleComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkBubbleComponent::mouseDown (const MouseEvent& e)
{
	DBG("TwonkBubbleComponent::mouseDown");
	myDragger.startDraggingComponent (this, e);
}

void TwonkBubbleComponent::mouseDrag (const MouseEvent& e)
{
	myDragger.dragComponent (this, e, nullptr);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkBubbleComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="1" initialWidth="32" initialHeight="32">
  <BACKGROUND backgroundColour="0">
    <ELLIPSE pos="2 2 4M 4M" fill=" radial: 0C 0C, 0C 0, 0=0, 1=ff008000"
             hasStroke="1" stroke="3, mitered, butt" strokeColour=" radial: 0C 0C, 0C 125%, 0=ff00ff0b, 1=8000"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

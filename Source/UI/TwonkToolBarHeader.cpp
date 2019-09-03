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

#include "TwonkToolBarHeader.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "GraphEditorPanel.h"
#include "MainHostWindow.h"
#include "TwonkToolBar.h"

#include "Platform/TwonkPlatformSpecific.h"
//[/MiscUserDefs]

//==============================================================================
TwonkToolBarHeader::TwonkToolBarHeader (GraphEditorPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
	baseColour = Colours::darkgrey;
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (64, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkToolBarHeader::~TwonkToolBarHeader()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkToolBarHeader::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(getWidth() * 0.02f));
	g.setColour(baseColour.withAlpha(0.5f));
	g.fillPath(roundingHexagon);
	g.reduceClipRegion(roundingHexagon);
	g.fillCheckerBoard(getLocalBounds().toFloat(), 4.0f, 4.0f, Colours::red, Colours::red.darker());
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkToolBarHeader::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth()*0.5f, float_Pi*0.5f);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkToolBarHeader::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	dragger.startDraggingComponent(getParentComponent(), e);
    //[/UserCode_mouseDown]
}

void TwonkToolBarHeader::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	dragger.dragComponent(getParentComponent(), e, nullptr);
    //[/UserCode_mouseDrag]
}

void TwonkToolBarHeader::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
	if (auto *t = dynamic_cast<TwonkToolBar *>(getParentComponent()))
	{
		t->toggleMenu();
	}
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkToolBarHeader" componentName=""
                 parentClasses="public Component" constructorParams="GraphEditorPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="64"
                 initialHeight="64">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


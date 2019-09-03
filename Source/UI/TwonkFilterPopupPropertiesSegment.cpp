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

#include "TwonkFilterPopupPropertiesSegment.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "UI/MainHostWindow.h"
//[/MiscUserDefs]

//==============================================================================
TwonkFilterPopupPropertiesSegment::TwonkFilterPopupPropertiesSegment ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
	baseColour = Colours::red;
    //[/UserPreSize]

    setSize (256, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkFilterPopupPropertiesSegment::~TwonkFilterPopupPropertiesSegment()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkFilterPopupPropertiesSegment::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	g.setColour(baseColour.contrasting(0.1f).withAlpha(iconAlpha));
	g.drawImage(icon, getLocalBounds().toFloat().constrainedWithin(pieSegmentPath.getBounds()).reduced(iconScale), RectanglePlacement::onlyReduceInSize, true);

	g.setColour(baseColour.withAlpha(segmentIsDown ? 0.65f : (segmentHasMouseOver ? 0.45f : 0.2f)));
	g.fillPath(pieSegmentPath);
	g.setColour(baseColour);
	g.strokePath(pieSegmentPath, PathStrokeType(1.5f));
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkFilterPopupPropertiesSegment::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	pieSegmentPath.clear();
	pieSegmentPath.addPieSegment(getLocalBounds().reduced(6).toFloat(), -(SEGMENT_RADIUS * 0.5f), SEGMENT_RADIUS * 0.5f, 0.35f);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

bool TwonkFilterPopupPropertiesSegment::hitTest (int x, int y)
{
    //[UserCode_hitTest] -- Add your code here...
	if (pieSegmentPath.contains(Point<float>(x, y)))
		return true;
	else
		return false;
    //[/UserCode_hitTest]
}

void TwonkFilterPopupPropertiesSegment::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
	if (pieSegmentPath.contains(e.getPosition().toFloat()))
		segmentHasMouseOver = true;
	else
		segmentHasMouseOver = false;

	repaint();
    //[/UserCode_mouseMove]
}

void TwonkFilterPopupPropertiesSegment::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
	segmentHasMouseOver = false;
	repaint();
    //[/UserCode_mouseExit]
}

void TwonkFilterPopupPropertiesSegment::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (pieSegmentPath.contains(e.getPosition().toFloat()))
	{
		segmentIsDown = true;
		repaint();
		sendChangeMessage();
	}
	return;
    //[/UserCode_mouseDown]
}

void TwonkFilterPopupPropertiesSegment::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	segmentIsDown = false;
	repaint();
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkFilterPopupPropertiesSegment::setIcon(Image _icon, float _scale, float _alpha)
{
	icon = _icon;
	iconScale = _scale;
	iconAlpha = _alpha;
	repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkFilterPopupPropertiesSegment"
                 componentName="" parentClasses="public Component, public ChangeBroadcaster"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="256"
                 initialHeight="256">
  <METHODS>
    <METHOD name="hitTest (int x, int y)"/>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


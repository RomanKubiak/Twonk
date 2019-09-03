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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../../JuceLibraryCode/JuceHeader.h"

#define SEGMENT_RADIUS 0.89759790102342862372f
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkFilterPopupPropertiesSegment  : public Component,
                                           public ChangeBroadcaster
{
public:
    //==============================================================================
    TwonkFilterPopupPropertiesSegment ();
    ~TwonkFilterPopupPropertiesSegment();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setBaseColour(Colour _base) { baseColour = _base; repaint(); }
	void setIcon(Image _icon, float _scale, float _alpha);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    bool hitTest (int x, int y) override;
    void mouseMove (const MouseEvent& e) override;
    void mouseExit (const MouseEvent& e) override;
    void mouseDown (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Path pieSegmentPath;
	Colour baseColour;
	Image icon;
	float iconScale;
	float iconAlpha = 0.5f;
	bool segmentIsDown = false;
	bool segmentHasMouseOver = false;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterPopupPropertiesSegment)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


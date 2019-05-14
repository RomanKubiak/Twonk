/*
  ==============================================================================

    TwonkLookAndFeel.h
    Created: 14 May 2019 5:03:44pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TwonkLookAndFeel : public LookAndFeel_V4
{
	public:
		void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
		int getTextButtonWidthToFitText(TextButton &, int);
		Font getTextButtonFont(TextButton &, int);
		void drawButtonText(Graphics &, TextButton &, bool, bool);
		void drawDrawableButton (Graphics&, DrawableButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
		void drawTickBox (Graphics&, Component&, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
		void changeToggleButtonWidthToFitText (ToggleButton&);
		void drawToggleButton (Graphics&, ToggleButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
};
/*
  ==============================================================================

    TwonkLookAndFeel.cpp
    Created: 14 May 2019 5:03:44pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkLookAndFeel.h"

void TwonkLookAndFeel::drawButtonBackground (Graphics &g, Button &button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	float x = 0.0f, y = 0.0f, width = static_cast<float> (button.proportionOfWidth (1.0000f)), height = static_cast<float> (button.proportionOfHeight (1.0000f));
	Colour fillColour1 = Colour (backgroundColour), fillColour2 = Colour (0x00ffffff);
	//[UserPaintCustomArguments] Customize the painting arguments here..
	//[/UserPaintCustomArguments]
	g.setGradientFill (ColourGradient (fillColour1,
		static_cast<float> ((button.getWidth() / 2)) - 0.0f + x,
		static_cast<float> ((button.getHeight() / 2)) - 0.0f + y,
		fillColour2,
		static_cast<float> (button.proportionOfWidth (shouldDrawButtonAsDown ? 0.25f : 0.5000f)) - 0.0f + x,
		0.0f - 0.0f + y,
		true));
	g.fillEllipse (x, y, width, height);
}
int TwonkLookAndFeel::getTextButtonWidthToFitText(TextButton &b, int buttonHeight)
{
	return getTextButtonFont (b, buttonHeight).getStringWidth (b.getButtonText()) + buttonHeight;
}

Font TwonkLookAndFeel::getTextButtonFont(TextButton &, int buttonHeight)
{
	return Font (jmin (32.0f, buttonHeight * 0.8f));
}
void TwonkLookAndFeel::drawButtonText(Graphics &g, TextButton &button, bool, bool)
{
	Font font (getTextButtonFont (button, button.getHeight()));
	g.setFont (font);
	g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId : TextButton::textColourOffId) .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
	g.drawFittedText (button.getButtonText(), Rectangle<int>(0, 0, button.getWidth(), button.getHeight()), Justification::bottomRight, 1);
}

void TwonkLookAndFeel::drawDrawableButton (Graphics&, DrawableButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{

}
void TwonkLookAndFeel::drawTickBox (Graphics&, Component&, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{

}
void TwonkLookAndFeel::changeToggleButtonWidthToFitText (ToggleButton&)
{

}
void TwonkLookAndFeel::drawToggleButton (Graphics&, ToggleButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{

}
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
	auto cornerSize = 6.0f;
	auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

	auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
		.withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

	if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
		baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

	g.setColour (baseColour);

	if (button.isConnectedOnLeft() || button.isConnectedOnRight())
	{
		Path path;
		path.addRoundedRectangle (bounds.getX(), bounds.getY(),
			bounds.getWidth(), bounds.getHeight(),
			cornerSize, cornerSize,
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight(),
			!button.isConnectedOnLeft(),
			!button.isConnectedOnRight());

		g.fillPath (path);

		g.setColour (button.findColour (ComboBox::outlineColourId));
		g.strokePath (path, PathStrokeType (1.0f));
	}
	else
	{
		g.fillRoundedRectangle (bounds, cornerSize);

		g.setColour (button.findColour (ComboBox::outlineColourId));
		g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
	}
}
int TwonkLookAndFeel::getTextButtonWidthToFitText(TextButton &b, int buttonHeight)
{
	return getTextButtonFont (b, buttonHeight).getStringWidth (b.getButtonText()) + buttonHeight;
}

Font TwonkLookAndFeel::getTextButtonFont(TextButton &b, int buttonHeight)
{
	Typeface::Ptr ptr = Typeface::createSystemTypefaceFor(BinaryData::_60sekuntia_ttf, BinaryData::_60sekuntia_ttfSize);
	Font f = Font(ptr);
	f.setHeight(b.proportionOfHeight (0.5f));
	
	return (f);
}
void TwonkLookAndFeel::drawButtonText(Graphics &g, TextButton &button, bool, bool)
{
	Font font (getTextButtonFont (button, button.getHeight()));
	g.setFont (font);
	g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId : TextButton::textColourOffId) .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
	g.drawFittedText (button.getButtonText(), Rectangle<int>(0, 0, button.getWidth(), button.getHeight()), Justification::centred, 1);
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
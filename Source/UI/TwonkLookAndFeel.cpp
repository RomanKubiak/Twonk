/*
  ==============================================================================

    TwonkLookAndFeel.cpp
    Created: 16 Aug 2019 12:06:09pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkLookAndFeel.h"
#include "MainHostWindow.h"

void TwonkLookAndFeel::drawResizableFrame (Graphics &g, int w, int h, const BorderSize<int> &border)
{
	if (!border.isEmpty())
	{
		const Rectangle<int> fullSize (0, 0, w, h);
		auto centreArea = border.subtractedFrom (fullSize);

		g.saveState();
		g.excludeClipRegion (centreArea);

		g.setColour (Colour (0x50ffffff));
		g.drawRect (fullSize, 3);

		//g.setColour (Colour (0x19000000));
		//g.drawRect (centreArea.expanded (1, 1));

		g.restoreState();
	}
}

Font TwonkLookAndFeel::getTextButtonFont (TextButton&, int buttonHeight)
{
	Font f = getDefaultTwonkSansFont();
	return (f.withHeight(jmin (16.0f, buttonHeight * 0.6f)));
}

void TwonkLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
		.withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

	if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
		baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

	Path roundingHexagon;
	roundingHexagon.addPolygon(button.getLocalBounds().getCentre().toFloat(), 6, button.getWidth() * 0.5f, float_Pi*0.5f);
	g.setColour(baseColour);
	g.fillPath(roundingHexagon);
}

AlertWindow* TwonkLookAndFeel::createAlertWindow (const String& title, const String& message,
	const String& button1, const String& button2, const String& button3,
	AlertWindow::AlertIconType iconType,
	int numButtons, Component* associatedComponent)
{
	auto boundsOffset = 50;

	auto* aw = LookAndFeel_V2::createAlertWindow (title, message, button1, button2, button3,
		iconType, numButtons, associatedComponent);

	auto bounds = aw->getBounds();
	bounds = bounds.withSizeKeepingCentre (bounds.getWidth() + boundsOffset, bounds.getHeight() + boundsOffset);
	aw->setBounds (bounds);

	for (auto* child : aw->getChildren())
		if (auto* button = dynamic_cast<TextButton*> (child))
			button->setBounds (button->getBounds() + Point<int> (25, 40));

	return aw;
}

void TwonkLookAndFeel::drawAlertBox (Graphics& g, AlertWindow& alert,
	const Rectangle<int>& textArea, TextLayout& textLayout)
{
	auto cornerSize = 4.0f;

	g.setColour (alert.findColour (AlertWindow::outlineColourId));
	g.drawRoundedRectangle (alert.getLocalBounds().toFloat(), cornerSize, 2.0f);

	auto bounds = alert.getLocalBounds().reduced (1);
	g.reduceClipRegion (bounds);

	g.setColour (Colours::black);
	g.fillRoundedRectangle (bounds.toFloat(), cornerSize);

	auto iconSpaceUsed = 0;

	auto iconWidth = 80;
	auto iconSize = jmin (iconWidth + 50, bounds.getHeight() + 20);

	if (alert.containsAnyExtraComponents() || alert.getNumButtons() > 2)
		iconSize = jmin (iconSize, textArea.getHeight() + 50);

	Rectangle<int> iconRect (iconSize / -10, iconSize / -10,
		iconSize, iconSize);

	if (alert.getAlertType() != AlertWindow::NoIcon)
	{
		Path icon;
		char character;
		uint32 colour;

		if (alert.getAlertType() == AlertWindow::WarningIcon)
		{
			character = '!';

			icon.addTriangle (iconRect.getX() + iconRect.getWidth() * 0.5f, (float)iconRect.getY(),
				static_cast<float> (iconRect.getRight()), static_cast<float> (iconRect.getBottom()),
				static_cast<float> (iconRect.getX()), static_cast<float> (iconRect.getBottom()));

			icon = icon.createPathWithRoundedCorners (5.0f);
			colour = 0x66ff2a00;
		}
		else
		{
			colour = Colour (0xff00b0b9).withAlpha (0.4f).getARGB();
			character = alert.getAlertType() == AlertWindow::InfoIcon ? 'i' : '?';

			icon.addEllipse (iconRect.toFloat());
		}

		GlyphArrangement ga;
		ga.addFittedText ({ iconRect.getHeight() * 0.9f, Font::bold },
			String::charToString ((juce_wchar)(uint8)character),
			static_cast<float> (iconRect.getX()), static_cast<float> (iconRect.getY()),
			static_cast<float> (iconRect.getWidth()), static_cast<float> (iconRect.getHeight()),
			Justification::centred, false);
		ga.createPath (icon);

		icon.setUsingNonZeroWinding (false);
		g.setColour (Colour (colour));
		g.fillPath (icon);

		iconSpaceUsed = iconWidth;
	}

	g.setColour (alert.findColour (AlertWindow::textColourId));

	Rectangle<int> alertBounds (bounds.getX() + iconSpaceUsed, 30,
		bounds.getWidth(), bounds.getHeight() - getAlertWindowButtonHeight() - 20);

	textLayout.draw (g, alertBounds.toFloat());
}
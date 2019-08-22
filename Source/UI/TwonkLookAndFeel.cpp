/*
  ==============================================================================

    TwonkLookAndFeel.cpp
    Created: 16 Aug 2019 12:06:09pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkLookAndFeel.h"
#include "MainHostWindow.h"


void TwonkLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
	float sliderPos,
	float minSliderPos,
	float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{
	if (slider.isBar())
	{
		Colour sliderColour = slider.findColour (Slider::trackColourId);
		Colour thumbColour = slider.findColour (Slider::thumbColourId);
		float dashes[4] = { 4.0f, 4.0f };
		if (slider.isHorizontal())
		{
			g.setColour(sliderColour.withAlpha(0.5f));
			g.drawDashedLine(Line<float>(2, height / 2, width-2, height / 2), dashes, 2, height * 0.5f);
			g.drawRect(x, y + 2, width, height-4);

			g.setColour(sliderColour);

			if (sliderPos > height*0.5f)
				sliderPos = sliderPos - height;
			
			if (sliderPos <= minSliderPos)
				sliderPos = minSliderPos;

			g.setColour(thumbColour);
			g.drawRoundedRectangle(sliderPos, 0.0f, (float)height, (float)height, height * 0.15f, height*0.08f);

			g.setColour(thumbColour.withAlpha(0.7f));
			g.fillRect(sliderPos, 0.0f, (float)height, (float)height);
		}
		else
		{
			g.drawDashedLine(Line<float>(width/2, 0, width/2, height), dashes, 2, width * 0.8f);	
		}
		
		
	}
	else
	{
		auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
		auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

		auto trackWidth = jmin (6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

		Point<float> startPoint (slider.isHorizontal() ? x : x + width * 0.5f,
			slider.isHorizontal() ? y + height * 0.5f : height + y);

		Point<float> endPoint (slider.isHorizontal() ? width + x : startPoint.x,
			slider.isHorizontal() ? startPoint.y : y);

		Path backgroundTrack;
		backgroundTrack.startNewSubPath (startPoint);
		backgroundTrack.lineTo (endPoint);
		g.setColour (slider.findColour (Slider::backgroundColourId));
		g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

		Path valueTrack;
		Point<float> minPoint, maxPoint, thumbPoint;

		if (isTwoVal || isThreeVal)
		{
			minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
						 slider.isHorizontal() ? height * 0.5f : minSliderPos };

			if (isThreeVal)
				thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
							   slider.isHorizontal() ? height * 0.5f : sliderPos };

			maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
						 slider.isHorizontal() ? height * 0.5f : maxSliderPos };
		}
		else
		{
			auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
			auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

			minPoint = startPoint;
			maxPoint = { kx, ky };
		}

		auto thumbWidth = getSliderThumbRadius (slider);

		valueTrack.startNewSubPath (minPoint);
		valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
		g.setColour (slider.findColour (Slider::trackColourId));
		g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

		if (!isTwoVal)
		{
			g.setColour (slider.findColour (Slider::thumbColourId));
			g.fillEllipse (Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (isThreeVal ? thumbPoint : maxPoint));
		}

		if (isTwoVal || isThreeVal)
		{
			auto sr = jmin (trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
			auto pointerColour = slider.findColour (Slider::thumbColourId);

			if (slider.isHorizontal())
			{
				drawPointer (g, minSliderPos - sr,
					jmax (0.0f, y + height * 0.5f - trackWidth * 2.0f),
					trackWidth * 2.0f, pointerColour, 2);

				drawPointer (g, maxSliderPos - trackWidth,
					jmin (y + height - trackWidth * 2.0f, y + height * 0.5f),
					trackWidth * 2.0f, pointerColour, 4);
			}
			else
			{
				drawPointer (g, jmax (0.0f, x + width * 0.5f - trackWidth * 2.0f),
					minSliderPos - trackWidth,
					trackWidth * 2.0f, pointerColour, 1);

				drawPointer (g, jmin (x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
					trackWidth * 2.0f, pointerColour, 3);
			}
		}
	}
}

void TwonkLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,float /*sliderPos*/,float /*minSliderPos*/,float /*maxSliderPos*/,const Slider::SliderStyle /*style*/, Slider& slider)
{
}

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
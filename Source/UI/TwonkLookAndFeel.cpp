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
		
		float dashes[4] = { 4.0f, 4.0f };
		if (slider.isHorizontal())
		{
			g.setColour(sliderColour.withAlpha(0.5f));
			g.drawDashedLine(Line<float>(4, height / 2, width-2, height / 2), dashes, 2, height * 0.5f);
			g.drawRect(x, y + 2, width, height-4);

			g.setColour(sliderColour);

			if (sliderPos > height*0.5f)
				sliderPos = sliderPos - height;
			
			if (sliderPos <= minSliderPos)
				sliderPos = minSliderPos;

			g.drawRoundedRectangle(sliderPos, 0.0f, (float)height, (float)height, height * 0.15f, height*0.08f);

			g.setColour(sliderColour.withAlpha(0.7f));
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

void TwonkLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
	float /*sliderPos*/,
	float /*minSliderPos*/,
	float /*maxSliderPos*/,
	const Slider::SliderStyle /*style*/, Slider& slider)
{
	const float sliderRadius = (float)(getSliderThumbRadius (slider) - 2);

	const Colour trackColour (slider.findColour (Slider::trackColourId));
	const Colour gradCol1 (trackColour.overlaidWith (Colour (slider.isEnabled() ? 0x13000000 : 0x09000000)));
	const Colour gradCol2 (trackColour.overlaidWith (Colour (0x06000000)));
	Path indent;

	if (slider.isHorizontal())
	{
		auto iy = y + height * 0.5f - sliderRadius * 0.5f;

		g.setGradientFill (ColourGradient::vertical (gradCol1, iy, gradCol2, iy + sliderRadius));

		indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius, 5.0f);
	}
	else
	{
		auto ix = x + width * 0.5f - sliderRadius * 0.5f;

		g.setGradientFill (ColourGradient::horizontal (gradCol1, ix, gradCol2, ix + sliderRadius));

		indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius, 5.0f);
	}

	g.fillPath (indent);

	g.setColour (trackColour.contrasting (0.5f));
	g.strokePath (indent, PathStrokeType (0.5f));
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

Font TwonkLookAndFeel::getLabelFont (Label &)
{
	return getDefaultTwonkMonoFont();
}
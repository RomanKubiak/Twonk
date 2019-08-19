/*
  ==============================================================================

    TwonkLookAndFeel.h
    Created: 16 Aug 2019 12:06:09pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
class TwonkLookAndFeel : public LookAndFeel_V4
{
	public:
		void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
			float sliderPos,
			float minSliderPos,
			float maxSliderPos,
			const Slider::SliderStyle style, Slider& slider);

		void drawLinearSliderBackground (Graphics&, int x, int y, int width, int height,
			float sliderPos, float minSliderPos, float maxSliderPos,
			const Slider::SliderStyle, Slider&);

		void drawResizableFrame (Graphics&, int w, int h, const BorderSize<int>&) override;

		//int getSliderThumbRadius (Slider&) override;
		Font getLabelFont (Label &);
		int getScrollbarButtonSize (ScrollBar &) { return (32); }
		int getDefaultScrollbarWidth () { return (32); }
};
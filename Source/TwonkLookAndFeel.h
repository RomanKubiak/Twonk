/*
  ==============================================================================

    TwonkLookAndFeel.h
    Created: 28 May 2019 3:13:25pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class TwonkFilterProperties : public LookAndFeel_V4
{
	public:
		void drawLinearSlider (Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &) override;
};

class TwonkFilterPropertiesEditor : public GenericAudioProcessorEditor
{
	public:
		TwonkFilterPropertiesEditor(AudioProcessor *owner);
	private:
		TwonkFilterProperties lf;
};
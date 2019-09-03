#pragma once
#include "../../../JuceLibraryCode/JuceHeader.h"

class FifteenStepHexStep  : public Button
{
	public:
		FifteenStepHexStep ();
		~FifteenStepHexStep();
		void paintButton(Graphics &g, bool, bool);
		void setIcon(Image _icon, float _shrink = 0.25f);
		void setBaseColour(Colour _baseColour) { baseColour = _baseColour; repaint(); }
		void setText(const String &test, Justification justificaion, float fontSize, double reduce);
		void setIconAlpha(const float _alpha) { iconAlpha = _alpha; repaint(); }
		bool hitTest(int x, int y) override;
		void resized() override;
		void setHighlited(bool _highlighted);
		void setHinted(bool _hinted);
		Colour getBaseColour() { return baseColour; }
	private:
		Colour baseColour = Colours::red;
		Path roundingHexagon;
		Image icon;
		String text;
		Justification justification = Justification::centred;
		float iconShrink;
		float fontSize;
		bool highlighted = false;
		bool hinted = false;
		float iconAlpha = 1.0f;
		double reduce;
		int index;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FifteenStepHexStep)
};
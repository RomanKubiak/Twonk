#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

/*
 *	A button that controls the toolbar
 */
class TwonkToolBarController : public Button
{
public:
	TwonkToolBarController();
	~TwonkToolBarController();
	void paintButton(Graphics &g, bool, bool) override;
	void triggerClick();
	void resized();

private:
	Path roundingHexagon;
	Colour baseColour;
	Image filterImage;
};

class TwonkToolBarButton : public Button
{
	public:
		TwonkToolBarButton ();
		~TwonkToolBarButton();
		void paintButton(Graphics &g, bool, bool);
		void setIcon(Image _icon, float _shrink = 0.25f);
		void setBaseColour(Colour _baseColour) { baseColour = _baseColour;  }
		void resized() override;
		void setText(const String &test, Justification justificaion, float fontSize, double reduce);
	private:
		Colour baseColour;
		Path roundingHexagon;
		Image icon;
		String text;
		Justification justification;
		float iconShrink;
		float fontSize;
		double reduce;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkToolBarButton)
};


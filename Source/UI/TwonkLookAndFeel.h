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
		TwonkLookAndFeel();
		void drawResizableFrame (Graphics&, int w, int h, const BorderSize<int>&) override;
		int getScrollbarButtonSize (ScrollBar &) { return (32); }
		int getDefaultScrollbarWidth () { return (32); }
		Font getTextButtonFont (TextButton&, int buttonHeight);
		void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);

		AlertWindow* createAlertWindow (const String& title, const String& message,
			const String& button1, const String& button2, const String& button3,
			AlertWindow::AlertIconType iconType,
			int numButtons, Component* associatedComponent);

		void drawAlertBox (Graphics& g, AlertWindow& alert,
			const Rectangle<int>& textArea, TextLayout& textLayout);

		Font getPopupMenuFont () override;

		void drawPopupMenuBackground (Graphics& g, int width, int height) override;

		int getPopupMenuBorderSize() override;

		void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
			const bool isSeparator, const bool isActive,
			const bool isHighlighted, const bool isTicked,
			const bool hasSubMenu, const String& text,
			const String& shortcutKeyText,
			const Drawable* icon, const Colour* const textColourToUse) override;

		void drawPointer (Graphics& g, const float x, const float y, const float diameter,
			const Colour& colour, const int direction) noexcept;

		void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
			float sliderPos,
			float minSliderPos,
			float maxSliderPos,
			const Slider::SliderStyle style, Slider& slider) override;

		int getSliderThumbRadius (Slider& slider) override;

		void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
			float /*sliderPos*/,
			float /*minSliderPos*/,
			float /*maxSliderPos*/,
			const Slider::SliderStyle /*style*/, Slider& slider) override;

		void drawConcertinaPanelHeader (Graphics& g, const Rectangle<int>& area,
			bool isMouseOver, bool /*isMouseDown*/,
			ConcertinaPanel& concertina, Component& panel) override;

		Font getComboBoxFont (ComboBox& box);

		void positionComboBoxText (ComboBox& box, Label& label);
};
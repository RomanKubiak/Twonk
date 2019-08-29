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
};
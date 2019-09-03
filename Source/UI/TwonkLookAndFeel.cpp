/*
  ==============================================================================

    TwonkLookAndFeel.cpp
    Created: 16 Aug 2019 12:06:09pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkLookAndFeel.h"
#include "MainHostWindow.h"

TwonkLookAndFeel::TwonkLookAndFeel()
{
	setColour(PopupMenu::highlightedBackgroundColourId, Colours::turquoise.withAlpha(0.5f));
	setColour(PopupMenu::backgroundColourId, Colours::black.brighter(0.1f));
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

Font TwonkLookAndFeel::getComboBoxFont (ComboBox& box)
{
	
	return getDefaultTwonkSansFont().withHeight(jmin (16.0f, box.getHeight() * 0.85f));
}

void TwonkLookAndFeel::positionComboBoxText (ComboBox& box, Label& label)
{
	label.setBounds (1, 1,
		box.getWidth() - 30,
		box.getHeight() - 2);

	label.setFont (getComboBoxFont (box));
}

Font TwonkLookAndFeel::getPopupMenuFont()
{
	return (getDefaultTwonkSansFont().withHeight(18.0f));
}

void TwonkLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
	//g.setTiledImageFill(IMG(popup_bg_png), 0, 0, 1.0f);
	//g.fillAll();
	
	g.setColour(findColour (PopupMenu::backgroundColourId));
	g.fillRect(0.0f, 0.0f, (float)width, (float)height);

	g.setColour(findColour (PopupMenu::backgroundColourId).brighter(0.7f));
	g.drawRect(1.0f, 1.0f, (float)width-2, (float)height-2, 1.5f);

	ignoreUnused (width, height);
}

int TwonkLookAndFeel::getPopupMenuBorderSize()
{
	return (2);
}

void TwonkLookAndFeel::drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
	const bool isSeparator, const bool isActive,
	const bool isHighlighted, const bool isTicked,
	const bool hasSubMenu, const String& text,
	const String& shortcutKeyText,
	const Drawable* icon, const Colour* const textColourToUse)
{
	if (isSeparator)
	{
		auto r = area.reduced (5, 0);
		r.removeFromTop (r.getHeight() / 2 - 1);

		g.setColour (Colour (0x33000000));
		g.fillRect (r.removeFromTop (1));

		g.setColour (Colour (0x66ffffff));
		g.fillRect (r.removeFromTop (1));
	}
	else
	{
		auto textColour = findColour (PopupMenu::textColourId);

		if (textColourToUse != nullptr)
			textColour = *textColourToUse;

		auto r = area.reduced (1);

		if (isHighlighted)
		{
			g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
			g.fillRect (r);

			g.setColour (findColour (PopupMenu::highlightedTextColourId));
		}
		else
		{
			g.setColour (textColour);
		}

		if (!isActive)
			g.setOpacity (0.3f);

		Font font (getPopupMenuFont());

		auto maxFontHeight = area.getHeight() / 1.3f;

		if (font.getHeight() > maxFontHeight)
			font.setHeight (maxFontHeight);

		g.setFont (font);

		auto iconArea = r.removeFromLeft ((r.getHeight() * 5) / 4).reduced (3).toFloat();

		if (icon != nullptr)
		{
			icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
		}
		else if (isTicked)
		{
			auto tick = getTickShape (1.0f);
			g.fillPath (tick, tick.getTransformToScaleToFit (iconArea, true));
		}

		if (hasSubMenu)
		{
			auto arrowH = 0.6f * getPopupMenuFont().getAscent();

			auto x = (float)r.removeFromRight ((int)arrowH).getX();
			auto halfH = (float)r.getCentreY();

			Path p;
			p.addTriangle (x, halfH - arrowH * 0.5f,
				x, halfH + arrowH * 0.5f,
				x + arrowH * 0.6f, halfH);

			g.fillPath (p);
		}

		r.removeFromRight (3);
		g.drawFittedText (text, r, Justification::centredLeft, 1);

		if (shortcutKeyText.isNotEmpty())
		{
			Font f2 (font);
			f2.setHeight (f2.getHeight() * 0.75f);
			f2.setHorizontalScale (0.95f);
			g.setFont (f2);

			g.drawText (shortcutKeyText, r, Justification::centredRight, true);
		}
	}
}

int TwonkLookAndFeel::getSliderThumbRadius (Slider& slider)
{
	return slider.isHorizontal() ? static_cast<int> (slider.getHeight() * 0.45f) : static_cast<int> (slider.getWidth()  * 0.45f);
}

void TwonkLookAndFeel::drawPointer (Graphics& g, const float x, const float y, const float diameter,
	const Colour& colour, const int direction) noexcept
{
	Path p;
	p.startNewSubPath (x + diameter * 0.5f, y);
	p.lineTo (x + diameter, y + diameter * 0.6f);
	p.lineTo (x + diameter, y + diameter);
	p.lineTo (x, y + diameter);
	p.lineTo (x, y + diameter * 0.6f);
	p.closeSubPath();

	p.applyTransform (AffineTransform::rotation (direction * MathConstants<float>::halfPi,
		x + diameter * 0.5f, y + diameter * 0.5f));
	g.setColour (colour);
	g.fillPath (p);
}

void TwonkLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
	float sliderPos,
	float minSliderPos,
	float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{
	if (slider.isBar())
	{
		g.setColour (slider.findColour (Slider::trackColourId));
		g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
			: Rectangle<float> (x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
	}
	else
	{
		auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
		auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

		auto trackWidth = slider.isHorizontal() ? height * 0.35f : width * 0.35f;

		Point<float> startPoint (slider.isHorizontal() ? x : x + width * 0.5f,
			slider.isHorizontal() ? y + height * 0.5f : height + y);

		Point<float> endPoint (slider.isHorizontal() ? width + x : startPoint.x,
			slider.isHorizontal() ? startPoint.y : y);

		/* this is the background drawn
		*/
		//Path backgroundTrack;
		//backgroundTrack.startNewSubPath (startPoint);
		//backgroundTrack.lineTo (endPoint);
		g.setColour (slider.findColour (Slider::backgroundColourId));
		//g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::butt });
		float dashes[] = { trackWidth  * 0.25f, trackWidth  * 0.25f };
		g.drawDashedLine(Line<float>(startPoint, endPoint), dashes, 2, trackWidth, 0);

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

		/* this fills the background tracking the value */
		//valueTrack.startNewSubPath (minPoint);
		//valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
		//g.setColour (slider.findColour (Slider::trackColourId));
		//g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });
		g.setColour (slider.findColour (Slider::trackColourId));
		g.drawDashedLine(Line<float>(minPoint, isThreeVal ? thumbPoint : maxPoint), dashes, 2, trackWidth, 0);

		if (!isTwoVal)
		{
			
			Path thumb;
			thumb.addPolygon(isThreeVal ? thumbPoint : maxPoint, 6, thumbWidth, float_Pi*0.5f);
			g.setColour (slider.findColour (Slider::thumbColourId).withAlpha(0.55f));
			g.fillPath(thumb);
			g.setColour (slider.findColour (Slider::thumbColourId));
			g.strokePath(thumb, PathStrokeType(thumbWidth * 0.08f));
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

class TwonkLookAndFeel::SliderLabelComp : public Label
{
public:
	SliderLabelComp() : Label ({}, {}) {}

	void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override {}
};

Label* TwonkLookAndFeel::createSliderTextBox (Slider& slider)
{
	auto l = new TwonkLookAndFeel::SliderLabelComp();
	l->setFont(getDefaultTwonkMonoFont());
	l->setJustificationType (Justification::centred);
	l->setKeyboardType (TextInputTarget::decimalKeyboard);

	l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));
	l->setColour (Label::backgroundColourId,
		(slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
		? Colours::transparentBlack
		: slider.findColour (Slider::textBoxBackgroundColourId));
	l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
	l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));
	l->setColour (TextEditor::backgroundColourId,
		slider.findColour (Slider::textBoxBackgroundColourId)
		.withAlpha ((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
			? 0.7f : 1.0f));
	l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
	l->setColour (TextEditor::highlightColourId, slider.findColour (Slider::textBoxHighlightColourId));

	return l;
}

void TwonkLookAndFeel::drawConcertinaPanelHeader (Graphics& g, const Rectangle<int>& area,
	bool isMouseOver, bool /*isMouseDown*/,
	ConcertinaPanel& concertina, Component& panel)
{
	auto bounds = area.toFloat().reduced (0.5f);
	auto cornerSize = 4.0f;
	auto isTopPanel = (concertina.getPanel (0) == &panel);

	Path p;
	p.addRoundedRectangle (bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(),
		cornerSize, cornerSize, isTopPanel, isTopPanel, false, false);

	g.setGradientFill (ColourGradient::vertical (Colours::white.withAlpha (isMouseOver ? 0.4f : 0.2f), static_cast<float> (area.getY()),
		Colours::darkgrey.withAlpha (0.1f), static_cast<float> (area.getBottom())));
	g.fillPath (p);
	g.setColour(Colours::white);
	g.setFont(getDefaultTwonkSansFont().withHeight(bounds.getHeight() * 0.7f));
	g.drawText(panel.getName(), bounds.withLeft(8), Justification::left);
}

void TwonkLookAndFeel::drawBubble (Graphics& g, BubbleComponent& comp, const Point<float>& tip, const Rectangle<float>& body)
{
	Path p;

	p.addBubble (body.reduced (0.5f), body.getUnion (Rectangle<float> (tip.x, tip.y, 1.0f, 1.0f)),
		tip, 5.0f, jmin (15.0f, body.getWidth() * 0.2f, body.getHeight() * 0.2f));

	g.setColour (comp.findColour (BubbleComponent::backgroundColourId));
	g.fillPath (p);

	g.setColour (comp.findColour (BubbleComponent::outlineColourId));
	g.strokePath (p, PathStrokeType (1.0f));
}
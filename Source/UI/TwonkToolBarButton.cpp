#include "TwonkToolBarButton.h"
#include "Twonk.h"
#include "MainHostWindow.h"
TwonkToolBarButton::TwonkToolBarButton () : Button(String()), justification(Justification::centredBottom)
{
	baseColour = Colours::red;
    setSize (64, 64);
}

TwonkToolBarButton::~TwonkToolBarButton()
{
}

void TwonkToolBarButton::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.5f, float_Pi*0.5f);
}

void TwonkToolBarButton::paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	g.setColour(baseColour.contrasting(0.1f));
	g.drawImage(icon, getLocalBounds().toFloat().reduced(getWidth() * iconShrink), RectanglePlacement::stretchToFit, true);
	g.setColour(baseColour.withAlpha(shouldDrawButtonAsDown ? 0.5f : 0.2f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(getWidth() * 0.02f));
	g.setColour(baseColour.contrasting(0.2f));
	g.setFont(getDefaultTwonkSansFont().withHeight(fontSize));
	g.drawText(text, getLocalBounds().reduced(reduce), justification, true);
}

void TwonkToolBarButton::setText(const String &_text, Justification _justification, float _fontSize, double _reduce)
{
	text = _text;
	justification = _justification;
	fontSize = _fontSize;
	reduce = _reduce;
	repaint();
}

void TwonkToolBarButton::setIcon(Image _icon, float shrink)
{
	icon = _icon;
	iconShrink = shrink;
}
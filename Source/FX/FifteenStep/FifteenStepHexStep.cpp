#include "FifteenStepHexStep.h"
#include "UI/MainHostWindow.h"

FifteenStepHexStep::FifteenStepHexStep ()
	: Button(String())
{
	setSize (48, 48);
}

FifteenStepHexStep::~FifteenStepHexStep()
{
}

void FifteenStepHexStep::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.47f, float_Pi*0.5f);
}

void FifteenStepHexStep::paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	g.reduceClipRegion(roundingHexagon);
	if (icon.isValid())
	{
		g.setColour(baseColour.contrasting(0.1f).withAlpha(iconAlpha));
		g.drawImage(icon, getLocalBounds().toFloat().reduced(getWidth() * iconShrink), RectanglePlacement::stretchToFit, true);
	}
	g.setColour(baseColour.withAlpha((getToggleState() || shouldDrawButtonAsDown) ? 0.8f : (shouldDrawButtonAsHighlighted ? 0.55f : 0.35f)));
	g.fillPath(roundingHexagon);

	g.setColour(highlighted ? baseColour.brighter(0.7f) : (baseColour.darker((getToggleState() || shouldDrawButtonAsDown) ? 0.5f : 0.0f)));
	g.strokePath(roundingHexagon, PathStrokeType(getWidth() * (highlighted ? 0.15f : (hinted ? 0.085f : 0.03f))));
	
	if (text.isNotEmpty())
	{
		g.setColour(baseColour.contrasting(0.5f));
		g.setFont(getDefaultTwonkSansFont().withHeight(fontSize));
		g.drawText(text, getLocalBounds().reduced(reduce), justification, true);
	}
}

void FifteenStepHexStep::setText(const String &_text, Justification _justification, float _fontSize, double _reduce)
{
	text = _text;
	justification = _justification;
	fontSize = _fontSize;
	reduce = _reduce;
	repaint();
}

void FifteenStepHexStep::setIcon(Image _icon, float shrink)
{
	icon = _icon;
	iconShrink = shrink;
	repaint();
}

bool FifteenStepHexStep::hitTest(int x, int y)
{
	return roundingHexagon.contains(Point<float>(x, y));
}

void FifteenStepHexStep::setHighlited(bool _highlighted)
{
	highlighted = _highlighted;
	repaint();
}

void FifteenStepHexStep::setHinted(bool _hinted)
{
	hinted = _hinted;
	repaint();
}
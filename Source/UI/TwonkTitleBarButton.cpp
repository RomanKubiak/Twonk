#include "TwonkTitleBarButton.h"
#include "Twonk.h"
TwonkTitleBarButton::TwonkTitleBarButton () : Button("toolbar")
{
	baseColour = Colours::red;
    setSize (64, 64);
}

TwonkTitleBarButton::~TwonkTitleBarButton()
{
}

void TwonkTitleBarButton::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, TOOLBAR_BUTTON_SIZE * 0.45f, float_Pi*0.5f);
}

void TwonkTitleBarButton::paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	g.setColour(baseColour.contrasting(0.5f));
	g.setFont(getDefaultTwonkSansFont());
	g.setColour(baseColour.contrasting(0.1f));
	g.drawImage(icon, getLocalBounds().toFloat().reduced(TOOLBAR_BUTTON_SIZE * 0.25f), RectanglePlacement::stretchToFit, true);
	g.setColour(baseColour.withAlpha(shouldDrawButtonAsDown ? 0.5f : 0.2f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(TOOLBAR_BUTTON_SIZE * 0.02f));

}

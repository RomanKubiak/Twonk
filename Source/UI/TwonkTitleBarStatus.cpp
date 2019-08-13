/*
  ==============================================================================

    TwonkTitleBarStatus.cpp
    Created: 12 Aug 2019 10:54:52pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkTitleBarStatus.h"
#include "Twonk.h"
TwonkTitleBarStatus::TwonkTitleBarStatus()
{
	baseColour = Colours::darkgrey;
	statusLabel.reset(new Label("statusLabel"));
	addAndMakeVisible(statusLabel.get());
	statusLabel->setFont(getDefaultTwonkMonoFont());
	statusLabel->setText("00:00:00", dontSendNotification);
}

TwonkTitleBarStatus::~TwonkTitleBarStatus()
{

}

void TwonkTitleBarStatus::paint(Graphics &g)
{
	g.setColour(baseColour.contrasting(0.5f));
	g.setFont(getDefaultTwonkSansFont());
	g.setColour(baseColour.withAlpha(0.3f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(TOOLBAR_BUTTON_SIZE * 0.02f));
}

void TwonkTitleBarStatus::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addRectangle(getLocalBounds());
	statusLabel->setBounds(getLocalBounds());
}
/*
  ==============================================================================

    TwonkTitleBarStatus.cpp
    Created: 12 Aug 2019 10:54:52pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkToolBarStatus.h"
#include "Twonk.h"

TwonkToolBarStatus::TwonkToolBarStatus()
{
	baseColour = Colours::darkgrey;
	statusLabel.reset(new Label("statusLabel"));
	addAndMakeVisible(statusLabel.get());
	statusLabel->setFont(getDefaultTwonkMonoFont());
	statusLabel->setText("00:00:00", dontSendNotification);
}

TwonkToolBarStatus::~TwonkToolBarStatus()
{

}

void TwonkToolBarStatus::paint(Graphics &g)
{
	g.setColour(baseColour.contrasting(0.5f));
	g.setFont(getDefaultTwonkSansFont());
	g.setColour(baseColour.withAlpha(0.3f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(TOOLBAR_BUTTON_SIZE * 0.02f));
}

void TwonkToolBarStatus::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addRectangle(getLocalBounds());
	statusLabel->setBounds(getLocalBounds());
}
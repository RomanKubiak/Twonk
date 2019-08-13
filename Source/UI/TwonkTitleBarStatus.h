/*
  ==============================================================================

    TwonkTitleBarStatus.h
    Created: 12 Aug 2019 10:54:52pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class TwonkTitleBarStatus : public Component
{
public:
	TwonkTitleBarStatus();
	~TwonkTitleBarStatus();
	void paint(Graphics &g);
	void resized();
private:
	Path roundingHexagon;
	Colour baseColour;
	std::unique_ptr <Label> statusLabel;
};
/*
  ==============================================================================

    TwonkPlayHead.cpp
    Created: 26 Jun 2019 2:22:01pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkPlayHead.h"
#include <chrono>

TwonkPlayHead::TwonkPlayHead(AudioDeviceManager &_dm) 
	: dm(_dm), bpm(120), currentStep(0), firstStep(0), lengthSteps(16),
	clockCount(0)
{
	DBG("TwonkPlayHead::ctor");	
	reset();
}

TwonkPlayHead::~TwonkPlayHead()
{
	stopTimer();
}

double TwonkPlayHead::getTempo()
{
	return (bpm);
}

void TwonkPlayHead::reset()
{
	stopTimer();
	currentStep = firstStep;
	clockCount = 0;
	startTimer(60000 / (bpm * 24));
}

void TwonkPlayHead::setTempo(const double _bpm)
{
	bpm = _bpm;
	reset();
}

bool TwonkPlayHead::getCurrentPosition(CurrentPositionInfo &result)
{
	result.bpm = getTempo();
	result.isLooping = true;
	return (true);
}

void TwonkPlayHead::stop()
{
	stopTimer();
}

void TwonkPlayHead::toggle(const bool pause)
{
	if (pause)
	{
		stopTimer();
	}
	else
	{
		startTimer(60000 / (bpm * 24));
	}
}

void TwonkPlayHead::setExternalSync(const bool _shouldSync)
{
}

void TwonkPlayHead::addClockListener(TwonkClockListener *listenerToAdd)
{
	listeners.add(listenerToAdd);
}
void TwonkPlayHead::removeClockListener(TwonkClockListener *listenerToRemove)
{
	listeners.remove(listenerToRemove);
}

void TwonkPlayHead::hiResTimerCallback()
{
	clockCount++;
	if (clockCount == 24)
	{
		clockCount = 0;
		currentStep++;
		if (currentStep == (lengthSteps-1))
			currentStep = firstStep;
	}

	triggerAsyncUpdate();
}

void TwonkPlayHead::handleAsyncUpdate()
{
	const int tmp = currentStep;
	if (currentStep != previousStep)
	{
		listeners.call ([tmp](TwonkClockListener& l) { l.stepIncrement (tmp); });
		previousStep = currentStep;
	}
}
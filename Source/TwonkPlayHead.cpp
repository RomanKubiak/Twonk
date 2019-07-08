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
	: dm(_dm),  sampleRate(44100)
{
	DBG("TwonkPlayHead::ctor");
	currentPostion.timeSigNumerator = 4;
	currentPostion.timeSigDenominator = 4;
	currentPostion.isLooping = true;
	currentPostion.isRecording = false;
	currentPostion.ppqLoopEnd = 0;
	currentPostion.ppqLoopStart = 0;
	dm.addAudioCallback(this);
	reset(false);
}

TwonkPlayHead::~TwonkPlayHead()
{
	dm.removeAudioCallback(this);
}

void TwonkPlayHead::audioDeviceStopped()
{
	reset(false);
}

void TwonkPlayHead::audioDeviceAboutToStart (AudioIODevice *iodev)
{
	if (iodev->isOpen())
	{
		ScopedLock sl(cs);
		currentPostion.timeInSeconds = 0.0;
		currentPostion.timeInSamples = 0.0;
		sampleRate = iodev->getCurrentSampleRate();
	}
}

void TwonkPlayHead::audioDeviceIOCallback (const float **in, int numIn, float **outputChannelData, int numOutputChannels, int numSamples)
{
	if (currentPostion.isPlaying)
	{
		ScopedLock sl(cs);
		currentPostion.timeInSeconds += (double)(numSamples / sampleRate);
		currentPostion.timeInSamples += numSamples;
		currentPostion.ppqPosition = (currentPostion.timeInSamples / sampleRate) * currentPostion.bpm / 60.0L;
	}

	for (int i = 0; i < numOutputChannels; ++i)
		FloatVectorOperations::clear (outputChannelData[i], numSamples);

	triggerAsyncUpdate();
}

void TwonkPlayHead::setTempo(const double bpm)
{
	ScopedLock sl(cs);
	currentPostion.bpm = bpm;
}

void TwonkPlayHead::reset(const bool startNow)
{
	ScopedLock sl(cs);
	currentPostion.isPlaying = startNow;
	currentPostion.timeInSamples = 0.0;
	currentPostion.ppqPosition = 0.0;
}

bool TwonkPlayHead::getCurrentPosition(CurrentPositionInfo &result)
{
	ScopedLock sl(cs);
	result = currentPostion;
	return (true);
}

void TwonkPlayHead::stop()
{
	DBG("TwonkPlayHead::stop");
	reset(false);
	triggerAsyncUpdate();
}

void TwonkPlayHead::play(const bool _isPlaying)
{
	DBG("TwonkPlayHead::play");
	reset(true);
	triggerAsyncUpdate();
}

void TwonkPlayHead::addClockListener(TwonkClockListener *listenerToAdd)
{
	listeners.add(listenerToAdd);
}
void TwonkPlayHead::removeClockListener(TwonkClockListener *listenerToRemove)
{
	listeners.remove(listenerToRemove);
}

void TwonkPlayHead::handleAsyncUpdate()
{
	AudioPlayHead::CurrentPositionInfo pos;
	getCurrentPosition(pos);
	listeners.call ([pos](TwonkClockListener& l) { l.positionChanged(pos); });
}
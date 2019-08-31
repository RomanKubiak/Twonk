#include "JuceHeader.h"
#include "TwonkPlayHead.h"
#include <chrono>

TwonkPlayHead::TwonkPlayHead(AudioDeviceManager &_dm) 
	: dm(_dm),  sampleRate(44100)
{
	DBG("TwonkPlayHead::ctor");
	currentPostion.timeSigNumerator = 4;
	currentPostion.timeSigDenominator = 4;
	currentPostion.isLooping = false;
	currentPostion.isRecording = false;
	currentPostion.ppqLoopEnd = 0;
	currentPostion.ppqLoopStart = 0;
	currentPostion.bpm = 120;
	currentPostion.isPlaying = false;
	dm.addAudioCallback(this);
	reset();
}

TwonkPlayHead::~TwonkPlayHead()
{
	dm.removeAudioCallback(this);
}

void TwonkPlayHead::audioDeviceStopped()
{
	ScopedLock sl(cs);
	reset();
	currentPostion.isPlaying = false;
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

const double TwonkPlayHead::getTempo() const
{
	ScopedLock sl(cs);
	return (currentPostion.bpm);
}

void TwonkPlayHead::reset()
{
	ScopedLock sl(cs);	
	currentPostion.timeInSamples = 0.0;
	currentPostion.timeInSeconds = 0.0;
	currentPostion.ppqPosition = 0.0;
}

bool TwonkPlayHead::getCurrentPosition(CurrentPositionInfo &result)
{
	ScopedLock sl(cs);
	result = currentPostion;
	return (true);
}

const bool TwonkPlayHead::isPlaying() const
{
	ScopedLock sl(cs);
	return (currentPostion.isPlaying);
}

void TwonkPlayHead::stop()
{
	DBG("TwonkPlayHead::stop");
	reset();
	ScopedLock sl(cs);
	currentPostion.isPlaying = false;

	triggerAsyncUpdate();
}

void TwonkPlayHead::pause()
{
	DBG("TwonkPlayHead::pause");
	ScopedLock sl(cs);
	currentPostion.isPlaying = false;
}

void TwonkPlayHead::play(const bool resetNow)
{
	DBG("TwonkPlayHead::play");
	if (resetNow)
		reset();
	ScopedLock sl(cs);
	currentPostion.isPlaying = true;

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
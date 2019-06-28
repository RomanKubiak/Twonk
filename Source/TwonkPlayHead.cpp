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
	: dm(_dm), bpm(60), sampleRate(44100), currentStep(0), firstStep(0), lengthSteps(16), clockCount(0), tickCount(0)
{
	DBG("TwonkPlayHead::ctor");
	
	dm.addAudioCallback(this);
	reset(false);
}

TwonkPlayHead::~TwonkPlayHead()
{
	dm.removeAudioCallback(this);
}

void TwonkPlayHead::audioDeviceAboutToStart (AudioIODevice *iodev)
{
	if (iodev->isOpen())
	{
		samplePosition = 0.0;
		timePassed = 0.0;
		sampleRate = iodev->getCurrentSampleRate();
	}
}

void TwonkPlayHead::audioDeviceStopped()
{
}

void TwonkPlayHead::audioDeviceIOCallback (const float **in, int numIn, float **outputChannelData, int numOutputChannels, int numSamples)
{
	
	timePassed += (double)(numSamples / sampleRate);
	samplePosition += numSamples;

	for (int i = 0; i < numOutputChannels; ++i)
		FloatVectorOperations::clear (outputChannelData[i], numSamples);
}

double TwonkPlayHead::getTempo()
{
	return (bpm);
}

void TwonkPlayHead::setTempo(const double _bpm)
{
	bpm = _bpm;
	midiClockInterval = 60.00 / (bpm * 24);
}

void TwonkPlayHead::reset(const bool startNow)
{
	quarterNotePosition = 0.0;
	samplePosition = 0.0;
	timePassed = 0.0;
	tickCount = 0.0;
	isPlaying = startNow;
}

void TwonkPlayHead::setLoopLength(const int _loopLength)
{
	loopLengthInPPQN = DEFAULT_PPQN * _loopLength;
}

bool TwonkPlayHead::getCurrentPosition(CurrentPositionInfo &result)
{
	/*
	static double fSmpteDiv[] =
  {
  24.f,
  25.f,
  24.f,
  30.f,
  29.97f,
  30.f
  };

double dPos = vstTimeInfo.samplePos / vstTimeInfo.sampleRate;
vstTimeInfo.ppqPos = dPos * vstTimeInfo.tempo / 60.L;
    
	double dOffsetInSecond = dPos - floor(dPos);
	vstTimeInfo.smpteOffset = (long)(dOffsetInSecond *
		fSmpteDiv[vstTimeInfo.smpteFrameRate] *
		80.L); 
	*/
	result.bpm = getTempo();
	result.isLooping = true;
	result.isRecording = false;
	result.timeInSamples = samplePosition;
	result.ppqPosition = (samplePosition / sampleRate) * bpm / 60.0L;
	result.isPlaying = isPlaying;
	result.timeSigNumerator = 4;
	result.timeSigDenominator = 4;
	result.ppqLoopEnd = loopLengthInPPQN;
	result.ppqLoopStart = 0;
	
	result.timeInSeconds = timePassed;
	return (true);
}

void TwonkPlayHead::stop()
{
	reset(false);
}

void TwonkPlayHead::play(const bool _isPlaying)
{
	isPlaying = _isPlaying;
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
	tickCount++;
	quarterNotePosition += tickCount;

	if ((quarterNotePosition / DEFAULT_PPQN) >= loopLengthInPPQN)
	{
		quarterNotePosition = 0.0;
		tickCount = 0.0;
	}

	triggerAsyncUpdate();
}

void TwonkPlayHead::handleAsyncUpdate()
{
	AudioPlayHead::CurrentPositionInfo pos;
	getCurrentPosition(pos);
	listeners.call ([pos](TwonkClockListener& l) { l.positionChanged(pos); });
}
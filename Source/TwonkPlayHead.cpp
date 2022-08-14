#include "JuceHeader.h"
#include "TwonkPlayHead.h"
#include <chrono>

TwonkPlayHead::TwonkPlayHead(AudioDeviceManager &_dm) 
	: dm(_dm),  sampleRate(44100)
{
	DBG("TwonkPlayHead::ctor");
    AudioPlayHead::TimeSignature ts;
    ts.numerator = 4;
    ts.denominator = 4;

	pi.setIsLooping(false);
    pi.setIsRecording(false);
    pi.setPpqPosition(0);
    pi.setBpm(120);
    pi.setIsPlaying(false);
    pi.setPpqPositionOfLastBarStart(0);
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
	pi.setIsPlaying(false);
}

void TwonkPlayHead::audioDeviceAboutToStart (AudioIODevice *iodev)
{
	if (iodev->isOpen())
	{
		ScopedLock sl(cs);
		pi.setTimeInSeconds(0.0);
        pi.setTimeInSamples(0.0);
		sampleRate = iodev->getCurrentSampleRate();
	}
}

void TwonkPlayHead::audioDeviceIOCallback (const float **in, int numIn, float **outputChannelData, int numOutputChannels, int numSamples)
{
	if (pi.getIsPlaying())
	{
		ScopedLock sl(cs);
        auto timeInSeconds = *pi.getTimeInSeconds() + (double)(numSamples / sampleRate);
        auto timeInSamples = *pi.getTimeInSamples() + numSamples;
        auto bpm = *pi.getBpm();

        pi.setTimeInSeconds( timeInSeconds );
        pi.setTimeInSamples( timeInSamples);

        pi.setPpqPosition((timeInSamples / sampleRate) * bpm / 60.0L);
	}

	for (int i = 0; i < numOutputChannels; ++i)
		FloatVectorOperations::clear (outputChannelData[i], numSamples);

	triggerAsyncUpdate();
}

void TwonkPlayHead::setTempo(const double bpm)
{
	ScopedLock sl(cs);
    pi.setBpm(bpm);
	// set offsets
	timeInSecondsOffset = *pi.getTimeInSeconds();
	ppqPositionOffset = *pi.getPpqPosition();
	timeInSamplesOffset = *pi.getTimeInSamples();
	reset();
}

const double TwonkPlayHead::getTempo() const
{
	ScopedLock sl(cs);
	return *pi.getBpm();
}

void TwonkPlayHead::reset()
{
	ScopedLock sl(cs);
    pi.setTimeInSamples(0.0);
    pi.setTimeInSeconds(timeInSecondsOffset);
    pi.setPpqPosition(ppqPositionOffset);
    pi.setPpqPositionOfLastBarStart(0);
}

Optional<AudioPlayHead::PositionInfo> TwonkPlayHead::getPosition() const
{
    ScopedLock sl(cs);
    PositionInfo pi;
    return pi;
}

const bool TwonkPlayHead::isPlaying() const
{
	ScopedLock sl(cs);
	return (pi.getIsPlaying());
}

void TwonkPlayHead::setLooping(const bool isLooping)
{
	ScopedLock sl(cs);
    pi.setIsLooping(isLooping);

	triggerAsyncUpdate();
}

void TwonkPlayHead::stop()
{
	reset();
	ScopedLock sl(cs);
	pi.setIsPlaying(false);

	triggerAsyncUpdate();
}

void TwonkPlayHead::pause()
{
	DBG("TwonkPlayHead::pause");
	ScopedLock sl(cs);
	pi.setIsPlaying(false);
}

void TwonkPlayHead::play(const bool resetNow)
{
	DBG("TwonkPlayHead::play");
	if (resetNow)
		reset();
	ScopedLock sl(cs);
	pi.setIsPlaying(true);

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
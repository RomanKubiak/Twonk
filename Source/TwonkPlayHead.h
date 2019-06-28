/*
  ==============================================================================

    TwonkPlayHead.h
    Created: 26 Jun 2019 2:22:01pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "Filters/FilterGraph.h"
#include "Filters/InternalFilters.h"
#define DEFAULT_PPQN 960.0

class TwonkClockListener
{
	public:
		virtual void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo) {}
};

class TwonkPlayHead : public AudioPlayHead, public AsyncUpdater, public AudioIODeviceCallback
{
	public:
		TwonkPlayHead(AudioDeviceManager &_dm);
		~TwonkPlayHead();
		bool getCurrentPosition(CurrentPositionInfo &result);
		double getTempo();
		void setTempo(const double _bpm);
		void stop();
		void play(const bool _isPlaying = true);
		void reset(const bool startNow = false);
		void setExternalSync(const bool _shouldSync);
		void addClockListener(TwonkClockListener *listenerToAdd);
		void removeClockListener(TwonkClockListener *listenerToRemove);
		void setLoopLength(const int loopLength);
		void hiResTimerCallback();
		void handleAsyncUpdate();

		//==============================================================================
		/** @internal */
		void audioDeviceIOCallback (const float **in, int numIn, float **outputChannelData, int numOutputChannels, int numSamples) override;
		/** @internal */
		void audioDeviceAboutToStart (AudioIODevice*) override;
		/** @internal */
		void audioDeviceStopped() override;
		/** @internal */
		void audioDeviceError (const String& errorMessage) override {}

	private:
		ListenerList<TwonkClockListener> listeners;
		int firstStep, lengthSteps, currentStep, previousStep;
		int clockCount, previousClockCount, midiClockIntervalInMs;
		double timePassed, midiClockInterval;
		int64 samplePosition;
		int midiResolution;
		double sampleRate;
		double bpm;
		bool isPlaying;
		AudioDeviceManager &dm;
		int64 startTime, currentTime;
		int loopLengthInPPQN;
		int currentStepInLoop;
		int quarterNotePosition;
		double tickCount;
};
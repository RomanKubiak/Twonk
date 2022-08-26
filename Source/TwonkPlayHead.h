/*
  ==============================================================================

    TwonkPlayHead.h
    Created: 26 Jun 2019 2:22:01pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "Twonk.h"

class TwonkClockListener
{
	public:
		virtual void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo) = 0;
};

class TwonkPlayHead : public AudioPlayHead, public AsyncUpdater, public AudioIODeviceCallback
{
	public:
		TwonkPlayHead(AudioDeviceManager &_dm);
		~TwonkPlayHead();
		// bool getCurrentPosition(CurrentPositionInfo &result);
        Optional<PositionInfo> getPosition() const;
		void setTempo(const double _bpm);
		const double getTempo() const;
		void stop();
		void play(const bool resetNow);
		const bool isPlaying() const;
		void pause();
		void reset();
		void setLooping(bool isLooping);
		void setExternalSync(const bool _shouldSync) { }
		void addClockListener(TwonkClockListener *listenerToAdd);
		void removeClockListener(TwonkClockListener *listenerToRemove);
		void setLoopLength(const int _loopLength) { currentPostion.ppqLoopEnd = _loopLength;  }
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
		CriticalSection cs;
		ListenerList<TwonkClockListener> listeners;		
		double sampleRate;
		AudioDeviceManager &dm;
		CurrentPositionInfo currentPostion;
		double timeInSecondsOffset = 0.0;
		double ppqPositionOffset = 0.0;
		double timeInSamplesOffset = 0.0;
};
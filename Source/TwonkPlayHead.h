/*
  ==============================================================================

    TwonkPlayHead.h
    Created: 26 Jun 2019 2:22:01pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "Twonk.h"
#include "Filters/InternalPlugins.h"


class TwonkClockListener
{
	public:
		virtual void positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo) = 0;
		virtual void transportStopped() {}
		virtual void transportStarted() {}
};

class TwonkPlayHead : public AudioPlayHead, public AsyncUpdater, public AudioIODeviceCallback
{
	public:
		TwonkPlayHead(AudioDeviceManager &_dm);
		~TwonkPlayHead();
		bool getCurrentPosition(CurrentPositionInfo &result);
		void setTempo(const double _bpm);
		void stop();
		void play(const bool _isPlaying = true);
		void reset(const bool startNow = false);
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
};
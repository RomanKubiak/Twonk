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

class TwonkClockListener
{
	public:
		virtual void midiTick(int midiClockCound) {}
		virtual void stepIncrement(int currentStep) {}
};

class TwonkPlayHead : public AudioPlayHead, public HighResolutionTimer, public AsyncUpdater
{
	public:
		TwonkPlayHead(AudioDeviceManager &_dm);
		~TwonkPlayHead();
		bool getCurrentPosition(CurrentPositionInfo &result);
		double getTempo();
		void setTempo(const double _bpm);
		void stop();
		void toggle(const bool pause = false);
		void reset();
		void setExternalSync(const bool _shouldSync);
		void addClockListener(TwonkClockListener *listenerToAdd);
		void removeClockListener(TwonkClockListener *listenerToRemove);
		void hiResTimerCallback();
		void handleAsyncUpdate();
	private:
		ListenerList<TwonkClockListener> listeners;
		int firstStep, lengthSteps, currentStep, previousStep;
		int clockCount, previousClockCount;
		int midiResolution;
		double bpm;
		bool isPaused;
		AudioDeviceManager &dm;
};
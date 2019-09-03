#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../PluginParameter.h"
#include "../../Filters/InternalPlugins.h"
#include "FifteenStep.h"

class FifteenStepProcessor : public TwonkPlugin
{
	public:
		FifteenStepProcessor(const PluginDescription& descr);
		~FifteenStepProcessor();
		void prepareToPlay (double sampleRate, int samplesPerBlock) override;
		void releaseResources() override;
		void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
		void getStateInformation (MemoryBlock& destData) override;
		void setStateInformation (const void* data, int sizeInBytes) override;
		AudioProcessorEditor* createEditor() override;
		bool hasEditor() const override { return (true); }
		const String getName() const override { return "FifteenStep"; }
		bool acceptsMidi() const override { return (true); }
		bool producesMidi() const override { return (true); }
		bool isMidiEffect () const override { return (true); }
		double getTailLengthSeconds() const override { return 0.0; };
		int getNumPrograms() override { return 1; };
		int getCurrentProgram() override { return 0; };
		void setCurrentProgram (int index) override {};
		const String getProgramName (int index) override { return {}; };
		void changeProgramName (int index, const String& newName) override {};
		MidiKeyboardState keyboardState;
		void handleNoteOn (MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) {}
		void handleNoteOff (MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) {}
		AudioPlayHead::CurrentPositionInfo lastPosInfo;
		int getLastStep() { return (lastPlayheadStep); }
		void updateSequencer(AudioPlayHead::CurrentPositionInfo &lastPosInfo, AudioSampleBuffer& buffer);
		double getPlayHeadColPrecise() { return (playheadColPrecise); }
	private:
		double currSampleRate;
		int playheadCol;
		int lastPlayheadStep;
		int speed; // playback speed multiplier
		FifteenStep fifteenStepInstance;
		int totalCols;
		double playheadColPrecise;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FifteenStepProcessor)
};

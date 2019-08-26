#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSampler.h"
#include "JucesamplerAudioProcessorEditor.h"
#include "Filters/InternalPlugins.h"

class JucesamplerAudioProcessor  : public TwonkPlugin
{
	public:
		JucesamplerAudioProcessor(const PluginDescription& descr);
		~JucesamplerAudioProcessor();
		void prepareToPlay (double sampleRate, int samplesPerBlock) override;
		void releaseResources() override;
		bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
		void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
		AudioProcessorEditor* createEditor() override;
		bool hasEditor() const override;
		const String getName() const override;
		bool acceptsMidi() const override;
		bool producesMidi() const override;
		bool isMidiEffect() const override;
		double getTailLengthSeconds() const override;
		int getNumPrograms() override;
		int getCurrentProgram() override;
		void setCurrentProgram (int index) override;
		const String getProgramName (int index) override;
		void changeProgramName (int index, const String& newName) override;
		void getStateInformation (MemoryBlock& destData) override;
		void setStateInformation (const void* data, int sizeInBytes) override;
		AudioProcessorValueTreeState& getValueTree() { return *valueTree; }
		CTAGSampler& getSampler() { return sampler; }
		OwnedArray<SamplerInstrument> &getInstrumentsArray() { return instrumentsLoaded; }
		void clearInstruments();
		void reloadInstruments();
		Result loadSamples(const File &bank, var &bankJsonInfo);
		void loadBank(const File &bank);
		MidiBuffer &getAdditionalMidiBuffer() { return additionalMessagesToConsider;  }
	private:
		OwnedArray<SamplerInstrument> instrumentsLoaded;
		CTAGSampler sampler;
		ScopedPointer<AudioProcessorValueTreeState> valueTree;
		ScopedPointer<UndoManager> undoManager;
		MidiBuffer additionalMessagesToConsider;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JucesamplerAudioProcessor)
};

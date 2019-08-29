#pragma once

#include "JuceHeader.h"
#include "Filters/InternalPlugins.h"
#include "SimplerSound.h"
#include "SimplerSynthesiser.h"

#define VOICES 16

struct SimplerInstrument
{
	String name;
	String velocityCurve;
	Array<File> fileList;
	int midiNote = 60;
	int midiChannel = 1;
	int audioOutputChannel = 0;
	Array<SimplerSound *> assosiatedSound;
};

class SimplerProcessor : public TwonkPlugin, public ChangeListener, public ChangeBroadcaster
{
	public:
		SimplerProcessor(const PluginDescription& descr);
		~SimplerProcessor();
		bool canAddBus    (bool isInput) const override { return (!isInput && getBusCount (false) < VOICES); }
		bool canRemoveBus (bool isInput) const override { return (!isInput && getBusCount (false) > 1); }
		void prepareToPlay (double newSampleRate, int samplesPerBlock) override;
		void releaseResources() override {}
		void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiBuffer) override;
		AudioProcessorEditor* createEditor() override;
		bool hasEditor() const override { return true; }
		const String getName() const override { return "Simpler"; }
		bool acceptsMidi() const override { return true; }
		bool producesMidi() const override { return false; }
		double getTailLengthSeconds() const override { return 0; }
		int getNumPrograms() override { return 1; }
		int getCurrentProgram() override { return 0; }
		void setCurrentProgram (int) override {}
		const String getProgramName (int) override { return {}; }
		void changeProgramName (int, const String&) override {}
		void getStateInformation (MemoryBlock&) override;
		void setStateInformation (const void*, int) override;
		AudioFormatManager &getFormatManager() { return formatManager; }
		const String createJsonFor(const File &bank);
		void loadBank(const File &bank);
		void loadBank(const int indexInArray) { loadBank(bankList[indexInArray]); }
		Result loadSamples(const File &bank, var &bankJsonInfo);
		void changeListenerCallback (ChangeBroadcaster* source);
		void reloadInstruments();
		const Array<File>& getBankList() { return bankList; }
		void addSoundToSampler(SimplerInstrument *instrumentToAdd);
		SimplerSynthesiser &getSampler() { return (sampler); }
		const OwnedArray<SimplerInstrument> &getLoadedInstruments() { return (instrumentsLoaded); }
		MidiBuffer &getAdditionalMidiMessageBuffer() { return(additionalMessagesToConsider); }
		AudioProcessorValueTreeState &getProcessorState() { return (processorState); }
	private:
		OwnedArray<SimplerInstrument> instrumentsLoaded;
		AudioFormatManager formatManager;
		MidiBuffer additionalMessagesToConsider;
		SimplerSynthesiser sampler;
		TimeSliceThread directoryThread { "Bank scanner thread" };
		WildcardFileFilter programFileFilter { "", "*.twonk", "bankList" };
		DirectoryContentsList programList { &programFileFilter, directoryThread };
		Array<File> bankList;
		File lastLoadedBank;
		AudioProcessorValueTreeState processorState;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplerProcessor)
};

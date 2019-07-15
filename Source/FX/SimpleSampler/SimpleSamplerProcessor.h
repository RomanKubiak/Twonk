/*
  ==============================================================================

    SimpleSamplerProcessor.h
    Created: 10 Jul 2019 6:16:31pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../../Filters/InternalFilters.h"

struct SoundParameters
{
	SoundParameters(int index, const String &soundName)
		: choiceParameter(soundName, soundName, choices, index)
	{}
	AudioParameterChoice choiceParameter;
	double attack;
	double release;
	double length;
	int channel;
	StringArray choices;
};

class SimpleSamplerProcessor : public InternalPlugin
{
	public:
		SimpleSamplerProcessor(const PluginDescription& descr);
		~SimpleSamplerProcessor();
		void prepareToPlay (double sampleRate, int samplesPerBlock) override;
		void releaseResources() override;
		void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
		void getStateInformation (MemoryBlock& destData) override;
		void setStateInformation (const void* data, int sizeInBytes) override;
		AudioProcessorEditor* createEditor() override;
		bool hasEditor() const override;
		#ifndef JucePlugin_PreferredChannelConfigurations
			bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
		#endif
		const String getName() const override;
		bool acceptsMidi() const override;
		bool producesMidi() const override;
		bool isMidiEffect () const override;
		double getTailLengthSeconds() const override;
		int getNumPrograms() override;
		int getCurrentProgram() override;
		void setCurrentProgram (int index) override;
		const String getProgramName (int index) override;
		void changeProgramName (int index, const String& newName) override;

	private:
		Array<File> programZipFiles;
		File programDir;
		ZipFile *currentProgramZip;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerProcessor)
};

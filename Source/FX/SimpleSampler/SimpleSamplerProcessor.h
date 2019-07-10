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

class TwonkSamplerSound : public SamplerSound
{
	public:
		TwonkSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLenthSecs);
		bool appliesToChannel(int midiChannel);
};

class TwonkSamplerSynth : public Synthesiser
{
	public:
		void setup();
	private:
		// manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
		AudioFormatManager audioFormatManager;
};

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
	//==============================================================================

	SimpleSamplerProcessor(const PluginDescription& descr);
	~SimpleSamplerProcessor();

	//==============================================================================

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
		void setFileForSound(int index, File &filePath);
	
	private:
		TwonkSamplerSynth samplerSynth;
		Array <TwonkSamplerSound*> samplerSounds;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerProcessor)
};

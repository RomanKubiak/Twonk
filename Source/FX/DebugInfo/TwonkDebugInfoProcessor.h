#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../PluginParameter.h"
#include "../../Filters/InternalFilters.h"

//==============================================================================

class DebugInfoProcessor : public InternalPlugin
{
public:
    //==============================================================================

	DebugInfoProcessor(const PluginDescription& descr);
    ~DebugInfoProcessor();

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
	void updateCurrentTimeInfoFromHost();
	AudioPlayHead::CurrentPositionInfo lastPosInfo;
	MidiBuffer lastMidiBuffer;
private:
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugInfoProcessor)
};

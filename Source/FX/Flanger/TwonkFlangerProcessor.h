#pragma once
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../PluginParameter.h"
#include "../../Filters/InternalFilters.h"
//==============================================================================

class FlangerAudioProcessor : public InternalPlugin
{
public:
    //==============================================================================

    FlangerAudioProcessor(const PluginDescription& descr);
    ~FlangerAudioProcessor();

    //==============================================================================

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================






    //==============================================================================

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================






    //==============================================================================

    StringArray waveformItemsUI = {
        "Sine",
        "Triangle",
        "Sawtooth (rising)",
        "Sawtooth (falling)"
    };

    enum waveformIndex {
        waveformSine = 0,
        waveformTriangle,
        waveformSawtooth,
        waveformInverseSawtooth,
    };

    //======================================

    StringArray interpolationItemsUI = {
        "None",
        "Linear",
        "Cubic"
    };

    enum interpolationIndex {
        interpolationNearestNeighbour = 0,
        interpolationLinear,
        interpolationCubic,
    };

    //======================================

    AudioSampleBuffer delayBuffer;
    int delayBufferSamples;
    int delayBufferChannels;
    int delayWritePosition;

    float lfoPhase;
    float inverseSampleRate;
    float twoPi;

    float lfo (float phase, int waveform);

    //======================================

    PluginParametersManager parameters;

    PluginParameterLinSlider paramDelay;
    PluginParameterLinSlider paramWidth;
    PluginParameterLinSlider paramDepth;
    PluginParameterLinSlider paramFeedback;
    PluginParameterToggle paramInverted;
    PluginParameterLinSlider paramFrequency;
    PluginParameterComboBox paramWaveform;
    PluginParameterComboBox paramInterpolation;
    PluginParameterToggle paramStereo;

private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessor)
};

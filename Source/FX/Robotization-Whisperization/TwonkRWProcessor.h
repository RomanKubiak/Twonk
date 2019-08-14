#pragma once
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../PluginParameter.h"
#include "STFT.h"
#include "../../Filters/InternalPlugins.h"
//==============================================================================

class RobotizationWhisperizationAudioProcessor : public TwonkPlugin
{
public:
    //==============================================================================

    RobotizationWhisperizationAudioProcessor(const PluginDescription& descr);
    ~RobotizationWhisperizationAudioProcessor();

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

    StringArray effectItemsUI = {
        "Pass-through",
        "Robotization",
        "Whisperization"
    };

    enum effectIndex {
        effectPassThrough = 0,
        effectRobotization,
        effectWhisperization,
    };

    //======================================

    StringArray fftSizeItemsUI = {
        "32",
        "64",
        "128",
        "256",
        "512",
        "1024",
        "2048",
        "4096",
        "8192"
    };

    enum fftSizeIndex {
        fftSize32 = 0,
        fftSize64,
        fftSize128,
        fftSize256,
        fftSize512,
        fftSize1024,
        fftSize2048,
        fftSize4096,
        fftSize8192,
    };

    //======================================

    StringArray hopSizeItemsUI = {
        "1/2 Window",
        "1/4 Window",
        "1/8 Window",
    };

    enum hopSizeIndex {
        hopSize2 = 0,
        hopSize4,
        hopSize8,
    };

    //======================================

    StringArray windowTypeItemsUI = {
        "Rectangular",
        "Bartlett",
        "Hann",
        "Hamming",
    };

    //======================================

    class RobotizationWhisperization : public STFT
    {
    public:
        RobotizationWhisperization (RobotizationWhisperizationAudioProcessor& p) : parent (p)
        {
        }

    private:
        void modification() override
        {
            fft->perform (timeDomainBuffer, frequencyDomainBuffer, false);

            switch ((int)parent.paramEffect.getTargetValue()) {
                case effectPassThrough: {
                    // nothing
                    break;
                }
                case effectRobotization: {
                    for (int index = 0; index < fftSize; ++index) {
                        float magnitude = abs (frequencyDomainBuffer[index]);
                        frequencyDomainBuffer[index].real (magnitude);
                        frequencyDomainBuffer[index].imag (0.0f);
                    }
                    break;
                }
                case effectWhisperization: {
                    for (int index = 0; index < fftSize / 2 + 1; ++index) {
                        float magnitude = abs (frequencyDomainBuffer[index]);
                        float phase = 2.0f * M_PI * (float)rand() / (float)RAND_MAX;

                        frequencyDomainBuffer[index].real (magnitude * cosf (phase));
                        frequencyDomainBuffer[index].imag (magnitude * sinf (phase));
                        if (index > 0 && index < fftSize / 2) {
                            frequencyDomainBuffer[fftSize - index].real (magnitude * cosf (phase));
                            frequencyDomainBuffer[fftSize - index].imag (magnitude * sinf (-phase));
                        }
                    }
                    break;
                }
            }

            fft->perform (frequencyDomainBuffer, timeDomainBuffer, true);
        }

        RobotizationWhisperizationAudioProcessor& parent;
    };

    //======================================

    CriticalSection lock;
    RobotizationWhisperization stft;

    //======================================

    PluginParametersManager parameters;

    PluginParameterComboBox paramEffect;
    PluginParameterComboBox paramFftSize;
    PluginParameterComboBox paramHopSize;
    PluginParameterComboBox paramWindowType;

private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RobotizationWhisperizationAudioProcessor)
};

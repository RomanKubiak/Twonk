#include "TwonkPPDelayProcessor.h"
#include "TwonkPPDelayEditor.h"
#include "../PluginParameter.h"

//==============================================================================

PingPongDelayAudioProcessor::PingPongDelayAudioProcessor(const PluginDescription& descr):
	TwonkPlugin (descr),
    parameters (*this)
    , paramBalance (parameters, "Balance input", "", 0.0f, 1.0f, 0.25f)
    , paramDelayTime (parameters, "Delay time", "s", 0.0f, 5.0f, 0.1f)
    , paramFeedback (parameters, "Feedback", "", 0.0f, 0.9f, 0.7f)
    , paramMix (parameters, "Mix", "", 0.0f, 1.0f, 1.0f)
{
    parameters.valueTreeState.state = ValueTree (Identifier (getName().removeCharacters ("- ")));
}

PingPongDelayAudioProcessor::~PingPongDelayAudioProcessor()
{
}

//==============================================================================

void PingPongDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const double smoothTime = 1e-3;
    paramBalance.reset (sampleRate, smoothTime);
    paramDelayTime.reset (sampleRate, smoothTime);
    paramFeedback.reset (sampleRate, smoothTime);
    paramMix.reset (sampleRate, smoothTime);

    //======================================

    float maxDelayTime = paramDelayTime.maxValue;
    delayBufferSamples = (int)(maxDelayTime * (float)sampleRate) + 1;
    if (delayBufferSamples < 1)
        delayBufferSamples = 1;

    delayBufferChannels = getTotalNumInputChannels();
    delayBuffer.setSize (delayBufferChannels, delayBufferSamples);
    delayBuffer.clear();

    delayWritePosition = 0;
}

void PingPongDelayAudioProcessor::releaseResources()
{
}

void PingPongDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    const int numInputChannels = getTotalNumInputChannels();
    const int numOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();

    //======================================

    float currentBalance = paramBalance.getNextValue();
    float currentDelayTime = paramDelayTime.getTargetValue() * (float)getSampleRate();
    float currentFeedback = paramFeedback.getNextValue();
    float currentMix = paramMix.getNextValue();

    int localWritePosition = delayWritePosition;

    float* channelDataL = buffer.getWritePointer (0);
    float* channelDataR = buffer.getWritePointer (1);
    float* delayDataL = delayBuffer.getWritePointer (0);
    float* delayDataR = delayBuffer.getWritePointer (1);

    for (int sample = 0; sample < numSamples; ++sample) {
        const float inL = (1.0f - currentBalance) * channelDataL[sample];
        const float inR = currentBalance * channelDataR[sample];
        float outL = 0.0f;
        float outR = 0.0f;

        float readPosition =
            fmodf ((float)localWritePosition - currentDelayTime + (float)delayBufferSamples, delayBufferSamples);
        int localReadPosition = floorf (readPosition);

        if (localReadPosition != localWritePosition) {
            float fraction = readPosition - (float)localReadPosition;
            float delayed1L = delayDataL[(localReadPosition + 0)];
            float delayed1R = delayDataR[(localReadPosition + 0)];
            float delayed2L = delayDataL[(localReadPosition + 1) % delayBufferSamples];
            float delayed2R = delayDataR[(localReadPosition + 1) % delayBufferSamples];
            outL = delayed1L + fraction * (delayed2L - delayed1L);
            outR = delayed1R + fraction * (delayed2R - delayed1R);

            channelDataL[sample] = inL + currentMix * (outL - inL);
            channelDataR[sample] = inR + currentMix * (outR - inR);
            delayDataL[localWritePosition] = inL + outR * currentFeedback;
            delayDataR[localWritePosition] = inR + outL * currentFeedback;
        }

        if (++localWritePosition >= delayBufferSamples)
            localWritePosition -= delayBufferSamples;
    }

    delayWritePosition = localWritePosition;

    //======================================

    for (int channel = numInputChannels; channel < numOutputChannels; ++channel)
        buffer.clear (channel, 0, numSamples);
}

//==============================================================================






//==============================================================================

void PingPongDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.valueTreeState.state.createXml().get());
    copyXmlToBinary (*xml, destData);
}

void PingPongDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes).get());
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.valueTreeState.state.getType()))
            parameters.valueTreeState.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================

AudioProcessorEditor* PingPongDelayAudioProcessor::createEditor()
{
    return new PingPongDelayAudioProcessorEditor (*this);
}

bool PingPongDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool PingPongDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================

const String PingPongDelayAudioProcessor::getName() const
{
    return "PingPong";
}

bool PingPongDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PingPongDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PingPongDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PingPongDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================

int PingPongDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PingPongDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PingPongDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String PingPongDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void PingPongDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

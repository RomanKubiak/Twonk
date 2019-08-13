/*
  ==============================================================================

    This code is based on the contents of the book: "Audio Effects: Theory,
    Implementation and Application" by Joshua D. Reiss and Andrew P. McPherson.

    Code by Juan Gil <https://juangil.com/>.
    Copyright (C) 2017-2019 Juan Gil.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

  ==============================================================================
*/

#include "TwonkRWProcessor.h"
#include "TwonkRWEditor.h"
#include "../PluginParameter.h"

//==============================================================================

RobotizationWhisperizationAudioProcessor::RobotizationWhisperizationAudioProcessor(const PluginDescription& descr):
	InternalPlugin (descr, true),
    stft (*this), parameters (*this)
    , paramEffect (parameters, "Effect", effectItemsUI, effectPassThrough)
    , paramFftSize (parameters, "FFT size", fftSizeItemsUI, fftSize512,
                    [this](float value){
                        const ScopedLock sl (lock);
                        value = (float)(1 << ((int)value + 5));
                        paramFftSize.setValue (value);
                        stft.updateParameters((int)paramFftSize.getTargetValue(),
                                              (int)paramHopSize.getTargetValue(),
                                              (int)paramWindowType.getTargetValue());
                        return value;
                    })
    , paramHopSize (parameters, "Hop size", hopSizeItemsUI, hopSize8,
                    [this](float value){
                        const ScopedLock sl (lock);
                        value = (float)(1 << ((int)value + 1));
                        paramHopSize.setValue (value);
                        stft.updateParameters((int)paramFftSize.getTargetValue(),
                                              (int)paramHopSize.getTargetValue(),
                                              (int)paramWindowType.getTargetValue());
                        return value;
                    })
    , paramWindowType (parameters, "Window type", windowTypeItemsUI, STFT::windowTypeHann,
                       [this](float value){
                           const ScopedLock sl (lock);
                           paramWindowType.setValue (value);
                           stft.updateParameters((int)paramFftSize.getTargetValue(),
                                                 (int)paramHopSize.getTargetValue(),
                                                 (int)paramWindowType.getTargetValue());
                           return value;
                       })
{
    parameters.valueTreeState.state = ValueTree (Identifier (getName().removeCharacters ("- ")));
}

RobotizationWhisperizationAudioProcessor::~RobotizationWhisperizationAudioProcessor()
{
}

//==============================================================================

void RobotizationWhisperizationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const double smoothTime = 1e-3;
    paramEffect.reset (sampleRate, smoothTime);
    paramFftSize.reset (sampleRate, smoothTime);
    paramHopSize.reset (sampleRate, smoothTime);
    paramWindowType.reset (sampleRate, smoothTime);

    //======================================

    stft.setup (getTotalNumInputChannels());
    stft.updateParameters((int)paramFftSize.getTargetValue(),
                          (int)paramHopSize.getTargetValue(),
                          (int)paramWindowType.getTargetValue());
}

void RobotizationWhisperizationAudioProcessor::releaseResources()
{
}

void RobotizationWhisperizationAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const ScopedLock sl (lock);

    ScopedNoDenormals noDenormals;

    const int numInputChannels = getTotalNumInputChannels();
    const int numOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();

    //======================================

    stft.processBlock (buffer);

    //======================================

    for (int channel = numInputChannels; channel < numOutputChannels; ++channel)
        buffer.clear (channel, 0, numSamples);
}

//==============================================================================






//==============================================================================

void RobotizationWhisperizationAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.valueTreeState.state.createXml().get());
    copyXmlToBinary (*xml, destData);
}

void RobotizationWhisperizationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes).get());
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.valueTreeState.state.getType()))
            parameters.valueTreeState.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================

AudioProcessorEditor* RobotizationWhisperizationAudioProcessor::createEditor()
{
    return new RobotizationWhisperizationAudioProcessorEditor (*this);
}

bool RobotizationWhisperizationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool RobotizationWhisperizationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

const String RobotizationWhisperizationAudioProcessor::getName() const
{
    return "Robot-Whisper";
}

bool RobotizationWhisperizationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RobotizationWhisperizationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RobotizationWhisperizationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RobotizationWhisperizationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================

int RobotizationWhisperizationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RobotizationWhisperizationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RobotizationWhisperizationAudioProcessor::setCurrentProgram (int index)
{
}

const String RobotizationWhisperizationAudioProcessor::getProgramName (int index)
{
    return {};
}

void RobotizationWhisperizationAudioProcessor::changeProgramName (int index, const String& newName)
{
}

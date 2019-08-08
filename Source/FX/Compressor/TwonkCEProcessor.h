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

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../PluginParameter.h"
#include "../../Filters/InternalFilters.h"
//==============================================================================

class CompressorExpanderAudioProcessor : public InternalPlugin
{
public:
    //==============================================================================

    CompressorExpanderAudioProcessor(const PluginDescription& descr);
    ~CompressorExpanderAudioProcessor();
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
	bool isBusesLayoutSupported (const BusesLayout& layouts) const override {
		return false;
	}
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
    AudioSampleBuffer mixedDownInput;
    float xl;
    float yl;
    float xg;
    float yg;
    float control;

    float inputLevel;
    float ylPrev;

    float inverseSampleRate;
    float inverseE;
    float calculateAttackOrRelease (float value);
    PluginParametersManager parameters;
    PluginParameterComboBox paramMode;
    PluginParameterLinSlider paramThreshold;
    PluginParameterLinSlider paramRatio;
    PluginParameterLinSlider paramAttack;
    PluginParameterLinSlider paramRelease;
    PluginParameterLinSlider paramMakeupGain;
    PluginParameterToggle paramBypass;

private:
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorExpanderAudioProcessor)
};

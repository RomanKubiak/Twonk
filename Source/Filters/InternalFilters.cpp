/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InternalFilters.h"
#include "FilterGraph.h"
#include "../FX/TwonkFilters.h"

//==============================================================================
class SineWaveSynth :   public InternalPlugin
{
public:
    SineWaveSynth (const PluginDescription& descr) :   InternalPlugin (descr)
    {
        const int numVoices = 8;

        // Add some voices...
        for (int i = numVoices; --i >= 0;)
            synth.addVoice (new SineWaveVoice());

        // ..and give the synth a sound to play
        synth.addSound (new SineWaveSound());
    }
	class Editor : public AudioProcessorEditor
	{
		public:
			Editor(AudioProcessor *filter) : AudioProcessorEditor(filter)
			{
				addAndMakeVisible (timecodeDisplayLabel);
				timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

				setSize(128, 32);
			}

			static String timeToTimecodeString (double seconds)
			{
				auto millisecs = roundToInt (seconds * 1000.0);
				auto absMillisecs = std::abs (millisecs);

				return String::formatted ("%02d:%02d:%02d.%03d",
					millisecs / 3600000,
					(absMillisecs / 60000) % 60,
					(absMillisecs / 1000) % 60,
					absMillisecs % 1000);
			}

			// quick - and-dirty function to format a bars / beats string
			static String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
			{
				if (numerator == 0 || denominator == 0)
					return "1|1|000";

				auto quarterNotesPerBar = (numerator * 4 / denominator);
				auto beats = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

				auto bar = ((int)quarterNotes) / quarterNotesPerBar + 1;
				auto beat = ((int)beats) + 1;
				auto ticks = ((int)(fmod (beats, 1.0) * 960.0 + 0.5));

				return String::formatted ("%d|%d|%03d", bar, beat, ticks);
			}

			void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
			{
				MemoryOutputStream displayText;

				displayText << "[" << SystemStats::getJUCEVersion() << "]   "
					<< String (pos.bpm, 2) << " bpm, "
					<< pos.timeSigNumerator << '/' << pos.timeSigDenominator
					<< "  -  " << timeToTimecodeString (pos.timeInSeconds)
					<< "  -  " << quarterNotePositionToBarsBeatsString (pos.ppqPosition,
						pos.timeSigNumerator,
						pos.timeSigDenominator);

				if (pos.isRecording)
					displayText << "  (recording)";
				else if (pos.isPlaying)
					displayText << "  (playing)";

				timecodeDisplayLabel.setText (displayText.toString(), dontSendNotification);
			}
	private:
		Label timecodeDisplayLabel;
	};

    static String getIdentifier()
    {
        return "Sine Wave Synth";
    }

    static PluginDescription getPluginDescription()
    {
        return InternalPlugin::getPluginDescription (getIdentifier(), true, true);
    }
	bool hasEditor() const override { return true; }
	AudioProcessorEditor *createEditor() override { return new Editor(this); }
	
    //==============================================================================
    void prepareToPlay (double newSampleRate, int) override
    {
        synth.setCurrentPlaybackSampleRate (newSampleRate);
    }

    void releaseResources() override {}

    //==============================================================================
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
    {
        const int numSamples = buffer.getNumSamples();

        buffer.clear();
        synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
        buffer.applyGain (0.8f);
    }

private:
    //==============================================================================
    class SineWaveSound : public SynthesiserSound
    {
    public:
        SineWaveSound() {}

        bool appliesToNote (int /*midiNoteNumber*/) override    { return true; }
        bool appliesToChannel (int /*midiChannel*/) override    { return true; }
    };

    class SineWaveVoice   : public SynthesiserVoice
    {
    public:
        SineWaveVoice()
        : currentAngle (0), angleDelta (0), level (0), tailOff (0)
        {
        }

        bool canPlaySound (SynthesiserSound* sound) override
        {
            return dynamic_cast<SineWaveSound*> (sound) != nullptr;
        }

        void startNote (int midiNoteNumber, float velocity,
                        SynthesiserSound* /*sound*/,
                        int /*currentPitchWheelPosition*/) override
        {
            currentAngle = 0.0;
            level = velocity * 0.15;
            tailOff = 0.0;

            double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
            double cyclesPerSample = cyclesPerSecond / getSampleRate();

            angleDelta = cyclesPerSample * 2.0 * double_Pi;
        }

        void stopNote (float /*velocity*/, bool allowTailOff) override
        {
            if (allowTailOff)
            {
                // start a tail-off by setting this flag. The render callback will pick up on
                // this and do a fade out, calling clearCurrentNote() when it's finished.

                if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                    // stopNote method could be called more than once.
                    tailOff = 1.0;
            }
            else
            {
                // we're being told to stop playing immediately, so reset everything..

                clearCurrentNote();
                angleDelta = 0.0;
            }
        }

        void pitchWheelMoved (int /*newValue*/) override
        {
            // not implemented for the purposes of this demo!
        }

        void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
        {
            // not implemented for the purposes of this demo!
        }

        void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
        {
            if (angleDelta != 0.0)
            {
                if (tailOff > 0)
                {
                    while (--numSamples >= 0)
                    {
                        const float currentSample = (float) (sin (currentAngle) * level * tailOff);

                        for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);

                        currentAngle += angleDelta;
                        ++startSample;

                        tailOff *= 0.99;

                        if (tailOff <= 0.005)
                        {
                            // tells the synth that this voice has stopped
                            clearCurrentNote();

                            angleDelta = 0.0;
                            break;
                        }
                    }
                }
                else
                {
                    while (--numSamples >= 0)
                    {
                        const float currentSample = (float) (sin (currentAngle) * level);

                        for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);

                        currentAngle += angleDelta;
                        ++startSample;
                    }
                }
            }
        }

    private:
        double currentAngle, angleDelta, level, tailOff;

    };

    //==============================================================================
    Synthesiser synth;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveSynth)
};

//==============================================================================
class ReverbFilter    : public InternalPlugin
{
public:
    ReverbFilter (const PluginDescription& descr) :   InternalPlugin (descr)
    {}

    static String getIdentifier()
    {
        return "Reverb";
    }

    static PluginDescription getPluginDescription()
    {
        return InternalPlugin::getPluginDescription (getIdentifier(), false, false);
    }

    void prepareToPlay (double newSampleRate, int) override
    {
        reverb.setSampleRate (newSampleRate);
    }

    void reset() override
    {
        reverb.reset();
    }
	bool hasEditor() const override { return false; }
	AudioProcessorEditor *createEditor() override { return nullptr; }
    void releaseResources() override {}

    void processBlock (AudioBuffer<float>& buffer, MidiBuffer&) override
    {
        auto numChannels = buffer.getNumChannels();

        if (numChannels == 1)
            reverb.processMono (buffer.getWritePointer (0), buffer.getNumSamples());
        else
            reverb.processStereo (buffer.getWritePointer (0),
                                  buffer.getWritePointer (1),
                                  buffer.getNumSamples());

        for (int ch = 2; ch < numChannels; ++ch)
            buffer.clear (ch, 0, buffer.getNumSamples());
    }

private:
    Reverb reverb;
};

//==============================================================================
InternalPluginFormat::InternalPluginFormat()
{
    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
        p.fillInPluginDescription (audioOutDesc);
    }

    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
        p.fillInPluginDescription (audioInDesc);
    }

    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);
        p.fillInPluginDescription (midiInDesc);
    }
}

AudioPluginInstance* InternalPluginFormat::createInstance (const String& name)
{
    if (name == audioOutDesc.name) return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
    if (name == audioInDesc.name)  return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
    if (name == midiInDesc.name)   return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);


    if (name == SineWaveSynth::getIdentifier()) return new SineWaveSynth (SineWaveSynth::getPluginDescription());
    if (name == ReverbFilter::getIdentifier())  return new ReverbFilter  (ReverbFilter::getPluginDescription());
	
	return TwonkFilters::createInstance(name);
    return nullptr;
}

void InternalPluginFormat::createPluginInstance (const PluginDescription& desc,
                                                 double /*initialSampleRate*/,
                                                 int /*initialBufferSize*/,
                                                 void* userData,
                                                 PluginCreationCallback callback)
{
    auto* p = createInstance (desc.name);

    callback (userData, p, p == nullptr ? NEEDS_TRANS ("Invalid internal filter name") : String());
}

bool InternalPluginFormat::requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const noexcept
{
    return false;
}

void InternalPluginFormat::getAllTypes (OwnedArray<PluginDescription>& results)
{
    results.add (new PluginDescription (audioInDesc));
    results.add (new PluginDescription (audioOutDesc));
    results.add (new PluginDescription (midiInDesc));
    results.add (new PluginDescription (SineWaveSynth::getPluginDescription()));
    results.add (new PluginDescription (ReverbFilter::getPluginDescription()));
	TwonkFilters::getAllTypes(results);
}
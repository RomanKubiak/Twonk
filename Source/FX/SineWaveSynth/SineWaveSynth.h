/*
  ==============================================================================

    SineWaveSynth.h
    Created: 26 Jun 2019 1:46:45pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../../Filters/InternalFilters.h"

class SineWaveSynth : public InternalPlugin
{
	public:
		SineWaveSynth (const PluginDescription& descr);
		void releaseResources() {}
		AudioProcessorEditor *createEditor() { return nullptr; }
		bool hasEditor()  const { return false; }
		static String getIdentifier() { return "Sine Wave Synth"; }
		static PluginDescription getPluginDescription() { return InternalPlugin::getPluginDescription (getIdentifier(), true, true); }
		void prepareToPlay (double newSampleRate, int) override;
		void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

	private:
		//==============================================================================
		class SineWaveSound : public SynthesiserSound
		{
		public:
			SineWaveSound() {}

			bool appliesToNote (int /*midiNoteNumber*/) override { return true; }
			bool appliesToChannel (int /*midiChannel*/) override { return true; }
		};

		class SineWaveVoice : public SynthesiserVoice
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
							const float currentSample = (float)(sin (currentAngle) * level * tailOff);

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
							const float currentSample = (float)(sin (currentAngle) * level);

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

		Synthesiser synth;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveSynth)
};
#pragma once
#include "JuceHeader.h"

class SimplerVoice : public SynthesiserVoice
{
	public:
		SimplerVoice(int voiceIndex);
		~SimplerVoice() override;
		bool canPlaySound (SynthesiserSound*) override;
		void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int pitchWheel) override;
		void stopNote (float velocity, bool allowTailOff) override;
		void pitchWheelMoved (int newValue) override;
		void controllerMoved (int controllerNumber, int newValue) override;
		void renderNextBlock (AudioBuffer<float>&, int startSample, int numSamples) override;
		using SynthesiserVoice::renderNextBlock;

	private:
		double pitchRatio = 0;
		double sourceSamplePosition = 0;
		float lgain = 0, rgain = 0;
		int voiceIndex;
		ADSR adsr;

		JUCE_LEAK_DETECTOR (SimplerVoice)
};
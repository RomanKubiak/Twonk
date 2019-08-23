/**
	A Sampler Sound Object, which is able to hold a sampled sound.



	@author Niklas Wantrupp
	@version v1.0 12/09/2018
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class CTAGSamplerSound : public SamplerSound
{
	public:
		friend class CTAGSamplerVoice;

		CTAGSamplerSound(const String &name, AudioFormatReader &source,
			const BigInteger &midiNotes, int midiNoteForNormalPitch,
			double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds);

	private:
		int midiRootNote = 0;
		int length = 0;
		double sourceSampleRate;
};
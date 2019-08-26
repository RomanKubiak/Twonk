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
			double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds, int _audioOutputChannel);
		const int getAudioOutputChannel() { return (audioOutputChannel); }
		void setAudioOutputChannel(int _audioOutputChannel) { audioOutputChannel = _audioOutputChannel; }
	
	private:
		int midiRootNote = 0;
		int length = 0;
		double sourceSampleRate;
		int audioOutputChannel = 0;
};
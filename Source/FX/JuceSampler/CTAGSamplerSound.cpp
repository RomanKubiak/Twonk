#include "CTAGSamplerSound.h"

CTAGSamplerSound::CTAGSamplerSound(const String &name, AudioFormatReader &source,
	const BigInteger &midiNotes, int midiNoteForNormalPitch,
	double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds, int _audioOutputChannel)
	: SamplerSound(name, source, midiNotes, midiNoteForNormalPitch,
		attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds),
		sourceSampleRate(source.sampleRate), length(source.lengthInSamples),
		midiRootNote(midiNoteForNormalPitch), audioOutputChannel(_audioOutputChannel)
{
}
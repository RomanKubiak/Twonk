#include "SimplerSound.h"

SimplerSound::SimplerSound (const String& soundName,
							AudioFormatReader& source,
							const BigInteger& notes,
							int midiNoteForNormalPitch,
							double attackTimeSecs,
							double releaseTimeSecs,
							double maxSampleLengthSeconds,
							int velocityRangeStart,
							int velocityRangeEnd,
							const File &_sampleFile)
	:	name (soundName),
		sourceSampleRate (source.sampleRate),
		length(source.lengthInSamples),
		midiNotes    (notes),
		midiRootNote (midiNoteForNormalPitch),
		velocityRange (velocityRangeStart, velocityRangeEnd+1),
		sampleFile (_sampleFile)
{
	if (sourceSampleRate > 0 && source.lengthInSamples > 0)
	{
		length = jmin ((int)source.lengthInSamples,
			(int)(maxSampleLengthSeconds * sourceSampleRate));

		data.reset (new AudioBuffer<float> (jmin (2, (int)source.numChannels), length + 4));

		source.read (data.get(), 0, length + 4, 0, true, true);

		params.attack = static_cast<float> (attackTimeSecs);
		params.release = static_cast<float> (releaseTimeSecs);
	}
}

SimplerSound::~SimplerSound()
{
}

bool SimplerSound::appliesToNote (int midiNoteNumber)
{
	return midiNotes[midiNoteNumber];
}

bool SimplerSound::appliesToChannel (int /*midiChannel*/)
{
	return (true);
}

bool SimplerSound::appliesToVelocity(const float velocity)
{
	uint8 normalVelo = roundFloatToInt(velocity * 127.0f);
	return (velocityRange.getRange().contains(normalVelo));
}

void SimplerSound::setEnvelopeParameters (ADSR::Parameters parametersToUse)
{
	/*DBG("SimplerSound::setEnvelopeParameters file:" + sampleFile.getFileName()
		+ " attack:" + String(parametersToUse.attack)
		+ " decay:" + String(parametersToUse.decay)
		+ " sustain:" + String(parametersToUse.sustain)
		+ " release:" + String(parametersToUse.release)
	);*/
	params = parametersToUse;
}
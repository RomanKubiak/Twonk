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
	DBG("SimplerSound::appliesToVelocity normalizedVelo:" + String(normalVelo));
	return (velocityRange.getRange().contains(normalVelo));
}

/*
SimplerSound *SimplerVoice::pickSoundBasedOnVelocity(int midiNoteNumber, float velo)
{
	SimplerSound *firstSound = dynamic_cast<SimplerSound *>(sound);
	SimplerSound *soundToPlay = nullptr;
	for (int i = 0; i < instrumentArray.size(); i++)
	{
		if (instrumentArray[i]->midiNote == midiNoteNumber)
		{
			int lastSample = instrumentArray[i]->assosiatedSound.size() - 1;
			int sampleNum = velo * lastSample;
			soundToPlay = instrumentArray[i]->assosiatedSound[sampleNum];
			break;
		}
	}
	return (soundToPlay);
}*/
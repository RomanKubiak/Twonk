#include "CTAGSampler.h"

#define NUM_VOICES 16

CTAGSampler::CTAGSampler(OwnedArray<SamplerInstrument> &_instrumentArray)
	: instrumentArray(_instrumentArray)
{
	formatManager.registerBasicFormats();
}

void CTAGSampler::init()
{
	for (int i = 0; i < NUM_VOICES; i++)
	{
		addVoice(new CTAGSamplerVoice(i));
	}
}

CTAGSampler::~CTAGSampler(){}

void CTAGSampler::noteOn(int midiChannel, int midiNoteNumber, float velocity)
{
	const ScopedLock sl(lock);

	for(int j = 0; j < getNumSounds(); j++)
	{
		auto sound = getSound(j);
		if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
		{
			for(int i = 0; i < getNumVoices(); i++)
			{
				if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(getVoice(i)))
				{
					if(voice->canPlayCTAGSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
					{
						stopVoice(voice, 0.0f, false);
					}
				}
			}

			for(int i = 0; i < getNumVoices(); i++)
			{
				if(auto* voice = dynamic_cast<CTAGSamplerVoice*> (getVoice(i)))
				{
					if(voice->canPlayCTAGSound(midiNoteNumber) && !voice->getCurrentlyPlayingSound())
					{
						playSampleOnVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
					}
				}
			}
		}
	}
}

void CTAGSampler::reloadInstruments()
{
	ScopedLock sl(lock);
	for (int i = 0; i < instrumentArray.size(); i++)
	{
		addCTAGSound(instrumentArray[i]);
	}
}

void CTAGSampler::addCTAGSound(SamplerInstrument *instrumentToAdd)
{
	const ScopedLock sl(lock);
	for (int i = 0; i < instrumentToAdd->fileList.size(); i++)
	{
		File file = instrumentToAdd->fileList[i];
		std::unique_ptr<AudioFormatReader> fileReader (formatManager.createReaderFor(file));
		BigInteger note;
		note.setBit(instrumentToAdd->midiNote);
		CTAGSamplerSound *sound = new CTAGSamplerSound(instrumentToAdd->name, *fileReader, note, instrumentToAdd->midiNote, 0.0f, 10.0f, 10.0f, instrumentToAdd->audioOutputChannel);
		addSound(sound);
		instrumentToAdd->assosiatedSound.add(sound);
	}
}

void CTAGSampler::playSampleOnVoice(SynthesiserVoice *voice, SynthesiserSound *sound, int ch, int note, float velo)
{
	SamplerSound *firstSound = dynamic_cast<SamplerSound *>(sound);
	SynthesiserSound *soundToPlay = nullptr;
	for (int i = 0; i < instrumentArray.size(); i++)
	{
		if (instrumentArray[i]->midiNote == note && instrumentArray[i]->midiChannel == ch)
		{
			int lastSample = instrumentArray[i]->assosiatedSound.size() - 1;
			int sampleNum = velo * lastSample;
			//DBG("CTAGSampler::playSampleOnVoice velo:" + String(velo) + " sampleNum:" + String(sampleNum) +" lastSample:"+String(lastSample));

			soundToPlay = instrumentArray[i]->assosiatedSound[sampleNum];

			break;
		}
	}

	startVoice(voice, soundToPlay, ch, note, velo);
} 
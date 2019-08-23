#include "CTAGSampler.h"

#define NUM_VOICES 8

CTAGSampler::CTAGSampler(){}

void CTAGSampler::init()
{
	for (int i = 0; i < NUM_VOICES; i++)
	{
		addVoice(new CTAGSamplerVoice(i));
	}

	formatManager.registerBasicFormats();
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
						//Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));
						
						if(isChokeGroupActive && (midiNoteNumber == 42 || midiNoteNumber == 46))
						{
								switch(midiNoteNumber)
								{
								case 42:
									for(int i = 0; i < getNumVoices(); i++)
									{
										if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(getVoice(i)))
										{
											if(voice->canPlayCTAGSound(46))
											{
												stopVoice(voice, 0.0f, false);
												break;
											}
										}
									}
								case 46:
									for (int i = 0; i < getNumVoices(); i++)
									{
										if (auto* voice = dynamic_cast<CTAGSamplerVoice*>(getVoice(i)))
										{
											if (voice->canPlayCTAGSound(42))
											{
												stopVoice(voice, 0.0f, false);
												break;
											}
										}
									}
								default:
									break;
								}
						}
						
						startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
					}
				}
			}
		}
	}
}

void CTAGSampler::loadSamples(ZipFile instrumentBank)
{
	const ScopedLock sl(lock);

	if (getNumSounds() != 0)
	{
		for(int i = 0; i < getNumSounds(); i++)
		{
			removeSound(i);
		}
	}
	
	/*
	for(int i = 0; i < instruments.size(); i++)
	{
		addCTAGSound(instruments[i], String(instruments[i] + "_" + number + "_" + rootNote + ".wav"), kit, 36+i);
	}*/
}

void CTAGSampler::addCTAGSound(BankInstrumentEntry instrumentToAdd)
{
	//File* file = new File(samplesFolder.getChildFile(instrument).getChildFile(kit).getChildFile(fileName));
	//ScopedPointer<AudioFormatReader> fileReader = formatManager.createReaderFor(*file);
	//BigInteger note;
	//note.setBit(midiNote);

	//addSound(new CTAGSamplerSound(instrument, *fileReader, note, midiNote, 0.0f, 10.0f, 10.0f));

	//fileReader = nullptr;
	//delete file;
}
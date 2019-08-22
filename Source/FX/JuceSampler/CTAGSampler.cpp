#include "CTAGSampler.h"

#define NUM_VOICES 4

void CTAGSampler::setup()
{
	samplesFolder = File::getSpecialLocation(File::userDesktopDirectory).getChildFile("Samples");
	instruments = {"Kick", "Snare", "Clap", "Tom", "Perc", "OpHat", "ClHat", "Crash", "Ride"};
	isChokeGroupActive = false;
	for (int i = 0; i < NUM_VOICES; i++)
	{
		auto* voice = new CTAGSamplerVoice(i);

		switch(i)
		{
		case KICK:
			voice->setMidiNote(36);
			break;
		case SNARE:
			voice->setMidiNote(38);
			break;
		case CLAP:
			voice->setMidiNote(39);
			break;
		case TOM:
			voice->setMidiNote(41);
			break;
		default:
			break;
		}
		
		addVoice(voice);
	}
	
	formatManager.registerBasicFormats();
	loadSamples("Kit 1", "C");
}


void CTAGSampler::noteOn(int midiChannel,
	int midiNoteNumber,
	float velocity)
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

void CTAGSampler::loadSamples(String kit, String rootNote)
{
	String number = String( String(0) + String(0) + kit.trimCharactersAtStart("Kit "));
	
	const ScopedLock sl(lock);

	if(getNumSounds() != 0)
	{
		for(int i = 0; i < getNumSounds(); i++)
		{
			removeSound(i);
		}
	}
	

	
	for(int i = 0; i < instruments.size(); i++)
	{
		addCTAGSound(instruments[i], String(instruments[i] + "_" + number + "_" + rootNote + ".wav"), kit);
		
	}
	
	
	
}


void CTAGSampler::addCTAGSound(String instrument, String fileName, String kit)
{
	int midiNote;
	if(instrument == String("Kick"))
	{
		midiNote = 36;
	}
	else if( instrument == String("Snare"))
	{
		midiNote = 38;
	}
	else if(instrument == String ("Clap"))
	{
		midiNote = 39;
	}
	else if (instrument == String("Tom"))
	{
		midiNote = 41;
	}

	File* file = new File(samplesFolder.getChildFile(instrument).getChildFile(kit).getChildFile(fileName));
	
	//Logger::outputDebugString(file->getFullPathName());
	
	ScopedPointer<AudioFormatReader> fileReader = formatManager.createReaderFor(*file);
	BigInteger note;
	note.setBit(midiNote);

	addSound(new CTAGSamplerSound(instrument, *fileReader, note, midiNote, 0.0f, 10.0f, 10.0f));

	fileReader = nullptr;
	delete file;

	
}

void CTAGSampler::parameterChanged(const String &parameterID, float newValue)
{
	if (parameterID == String("Choke ON/OFF"))
	{
		isChokeGroupActive = static_cast<bool> (newValue);
		
		//For Debugging Purposes
		/*String value;
		value = (isChokeGroupActive == true) ? "true" : "false";
 		Logger::outputDebugString(value);*/
	}
}
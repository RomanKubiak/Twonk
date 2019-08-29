/*
  ==============================================================================

    SimplerSynthesizer.cpp
    Created: 28 Aug 2019 9:35:53pm
    Author:  rkubiak

  ==============================================================================
*/

#include "SimplerSynthesiser.h"
#include "SimplerSound.h"


SimplerSynthesiser::SimplerSynthesiser()
{
}

void SimplerSynthesiser::noteOn (const int midiChannel, const int midiNoteNumber, const float velocity)
{
	const ScopedLock sl (lock);

	for (auto* sound : sounds)
	{
		auto *simplerSound = dynamic_cast<SimplerSound*>(sound);
		if (simplerSound->appliesToNote (midiNoteNumber) 
			&& simplerSound->appliesToChannel (midiChannel)
			&& simplerSound->appliesToVelocity(velocity))
		{
			// If hitting a note that's still ringing, stop it first (it could be
			// still playing because of the sustain or sostenuto pedal).
			for (auto* voice : voices)
				if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel (midiChannel))
					stopVoice (voice, 1.0f, true);

			startVoice (findFreeVoice (sound, midiChannel, midiNoteNumber, shouldStealNotes),
				sound, midiChannel, midiNoteNumber, velocity);
		}
	}
}
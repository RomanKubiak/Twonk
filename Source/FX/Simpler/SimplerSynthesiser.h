/*
  ==============================================================================

    SimplerSynthesizer.h
    Created: 28 Aug 2019 9:35:53pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class SimplerSynthesiser : public Synthesiser
{
	public:
		SimplerSynthesiser();
		void noteOn (const int midiChannel, const int midiNoteNumber, const float velocity) override;

	private:
		bool shouldStealNotes = true;
};
/**
	The Sampler which handles all incoming midi messages and plays the corresponding sounds.



	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "CTAGSamplerVoice.h"

struct BankInstrumentEntry
{
	ZipFile::ZipEntry zipEntry;
	JSON instrumentDefaults;
};

class CTAGSampler : public Synthesiser, public AudioProcessorValueTreeState::Listener
{
	public:
		CTAGSampler();
		~CTAGSampler();
		void init();
		void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;
		void loadSamples(ZipFile instrumentBank);
		void addCTAGSound(BankInstrumentEntry instrumentToAdd);
		void parameterChanged (const String& parameterID, float newValue) {}
	private:
		AudioFormatManager formatManager;
		bool isChokeGroupActive = false;
};
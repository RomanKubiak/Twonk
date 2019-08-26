/**
	The Sampler which handles all incoming midi messages and plays the corresponding sounds.



	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "CTAGSamplerVoice.h"

struct SamplerInstrument
{
	String name;
	String velocityCurve;
	Array<File> fileList;
	int midiNote;
	int midiChannel;
	int audioOutputChannel;
	Array<CTAGSamplerSound*> assosiatedSound;
};

class CTAGSampler : public Synthesiser, public AudioProcessorValueTreeState::Listener
{
	public:
		CTAGSampler(OwnedArray<SamplerInstrument> &_instrumentArray);
		~CTAGSampler();
		void init();
		void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;
		void addCTAGSound(SamplerInstrument *instrumentToAdd);
		void playSampleOnVoice(SynthesiserVoice *voice, SynthesiserSound *sound, int ch, int note, float velo);
		void parameterChanged (const String& parameterID, float newValue) {}
		void reloadInstruments();
	private:
		AudioFormatManager formatManager;
		bool isChokeGroupActive = false;
		OwnedArray<SamplerInstrument> &instrumentArray;
};
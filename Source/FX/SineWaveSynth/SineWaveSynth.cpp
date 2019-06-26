#include "SineWaveSynth.h"

SineWaveSynth::SineWaveSynth (const PluginDescription& descr) : InternalPlugin (descr)
{
	const int numVoices = 8;

	// Add some voices...
	for (int i = numVoices; --i >= 0;)
		synth.addVoice (new SineWaveVoice());

	// ..and give the synth a sound to play
	synth.addSound (new SineWaveSound());
}

void SineWaveSynth::prepareToPlay (double newSampleRate, int)
{
	synth.setCurrentPlaybackSampleRate (newSampleRate);

}

void SineWaveSynth::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	const int numSamples = buffer.getNumSamples();

	buffer.clear();
	synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
	buffer.applyGain (0.8f);
}
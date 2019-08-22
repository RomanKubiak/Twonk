#include "MidiControllerProcessor.h"
#include "MidiControllerEditor.h"
#include "../PluginParameter.h"

MidiControllerProcessor::MidiControllerProcessor(const PluginDescription& descr) : TwonkPlugin (descr){}
MidiControllerProcessor::~MidiControllerProcessor() {}
void MidiControllerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	keyboardState.reset();
}
void MidiControllerProcessor::releaseResources()
{
	keyboardState.reset();
}
void MidiControllerProcessor::getStateInformation (MemoryBlock& destData) {}
void MidiControllerProcessor::setStateInformation (const void* data, int sizeInBytes) {}
void MidiControllerProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
}
AudioProcessorEditor* MidiControllerProcessor::createEditor()
{
	return new MidiControllerEditor (*this);
}
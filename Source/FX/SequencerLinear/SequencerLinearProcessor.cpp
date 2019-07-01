#include "SequencerLinearProcessor.h"
#include "SequencerLinearEditor.h"
#include "../PluginParameter.h"

SequencerLinearProcessor::SequencerLinearProcessor(const PluginDescription& descr) : InternalPlugin (descr, true)
{
	lastPosInfo.resetToDefault();
}
SequencerLinearProcessor::~SequencerLinearProcessor() {}
void SequencerLinearProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}
void SequencerLinearProcessor::releaseResources() {}
void SequencerLinearProcessor::getStateInformation (MemoryBlock& destData) {}
void SequencerLinearProcessor::setStateInformation (const void* data, int sizeInBytes) {}
bool SequencerLinearProcessor::hasEditor() const { return true; }
bool SequencerLinearProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const { return true; }
const String SequencerLinearProcessor::getName() const { return "Sequencer Linear"; }
bool SequencerLinearProcessor::acceptsMidi() const { return true; }
bool SequencerLinearProcessor::producesMidi() const { return false; }
bool SequencerLinearProcessor::isMidiEffect() const { return false; }
double SequencerLinearProcessor::getTailLengthSeconds() const { return 0.0; }
int SequencerLinearProcessor::getNumPrograms() { return 1; }
int SequencerLinearProcessor::getCurrentProgram() { return 0; }
void SequencerLinearProcessor::setCurrentProgram (int index) { }
const String SequencerLinearProcessor::getProgramName (int index) { return {}; }
void SequencerLinearProcessor::changeProgramName (int index, const String& newName) {}

void SequencerLinearProcessor::updateCurrentTimeInfoFromHost()
{
	if (auto* ph = getPlayHead())
	{
		AudioPlayHead::CurrentPositionInfo newTime;

		if (ph->getCurrentPosition (newTime))
		{
			lastPosInfo = newTime;  // Successfully got the current time from the host..
			return;
		}
	}


	// If the host fails to provide the current time, we'll just reset our copy to a default..
	lastPosInfo.resetToDefault();
}

void SequencerLinearProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	updateCurrentTimeInfoFromHost();
	lastMidiBuffer.addEvents(midiMessages, 0, buffer.getNumSamples(), 0);
}

AudioProcessorEditor* SequencerLinearProcessor::createEditor()
{
	return new SequencerLinearEditor (*this);
}
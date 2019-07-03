#include "SequencerLinearProcessor.h"
#include "SequencerLinearEditor.h"
#include "../PluginParameter.h"

SequencerLinearProcessor::SequencerLinearProcessor(const PluginDescription& descr) : InternalPlugin (descr, true)
{
	lastPosInfo.resetToDefault();

	for (int i = 0; i < 16; i++)
	{
		sequencerNotes.set(i, SeqNote());

		AudioParameterInt *p = new AudioParameterInt(
			String::formatted("step_%d", i),
			String::formatted("Step %d", i),
			0, 131, 100
		);
		addParameter(p);
	}
}
SequencerLinearProcessor::~SequencerLinearProcessor() {}
void SequencerLinearProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	currentSampleRate = sampleRate;
}

void SequencerLinearProcessor::releaseResources() {}
void SequencerLinearProcessor::getStateInformation (MemoryBlock& destData) {}
void SequencerLinearProcessor::setStateInformation (const void* data, int sizeInBytes) {}
bool SequencerLinearProcessor::hasEditor() const { return true; }
bool SequencerLinearProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const { return true; }
const String SequencerLinearProcessor::getName() const { return "Sequencer Linear"; }
bool SequencerLinearProcessor::acceptsMidi() const { return true; }
bool SequencerLinearProcessor::producesMidi() const { return true; }
bool SequencerLinearProcessor::isMidiEffect() const { return true; }
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
			lastPosInfo = newTime;
			return;
		}
	}

	lastPosInfo.resetToDefault();
}

void SequencerLinearProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	updateCurrentTimeInfoFromHost();
}

void SequencerLinearProcessor::setSequencerNoteNumber(const int index, double noteNumber)
{
	const ScopedLock sl (getCallbackLock());
	sequencerNotes.getReference(index).number = noteNumber;
}

void SequencerLinearProcessor::setSequencerNoteState(const int index, SeqNoteState noteState)
{
	const ScopedLock sl (getCallbackLock());
	sequencerNotes.getReference(index).state = noteState;
}
AudioProcessorEditor* SequencerLinearProcessor::createEditor()
{
	return new SequencerLinearEditor (*this);
}
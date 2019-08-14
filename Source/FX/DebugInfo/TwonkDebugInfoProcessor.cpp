#include "TwonkDebugInfoProcessor.h"
#include "TwonkDebugInfoEditor.h"
#include "../PluginParameter.h"

DebugInfoProcessor::DebugInfoProcessor(const PluginDescription& descr): TwonkPlugin (descr)
{
	lastPosInfo.resetToDefault();
}
DebugInfoProcessor::~DebugInfoProcessor(){}
void DebugInfoProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){}
void DebugInfoProcessor::releaseResources(){}
void DebugInfoProcessor::getStateInformation (MemoryBlock& destData){}
void DebugInfoProcessor::setStateInformation (const void* data, int sizeInBytes){}
bool DebugInfoProcessor::hasEditor() const { return true; }
bool DebugInfoProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const { return true; }
const String DebugInfoProcessor::getName() const { return "Debug Info"; }
bool DebugInfoProcessor::acceptsMidi() const { return true; }
bool DebugInfoProcessor::producesMidi() const { return false; }
bool DebugInfoProcessor::isMidiEffect() const { return false; }
double DebugInfoProcessor::getTailLengthSeconds() const { return 0.0; }
int DebugInfoProcessor::getNumPrograms() { return 1; }
int DebugInfoProcessor::getCurrentProgram() { return 0; }
void DebugInfoProcessor::setCurrentProgram (int index){ }
const String DebugInfoProcessor::getProgramName (int index) { return {}; }
void DebugInfoProcessor::changeProgramName (int index, const String& newName) {}

void DebugInfoProcessor::updateCurrentTimeInfoFromHost()
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

void DebugInfoProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	updateCurrentTimeInfoFromHost();
	lastMidiBuffer.addEvents(midiMessages, 0, buffer.getNumSamples(), 0);
}

AudioProcessorEditor* DebugInfoProcessor::createEditor()
{
	return new DebugInfoProcessorEditor (*this);
}
#include "FifteenStepProcessor.h"
#include "FifteenStepEditor.h"
#include "../PluginParameter.h"

FifteenStepProcessor::FifteenStepProcessor(const PluginDescription& descr)
	: TwonkPlugin (descr), totalCols(16), speed(4), lastPlayheadStep(-1), playheadColPrecise(-1)
{
	lastPosInfo.resetToDefault();
}

FifteenStepProcessor::~FifteenStepProcessor() {}

void FifteenStepProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	lastPosInfo.resetToDefault();
	currSampleRate = sampleRate;
}

void FifteenStepProcessor::releaseResources()
{
}

void FifteenStepProcessor::getStateInformation (MemoryBlock& destData) {}

void FifteenStepProcessor::setStateInformation (const void* data, int sizeInBytes) {}

void FifteenStepProcessor::updateSequencer(AudioPlayHead::CurrentPositionInfo &lastPosInfo, AudioSampleBuffer& buffer)
{
	if (!lastPosInfo.isPlaying) {
		return;
	}

	double ppq = lastPosInfo.ppqPosition;

	playheadColPrecise = fmod (ppq * speed, 16);
	playheadCol = (int)playheadColPrecise;

	if (playheadCol != lastPlayheadStep)
	{
		lastPlayheadStep = playheadCol;

		double beatsPerSec = lastPosInfo.bpm * speed / 60.0;
		double secPerBeat = 1.0 / beatsPerSec;

		double playheadOffset = playheadColPrecise - playheadCol;
		int playheadOffsetSamples = playheadOffset * secPerBeat * currSampleRate;
		playheadOffsetSamples = jmax (buffer.getNumSamples() - playheadOffsetSamples - 1, 0);

		/*
		for (int i = 0; i < 16; i++)
		{

			Cell* cell = getCellAt (i, playheadCol);
			int noteNumber = cell->getNoteNumber();
			if (noteNumber != -1) {
				MidiMessage m = MidiMessage::noteOn(1, noteNumber, 0.9f);
				//midiMessages.addEvent (m, 0);
				midiMessages.addEvent (m, playheadOffsetSamples);
			}

		}*/
	}
}

void FifteenStepProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	if (auto* ph = getPlayHead())
	{
		AudioPlayHead::CurrentPositionInfo newTime;

		if (ph->getCurrentPosition (newTime))
		{
			lastPosInfo = newTime;  // Successfully got the current time from the host..
			updateSequencer(lastPosInfo, buffer);

			for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
				buffer.clear (i, 0, buffer.getNumSamples());

			return;
		}
	}

	lastPosInfo.resetToDefault();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear (i, 0, buffer.getNumSamples());	
}

AudioProcessorEditor* FifteenStepProcessor::createEditor()
{
	return new FifteenStepEditor (*this);
}
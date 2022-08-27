#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TwonkDebugInfoProcessor.h"

class DebugInfoProcessorEditor : public AudioProcessorEditor, public Timer
{
public:
	DebugInfoProcessorEditor (DebugInfoProcessor&);
    ~DebugInfoProcessorEditor();
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;
	void updateTimecodeDisplay (AudioPlayHead::PositionInfo pos);
	String timeToTimecodeString (double seconds);
	void updateMidiDisplay (MidiBuffer &midiBuffer);
private:
	DebugInfoProcessor& processor;
	Label timecodeDisplayLabel, midiBufferDisplayLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugInfoProcessorEditor)
};

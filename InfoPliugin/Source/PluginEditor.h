/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class InfoPliuginAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    InfoPliuginAudioProcessorEditor (InfoPliuginAudioProcessor&);
    ~InfoPliuginAudioProcessorEditor();

	
	void paint (Graphics&) override;
	void resized() override;
	void timerCallback() override;
	void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos);
	String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator);
	String timeToTimecodeString (double seconds);
	void updateMidiDisplay (MidiBuffer &midiBuffer);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    InfoPliuginAudioProcessor& processor;
	Label timecodeDisplayLabel, midiBufferDisplayLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoPliuginAudioProcessorEditor)
};

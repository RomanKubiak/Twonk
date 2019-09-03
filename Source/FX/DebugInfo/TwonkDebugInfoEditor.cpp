#include "TwonkDebugInfoEditor.h"
#include "TwonkDebugInfoProcessor.h"
#include "Twonk.h"
//==============================================================================

DebugInfoProcessorEditor::DebugInfoProcessorEditor (DebugInfoProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible (timecodeDisplayLabel);
	addAndMakeVisible (midiBufferDisplayLabel);
	timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 12.0f, Font::plain));
	midiBufferDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 12.0f, Font::plain));
    setSize (500, 200);
	startTimerHz (30);
}

DebugInfoProcessorEditor::~DebugInfoProcessorEditor()
{
}

void DebugInfoProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DebugInfoProcessorEditor::resized()
{
	timecodeDisplayLabel.setBounds(0, 0, getWidth(), getHeight()/4);
	midiBufferDisplayLabel.setBounds(0, getHeight()/4, getWidth(), getHeight()/4);
}

void DebugInfoProcessorEditor::timerCallback()
{
	updateTimecodeDisplay (processor.lastPosInfo);
	updateMidiDisplay (processor.lastMidiBuffer);
}

String DebugInfoProcessorEditor::timeToTimecodeString (double seconds)
{
	auto millisecs = roundToInt (seconds * 1000.0);
	auto absMillisecs = std::abs (millisecs);

	return String::formatted ("%02d:%02d:%02d.%03d",
		millisecs / 3600000,
		(absMillisecs / 60000) % 60,
		(absMillisecs / 1000) % 60,
		absMillisecs % 1000);
}

// Updates the text in our position label.
void DebugInfoProcessorEditor::updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
{
	MemoryOutputStream displayText;

	displayText << "[" << SystemStats::getJUCEVersion() << "]   "
		<< String (pos.bpm, 2) << " bpm, "
		<< pos.timeSigNumerator << '/' << pos.timeSigDenominator
		<< "  -  " << timeToTimecodeString (pos.timeInSeconds)
		<< "  -  " << quarterNotePositionToBarsBeatsString (pos.ppqPosition,
			pos.timeSigNumerator,
			pos.timeSigDenominator);

	if (pos.isRecording)
		displayText << "  (recording)";
	else if (pos.isPlaying)
		displayText << "  (playing)";

	timecodeDisplayLabel.setText (displayText.toString(), dontSendNotification);
}

void DebugInfoProcessorEditor::updateMidiDisplay (MidiBuffer &midiBuffer)
{
	MemoryOutputStream displayText;
	MidiBuffer::Iterator i(midiBuffer);
	MidiMessage event;
	int sample;
	while (i.getNextEvent(event, sample))
	{
		displayText << String(sample) << ": "
			<< event.getDescription()
			<< "\n";
	}

	midiBufferDisplayLabel.setText(displayText.toString(), dontSendNotification);
}

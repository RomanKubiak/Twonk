#include "PianoKeys.h"
#include "MidiControllerProcessor.h"

//==============================================================================

PianoKeys::PianoKeys (MidiControllerProcessor& p) : processor (p)
{
	midiKeyboard.reset(new MidiKeyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard));
	addAndMakeVisible(midiKeyboard.get());
	setName("Piano Keys");
	setSize(512, 256);
}

PianoKeys::~PianoKeys()
{
	midiKeyboard = nullptr;
}

void PianoKeys::resized()
{
	midiKeyboard->setBounds(getLocalBounds());
}

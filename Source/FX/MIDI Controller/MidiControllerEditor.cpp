#include "MidiControllerEditor.h"
#include "MidiControllerProcessor.h"

//==============================================================================

MidiControllerEditor::MidiControllerEditor (MidiControllerProcessor& p) : AudioProcessorEditor (&p), processor (p)
{
	midiKeyboard.reset(new MidiKeyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard));
	addAndMakeVisible(midiKeyboard.get());

	sizeConstrainer.reset(new ComponentBoundsConstrainer());
	sizeConstrainer->setMaximumWidth(900);
	sizeConstrainer->setMaximumHeight(500);
	sizeConstrainer->setMinimumHeight(64);
	sizeConstrainer->setMinimumWidth(128);
	cornerResizer.reset(new ResizableCornerComponent(this, sizeConstrainer.get()));
	addAndMakeVisible(cornerResizer.get());

	setSize(128, 128);
}

MidiControllerEditor::~MidiControllerEditor()
{
}

void MidiControllerEditor::paint (Graphics& g)
{
}

void MidiControllerEditor::resized()
{
	DBG("MidiControllerEditor::resized " + getLocalBounds().toString());
	midiKeyboard->setBounds(getLocalBounds());
	cornerResizer->setBounds(getWidth() - 32, getHeight() - 32, 32, 32);
}

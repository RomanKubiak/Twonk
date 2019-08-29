#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MidiControllerProcessor;
class PianoKeys : public Component
{
	public:
		PianoKeys (MidiControllerProcessor &);
		~PianoKeys();
		void resized() override;
	private:
		std::unique_ptr<MidiKeyboardComponent> midiKeyboard;
		MidiControllerProcessor& processor;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PianoKeys)
};

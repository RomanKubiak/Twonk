#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiControllerProcessor.h"

class MidiControllerEditor : public AudioProcessorEditor
{
	public:
		MidiControllerEditor (MidiControllerProcessor &);
		~MidiControllerEditor();
		void paint (Graphics&) override;
		void resized() override;
	private:
		std::unique_ptr<MidiKeyboardComponent> midiKeyboard;
		std::unique_ptr<ResizableCornerComponent> cornerResizer;
		std::unique_ptr<ComponentBoundsConstrainer> sizeConstrainer;
		MidiControllerProcessor& processor;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiControllerEditor)
};

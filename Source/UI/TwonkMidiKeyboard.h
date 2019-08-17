#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TwonkLookAndFeel.h"
class TwonkToolBarButton;

class TwonkMidiKeyboard  : public Component, public Slider::Listener
{
public:
    TwonkMidiKeyboard (MidiKeyboardState &state, MidiKeyboardComponent::Orientation orientation);
    ~TwonkMidiKeyboard();
    void paint (Graphics& g) override;
    void resized() override;
	void mouseDown(const MouseEvent &e) override;
	void mouseDrag(const MouseEvent &e) override;
	void sliderValueChanged(Slider *) override;
private:
	ComponentDragger dragger;
	std::unique_ptr <ResizableCornerComponent> corner;
	std::unique_ptr <MidiKeyboardComponent> midiKeyboardComponent;
	std::unique_ptr <Slider> keyWidth;
	std::unique_ptr <Slider> keyHeight;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkMidiKeyboard)
};


/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
struct SimplerInstrument;
class SimplerEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentButton  : public Component,
                          public Button::Listener
{
public:
    //==============================================================================
    InstrumentButton (SimplerEditor &_owner);
    ~InstrumentButton();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setInfo(SimplerInstrument *instrument);
	void setSelected(const bool _selected);
	void toggleSelected() { setSelected(!selected); repaint(); }
	bool isSelected() { return (selected); }
	void previewAudio();
	SimplerInstrument *getCurrentInstrument() { return (currentInstrument); }
	void setCurrentInstrument(SimplerInstrument *_currentInstrument);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimplerEditor &owner;
	bool selected;
	int midiNote;
	int midiChannel;
	int audioChannel;
	String name;
	SimplerInstrument *currentInstrument;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> instrumentName;
    std::unique_ptr<TextButton> muteButton;
    std::unique_ptr<TextButton> soloButton;
    std::unique_ptr<Label> instrumentNote;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentButton)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


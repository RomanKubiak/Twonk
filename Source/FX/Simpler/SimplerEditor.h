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
#include "InstrumentButton.h"
#include "UI/MainHostWindow.h"
#include "UI/TwonkLookAndFeel.h"
class SimplerProcessor;
class InstrumentButtonsPanel;
class InstrumentParametersEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SimplerEditor  : public AudioProcessorEditor,
                       public ChangeListener,
                       public AudioProcessorValueTreeState::Listener,
                       public ComboBox::Listener
{
public:
    //==============================================================================
    SimplerEditor (SimplerProcessor &_processor);
    ~SimplerEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	void loadInstrumentsToGui();
	void currentInstrumentSelectionChanged(InstrumentButton *buttonSelected);
	void loadBanksToCombo();
	SimplerProcessor &getNamedAudioProcessor() { return (processor); }
	void parameterChanged (const String &parameterID, float newValue);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimplerProcessor &processor;
	InstrumentParametersEditor *instrumentEditor;
	std::unique_ptr<ResizableCornerComponent> cornerResizer;
	std::unique_ptr<ComponentBoundsConstrainer> sizeConstrainer;
	TwonkLookAndFeel twonkLookAndFeel;
	InstrumentButtonsPanel *buttonsPanel;
	std::unique_ptr< AudioProcessorValueTreeState::ComboBoxAttachment> bankListLink;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> bankListCombo;
    std::unique_ptr<ConcertinaPanel> panel;
    std::unique_ptr<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplerEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


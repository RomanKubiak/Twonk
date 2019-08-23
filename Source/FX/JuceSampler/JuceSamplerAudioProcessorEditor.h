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
#include "../../../JuceLibraryCode/JuceHeader.h"
class JucesamplerAudioProcessor;
//[/Headers]

#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentButton.h"
#include "InstrumentWaveViewer.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JuceSamplerAudioProcessorEditor  : public AudioProcessorEditor,
                                         public ChangeListener,
                                         public ComboBox::Listener
{
public:
    //==============================================================================
    JuceSamplerAudioProcessorEditor (JucesamplerAudioProcessor &_processor);
    ~JuceSamplerAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	void loadBank(ZipFile &z);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	JucesamplerAudioProcessor &processor;

	TimeSliceThread directoryThread{ "Image File Scanner Thread" };
	WildcardFileFilter zipWildcard{ "*.zip", "", "ZIP files" };
	DirectoryContentsList programList{ &zipWildcard, directoryThread };
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> bankListCombo;
    std::unique_ptr<InstrumentButton> instrumentButton1;
    std::unique_ptr<InstrumentButton> instrumentButton2;
    std::unique_ptr<InstrumentButton> instrumentButton3;
    std::unique_ptr<InstrumentButton> instrumentButton4;
    std::unique_ptr<InstrumentButton> instrumentButton5;
    std::unique_ptr<InstrumentButton> instrumentButton6;
    std::unique_ptr<InstrumentButton> instrumentButton7;
    std::unique_ptr<InstrumentButton> instrumentButton8;
    std::unique_ptr<InstrumentButton> instrumentButton9;
    std::unique_ptr<InstrumentButton> instrumentButton10;
    std::unique_ptr<InstrumentButton> instrumentButton11;
    std::unique_ptr<InstrumentButton> instrumentButton12;
    std::unique_ptr<InstrumentButton> instrumentButton13;
    std::unique_ptr<InstrumentButton> instrumentButton14;
    std::unique_ptr<InstrumentButton> instrumentButton15;
    std::unique_ptr<InstrumentButton> instrumentButton16;
    std::unique_ptr<InstrumentButton> instrumentButton17;
    std::unique_ptr<InstrumentButton> instrumentButton18;
    std::unique_ptr<InstrumentWaveViewer> component;
    std::unique_ptr<Label> bankInfo;
    std::unique_ptr<HyperlinkButton> bankUrl;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSamplerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


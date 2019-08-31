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
#include "UI/TwonkLookAndFeel.h"
struct SamplerInstrument;
class SimplerProcessor;
//[/Headers]

#include "InstrumentWaveViewer.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentParametersEditor  : public Component,
                                    public Slider::Listener
{
public:
    //==============================================================================
    InstrumentParametersEditor (SimplerProcessor &_processor);
    ~InstrumentParametersEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setEditedInstrument(SimplerInstrument *si);
	void parameterChanged (const String &parameterID, float newValue);
	void setEditedSound (SimplerSound *editedSound);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TwonkLookAndFeel twonkLookAndFeel;
	SimplerProcessor &processor;
	SimplerInstrument *currentSamplerInstrument;
	SimplerSound *currentSimplerSound;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<InstrumentWaveViewer> waveViewer;
    std::unique_ptr<Slider> attack;
    std::unique_ptr<Slider> decay;
    std::unique_ptr<Slider> sustain;
    std::unique_ptr<Slider> release;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentParametersEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


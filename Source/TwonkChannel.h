/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
class TwonkMain;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkChannel  : public Component,
                      public ComboBox::Listener
{
public:
    //==============================================================================
    TwonkChannel (TwonkMain *_parent, uint8_t _idx);
    ~TwonkChannel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TwonkMain *parent;
    uint8_t idx;
	AudioProcessor *currentAudioProcessor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> comboBox;
    std::unique_ptr<ComboBox> comboBox2;
    std::unique_ptr<ComboBox> comboBox3;
    std::unique_ptr<ComboBox> comboBox4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkChannel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


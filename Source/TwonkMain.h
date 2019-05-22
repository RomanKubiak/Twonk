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
#include "TwonkLookAndFeel.h"
//[/Headers]

#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkChannel.h"
#include "TwonkToolbar.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkMain  : public AudioAppComponent
{
public:
    //==============================================================================
    TwonkMain ();
    ~TwonkMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void prepareToPlay (int, double) override;
	void releaseResources() override;
	void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
	AudioProcessorGraph &getProcessorGraph() { return (processorGraph); }
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	std::unique_ptr<TimeSliceThread> uiManagerThread;
	Typeface::Ptr defaultTypeface;
	TwonkLookAndFeel twonkLookAndFeel;
	AudioProcessorGraph processorGraph;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkChannel> ch1;
    std::unique_ptr<TwonkChannel> ch2;
    std::unique_ptr<TwonkChannel> ch3;
    std::unique_ptr<TwonkChannel> ch4;
    std::unique_ptr<TwonkChannel> ch5;
    std::unique_ptr<TwonkChannel> ch6;
    std::unique_ptr<TwonkChannel> ch7;
    std::unique_ptr<TwonkChannel> ch8;
    std::unique_ptr<TwonkToolbar> toolbar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkMain)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


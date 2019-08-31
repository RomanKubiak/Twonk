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
#include "SimplerProcessor.h"
class SimplerSound;
class InstrumentParametersEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentWaveViewer  : public Component,
                              public ChangeListener,
                              public ComboBox::Listener,
                              public Slider::Listener
{
public:
    //==============================================================================
    InstrumentWaveViewer (InstrumentParametersEditor &_owner, SimplerProcessor &_processor);
    ~InstrumentWaveViewer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds);
	void paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds);
	void changeListenerCallback (ChangeBroadcaster* source);
	void thumbnailChanged();
	void setSoundToShow(SimplerInstrument *instrument);
	void loadNewThumbnail(SimplerSound *sound);
	void setSampleData(SimplerSound *sound);
	void fillSampleCombo(SimplerInstrument *instrumentToShow);
	void setVelocityRangeData(SimplerSound *sound);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioThumbnailCache thumbnailCache;
	AudioThumbnail thumbnail;
	SimplerInstrument *instrumentToShow;
	SimplerProcessor &processor;
	SimplerSound *lastSelectedSound;
	InstrumentParametersEditor &owner;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> soundName;
    std::unique_ptr<Label> soundData;
    std::unique_ptr<ComboBox> sampleList;
    std::unique_ptr<Slider> velocityRange;
    std::unique_ptr<Label> velocityRangeLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentWaveViewer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


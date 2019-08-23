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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InstrumentWaveViewer  : public Component,
                              public ChangeListener
{
public:
    //==============================================================================
    InstrumentWaveViewer ();
    ~InstrumentWaveViewer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds);
	void paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds);
	void changeListenerCallback (ChangeBroadcaster* source);
	void thumbnailChanged();
	void loadData(InputStream *dataInputStream);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioThumbnailCache thumbnailCache;
	AudioThumbnail thumbnail;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioFormatManager formatManager;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentWaveViewer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


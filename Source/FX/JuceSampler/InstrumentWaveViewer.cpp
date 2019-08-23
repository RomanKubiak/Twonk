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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "InstrumentWaveViewer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentWaveViewer::InstrumentWaveViewer ()
    : thumbnailCache (5), thumbnail (512, formatManager, thumbnailCache)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentWaveViewer::~InstrumentWaveViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentWaveViewer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
	Rectangle<int> thumbnailBounds (0, 0, getWidth(), getHeight());

	if (thumbnail.getNumChannels() == 0)
		paintIfNoFileLoaded (g, thumbnailBounds);
	else
		paintIfFileLoaded (g, thumbnailBounds);
    //[/UserPaint]
}

void InstrumentWaveViewer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentWaveViewer::paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour (Colours::darkgrey);
	g.fillRect (thumbnailBounds);
	g.setColour (Colours::white);
	g.drawFittedText ("No File Loaded", thumbnailBounds, Justification::centred, 1.0f);
}

void InstrumentWaveViewer::paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour (Colours::white);
	g.fillRect (thumbnailBounds);

	g.setColour (Colours::red);                                     // [8]

	thumbnail.drawChannels (g,                                      // [9]
		thumbnailBounds,
		0.0,                                    // start time
		thumbnail.getTotalLength(),             // end time
		1.0f);                                  // vertical zoom
}

void InstrumentWaveViewer::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == &thumbnail)
		thumbnailChanged();
}

void InstrumentWaveViewer::thumbnailChanged()
{
	repaint();
}

void InstrumentWaveViewer::loadData(InputStream *dataInputStream)
{
	auto* reader = formatManager.createReaderFor(dataInputStream);
	if (reader != nullptr)
	{
		thumbnail.setReader(reader, 0);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentWaveViewer" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams=""
                 variableInitialisers="thumbnailCache (5), thumbnail (512, formatManager, thumbnailCache)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


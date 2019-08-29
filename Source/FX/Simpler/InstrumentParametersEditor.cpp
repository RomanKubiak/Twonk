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
#include "SimplerProcessor.h"
//[/Headers]

#include "InstrumentParametersEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentParametersEditor::InstrumentParametersEditor (SimplerProcessor &_processor)
    : processor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
	setLookAndFeel(&twonkLookAndFeel);
    //[/Constructor_pre]

    waveViewer.reset (new InstrumentWaveViewer (processor));
    addAndMakeVisible (waveViewer.get());
    waveViewer->setBounds (8, 8, 448, 232);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 250);


    //[Constructor] You can add your own custom stuff here..

    //[/Constructor]
}

InstrumentParametersEditor::~InstrumentParametersEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
    //[/Destructor_pre]

    waveViewer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentParametersEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentParametersEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentParametersEditor::parameterChanged (const String &parameterID, float newValue)
{
}

void InstrumentParametersEditor::setEditedInstrument(SimplerInstrument *si)
{
	currentSamplerInstrument = si;
	waveViewer->setSoundToShow(si);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentParametersEditor"
                 componentName="" parentClasses="public Component" constructorParams="SimplerProcessor &amp;_processor"
                 variableInitialisers="processor(_processor)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="700"
                 initialHeight="250">
  <BACKGROUND backgroundColour="0"/>
  <JUCERCOMP name="" id="eb72ef829a6868cf" memberName="waveViewer" virtualName=""
             explicitFocusOrder="0" pos="8 8 448 232" sourceFile="InstrumentWaveViewer.cpp"
             constructorParams="processor"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


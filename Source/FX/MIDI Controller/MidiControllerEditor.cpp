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
#include "MidiControllerProcessor.h"
#include "PianoKeys.h"
#include "HexagonController.h"
//[/Headers]

#include "MidiControllerEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiControllerEditor::MidiControllerEditor (MidiControllerProcessor &_processor)
    : AudioProcessorEditor(_processor), processor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    panel.reset (new ConcertinaPanel());
    addAndMakeVisible (panel.get());

    corner.reset (new ResizableCornerComponent (this, nullptr));
    addAndMakeVisible (corner.get());
    corner->setName ("new component");


    //[UserPreSize]
	panel->addPanel(0, new PianoKeys(processor), true);
	//panel->addPanel(1, hexagonController = new HexagonController(), true);
	//panel->setPanelHeaderSize(pianoKeys, 28);
	//panel->setPanelHeaderSize(hexagonController, 28);
	//panel->expandPanelFully(pianoKeys, false);

	// set lookAndFeel only after a panel has been added
	// otherwise bad things happen
	//setLookAndFeel(&lookAndFeel);
	
    //[/UserPreSize]

    setSize (600, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MidiControllerEditor::~MidiControllerEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//setLookAndFeel(nullptr);
    //[/Destructor_pre]

    panel = nullptr;
    corner = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiControllerEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiControllerEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    panel->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    corner->setBounds (getWidth() - 24, getHeight() - 24, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiControllerEditor" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="MidiControllerProcessor &amp;_processor"
                 variableInitialisers="AudioProcessorEditor(_processor), processor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="256">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="" id="9a0224d9b0d0e31a" memberName="panel" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="ConcertinaPanel"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="8ba15d77c6a661f7" memberName="corner"
                    virtualName="" explicitFocusOrder="0" pos="24R 24R 24 24" class="ResizableCornerComponent"
                    params="this, nullptr"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


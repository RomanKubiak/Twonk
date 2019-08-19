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
#include "BinaryData.h"
//[/Headers]

#include "TwonkSaveFileDialog.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkSaveFileDialog::TwonkSaveFileDialog ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    saveButton.reset (new TextButton ("Save"));
    addAndMakeVisible (saveButton.get());
    saveButton->addListener (this);
    saveButton->setColour (TextButton::buttonColourId, Colour (0xdc0bdd40));

    cancelButton.reset (new TextButton ("Cancel"));
    addAndMakeVisible (cancelButton.get());
    cancelButton->addListener (this);
    cancelButton->setColour (TextButton::buttonColourId, Colour (0xffdf5454));

    programName.reset (new Label ("Program Name",
                                  TRANS("Program Name")));
    addAndMakeVisible (programName.get());
    programName->setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.013f));
    programName->setJustificationType (Justification::centred);
    programName->setEditable (true, true, false);
    programName->setColour (Label::backgroundColourId, Colour (0x4d4cdcff));
    programName->setColour (Label::outlineColourId, Colour (0xf4ffffff));
    programName->setColour (TextEditor::textColourId, Colours::black);
    programName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    programName->addListener (this);

    fxProgamType.reset (new ImageButton ("Effect Program"));
    addAndMakeVisible (fxProgamType.get());
    fxProgamType->setTooltip (TRANS("Use this to indicate your program is a typical effect processing program"));
    fxProgamType->setButtonText (TRANS("new button"));
    fxProgamType->addListener (this);

    fxProgamType->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::icon_effect_png, BinaryData::icon_effect_pngSize), 0.200f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::icon_effect_png, BinaryData::icon_effect_pngSize), 0.661f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::icon_effect_png, BinaryData::icon_effect_pngSize), 1.000f, Colour (0x00000000));
    generatorProgram.reset (new ImageButton ("Generator Program"));
    addAndMakeVisible (generatorProgram.get());
    generatorProgram->setTooltip (TRANS("Use this to indicate your program is a typical synthesizer  program"));
    generatorProgram->setButtonText (TRANS("new button"));
    generatorProgram->addListener (this);

    generatorProgram->setImages (false, true, true,
                                 ImageCache::getFromMemory (BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize), 0.209f, Colour (0x00000000),
                                 ImageCache::getFromMemory (BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize), 0.626f, Colour (0x00000000),
                                 ImageCache::getFromMemory (BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize), 1.000f, Colour (0x00000000));
    midiProgram.reset (new ImageButton ("MIDI Program"));
    addAndMakeVisible (midiProgram.get());
    midiProgram->setTooltip (TRANS("Use this to indicate your program is MIDI processor"));
    midiProgram->setButtonText (TRANS("new button"));
    midiProgram->addListener (this);

    midiProgram->setImages (false, true, true,
                            ImageCache::getFromMemory (BinaryData::icon_midi_64_png, BinaryData::icon_midi_64_pngSize), 0.209f, Colour (0x00000000),
                            ImageCache::getFromMemory (BinaryData::icon_midi_64_png, BinaryData::icon_midi_64_pngSize), 0.450f, Colour (0x00000000),
                            ImageCache::getFromMemory (BinaryData::icon_midi_64_png, BinaryData::icon_midi_64_pngSize), 1.000f, Colour (0x00000000));
    generalProgram.reset (new ImageButton ("General Program"));
    addAndMakeVisible (generalProgram.get());
    generalProgram->setTooltip (TRANS("Use this to indicate your program general usage program"));
    generalProgram->setButtonText (TRANS("new button"));
    generalProgram->addListener (this);

    generalProgram->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::icon_project_png, BinaryData::icon_project_pngSize), 0.209f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::icon_project_png, BinaryData::icon_project_pngSize), 0.626f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::icon_project_png, BinaryData::icon_project_pngSize), 1.000f, Colour (0x00000000));

    //[UserPreSize]
	generatorProgram->setClickingTogglesState(true);
	generatorProgram->setRadioGroupId(1, dontSendNotification);
	fxProgamType->setClickingTogglesState(true);
	fxProgamType->setRadioGroupId(1, dontSendNotification);
	midiProgram->setClickingTogglesState(true);
	midiProgram->setRadioGroupId(1, dontSendNotification);
	generalProgram->setClickingTogglesState(true);
	generalProgram->setRadioGroupId(1, dontSendNotification);
    //[/UserPreSize]

    setSize (320, 320);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkSaveFileDialog::~TwonkSaveFileDialog()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    saveButton = nullptr;
    cancelButton = nullptr;
    programName = nullptr;
    fxProgamType = nullptr;
    generatorProgram = nullptr;
    midiProgram = nullptr;
    generalProgram = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkSaveFileDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x51000000));

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xff898989), fillColour2 = Colour (0xff5e5e5e);
        Colour strokeColour = Colour (0xb0000000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       160.0f - 0.0f + x,
                                       200.0f - 0.0f + y,
                                       fillColour2,
                                       160.0f - 0.0f + x,
                                       8.0f - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkSaveFileDialog::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    saveButton->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.8500f), proportionOfWidth (0.3000f), proportionOfHeight (0.1000f));
    cancelButton->setBounds (proportionOfWidth (0.6000f), proportionOfHeight (0.8500f), proportionOfWidth (0.3000f), proportionOfHeight (0.1000f));
    programName->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.1000f), proportionOfWidth (0.8000f), proportionOfHeight (0.1500f));
    fxProgamType->setBounds (proportionOfWidth (0.2250f), proportionOfHeight (0.3000f), proportionOfWidth (0.2000f), proportionOfHeight (0.2000f));
    generatorProgram->setBounds (proportionOfWidth (0.6000f), proportionOfHeight (0.3000f), proportionOfWidth (0.2000f), proportionOfHeight (0.2000f));
    midiProgram->setBounds (proportionOfWidth (0.2250f), proportionOfHeight (0.5500f), proportionOfWidth (0.2000f), proportionOfHeight (0.2000f));
    generalProgram->setBounds (proportionOfWidth (0.6000f), proportionOfHeight (0.5500f), proportionOfWidth (0.2000f), proportionOfHeight (0.2000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkSaveFileDialog::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == saveButton.get())
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
			dw->exitModalState ((int)programType);
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == cancelButton.get())
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
		if (DialogWindow* dw = findParentComponentOfClass<DialogWindow>())
			dw->exitModalState (-1);
        //[/UserButtonCode_cancelButton]
    }
    else if (buttonThatWasClicked == fxProgamType.get())
    {
        //[UserButtonCode_fxProgamType] -- add your button handler code here..
		programType = Effect;
        //[/UserButtonCode_fxProgamType]
    }
    else if (buttonThatWasClicked == generatorProgram.get())
    {
        //[UserButtonCode_generatorProgram] -- add your button handler code here..
		programType = Synth;
        //[/UserButtonCode_generatorProgram]
    }
    else if (buttonThatWasClicked == midiProgram.get())
    {
        //[UserButtonCode_midiProgram] -- add your button handler code here..
		programType = MIDI;
        //[/UserButtonCode_midiProgram]
    }
    else if (buttonThatWasClicked == generalProgram.get())
    {
        //[UserButtonCode_generalProgram] -- add your button handler code here..
		programType = General;
        //[/UserButtonCode_generalProgram]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TwonkSaveFileDialog::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == programName.get())
    {
        //[UserLabelCode_programName] -- add your label text handling code here..
        //[/UserLabelCode_programName]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkSaveFileDialog" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="320" initialHeight="320">
  <BACKGROUND backgroundColour="51000000">
    <RECT pos="0 0 0M 0M" fill="linear: 160 200, 160 8, 0=ff898989, 1=ff5e5e5e"
          hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: b0000000"/>
  </BACKGROUND>
  <TEXTBUTTON name="Save" id="857d207ba7463537" memberName="saveButton" virtualName=""
              explicitFocusOrder="0" pos="10% 85% 30% 10%" bgColOff="dc0bdd40"
              buttonText="Save" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Cancel" id="b0e0292cc227f36d" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="60% 85% 30% 10%" bgColOff="ffdf5454"
              buttonText="Cancel" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Program Name" id="11eb7b7779af829" memberName="programName"
         virtualName="" explicitFocusOrder="0" pos="10% 10% 80% 15%" bkgCol="4d4cdcff"
         outlineCol="f4ffffff" edTextCol="ff000000" edBkgCol="0" labelText="Program Name"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18.0" kerning="0.013" bold="0"
         italic="0" justification="36"/>
  <IMAGEBUTTON name="Effect Program" id="c5541012848f3159" memberName="fxProgamType"
               virtualName="" explicitFocusOrder="0" pos="22.5% 30% 20% 20%"
               tooltip="Use this to indicate your program is a typical effect processing program"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::icon_effect_png"
               opacityNormal="0.2000000029802322" colourNormal="0" resourceOver="BinaryData::icon_effect_png"
               opacityOver="0.6608695387840271" colourOver="0" resourceDown="BinaryData::icon_effect_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Generator Program" id="6855181d892626b" memberName="generatorProgram"
               virtualName="" explicitFocusOrder="0" pos="60% 30% 20% 20%" tooltip="Use this to indicate your program is a typical synthesizer  program"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::icon_synth_png"
               opacityNormal="0.208695650100708" colourNormal="0" resourceOver="BinaryData::icon_synth_png"
               opacityOver="0.626086950302124" colourOver="0" resourceDown="BinaryData::icon_synth_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="MIDI Program" id="b884c16a8afad414" memberName="midiProgram"
               virtualName="" explicitFocusOrder="0" pos="22.5% 55% 20% 20%"
               tooltip="Use this to indicate your program is MIDI processor"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::icon_midi_64_png"
               opacityNormal="0.208695650100708" colourNormal="0" resourceOver="BinaryData::icon_midi_64_png"
               opacityOver="0.450305700302124" colourOver="0" resourceDown="BinaryData::icon_midi_64_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="General Program" id="bdedc12d6ed4d00b" memberName="generalProgram"
               virtualName="" explicitFocusOrder="0" pos="60% 55% 20% 20%" tooltip="Use this to indicate your program general usage program"
               buttonText="new button" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::icon_project_png"
               opacityNormal="0.208695650100708" colourNormal="0" resourceOver="BinaryData::icon_project_png"
               opacityOver="0.626086950302124" colourOver="0" resourceDown="BinaryData::icon_project_png"
               opacityDown="1.0" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


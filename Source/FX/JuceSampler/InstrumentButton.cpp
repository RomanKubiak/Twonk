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

#include "InstrumentButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentButton::InstrumentButton ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    instrumentName.reset (new Label (String(),
                                     TRANS("Instrument")));
    addAndMakeVisible (instrumentName.get());
    instrumentName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentName->setJustificationType (Justification::centred);
    instrumentName->setEditable (false, false, false);
    instrumentName->setColour (Label::textColourId, Colour (0xff595959));
    instrumentName->setColour (TextEditor::textColourId, Colours::black);
    instrumentName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    muteButton.reset (new TextButton ("new button"));
    addAndMakeVisible (muteButton.get());
    muteButton->setButtonText (TRANS("M"));
    muteButton->addListener (this);
    muteButton->setColour (TextButton::buttonColourId, Colour (0xffeb0000));

    textButton2.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton2.get());
    textButton2->setButtonText (TRANS("S"));
    textButton2->addListener (this);
    textButton2->setColour (TextButton::buttonColourId, Colour (0xff0dbf00));

    label.reset (new Label ("new label",
                            TRANS("D#")));
    addAndMakeVisible (label.get());
    label->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::backgroundColourId, Colours::black);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (64, 72);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentButton::~InstrumentButton()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    instrumentName = nullptr;
    muteButton = nullptr;
    textButton2 = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentButton::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour1 = Colours::white, fillColour2 = Colour (0xffa4a4a4);
        Colour strokeColour = Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       0.0f - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 2.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 2.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentButton::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    instrumentName->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.5000f));
    muteButton->setBounds (2, proportionOfHeight (0.5000f), 28, proportionOfHeight (0.2778f));
    textButton2->setBounds (2 + 28 - -4, proportionOfHeight (0.5000f), 28, proportionOfHeight (0.2778f));
    label->setBounds (4, proportionOfHeight (0.8056f), getWidth() - 8, proportionOfHeight (0.1667f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void InstrumentButton::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteButton.get())
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        //[/UserButtonCode_muteButton]
    }
    else if (buttonThatWasClicked == textButton2.get())
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentButton" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="64" initialHeight="72">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="2.0" fill="linear: 0 0, 0 0R, 0=ffffffff, 1=ffa4a4a4"
               hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <LABEL name="" id="41b2fc1df68cb5fe" memberName="instrumentName" virtualName=""
         explicitFocusOrder="0" pos="0 0 100% 50%" textCol="ff595959"
         edTextCol="ff000000" edBkgCol="0" labelText="Instrument" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="new button" id="853c62af9ba8662c" memberName="muteButton"
              virtualName="" explicitFocusOrder="0" pos="2 50% 28 27.778%"
              bgColOff="ffeb0000" buttonText="M" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="375fe5224d77cc3e" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="-4R 50% 28 27.778%"
              posRelativeX="853c62af9ba8662c" bgColOff="ff0dbf00" buttonText="S"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="d375574c84583205" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="4 80.556% 8M 16.667%" bkgCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="D#" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


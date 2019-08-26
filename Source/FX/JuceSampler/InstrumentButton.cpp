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
#include "CTAGSampler.h"
//[/Headers]

#include "InstrumentButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "JuceSamplerAudioProcessorEditor.h"
#include "JuceSamplerAudioProcessor.h"
//[/MiscUserDefs]

//==============================================================================
InstrumentButton::InstrumentButton (JuceSamplerAudioProcessorEditor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
	selected = false;
    //[/Constructor_pre]

    instrumentName.reset (new Label (String(),
                                     String()));
    addAndMakeVisible (instrumentName.get());
    instrumentName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentName->setJustificationType (Justification::centred);
    instrumentName->setEditable (false, false, false);
    instrumentName->setColour (Label::textColourId, Colour (0xff595959));
    instrumentName->setColour (TextEditor::textColourId, Colours::black);
    instrumentName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    muteButton.reset (new TextButton (String()));
    addAndMakeVisible (muteButton.get());
    muteButton->setButtonText (TRANS("M"));
    muteButton->addListener (this);
    muteButton->setColour (TextButton::buttonColourId, Colour (0xffeb0000));

    soloButton.reset (new TextButton (String()));
    addAndMakeVisible (soloButton.get());
    soloButton->setButtonText (TRANS("S"));
    soloButton->addListener (this);
    soloButton->setColour (TextButton::buttonColourId, Colour (0xff0dbf00));

    instrumentNote.reset (new Label (String(),
                                     String()));
    addAndMakeVisible (instrumentNote.get());
    instrumentNote->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    instrumentNote->setJustificationType (Justification::centred);
    instrumentNote->setEditable (false, false, false);
    instrumentNote->setColour (Label::backgroundColourId, Colour (0xbf313131));
    instrumentNote->setColour (Label::textColourId, Colour (0xffababab));
    instrumentNote->setColour (TextEditor::textColourId, Colours::black);
    instrumentNote->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
	midiNote = 1;
	midiChannel = 1;
	instrumentName->addMouseListener(this, true);
	muteButton->setClickingTogglesState(true);
	soloButton->setClickingTogglesState(true);
    //[/UserPreSize]

    setSize (80, 80);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentButton::~InstrumentButton()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    instrumentName = nullptr;
    muteButton = nullptr;
    soloButton = nullptr;
    instrumentNote = nullptr;


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
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		if (selected)
    		{
    			fillColour1 = Colour(0xffc8ff67);
    			fillColour2 = Colour (0xff748100);
    		}
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       0.0f - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentButton::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    instrumentName->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.4000f));
    muteButton->setBounds (proportionOfWidth (0.0390f), proportionOfHeight (0.4000f), proportionOfWidth (0.4286f), proportionOfHeight (0.3444f));
    soloButton->setBounds (proportionOfWidth (0.5195f), proportionOfHeight (0.4000f), proportionOfWidth (0.4286f), proportionOfHeight (0.3444f));
    instrumentNote->setBounds (proportionOfWidth (0.0520f), proportionOfHeight (0.8000f), proportionOfWidth (0.8961f), proportionOfHeight (0.1556f));
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
    else if (buttonThatWasClicked == soloButton.get())
    {
        //[UserButtonCode_soloButton] -- add your button handler code here..
        //[/UserButtonCode_soloButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void InstrumentButton::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.eventComponent == instrumentName.get())
	{
		owner.currentInstrumentSelectionChanged(this);
	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentButton::setInfo(SamplerInstrument *instrument)
{
	midiNote = instrument->midiNote;
	midiChannel = instrument->midiChannel;
	audioChannel = instrument->audioOutputChannel;
	name = instrument->name;

	instrumentName->setText(name, dontSendNotification);
	instrumentNote->setText(MidiMessage::getMidiNoteName(midiNote, true, true, 3), dontSendNotification);

	if (MidiMessage::isMidiNoteBlack(midiNote))
	{
		instrumentNote->setColour(Label::backgroundColourId, Colours::black);
		instrumentNote->setColour(Label::textColourId, Colours::white);
	}
	else
	{
		instrumentNote->setColour(Label::backgroundColourId, Colours::white);
		instrumentNote->setColour(Label::textColourId, Colours::black);
	}
}

void InstrumentButton::setSelected(const bool _selected)
{
	selected = _selected;
	repaint();
}

void InstrumentButton::previewAudio()
{
	owner.getNamedProcessor().getAdditionalMidiBuffer().addEvent(MidiMessage::noteOn(midiChannel, midiNote, (uint8)127), 1);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentButton" componentName=""
                 parentClasses="public Component" constructorParams="JuceSamplerAudioProcessorEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="80"
                 initialHeight="80">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="2.0" fill="linear: 0 0, 0 0R, 0=ffffffff, 1=ffa4a4a4"
               hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="41b2fc1df68cb5fe" memberName="instrumentName" virtualName=""
         explicitFocusOrder="0" pos="0 0 100% 40%" textCol="ff595959"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="853c62af9ba8662c" memberName="muteButton" virtualName=""
              explicitFocusOrder="0" pos="3.75% 40% 42.5% 35%" bgColOff="ffeb0000"
              buttonText="M" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="375fe5224d77cc3e" memberName="soloButton" virtualName=""
              explicitFocusOrder="0" pos="52.5% 40% 42.5% 35%" bgColOff="ff0dbf00"
              buttonText="S" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="d375574c84583205" memberName="instrumentNote" virtualName=""
         explicitFocusOrder="0" pos="5% 80% 90% 15%" bkgCol="bf313131"
         textCol="ffababab" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="13.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


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

#include "InstrumentParametersEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentParametersEditor::InstrumentParametersEditor ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	setLookAndFeel(&twonkLookAndFeel);
    //[/Constructor_pre]

    envelopeAttack.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack.get());
    envelopeAttack->setRange (0, 255, 1);
    envelopeAttack->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack->setColour (Slider::rotarySliderFillColourId, Colour (0xffff3a3a));
    envelopeAttack->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffeb2c2c));
    envelopeAttack->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack->addListener (this);

    envelopeAttack->setBounds (16, 32, 88, 88);

    toggleButton.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton.get());
    toggleButton->setButtonText (TRANS("Filter"));
    toggleButton->addListener (this);

    toggleButton->setBounds (16, 8, 88, 24);

    toggleButton2.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton2.get());
    toggleButton2->setButtonText (TRANS("Distortion"));
    toggleButton2->addListener (this);

    toggleButton2->setBounds (112, 8, 88, 24);

    envelopeAttack5.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack5.get());
    envelopeAttack5->setRange (0, 255, 1);
    envelopeAttack5->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack5->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack5->setColour (Slider::rotarySliderFillColourId, Colour (0xffff3a3a));
    envelopeAttack5->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffeb2c2c));
    envelopeAttack5->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack5->addListener (this);

    envelopeAttack5->setBounds (112, 32, 88, 88);

    envelopeAttack2.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack2.get());
    envelopeAttack2->setRange (0, 255, 1);
    envelopeAttack2->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack2->setColour (Slider::rotarySliderFillColourId, Colour (0xffffce3a));
    envelopeAttack2->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff43ff00));
    envelopeAttack2->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack2->addListener (this);

    envelopeAttack2->setBounds (216, 30, 88, 88);

    envelopeAttack3.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack3.get());
    envelopeAttack3->setRange (0, 255, 1);
    envelopeAttack3->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack3->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack3->setColour (Slider::rotarySliderFillColourId, Colour (0xffffce3a));
    envelopeAttack3->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff43ff00));
    envelopeAttack3->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack3->addListener (this);

    envelopeAttack3->setBounds (312, 30, 88, 88);

    envelopeAttack4.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack4.get());
    envelopeAttack4->setRange (0, 255, 1);
    envelopeAttack4->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack4->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack4->setColour (Slider::rotarySliderFillColourId, Colour (0xffffce3a));
    envelopeAttack4->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff43ff00));
    envelopeAttack4->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack4->addListener (this);

    envelopeAttack4->setBounds (408, 30, 88, 88);

    envelopeAttack6.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack6.get());
    envelopeAttack6->setRange (0, 255, 1);
    envelopeAttack6->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack6->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack6->setColour (Slider::rotarySliderFillColourId, Colour (0xffffce3a));
    envelopeAttack6->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff43ff00));
    envelopeAttack6->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack6->addListener (this);

    envelopeAttack6->setBounds (504, 30, 88, 88);

    label.reset (new Label ("new label",
                            TRANS("Attack")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (232, 8, 48, 24);

    label2.reset (new Label ("new label",
                             TRANS("Decay")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (328, 8, 48, 24);

    label3.reset (new Label ("new label",
                             TRANS("Sustain")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (416, 8, 64, 24);

    label4.reset (new Label ("new label",
                             TRANS("Release")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (512, 8, 64, 24);

    envelopeAttack7.reset (new Slider (String()));
    addAndMakeVisible (envelopeAttack7.get());
    envelopeAttack7->setRange (0, 255, 1);
    envelopeAttack7->setSliderStyle (Slider::RotaryVerticalDrag);
    envelopeAttack7->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    envelopeAttack7->setColour (Slider::thumbColourId, Colour (0xffc84242));
    envelopeAttack7->setColour (Slider::rotarySliderFillColourId, Colour (0xffff3a3a));
    envelopeAttack7->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff2ca0eb));
    envelopeAttack7->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    envelopeAttack7->addListener (this);

    envelopeAttack7->setBounds (608, 32, 88, 88);

    label5.reset (new Label ("new label",
                             TRANS("Pitch")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (624, 8, 48, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentParametersEditor::~InstrumentParametersEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
    //[/Destructor_pre]

    envelopeAttack = nullptr;
    toggleButton = nullptr;
    toggleButton2 = nullptr;
    envelopeAttack5 = nullptr;
    envelopeAttack2 = nullptr;
    envelopeAttack3 = nullptr;
    envelopeAttack4 = nullptr;
    envelopeAttack6 = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    envelopeAttack7 = nullptr;
    label5 = nullptr;


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

void InstrumentParametersEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == envelopeAttack.get())
    {
        //[UserSliderCode_envelopeAttack] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack]
    }
    else if (sliderThatWasMoved == envelopeAttack5.get())
    {
        //[UserSliderCode_envelopeAttack5] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack5]
    }
    else if (sliderThatWasMoved == envelopeAttack2.get())
    {
        //[UserSliderCode_envelopeAttack2] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack2]
    }
    else if (sliderThatWasMoved == envelopeAttack3.get())
    {
        //[UserSliderCode_envelopeAttack3] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack3]
    }
    else if (sliderThatWasMoved == envelopeAttack4.get())
    {
        //[UserSliderCode_envelopeAttack4] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack4]
    }
    else if (sliderThatWasMoved == envelopeAttack6.get())
    {
        //[UserSliderCode_envelopeAttack6] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack6]
    }
    else if (sliderThatWasMoved == envelopeAttack7.get())
    {
        //[UserSliderCode_envelopeAttack7] -- add your slider handling code here..
        //[/UserSliderCode_envelopeAttack7]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void InstrumentParametersEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButton.get())
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }
    else if (buttonThatWasClicked == toggleButton2.get())
    {
        //[UserButtonCode_toggleButton2] -- add your button handler code here..
        //[/UserButtonCode_toggleButton2]
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

<JUCER_COMPONENT documentType="Component" className="InstrumentParametersEditor"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="700" initialHeight="200">
  <BACKGROUND backgroundColour="0"/>
  <SLIDER name="" id="39e754fa59febde5" memberName="envelopeAttack" virtualName=""
          explicitFocusOrder="0" pos="16 32 88 88" rotarysliderfill="ffff3a3a"
          rotaryslideroutline="ffeb2c2c" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="924f76a4e0d98f4a" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="16 8 88 24" buttonText="Filter"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="3e9eb84124cb1154" memberName="toggleButton2"
                virtualName="" explicitFocusOrder="0" pos="112 8 88 24" buttonText="Distortion"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="" id="414deb761c142a1e" memberName="envelopeAttack5" virtualName=""
          explicitFocusOrder="0" pos="112 32 88 88" rotarysliderfill="ffff3a3a"
          rotaryslideroutline="ffeb2c2c" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="f3bec83386f1e4f" memberName="envelopeAttack2" virtualName=""
          explicitFocusOrder="0" pos="216 30 88 88" rotarysliderfill="ffffce3a"
          rotaryslideroutline="ff43ff00" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="550eddd363e93172" memberName="envelopeAttack3" virtualName=""
          explicitFocusOrder="0" pos="312 30 88 88" rotarysliderfill="ffffce3a"
          rotaryslideroutline="ff43ff00" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="a80a5739eeb14dfa" memberName="envelopeAttack4" virtualName=""
          explicitFocusOrder="0" pos="408 30 88 88" rotarysliderfill="ffffce3a"
          rotaryslideroutline="ff43ff00" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="e2236c347fefc82e" memberName="envelopeAttack6" virtualName=""
          explicitFocusOrder="0" pos="504 30 88 88" rotarysliderfill="ffffce3a"
          rotaryslideroutline="ff43ff00" textboxoutline="0" min="0.0" max="255.0"
          int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="d5d91fa72bdffc5b" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="232 8 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9f8906541edb0e25" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="328 8 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="2bfa1853ff024d93" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="416 8 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b1c41664a19879e5" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="512 8 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="6b5b1f2b237274df" memberName="envelopeAttack7" virtualName=""
          explicitFocusOrder="0" pos="608 32 88 88" thumbcol="ffc84242"
          rotarysliderfill="ffff3a3a" rotaryslideroutline="ff2ca0eb" textboxoutline="0"
          min="0.0" max="255.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="d86b08f5d7a10b" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="624 8 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


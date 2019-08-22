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

#include "BankEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "PluginProcessor.h"
//[/MiscUserDefs]

//==============================================================================
BankEditor::BankEditor (JucesamplerAudioProcessor &_processor)
    : processor(_processor), AudioProcessorEditor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    component.reset (new Component());
    addAndMakeVisible (component.get());
    component->setName ("new component");

    slider.reset (new Slider ("new slider"));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (328, 56, 80, 64);

    slider2.reset (new Slider ("new slider"));
    addAndMakeVisible (slider2.get());
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::RotaryVerticalDrag);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider2->addListener (this);

    slider2->setBounds (408, 56, 80, 64);

    slider3.reset (new Slider ("new slider"));
    addAndMakeVisible (slider3.get());
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (Slider::RotaryVerticalDrag);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider3->addListener (this);

    slider3->setBounds (328, 128, 80, 64);

    slider4.reset (new Slider ("new slider"));
    addAndMakeVisible (slider4.get());
    slider4->setRange (0, 10, 0);
    slider4->setSliderStyle (Slider::RotaryVerticalDrag);
    slider4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider4->addListener (this);

    slider4->setBounds (408, 128, 80, 64);

    slider5.reset (new Slider ("new slider"));
    addAndMakeVisible (slider5.get());
    slider5->setRange (1, 8, 1);
    slider5->setSliderStyle (Slider::IncDecButtons);
    slider5->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 20);
    slider5->addListener (this);

    slider5->setBounds (496, 112, 80, 24);

    textButton.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton.get());
    textButton->setButtonText (TRANS("Load Bank"));
    textButton->addListener (this);

    textButton->setBounds (360, 8, 104, 24);

    textButton2.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton2.get());
    textButton2->setButtonText (TRANS("Save Bank"));
    textButton2->addListener (this);
    textButton2->setColour (TextButton::buttonColourId, Colour (0xff5c7fa4));

    textButton2->setBounds (480, 8, 104, 24);

    comboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox.get());
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addListener (this);

    comboBox->setBounds (16, 8, 288, 24);

    component2.reset (new Component());
    addAndMakeVisible (component2.get());
    component2->setName ("new component");

    component2->setBounds (16, 224, 64, 56);

    component3.reset (new Component());
    addAndMakeVisible (component3.get());
    component3->setName ("new component");

    component3->setBounds (88, 224, 64, 56);

    component4.reset (new Component());
    addAndMakeVisible (component4.get());
    component4->setName ("new component");

    component4->setBounds (232, 224, 64, 56);

    component5.reset (new Component());
    addAndMakeVisible (component5.get());
    component5->setName ("new component");

    component5->setBounds (160, 224, 64, 56);

    component6.reset (new Component());
    addAndMakeVisible (component6.get());
    component6->setName ("new component");

    component6->setBounds (304, 224, 64, 56);

    component7.reset (new Component());
    addAndMakeVisible (component7.get());
    component7->setName ("new component");

    component7->setBounds (376, 224, 64, 56);

    component8.reset (new Component());
    addAndMakeVisible (component8.get());
    component8->setName ("new component");

    component8->setBounds (520, 224, 64, 56);

    component9.reset (new Component());
    addAndMakeVisible (component9.get());
    component9->setName ("new component");

    component9->setBounds (448, 224, 64, 56);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

BankEditor::~BankEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    component = nullptr;
    slider = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;
    slider4 = nullptr;
    slider5 = nullptr;
    textButton = nullptr;
    textButton2 = nullptr;
    comboBox = nullptr;
    component2 = nullptr;
    component3 = nullptr;
    component4 = nullptr;
    component5 = nullptr;
    component6 = nullptr;
    component7 = nullptr;
    component8 = nullptr;
    component9 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BankEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BankEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    component->setBounds (8, 48, proportionOfWidth (0.5000f), proportionOfHeight (0.5000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BankEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2.get())
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3.get())
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4.get())
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }
    else if (sliderThatWasMoved == slider5.get())
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        //[/UserSliderCode_slider5]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void BankEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2.get())
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void BankEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void BankEditor::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BankEditor" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="JucesamplerAudioProcessor &amp;_processor"
                 variableInitialisers="processor(_processor), AudioProcessorEditor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="300">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="new component" id="91eb62aad49698c7" memberName="component"
                    virtualName="" explicitFocusOrder="0" pos="8 48 50% 50%" class="Component"
                    params=""/>
  <SLIDER name="new slider" id="50325a98e9272719" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="328 56 80 64" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="c396bd3cccbf8da7" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="408 56 80 64" min="0.0"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="ce07b41f051c882e" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="328 128 80 64" min="0.0"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="df2b621841824f53" memberName="slider4"
          virtualName="" explicitFocusOrder="0" pos="408 128 80 64" min="0.0"
          max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="81a06d7818c79b4b" memberName="slider5"
          virtualName="" explicitFocusOrder="0" pos="496 112 80 24" min="1.0"
          max="8.0" int="1.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="c85231afed0bf43a" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="360 8 104 24" buttonText="Load Bank"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="8f9f3cb92b144363" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="480 8 104 24" bgColOff="ff5c7fa4"
              buttonText="Save Bank" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="a874eedfa3cfe441" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="16 8 288 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="new component" id="3c4916620de64213" memberName="component2"
                    virtualName="" explicitFocusOrder="0" pos="16 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="883750e363bebe2" memberName="component3"
                    virtualName="" explicitFocusOrder="0" pos="88 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="9201307a6e38e3d" memberName="component4"
                    virtualName="" explicitFocusOrder="0" pos="232 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="d5943312ced4f015" memberName="component5"
                    virtualName="" explicitFocusOrder="0" pos="160 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="de66540708083a30" memberName="component6"
                    virtualName="" explicitFocusOrder="0" pos="304 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="5cf4d1d5dfd80f6" memberName="component7"
                    virtualName="" explicitFocusOrder="0" pos="376 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="f9ae2fd8e61854fe" memberName="component8"
                    virtualName="" explicitFocusOrder="0" pos="520 224 64 56" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="30811ec45694fe23" memberName="component9"
                    virtualName="" explicitFocusOrder="0" pos="448 224 64 56" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


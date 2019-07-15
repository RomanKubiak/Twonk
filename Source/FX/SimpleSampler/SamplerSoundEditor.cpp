/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SamplerSoundEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SamplerSoundEditor::SamplerSoundEditor (const uint8_t _index, SimpleSamplerProcessor &_p)
    : index(_index), p(_p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    textButton.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton.get());
    textButton->setButtonText (TRANS("1"));
    textButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton->addListener (this);
    textButton->setColour (TextButton::buttonColourId, Colour (0xff5c7fa4));

    textButton->setBounds (0, 0, 56, 56);

    label.reset (new Label ("new label",
                            TRANS("Sample Name")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::outlineColourId, Colour (0x28ffffff));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (64, 8, 128, 32);

    slider.reset (new Slider ("new slider"));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 10, 0.1);
    slider->setSliderStyle (Slider::LinearBar);
    slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (200, 8, 136, 32);

    slider2.reset (new Slider ("new slider"));
    addAndMakeVisible (slider2.get());
    slider2->setRange (0, 10, 0.1);
    slider2->setSliderStyle (Slider::LinearBar);
    slider2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider2->addListener (this);

    slider2->setBounds (488, 8, 88, 32);

    slider3.reset (new Slider ("new slider"));
    addAndMakeVisible (slider3.get());
    slider3->setRange (0, 10, 0.1);
    slider3->setSliderStyle (Slider::LinearBar);
    slider3->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slider3->addListener (this);

    slider3->setBounds (344, 8, 136, 32);


    //[UserPreSize]
	textButton->setButtonText(String(index));
    //[/UserPreSize]

    setSize (580, 56);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SamplerSoundEditor::~SamplerSoundEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textButton = nullptr;
    label = nullptr;
    slider = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SamplerSoundEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SamplerSoundEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SamplerSoundEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		WildcardFileFilter wildcardFilter ("*.wav", String(), "Supported sound files");
		FileBrowserComponent browser (FileBrowserComponent::openMode|FileBrowserComponent::canSelectFiles,
			File(),
			&wildcardFilter,
			nullptr);
		FileChooserDialogBox dialogBox ("Open",
			"Please choose some kind of file that you want to open...",
			browser,
			false,
			Colours::lightgrey);
		if (dialogBox.show())
		{
		}
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SamplerSoundEditor::sliderValueChanged (Slider* sliderThatWasMoved)
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SamplerSoundEditor" componentName=""
                 parentClasses="public Component" constructorParams="const uint8_t _index, SimpleSamplerProcessor &amp;_p"
                 variableInitialisers="index(_index), p(_p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="580"
                 initialHeight="56">
  <BACKGROUND backgroundColour="0"/>
  <TEXTBUTTON name="new button" id="97d7c0e86290cc8c" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="0 0 56 56" bgColOff="ff5c7fa4"
              buttonText="1" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="6367eb80fa4cd50f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="64 8 128 32" outlineCol="28ffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sample Name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="865e811e7108b09d" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="200 8 136 32" min="0.0" max="10.0"
          int="0.1" style="LinearBar" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="5dcb09056ab9c81e" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="488 8 88 32" min="0.0"
          max="10.0" int="0.1" style="LinearBar" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="d81539b65cbc2af6" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="344 8 136 32" min="0.0"
          max="10.0" int="0.1" style="LinearBar" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


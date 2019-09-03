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
	currentSimplerSound = nullptr;
    //[/Constructor_pre]

    waveViewer.reset (new InstrumentWaveViewer (*this, processor));
    addAndMakeVisible (waveViewer.get());
    waveViewer->setBounds (8, 8, 392, 232);

    attack.reset (new Slider (String()));
    addAndMakeVisible (attack.get());
    attack->setRange (0, 10, 0.1);
    attack->setSliderStyle (Slider::LinearVertical);
    attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attack->setColour (Slider::backgroundColourId, Colour (0x4bff0000));
    attack->setColour (Slider::thumbColourId, Colour (0xfff01717));
    attack->setColour (Slider::trackColourId, Colour (0xbbff0000));
    attack->addListener (this);

    attack->setBounds (424, 32, 48, 200);

    decay.reset (new Slider (String()));
    addAndMakeVisible (decay.get());
    decay->setRange (0, 10, 0.1);
    decay->setSliderStyle (Slider::LinearVertical);
    decay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decay->setColour (Slider::backgroundColourId, Colour (0xda13384a));
    decay->setColour (Slider::trackColourId, Colour (0xff0f89be));
    decay->addListener (this);

    decay->setBounds (472, 32, 48, 200);

    sustain.reset (new Slider (String()));
    addAndMakeVisible (sustain.get());
    sustain->setRange (0, 1, 0.01);
    sustain->setSliderStyle (Slider::LinearVertical);
    sustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustain->setColour (Slider::backgroundColourId, Colour (0x543f0852));
    sustain->setColour (Slider::thumbColourId, Colour (0xffae20c6));
    sustain->setColour (Slider::trackColourId, Colour (0xffb50ec1));
    sustain->addListener (this);

    sustain->setBounds (520, 32, 48, 200);

    release.reset (new Slider (String()));
    addAndMakeVisible (release.get());
    release->setRange (0, 10, 0.1);
    release->setSliderStyle (Slider::LinearVertical);
    release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    release->setColour (Slider::backgroundColourId, Colour (0xb603802c));
    release->setColour (Slider::thumbColourId, Colour (0xff17cd61));
    release->setColour (Slider::trackColourId, Colour (0xff18dd49));
    release->addListener (this);

    release->setBounds (568, 32, 48, 200);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 250);


    //[Constructor] You can add your own custom stuff here..
	attack->setPopupDisplayEnabled(true, false, this, 500);
	decay->setPopupDisplayEnabled(true, false, this, 500);
	sustain->setPopupDisplayEnabled(true, false, this, 500);
	release->setPopupDisplayEnabled(true, false, this, 500);
    //[/Constructor]
}

InstrumentParametersEditor::~InstrumentParametersEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
    //[/Destructor_pre]

    waveViewer = nullptr;
    attack = nullptr;
    decay = nullptr;
    sustain = nullptr;
    release = nullptr;


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

    if (sliderThatWasMoved == attack.get())
    {
        //[UserSliderCode_attack] -- add your slider handling code here..
		if (currentSimplerSound)
		{
			ADSR::Parameters params = currentSimplerSound->getCurrentADSRParameters();
			params.attack = (float)attack->getValue();
			currentSimplerSound->setEnvelopeParameters(params);
		}
        //[/UserSliderCode_attack]
    }
    else if (sliderThatWasMoved == decay.get())
    {
        //[UserSliderCode_decay] -- add your slider handling code here..
		if (currentSimplerSound)
		{
			ADSR::Parameters params = currentSimplerSound->getCurrentADSRParameters();
			params.decay = (float)decay->getValue();
			currentSimplerSound->setEnvelopeParameters(params);
		}
        //[/UserSliderCode_decay]
    }
    else if (sliderThatWasMoved == sustain.get())
    {
        //[UserSliderCode_sustain] -- add your slider handling code here..
		if (currentSimplerSound)
		{
			ADSR::Parameters params = currentSimplerSound->getCurrentADSRParameters();
			params.sustain = (float)sustain->getValue();
			currentSimplerSound->setEnvelopeParameters(params);
		}
        //[/UserSliderCode_sustain]
    }
    else if (sliderThatWasMoved == release.get())
    {
        //[UserSliderCode_release] -- add your slider handling code here..
		if (currentSimplerSound)
		{
			ADSR::Parameters params = currentSimplerSound->getCurrentADSRParameters();
			params.release = (float)release->getValue();
			currentSimplerSound->setEnvelopeParameters(params);
		}
        //[/UserSliderCode_release]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentParametersEditor::parameterChanged (const String &parameterID, float newValue)
{
}

void InstrumentParametersEditor::setEditedInstrument(SimplerInstrument *si)
{
	if (si)
	{
		currentSamplerInstrument = si;
		waveViewer->setSoundToShow(si);
	}
}

void InstrumentParametersEditor::setEditedSound (SimplerSound *editedSound)
{
	currentSimplerSound = editedSound;

	if (currentSimplerSound)
	{
		double lenInSecs = currentSimplerSound->getLength() / currentSimplerSound->getSampleRate();
		attack->setRange(0.0f, lenInSecs, (lenInSecs < 0.3) ? 0.001 : 0.01);
		attack->setValue(currentSimplerSound->getCurrentADSRParameters().attack, dontSendNotification);
		decay->setRange(0, lenInSecs, (lenInSecs < 0.3) ? 0.001 : 0.01);
		decay->setValue(currentSimplerSound->getCurrentADSRParameters().decay, dontSendNotification);
		sustain->setValue(currentSimplerSound->getCurrentADSRParameters().sustain, dontSendNotification);

		release->setRange(0, lenInSecs, (lenInSecs < 0.3) ? 0.001 : 0.01);
		release->setValue(currentSimplerSound->getCurrentADSRParameters().release, dontSendNotification);
	}
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
             explicitFocusOrder="0" pos="8 8 392 232" sourceFile="InstrumentWaveViewer.cpp"
             constructorParams="*this, processor"/>
  <SLIDER name="" id="a701a4b674dae16e" memberName="attack" virtualName=""
          explicitFocusOrder="0" pos="424 32 48 200" bkgcol="4bff0000"
          thumbcol="fff01717" trackcol="bbff0000" min="0.0" max="10.0"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="" id="310093749b5340cf" memberName="decay" virtualName=""
          explicitFocusOrder="0" pos="472 32 48 200" bkgcol="da13384a"
          trackcol="ff0f89be" min="0.0" max="10.0" int="0.1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="" id="7ce63505be6b42aa" memberName="sustain" virtualName=""
          explicitFocusOrder="0" pos="520 32 48 200" bkgcol="543f0852"
          thumbcol="ffae20c6" trackcol="ffb50ec1" min="0.0" max="1.0" int="0.01"
          style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="" id="eecc200e0866d810" memberName="release" virtualName=""
          explicitFocusOrder="0" pos="568 32 48 200" bkgcol="b603802c"
          thumbcol="ff17cd61" trackcol="ff18dd49" min="0.0" max="10.0"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


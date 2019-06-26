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
#include "GraphDocument.h"
//[/Headers]

#include "TwonkTitleBarComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkTitleBarComponent::TwonkTitleBarComponent (GraphDocumentComponent &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    settingsButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (settingsButton.get());
    settingsButton->addListener (this);

    settingsButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::iconfinder_Streamline75_185095_png, BinaryData::iconfinder_Streamline75_185095_pngSize), 1.000f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::iconfinder_Streamline75_185095_png, BinaryData::iconfinder_Streamline75_185095_pngSize), 1.000f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::iconfinder_Streamline75_185095_png, BinaryData::iconfinder_Streamline75_185095_pngSize), 1.000f, Colour (0x00000000));
    settingsButton->setBounds (0, 4, 40, 40);

    midiKeysButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (midiKeysButton.get());
    midiKeysButton->addListener (this);

    midiKeysButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::PianoKeyboard_svg_png, BinaryData::PianoKeyboard_svg_pngSize), 1.000f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::PianoKeyboard_svg_png, BinaryData::PianoKeyboard_svg_pngSize), 1.000f, Colour (0x00000000),
                               ImageCache::getFromMemory (BinaryData::PianoKeyboard_svg_png, BinaryData::PianoKeyboard_svg_pngSize), 1.000f, Colour (0x00000000));
    midiKeysButton->setBounds (40, 4, 40, 40);

    pluginButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (pluginButton.get());
    pluginButton->addListener (this);

    pluginButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::iconfinder_plugin_3671838_png, BinaryData::iconfinder_plugin_3671838_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::iconfinder_plugin_3671838_png, BinaryData::iconfinder_plugin_3671838_pngSize), 1.000f, Colour (0x00000000),
                             ImageCache::getFromMemory (BinaryData::iconfinder_plugin_3671838_png, BinaryData::iconfinder_plugin_3671838_pngSize), 1.000f, Colour (0x00000000));
    pluginButton->setBounds (552, 4, 40, 40);

    syncButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (syncButton.get());
    syncButton->addListener (this);

    syncButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::sync_off_png, BinaryData::sync_off_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::sync_off_png, BinaryData::sync_off_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::sync_on_png, BinaryData::sync_on_pngSize), 1.000f, Colour (0x00000000));
    syncButton->setBounds (102, 4, 40, 40);

    stopButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (stopButton.get());
    stopButton->addListener (this);

    stopButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconstop_211931_png, BinaryData::iconfinder_iconstop_211931_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconstop_211931_png, BinaryData::iconfinder_iconstop_211931_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconstop_211931_png, BinaryData::iconfinder_iconstop_211931_pngSize), 1.000f, Colour (0x00000000));
    stopButton->setBounds (158, 4, 40, 40);

    playButton.reset (new ImageButton ("new button"));
    addAndMakeVisible (playButton.get());
    playButton->addListener (this);

    playButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconplay_211876_png, BinaryData::iconfinder_iconplay_211876_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconplay_211876_png, BinaryData::iconfinder_iconplay_211876_pngSize), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (BinaryData::iconfinder_iconpause_211871_png, BinaryData::iconfinder_iconpause_211871_pngSize), 1.000f, Colour (0x00000000));
    playButton->setBounds (198, 4, 40, 40);

    tempoSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (tempoSlider.get());
    tempoSlider->setRange (1, 240, 0.5);
    tempoSlider->setSliderStyle (Slider::LinearHorizontal);
    tempoSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
    tempoSlider->setColour (Slider::thumbColourId, Colour (0xff1afa00));
    tempoSlider->addListener (this);

    tempoSlider->setBounds (246, 4, 150, 20);

    positionIndicator.reset (new Slider ("new slider"));
    addAndMakeVisible (positionIndicator.get());
    positionIndicator->setRange (0, 128, 1);
    positionIndicator->setSliderStyle (Slider::ThreeValueHorizontal);
    positionIndicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    positionIndicator->addListener (this);

    seqLength.reset (new Slider ("new slider"));
    addAndMakeVisible (seqLength.get());
    seqLength->setRange (1, 128, 1);
    seqLength->setSliderStyle (Slider::LinearHorizontal);
    seqLength->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 20);
    seqLength->addListener (this);

    seqLength->setBounds (399, 4, 150, 20);

    seqFirst.reset (new Slider ("new slider"));
    addAndMakeVisible (seqFirst.get());
    seqFirst->setRange (1, 128, 1);
    seqFirst->setSliderStyle (Slider::LinearHorizontal);
    seqFirst->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 16);
    seqFirst->setColour (Slider::thumbColourId, Colour (0xffc84242));
    seqFirst->addListener (this);

    seqFirst->setBounds (399, 28, 150, 20);


    //[UserPreSize]
	seqFirst->setValue(0);
	seqLength->setValue(16);
	positionIndicator->setMinAndMaxValues(0, 128);
	positionIndicator->setValue(0);
	tempoSlider->setValue(60.0);
	playButton->setClickingTogglesState(true);
	syncButton->setClickingTogglesState(true);
    //[/UserPreSize]

    setSize (600, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkTitleBarComponent::~TwonkTitleBarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    settingsButton = nullptr;
    midiKeysButton = nullptr;
    pluginButton = nullptr;
    syncButton = nullptr;
    stopButton = nullptr;
    playButton = nullptr;
    tempoSlider = nullptr;
    positionIndicator = nullptr;
    seqLength = nullptr;
    seqFirst = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkTitleBarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkTitleBarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    positionIndicator->setBounds (0, 48, getWidth() - 0, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkTitleBarComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == settingsButton.get())
    {
        //[UserButtonCode_settingsButton] -- add your button handler code here..
		owner.showSidePanel(true);
        //[/UserButtonCode_settingsButton]
    }
    else if (buttonThatWasClicked == midiKeysButton.get())
    {
        //[UserButtonCode_midiKeysButton] -- add your button handler code here..
		owner.showMidiKeyboardComponent();
        //[/UserButtonCode_midiKeysButton]
    }
    else if (buttonThatWasClicked == pluginButton.get())
    {
        //[UserButtonCode_pluginButton] -- add your button handler code here..
		owner.showSidePanel(false);
        //[/UserButtonCode_pluginButton]
    }
    else if (buttonThatWasClicked == syncButton.get())
    {
        //[UserButtonCode_syncButton] -- add your button handler code here..
		owner.toggleSync(syncButton->getToggleState());
        //[/UserButtonCode_syncButton]
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		owner.stop();
		playButton->setToggleState(false, NotificationType::sendNotification);
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == playButton.get())
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
		owner.toggleTransport(!playButton->getToggleState());
        //[/UserButtonCode_playButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TwonkTitleBarComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == tempoSlider.get())
    {
        //[UserSliderCode_tempoSlider] -- add your slider handling code here..
		owner.setTempo(tempoSlider->getValue());
        //[/UserSliderCode_tempoSlider]
    }
    else if (sliderThatWasMoved == positionIndicator.get())
    {
        //[UserSliderCode_positionIndicator] -- add your slider handling code here..
        //[/UserSliderCode_positionIndicator]
    }
    else if (sliderThatWasMoved == seqLength.get())
    {
        //[UserSliderCode_seqLength] -- add your slider handling code here..
        //[/UserSliderCode_seqLength]
    }
    else if (sliderThatWasMoved == seqFirst.get())
    {
        //[UserSliderCode_seqFirst] -- add your slider handling code here..
        //[/UserSliderCode_seqFirst]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkTitleBarComponent::stepIncrement(int currentStep)
{
	DBG("TwonkTitleBarComponent::stepIncrement " + String(currentStep));
	positionIndicator->setValue(currentStep);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkTitleBarComponent" componentName=""
                 parentClasses="public Component, public TwonkClockListener" constructorParams="GraphDocumentComponent &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="64">
  <BACKGROUND backgroundColour="ff323e44"/>
  <IMAGEBUTTON name="new button" id="97401225f34bada3" memberName="settingsButton"
               virtualName="" explicitFocusOrder="0" pos="0 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::iconfinder_Streamline75_185095_png"
               opacityNormal="1.0" colourNormal="0" resourceOver="BinaryData::iconfinder_Streamline75_185095_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::iconfinder_Streamline75_185095_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="c03949025f893e8d" memberName="midiKeysButton"
               virtualName="" explicitFocusOrder="0" pos="40 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::PianoKeyboard_svg_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="BinaryData::PianoKeyboard_svg_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::PianoKeyboard_svg_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="7ad03a9df36a417e" memberName="pluginButton"
               virtualName="" explicitFocusOrder="0" pos="552 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::iconfinder_plugin_3671838_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="BinaryData::iconfinder_plugin_3671838_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::iconfinder_plugin_3671838_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="fd72eb5beac6ce9b" memberName="syncButton"
               virtualName="" explicitFocusOrder="0" pos="102 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::sync_off_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="BinaryData::sync_off_png" opacityOver="1.0"
               colourOver="0" resourceDown="BinaryData::sync_on_png" opacityDown="1.0"
               colourDown="0"/>
  <IMAGEBUTTON name="new button" id="f013d10b535ec374" memberName="stopButton"
               virtualName="" explicitFocusOrder="0" pos="158 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::iconfinder_iconstop_211931_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="BinaryData::iconfinder_iconstop_211931_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::iconfinder_iconstop_211931_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="78b1f24f98381fad" memberName="playButton"
               virtualName="" explicitFocusOrder="0" pos="198 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::iconfinder_iconplay_211876_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="BinaryData::iconfinder_iconplay_211876_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::iconfinder_iconpause_211871_png"
               opacityDown="1.0" colourDown="0"/>
  <SLIDER name="new slider" id="1b0eb9cd7e232c5f" memberName="tempoSlider"
          virtualName="" explicitFocusOrder="0" pos="246 4 150 20" thumbcol="ff1afa00"
          min="1.0" max="240.0" int="0.5" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="48" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="f61a56a7717aba4" memberName="positionIndicator"
          virtualName="" explicitFocusOrder="0" pos="0 48 0M 16" min="0.0"
          max="128.0" int="1.0" style="ThreeValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="85533c4edcae7d0c" memberName="seqLength"
          virtualName="" explicitFocusOrder="0" pos="399 4 150 20" min="1.0"
          max="128.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="4b96b9a112dc951c" memberName="seqFirst"
          virtualName="" explicitFocusOrder="0" pos="399 28 150 20" thumbcol="ffc84242"
          min="1.0" max="128.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


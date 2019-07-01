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
	labelFont = CustomTypeface::createSystemTypefaceFor(BinaryData::terminess_ttf, BinaryData::terminess_ttfSize);
	titleBarLookAndFeel = new TitleBarLookAndFeel(labelFont);
	setLookAndFeel(titleBarLookAndFeel);
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
    midiKeysButton->setBounds (48, 4, 40, 40);

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

    tempoSlider.reset (new Slider (String()));
    addAndMakeVisible (tempoSlider.get());
    tempoSlider->setRange (1, 240, 0.5);
    tempoSlider->setSliderStyle (Slider::LinearHorizontal);
    tempoSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
    tempoSlider->setColour (Slider::thumbColourId, Colour (0xff1afa00));
    tempoSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    tempoSlider->addListener (this);

    tempoSlider->setBounds (246, 4, 150, 16);

    timeLabel.reset (new Label (String(),
                                TRANS("00:00:00:000")));
    addAndMakeVisible (timeLabel.get());
    timeLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain).withTypefaceStyle ("Regular"));
    timeLabel->setJustificationType (Justification::centred);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (Label::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    timeLabel->setBounds (400, 4, 96, 20);

    clockPositionIndicator.reset (new Slider (String()));
    addAndMakeVisible (clockPositionIndicator.get());
    clockPositionIndicator->setRange (1, 24, 1);
    clockPositionIndicator->setSliderStyle (Slider::LinearBar);
    clockPositionIndicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    clockPositionIndicator->setColour (Slider::backgroundColourId, Colour (0xff55cd32));
    clockPositionIndicator->setColour (Slider::trackColourId, Colour (0xff43c7ff));
    clockPositionIndicator->setColour (Slider::rotarySliderFillColourId, Colour (0xff0eb7ff));
    clockPositionIndicator->addListener (this);

    clockPositionIndicator->setBounds (400, 24, 96, 8);

    loopLengthSlider.reset (new Slider (String()));
    addAndMakeVisible (loopLengthSlider.get());
    loopLengthSlider->setRange (1, 256, 1);
    loopLengthSlider->setSliderStyle (Slider::LinearHorizontal);
    loopLengthSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
    loopLengthSlider->setColour (Slider::thumbColourId, Colour (0xfffa9400));
    loopLengthSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    loopLengthSlider->addListener (this);

    loopLengthSlider->setBounds (246, 28, 150, 16);

    loopPositionIndicator.reset (new Slider (String()));
    addAndMakeVisible (loopPositionIndicator.get());
    loopPositionIndicator->setRange (1, 24, 1);
    loopPositionIndicator->setSliderStyle (Slider::LinearBar);
    loopPositionIndicator->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loopPositionIndicator->setColour (Slider::backgroundColourId, Colour (0xff55cd32));
    loopPositionIndicator->setColour (Slider::thumbColourId, Colour (0xffc84242));
    loopPositionIndicator->setColour (Slider::trackColourId, Colour (0xffff4343));
    loopPositionIndicator->setColour (Slider::rotarySliderFillColourId, Colour (0xff0eb7ff));
    loopPositionIndicator->addListener (this);

    loopPositionIndicator->setBounds (400, 36, 96, 8);


    //[UserPreSize]
	tempoSlider->setValue(60.0);
	loopLengthSlider->setValue(16);
	playButton->setClickingTogglesState(true);
	syncButton->setClickingTogglesState(true);
	timeLabel->setFont(labelFont);
    //[/UserPreSize]

    setSize (600, 48);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkTitleBarComponent::~TwonkTitleBarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
	deleteAndZero(titleBarLookAndFeel);
    //[/Destructor_pre]

    settingsButton = nullptr;
    midiKeysButton = nullptr;
    pluginButton = nullptr;
    syncButton = nullptr;
    stopButton = nullptr;
    playButton = nullptr;
    tempoSlider = nullptr;
    timeLabel = nullptr;
    clockPositionIndicator = nullptr;
    loopLengthSlider = nullptr;
    loopPositionIndicator = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkTitleBarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xffbcbcbc), fillColour2 = Colour (0xff464646);
        Colour strokeColour1 = Colour (0x00000000), strokeColour2 = Colour (0x80000000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       0.0f - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
        g.setGradientFill (ColourGradient (strokeColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       strokeColour2,
                                       0.0f - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkTitleBarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

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
		owner.play(playButton->getToggleState());
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
    else if (sliderThatWasMoved == clockPositionIndicator.get())
    {
        //[UserSliderCode_clockPositionIndicator] -- add your slider handling code here..
        //[/UserSliderCode_clockPositionIndicator]
    }
    else if (sliderThatWasMoved == loopLengthSlider.get())
    {
        //[UserSliderCode_loopLengthSlider] -- add your slider handling code here..
		owner.setLoopLength(loopLengthSlider->getValue());
		loopPositionIndicator->setRange(24.0, (double)(loopLengthSlider->getValue() * 24.0));
        //[/UserSliderCode_loopLengthSlider]
    }
    else if (sliderThatWasMoved == loopPositionIndicator.get())
    {
        //[UserSliderCode_loopPositionIndicator] -- add your slider handling code here..
        //[/UserSliderCode_loopPositionIndicator]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkTitleBarComponent::positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo)
{
	double millis = Time::currentTimeMillis();
	//3600000 milliseconds in an hour
	long hr = millis / 3600000;
	millis = millis - 3600000 * hr;
	//60000 milliseconds in a minute
	long min = millis / 60000;
	millis = millis - 60000 * min;

	//1000 milliseconds in a second
	long sec = millis / 1000;
	millis = millis - 1000 * sec;

	timeLabel->setText(
		String::formatted("%02d:%02d:%02d:%03d", hr, min, sec, millis),
		dontSendNotification
	);
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
                 initialHeight="48">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 0 0R, 0=ffbcbcbc, 1=ff464646"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="linear: 0 0, 0 0R, 0=0, 1=80000000"/>
  </BACKGROUND>
  <IMAGEBUTTON name="new button" id="97401225f34bada3" memberName="settingsButton"
               virtualName="" explicitFocusOrder="0" pos="0 4 40 40" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::iconfinder_Streamline75_185095_png"
               opacityNormal="1.0" colourNormal="0" resourceOver="BinaryData::iconfinder_Streamline75_185095_png"
               opacityOver="1.0" colourOver="0" resourceDown="BinaryData::iconfinder_Streamline75_185095_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="c03949025f893e8d" memberName="midiKeysButton"
               virtualName="" explicitFocusOrder="0" pos="48 4 40 40" buttonText="new button"
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
  <SLIDER name="" id="1b0eb9cd7e232c5f" memberName="tempoSlider" virtualName=""
          explicitFocusOrder="0" pos="246 4 150 16" thumbcol="ff1afa00"
          textboxtext="ff000000" min="1.0" max="240.0" int="0.5" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="48"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="" id="eedeb92a13be3a7a" memberName="timeLabel" virtualName=""
         explicitFocusOrder="0" pos="400 4 96 20" textCol="ff000000" edTextCol="ff000000"
         edBkgCol="0" labelText="00:00:00:000" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="c4252987aa16bfc4" memberName="clockPositionIndicator"
          virtualName="" explicitFocusOrder="0" pos="400 24 96 8" bkgcol="ff55cd32"
          trackcol="ff43c7ff" rotarysliderfill="ff0eb7ff" min="1.0" max="24.0"
          int="1.0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="" id="1a1a1086301ec67" memberName="loopLengthSlider" virtualName=""
          explicitFocusOrder="0" pos="246 28 150 16" thumbcol="fffa9400"
          textboxtext="ff000000" min="1.0" max="256.0" int="1.0" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="48"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="" id="1e520ada967b42f6" memberName="loopPositionIndicator"
          virtualName="" explicitFocusOrder="0" pos="400 36 96 8" bkgcol="ff55cd32"
          thumbcol="ffc84242" trackcol="ffff4343" rotarysliderfill="ff0eb7ff"
          min="1.0" max="24.0" int="1.0" style="LinearBar" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


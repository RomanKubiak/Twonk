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

#include "TwonkMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkMain::TwonkMain ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	LookAndFeel::setDefaultLookAndFeel(&twonkLookAndFeel);
	uiManagerThread.reset(new TimeSliceThread("ui thread"));
	uiManagerThread->startThread(2);

	setAudioChannels (1, 0);  // we want a couple of input channels but no outputs
	setOpaque (true);

	defaultTypeface = Typeface::createSystemTypefaceFor(BinaryData::RobotoMedium_ttf, BinaryData::RobotoMedium_ttfSize);
	LookAndFeel &lf = getLookAndFeel();
	lf.setDefaultSansSerifTypeface(defaultTypeface);
    //[/Constructor_pre]

    settingsButton.reset (new TextButton ("Settings"));
    addAndMakeVisible (settingsButton.get());
    settingsButton->addListener (this);
    settingsButton->setColour (TextButton::buttonColourId, Colour (0xff5c85a4));

    drowScope.reset (new drow::Spectroscope (10));
    addAndMakeVisible (drowScope.get());
    drowScope->setName ("Scope Alt");

    drowOsc.reset (new drow::TriggeredScope (nullptr));
    addAndMakeVisible (drowOsc.get());
    drowOsc->setName ("Oscilloscope");

    verticalZoomFactor.reset (new Slider ("Verical Zoom"));
    addAndMakeVisible (verticalZoomFactor.get());
    verticalZoomFactor->setRange (1.01, 127, 0.5);
    verticalZoomFactor->setSliderStyle (Slider::LinearBar);
    verticalZoomFactor->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    verticalZoomFactor->setColour (Slider::backgroundColourId, Colour (0xff092d5b));
    verticalZoomFactor->setColour (Slider::trackColourId, Colour (0xff255a77));
    verticalZoomFactor->addListener (this);

    drowBar.reset (new drow::SegmentedMeter());
    addAndMakeVisible (drowBar.get());
    drowBar->setName ("Level Bar");

    qucikReverb_btn.reset (new TextButton ("QReverb"));
    addAndMakeVisible (qucikReverb_btn.get());
    qucikReverb_btn->setButtonText (TRANS("RV"));
    qucikReverb_btn->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    qucikReverb_btn->addListener (this);
    qucikReverb_btn->setColour (TextButton::buttonColourId, Colour (0x934bd6f8));
    qucikReverb_btn->setColour (TextButton::buttonOnColourId, Colour (0x00000000));

    quickDistortion_btn.reset (new TextButton ("QDist"));
    addAndMakeVisible (quickDistortion_btn.get());
    quickDistortion_btn->setButtonText (TRANS("D"));
    quickDistortion_btn->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    quickDistortion_btn->addListener (this);
    quickDistortion_btn->setColour (TextButton::buttonColourId, Colour (0x67e129a4));
    quickDistortion_btn->setColour (TextButton::buttonOnColourId, Colour (0x00000000));


    //[UserPreSize]
	uiManagerThread->addTimeSliceClient (drowScope.get());
	uiManagerThread->addTimeSliceClient (drowBar.get());
    //[/UserPreSize]

    setSize (1024, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkMain::~TwonkMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	shutdownAudio();
	uiManagerThread->removeAllClients();
    //[/Destructor_pre]

    settingsButton = nullptr;
    drowScope = nullptr;
    drowOsc = nullptr;
    verticalZoomFactor = nullptr;
    drowBar = nullptr;
    qucikReverb_btn = nullptr;
    quickDistortion_btn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	uiManagerThread = nullptr;
    //[/Destructor]
}

//==============================================================================
void TwonkMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colours::black, fillColour2 = Colour (0xff0f1f26);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       static_cast<float> (getWidth()) - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    settingsButton->setBounds (0, proportionOfHeight (0.9000f), getWidth() - 0, proportionOfHeight (0.1000f));
    drowScope->setBounds (proportionOfWidth (0.0596f), 0, proportionOfWidth (0.4697f), proportionOfHeight (0.4500f));
    drowOsc->setBounds (proportionOfWidth (0.5303f), 0, proportionOfWidth (0.4697f), proportionOfHeight (0.4000f));
    verticalZoomFactor->setBounds (proportionOfWidth (0.5303f), proportionOfHeight (0.4000f), proportionOfWidth (0.4697f), proportionOfHeight (0.0500f));
    drowBar->setBounds (0, 0, proportionOfWidth (0.0596f), proportionOfHeight (0.9000f));
    qucikReverb_btn->setBounds (proportionOfWidth (0.0596f), proportionOfHeight (0.4500f), proportionOfWidth (0.1504f), proportionOfHeight (0.2500f));
    quickDistortion_btn->setBounds (proportionOfWidth (0.2100f), proportionOfHeight (0.4500f), 150, proportionOfHeight (0.2500f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkMain::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == settingsButton.get())
    {
        //[UserButtonCode_settingsButton] -- add your button handler code here..
		AudioDeviceSelectorComponent selector(deviceManager,1,16,0,16, false, false, false, false);
		selector.setSize(900, 400);
		selector.setItemHeight(64);
		DialogWindow::showModalDialog("Settings", &selector, this, Colours::black, true, true, true);
        //[/UserButtonCode_settingsButton]
    }
    else if (buttonThatWasClicked == qucikReverb_btn.get())
    {
        //[UserButtonCode_qucikReverb_btn] -- add your button handler code here..
        //[/UserButtonCode_qucikReverb_btn]
    }
    else if (buttonThatWasClicked == quickDistortion_btn.get())
    {
        //[UserButtonCode_quickDistortion_btn] -- add your button handler code here..
        //[/UserButtonCode_quickDistortion_btn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TwonkMain::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == verticalZoomFactor.get())
    {
        //[UserSliderCode_verticalZoomFactor] -- add your slider handling code here..
		drowOsc->setVerticalZoomFactor(sliderThatWasMoved->getValue());
        //[/UserSliderCode_verticalZoomFactor]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void TwonkMain::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}

void TwonkMain::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    //[/UserCode_mouseWheelMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkMain::prepareToPlay (int, double)
{

}

void TwonkMain::releaseResources()
{

}

void TwonkMain::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	if (bufferToFill.buffer->getNumChannels() > 0)
	{
		auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);

		if (drowScope)
			drowScope->copySamples (channelData, bufferToFill.numSamples);
		if (drowBar)
			drowBar->copySamples (channelData, bufferToFill.numSamples);
	}

	if (drowOsc)
	{
		drowOsc->addSamples(*bufferToFill.buffer);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkMain" componentName=""
                 parentClasses="public AudioAppComponent" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="1024" initialHeight="600">
  <METHODS>
    <METHOD name="mouseWheelMove (const MouseEvent&amp; e, const MouseWheelDetails&amp; wheel)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 0R 0R, 0=ff000000, 1=ff0f1f26"
          hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="Settings" id="27e35d18b20eab94" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="0 90% 0M 10%" bgColOff="ff5c85a4"
              buttonText="Settings" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Scope Alt" id="f78267218e40ea7" memberName="drowScope"
                    virtualName="" explicitFocusOrder="0" pos="5.957% 0 46.973% 45%"
                    class="drow::Spectroscope" params="10"/>
  <GENERICCOMPONENT name="Oscilloscope" id="51d4a9aade6dfd31" memberName="drowOsc"
                    virtualName="" explicitFocusOrder="0" pos="53.027% 0 46.973% 40%"
                    class="drow::TriggeredScope" params="nullptr"/>
  <SLIDER name="Verical Zoom" id="4824d8a5fb869c53" memberName="verticalZoomFactor"
          virtualName="" explicitFocusOrder="0" pos="53.027% 40% 46.973% 5%"
          bkgcol="ff092d5b" trackcol="ff255a77" min="1.01" max="127.0"
          int="0.5" style="LinearBar" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <GENERICCOMPONENT name="Level Bar" id="118a09b67acf7ba1" memberName="drowBar" virtualName=""
                    explicitFocusOrder="0" pos="0 0 5.957% 90%" class="drow::SegmentedMeter"
                    params=""/>
  <TEXTBUTTON name="QReverb" id="71f87e916c0cf845" memberName="qucikReverb_btn"
              virtualName="" explicitFocusOrder="0" pos="5.957% 45% 15.039% 25%"
              bgColOff="934bd6f8" bgColOn="0" buttonText="RV" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="QDist" id="17e539559cc8386a" memberName="quickDistortion_btn"
              virtualName="" explicitFocusOrder="0" pos="20.996% 45% 150 25%"
              bgColOff="67e129a4" bgColOn="0" buttonText="D" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


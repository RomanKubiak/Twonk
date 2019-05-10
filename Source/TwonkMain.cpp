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
	uiManagerThread.reset(new TimeSliceThread("ui thread"));
	uiManagerThread->startThread(2);

	setAudioChannels (1, 0);  // we want a couple of input channels but no outputs
	setOpaque (true);
    //[/Constructor_pre]

    settingsButton.reset (new TextButton ("Settings"));
    addAndMakeVisible (settingsButton.get());
    settingsButton->addListener (this);

    drowScope.reset (new drow::Spectroscope (10));
    addAndMakeVisible (drowScope.get());
    drowScope->setName ("Scope Alt");

    drowOsc.reset (new drow::TriggeredScope (nullptr));
    addAndMakeVisible (drowOsc.get());
    drowOsc->setName ("Oscilloscope");

    verticalZoomFactor.reset (new Slider ("Verical Zoom"));
    addAndMakeVisible (verticalZoomFactor.get());
    verticalZoomFactor->setRange (1.01, 255.01, 0.5);
    verticalZoomFactor->setSliderStyle (Slider::LinearHorizontal);
    verticalZoomFactor->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    verticalZoomFactor->addListener (this);


    //[UserPreSize]
	uiManagerThread->addTimeSliceClient (drowScope.get());
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


    //[Destructor]. You can add your own custom destruction code here..
	uiManagerThread = nullptr;
    //[/Destructor]
}

//==============================================================================
void TwonkMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    settingsButton->setBounds (0, proportionOfHeight (0.9000f), getWidth() - 0, proportionOfHeight (0.1000f));
    drowScope->setBounds (proportionOfWidth (0.0000f), 0, proportionOfWidth (0.5000f), proportionOfHeight (0.4500f));
    drowOsc->setBounds (proportionOfWidth (0.5000f), 0, proportionOfWidth (0.5000f), proportionOfHeight (0.4000f));
    verticalZoomFactor->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.4000f), proportionOfWidth (0.5000f), proportionOfHeight (0.0500f));
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
		selector.setSize(1024, 600);
		DialogWindow::showModalDialog("Settings", &selector, this, Colours::black, true, true, true);
        //[/UserButtonCode_settingsButton]
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
	if (drowScope)
	{
		if (bufferToFill.buffer->getNumChannels() > 0)
		{
			auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
			drowScope->copySamples (channelData, bufferToFill.numSamples);
		}
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
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="Settings" id="27e35d18b20eab94" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="0 90% 0M 10%" buttonText="Settings"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Scope Alt" id="f78267218e40ea7" memberName="drowScope"
                    virtualName="" explicitFocusOrder="0" pos="0% 0 50% 45%" class="drow::Spectroscope"
                    params="10"/>
  <GENERICCOMPONENT name="Oscilloscope" id="51d4a9aade6dfd31" memberName="drowOsc"
                    virtualName="" explicitFocusOrder="0" pos="50% 0 50% 40%" class="drow::TriggeredScope"
                    params="nullptr"/>
  <SLIDER name="Verical Zoom" id="4824d8a5fb869c53" memberName="verticalZoomFactor"
          virtualName="" explicitFocusOrder="0" pos="50% 40% 50% 5%" min="1.01"
          max="255.01" int="0.5" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


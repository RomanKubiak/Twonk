/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TwonkTransport.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "TwonkToolBarButton.h"
#include "UI/MainHostWindow.h"

#include "Platform/TwonkPlatformSpecific.h"
//[/MiscUserDefs]

//==============================================================================
TwonkTransport::TwonkTransport (TwonkPlayHead &_playHead)
    : playHead(_playHead)
{
    //[Constructor_pre] You can add your own custom stuff here..
	dragger.reset(new ComponentDragger());
	playHead.addClockListener(this);
    //[/Constructor_pre]

    playButton.reset (new TwonkToolBarButton());
    addAndMakeVisible (playButton.get());
    playButton->setName ("Play");

    playButton->setBounds (104, 7, 48, 48);

    stopButton.reset (new TwonkToolBarButton());
    addAndMakeVisible (stopButton.get());
    stopButton->setName ("Stop");

    stopButton->setBounds (56, 7, 48, 48);

    loopButton.reset (new TwonkToolBarButton());
    addAndMakeVisible (loopButton.get());
    loopButton->setName ("Loop");

    loopButton->setBounds (8, 7, 48, 48);

    tempoSlider.reset (new juce::Slider ("Tempo"));
    addAndMakeVisible (tempoSlider.get());
    tempoSlider->setRange (30, 300, 1);
    tempoSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    tempoSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 50, 20);
    tempoSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0x82005179));
    tempoSlider->setColour (juce::Slider::trackColourId, juce::Colour (0xff00b2ff));
    tempoSlider->addListener (this);

    tempoSlider->setBounds (0, 60, 312, 40);

    loopLengthSlider.reset (new juce::Slider ("Loop Length"));
    addAndMakeVisible (loopLengthSlider.get());
    loopLengthSlider->setRange (4, 64, 1);
    loopLengthSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    loopLengthSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 50, 20);
    loopLengthSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xbf879e00));
    loopLengthSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xffb8dc1a));
    loopLengthSlider->setColour (juce::Slider::trackColourId, juce::Colour (0xedf4ff56));
    loopLengthSlider->addListener (this);

    loopLengthSlider->setBounds (0, 100, 312, 40);

    timeLabel.reset (new juce::Label ("Time",
                                      TRANS("00:00:000")));
    addAndMakeVisible (timeLabel.get());
    timeLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain));
    timeLabel->setJustificationType (juce::Justification::centredLeft);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    timeLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    positionLabel.reset (new juce::Label ("Time",
                                          TRANS("00.00.000")));
    addAndMakeVisible (positionLabel.get());
    positionLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain));
    positionLabel->setJustificationType (juce::Justification::centredLeft);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    positionLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    tempoLabel.reset (new juce::Label ("Tempo",
                                       TRANS("120")));
    addAndMakeVisible (tempoLabel.get());
    tempoLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain));
    tempoLabel->setJustificationType (juce::Justification::centredLeft);
    tempoLabel->setEditable (false, false, false);
    tempoLabel->setColour (juce::Label::textColourId, juce::Colours::white);
    tempoLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    tempoLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    cpuUsage.reset (new juce::Label ("CPU Usage",
                                     TRANS("CPU: 99%")));
    addAndMakeVisible (cpuUsage.get());
    cpuUsage->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 12.00f, juce::Font::plain));
    cpuUsage->setJustificationType (juce::Justification::centred);
    cpuUsage->setEditable (false, false, false);
    cpuUsage->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    cpuUsage->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    memUsage.reset (new juce::Label ("Memory Usage",
                                     TRANS("MEM: 1900")));
    addAndMakeVisible (memUsage.get());
    memUsage->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 12.00f, juce::Font::plain));
    memUsage->setJustificationType (juce::Justification::centred);
    memUsage->setEditable (false, false, false);
    memUsage->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    memUsage->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label.reset (new juce::Label ("new label",
                                        TRANS("Position")));
    addAndMakeVisible (juce__label.get());
    juce__label->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    juce__label->setJustificationType (juce::Justification::centredLeft);
    juce__label->setEditable (false, false, false);
    juce__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label2.reset (new juce::Label ("new label",
                                         TRANS("Time")));
    addAndMakeVisible (juce__label2.get());
    juce__label2->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    juce__label2->setJustificationType (juce::Justification::centredLeft);
    juce__label2->setEditable (false, false, false);
    juce__label2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    juce__label3.reset (new juce::Label ("new label",
                                         TRANS("Tempo")));
    addAndMakeVisible (juce__label3.get());
    juce__label3->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    juce__label3->setJustificationType (juce::Justification::centredLeft);
    juce__label3->setEditable (false, false, false);
    juce__label3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    juce__label3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
	timeLabel->addMouseListener(this, true);
	positionLabel->addMouseListener(this, true);
	tempoLabel->addMouseListener(this, true);

	playButton->setIcon(IMG(icon_play_png));
	playButton->setBaseColour(Colours::lightgreen);
	playButton->addListener(this);
	stopButton->setIcon(IMG(icon_stop_png));
	stopButton->addListener(this);
	loopButton->setIcon(IMG(icon_loop_png));
	loopButton->addListener(this);
	loopButton->setBaseColour(Colours::turquoise);
	loopButton->setIconAlpha(0.3f);
	loopButton->setClickingTogglesState(true);
    //[/UserPreSize]

    setSize (400, 64);


    //[Constructor] You can add your own custom stuff here..
	tempoLabel->setText(String(playHead.getTempo()), dontSendNotification);
	tempoSlider->setValue(playHead.getTempo(), dontSendNotification);

	startTimer(3000);
    //[/Constructor]
}

TwonkTransport::~TwonkTransport()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	playHead.removeClockListener(this);
    //[/Destructor_pre]

    playButton = nullptr;
    stopButton = nullptr;
    loopButton = nullptr;
    tempoSlider = nullptr;
    loopLengthSlider = nullptr;
    timeLabel = nullptr;
    positionLabel = nullptr;
    tempoLabel = nullptr;
    cpuUsage = nullptr;
    memUsage = nullptr;
    juce__label = nullptr;
    juce__label2 = nullptr;
    juce__label3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkTransport::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff343434));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkTransport::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    timeLabel->setBounds (getWidth() - 160, 16, 80, 16);
    positionLabel->setBounds (getWidth() - 240, 16, 80, 16);
    tempoLabel->setBounds (getWidth() - 80, 16, 80, 14);
    cpuUsage->setBounds (getWidth() - 152, 40, 90, 14);
    memUsage->setBounds (getWidth() - 80, 40, 90, 14);
    juce__label->setBounds (getWidth() - 240, 0, 72, 16);
    juce__label2->setBounds (getWidth() - 160, 0, 72, 16);
    juce__label3->setBounds (getWidth() - 80, 0, 80, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkTransport::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == tempoSlider.get())
    {
        //[UserSliderCode_tempoSlider] -- add your slider handling code here..
		playHead.setTempo(tempoSlider->getValue());
        //[/UserSliderCode_tempoSlider]
    }
    else if (sliderThatWasMoved == loopLengthSlider.get())
    {
        //[UserSliderCode_loopLengthSlider] -- add your slider handling code here..
        //[/UserSliderCode_loopLengthSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void TwonkTransport::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.eventComponent == this
		|| e.eventComponent == tempoLabel.get()
		|| e.eventComponent == positionLabel.get()
		|| e.eventComponent == timeLabel.get()
		|| e.eventComponent == cpuUsage.get()
		|| e.eventComponent == memUsage.get())
		dragger->startDraggingComponent(this, e);
    //[/UserCode_mouseDown]
}

void TwonkTransport::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	if (e.eventComponent == this
		|| e.eventComponent == tempoLabel.get()
		|| e.eventComponent == positionLabel.get()
		|| e.eventComponent == timeLabel.get()
		|| e.eventComponent == cpuUsage.get()
		|| e.eventComponent == memUsage.get())
		dragger->dragComponent(this, e, nullptr);
    //[/UserCode_mouseDrag]
}

void TwonkTransport::mouseDoubleClick (const juce::MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
	if (e.eventComponent == this
		|| e.eventComponent == tempoLabel.get()
		|| e.eventComponent == positionLabel.get()
		|| e.eventComponent == timeLabel.get()
		|| e.eventComponent == cpuUsage.get()
		|| e.eventComponent == memUsage.get())
	{
		if (getHeight() > 64)
			setSize(getWidth(), 64);
		else
			setSize(getWidth(), 64 + 40 + 40);
	}
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkTransport::buttonClicked(Button *button)
{
	if (playButton.get() == button)
	{
		if (playHead.isPlaying())
		{
			playHead.pause();
			playButton->setIcon(IMG(icon_play_png));
		}
		else
		{
			playHead.play(false);
			playButton->setIcon(IMG(icon_pause_png));
		}
	}

	if (stopButton.get() == button)
	{
		playHead.stop();
		playButton->setIcon(IMG(icon_play_png));
		playButton->repaint();
	}

	if (loopButton.get() == button)
	{
		if (loopButton->getToggleState())
		{
			loopButton->setIconAlpha(1.0f);
		}
		else
		{
			loopButton->setIconAlpha(0.3f);
		}

		playHead.setLooping(loopButton->getToggleState());
	}
}

void TwonkTransport::positionChanged(const AudioPlayHead::PositionInfo &positionInfo)
{
		auto millisecs = roundToInt (positionInfo.timeInSeconds * 1000.0);
		auto absMillisecs = std::abs (millisecs);

		timeLabel->setText(String::formatted ("%02d:%02d.%03d",
			(absMillisecs / 60000) % 60,
			(absMillisecs / 1000) % 60,
			absMillisecs % 1000), dontSendNotification);

		positionLabel->setText(quarterNotePositionToBarsBeatsString (positionInfo.ppqPosition,
			positionInfo.timeSigNumerator,
			positionInfo.timeSigDenominator), dontSendNotification);

		tempoLabel->setText(String(positionInfo.bpm), dontSendNotification);
}

void TwonkTransport::timerCallback()
{
	cpuUsage->setText(String(TwonkPlatform::getCpuUsage())+"%", dontSendNotification);
	memUsage->setText(String(TwonkPlatform::getMemoryUsageMegabytes()) + "MB", dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkTransport" componentName=""
                 parentClasses="public Component, public TwonkClockListener, public Button::Listener, public Timer"
                 constructorParams="TwonkPlayHead &amp;_playHead" variableInitialisers="playHead(_playHead)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="64">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff343434"/>
  <GENERICCOMPONENT name="Play" id="2c55bb8ca25e0670" memberName="playButton" virtualName=""
                    explicitFocusOrder="0" pos="104 7 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Stop" id="3939c49b154d616b" memberName="stopButton" virtualName=""
                    explicitFocusOrder="0" pos="56 7 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Loop" id="1eb53a8fbe2c1759" memberName="loopButton" virtualName=""
                    explicitFocusOrder="0" pos="8 7 48 48" class="TwonkToolBarButton"
                    params=""/>
  <SLIDER name="Tempo" id="9d6c76ef260baea1" memberName="tempoSlider" virtualName=""
          explicitFocusOrder="0" pos="0 60 312 40" bkgcol="82005179" trackcol="ff00b2ff"
          min="30.0" max="300.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Loop Length" id="653c441302bacde0" memberName="loopLengthSlider"
          virtualName="" explicitFocusOrder="0" pos="0 100 312 40" bkgcol="bf879e00"
          thumbcol="ffb8dc1a" trackcol="edf4ff56" min="4.0" max="64.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Time" id="652beaf6f8698602" memberName="timeLabel" virtualName=""
         explicitFocusOrder="0" pos="160R 16 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="00:00:000" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Time" id="1f6e782fb5035eac" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="240R 16 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="00.00.000" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Tempo" id="5485653b957cb88d" memberName="tempoLabel" virtualName=""
         explicitFocusOrder="0" pos="80R 16 80 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="CPU Usage" id="8f8b6394fbbd65c1" memberName="cpuUsage"
         virtualName="" explicitFocusOrder="0" pos="152R 40 90 14" edTextCol="ff000000"
         edBkgCol="0" labelText="CPU: 99%" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Memory Usage" id="94dfb8c0a903d21e" memberName="memUsage"
         virtualName="" explicitFocusOrder="0" pos="80R 40 90 14" edTextCol="ff000000"
         edBkgCol="0" labelText="MEM: 1900" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a04f59f5984ee2d0" memberName="juce__label"
         virtualName="" explicitFocusOrder="0" pos="240R 0 72 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Position" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12.0"
         kerning="0.0" bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  <LABEL name="new label" id="fa9a510c23e643a3" memberName="juce__label2"
         virtualName="" explicitFocusOrder="0" pos="160R 0 72 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12.0"
         kerning="0.0" bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  <LABEL name="new label" id="8c78d1c403a93b9f" memberName="juce__label3"
         virtualName="" explicitFocusOrder="0" pos="80R 0 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12.0"
         kerning="0.0" bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


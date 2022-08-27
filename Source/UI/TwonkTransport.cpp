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

#include "TwonkTransport.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "TwonkToolBarButton.h"
#include "UI/MainHostWindow.h"

#include "Platform/TwonkPlatformSpecific.h"
//[/MiscUserDefs]

//==============================================================================
TwonkTransport::TwonkTransport(TwonkPlayHead &_playHead)
        : playHead(_playHead) {
    //[Constructor_pre] You can add your own custom stuff here..
    dragger.reset(new ComponentDragger());
    playHead.addClockListener(this);
    //[/Constructor_pre]

    playButton.reset(new TwonkToolBarButton());
    addAndMakeVisible(playButton.get());
    playButton->setName("Play");

    playButton->setBounds(96, 0, 48, 48);

    stopButton.reset(new TwonkToolBarButton());
    addAndMakeVisible(stopButton.get());
    stopButton->setName("Stop");

    stopButton->setBounds(48, 0, 48, 48);

    loopButton.reset(new TwonkToolBarButton());
    addAndMakeVisible(loopButton.get());
    loopButton->setName("Loop");

    loopButton->setBounds(0, 0, 48, 48);

    tempoSlider.reset(new Slider("Tempo"));
    addAndMakeVisible(tempoSlider.get());
    tempoSlider->setRange(30, 300, 1);
    tempoSlider->setSliderStyle(Slider::LinearHorizontal);
    tempoSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    tempoSlider->setColour(Slider::backgroundColourId, Colour(0x82005179));
    tempoSlider->setColour(Slider::trackColourId, Colour(0xff00b2ff));
    tempoSlider->addListener(this);

    tempoSlider->setBounds(0, 48, 312, 40);

    loopLengthSlider.reset(new Slider("Loop Length"));
    addAndMakeVisible(loopLengthSlider.get());
    loopLengthSlider->setRange(4, 64, 1);
    loopLengthSlider->setSliderStyle(Slider::LinearHorizontal);
    loopLengthSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    loopLengthSlider->setColour(Slider::backgroundColourId, Colour(0xbf879e00));
    loopLengthSlider->setColour(Slider::thumbColourId, Colour(0xffb8dc1a));
    loopLengthSlider->setColour(Slider::trackColourId, Colour(0xedf4ff56));
    loopLengthSlider->addListener(this);

    loopLengthSlider->setBounds(0, 88, 312, 40);

    timeLabel.reset(new Label("Time",
                              TRANS("00:00:000")));
    addAndMakeVisible(timeLabel.get());
    timeLabel->setFont(Font(Font::getDefaultMonospacedFontName(), 14.00f, Font::plain).withTypefaceStyle(
            "Regular").withExtraKerningFactor(-0.074f));
    timeLabel->setJustificationType(Justification::centred);
    timeLabel->setEditable(false, false, false);
    timeLabel->setColour(TextEditor::textColourId, Colours::black);
    timeLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    timeLabel->setBounds(232, 28, 80, 16);

    positionLabel.reset(new Label("Time",
                                  TRANS("00.00.000")));
    addAndMakeVisible(positionLabel.get());
    positionLabel->setFont(Font(Font::getDefaultMonospacedFontName(), 14.00f, Font::plain).withTypefaceStyle(
            "Regular").withExtraKerningFactor(-0.065f));
    positionLabel->setJustificationType(Justification::centredLeft);
    positionLabel->setEditable(false, false, false);
    positionLabel->setColour(TextEditor::textColourId, Colours::black);
    positionLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    positionLabel->setBounds(160, 8, 80, 16);

    tempoLabel.reset(new Label("Tempo",
                               TRANS("120")));
    addAndMakeVisible(tempoLabel.get());
    tempoLabel->setFont(Font(Font::getDefaultMonospacedFontName(), 14.00f, Font::plain).withTypefaceStyle("Regular"));
    tempoLabel->setJustificationType(Justification::centredLeft);
    tempoLabel->setEditable(false, false, false);
    tempoLabel->setColour(Label::textColourId, Colour(0xff42a2c8));
    tempoLabel->setColour(TextEditor::textColourId, Colours::black);
    tempoLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    tempoLabel->setBounds(160, 29, 40, 14);

    cpuUsage.reset(new Label("CPU Usage",
                             TRANS("99%")));
    addAndMakeVisible(cpuUsage.get());
    cpuUsage->setFont(Font(10.00f, Font::plain).withTypefaceStyle("Regular"));
    cpuUsage->setJustificationType(Justification::centredLeft);
    cpuUsage->setEditable(false, false, false);
    cpuUsage->setColour(TextEditor::textColourId, Colours::black);
    cpuUsage->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    cpuUsage->setBounds(237, 8, 30, 14);

    memUsage.reset(new Label("Memory Usage",
                             TRANS("1900MB")));
    addAndMakeVisible(memUsage.get());
    memUsage->setFont(Font(10.00f, Font::plain).withTypefaceStyle("Regular"));
    memUsage->setJustificationType(Justification::centredLeft);
    memUsage->setEditable(false, false, false);
    memUsage->setColour(TextEditor::textColourId, Colours::black);
    memUsage->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    memUsage->setBounds(264, 8, 44, 14);


    //[UserPreSize]
    timeLabel->setFont(getDefaultTwonkMonoFont().withHeight(14.0f).withExtraKerningFactor(-0.03f));
    timeLabel->addMouseListener(this, true);
    positionLabel->setFont(getDefaultTwonkMonoFont().withHeight(14.0f).withExtraKerningFactor(-0.03f));
    positionLabel->addMouseListener(this, true);
    tempoLabel->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
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

    memUsage->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
    cpuUsage->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
    //[/UserPreSize]

    setSize(316, 48);


    //[Constructor] You can add your own custom stuff here..
    tempoLabel->setText(String(playHead.getTempo()), dontSendNotification);
    tempoSlider->setValue(playHead.getTempo(), dontSendNotification);

    startTimer(3000);
    //[/Constructor]
}

TwonkTransport::~TwonkTransport() {
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


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkTransport::paint(Graphics &g) {
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 152.0f, y = 2.0f, width = 160.0f, height = 44.0f;
        Colour fillColour1 = Colour(0x4b000000), fillColour2 = Colour(0x91000000);
        Colour strokeColour1 = Colour(0xff323232), strokeColour2 = Colour(0xff4a4a4a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill(ColourGradient(fillColour1,
                                         192.0f - 152.0f + x,
                                         0.0f - 2.0f + y,
                                         fillColour2,
                                         192.0f - 152.0f + x,
                                         48.0f - 2.0f + y,
                                         false));
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
        g.setGradientFill(ColourGradient(strokeColour1,
                                         232.0f - 152.0f + x,
                                         48.0f - 2.0f + y,
                                         strokeColour2,
                                         232.0f - 152.0f + x,
                                         static_cast<float> (-8) - 2.0f + y,
                                         false));
        g.drawRoundedRectangle(x, y, width, height, 10.000f, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkTransport::resized() {
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkTransport::sliderValueChanged(Slider *sliderThatWasMoved) {
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == tempoSlider.get()) {
        //[UserSliderCode_tempoSlider] -- add your slider handling code here..
        playHead.setTempo(tempoSlider->getValue());
        //[/UserSliderCode_tempoSlider]
    } else if (sliderThatWasMoved == loopLengthSlider.get()) {
        //[UserSliderCode_loopLengthSlider] -- add your slider handling code here..
        //[/UserSliderCode_loopLengthSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void TwonkTransport::mouseDown(const MouseEvent &e) {
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

void TwonkTransport::mouseDrag(const MouseEvent &e) {
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

void TwonkTransport::mouseDoubleClick(const MouseEvent &e) {
    //[UserCode_mouseDoubleClick] -- Add your code here...
    if (e.eventComponent == this
        || e.eventComponent == tempoLabel.get()
        || e.eventComponent == positionLabel.get()
        || e.eventComponent == timeLabel.get()
        || e.eventComponent == cpuUsage.get()
        || e.eventComponent == memUsage.get()) {
        if (getHeight() > 48)
            setSize(getWidth(), 48);
        else
            setSize(getWidth(), 48 + 40 + 40);
    }
    //[/UserCode_mouseDoubleClick]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkTransport::buttonClicked(Button *button) {
    if (playButton.get() == button) {
        if (playHead.isPlaying()) {
            playHead.pause();
            playButton->setIcon(IMG(icon_play_png));
        } else {
            playHead.play(false);
            playButton->setIcon(IMG(icon_pause_png));
        }
    }

    if (stopButton.get() == button) {
        playHead.stop();
        playButton->setIcon(IMG(icon_play_png));
        playButton->repaint();
    }

    if (loopButton.get() == button) {
        if (loopButton->getToggleState()) {
            loopButton->setIconAlpha(1.0f);
        } else {
            loopButton->setIconAlpha(0.3f);
        }

        playHead.setLooping(loopButton->getToggleState());
    }
}

void TwonkTransport::positionChanged(const AudioPlayHead::PositionInfo &positionInfo) {
    auto secs = positionInfo.getTimeInSeconds().orFallback(0.0);
    auto ppq = positionInfo.getPpqPosition().orFallback(0.0);
    auto sig = positionInfo.getTimeSignature().orFallback(AudioPlayHead::TimeSignature{});
    auto bpm = positionInfo.getBpm().orFallback(120.0);

    auto millisecs = roundToInt(secs * 1000.0);
    auto absMillisecs = std::abs(millisecs);

    timeLabel->setText(String::formatted("%02d:%02d.%03d",
                                         (absMillisecs / 60000) % 60,
                                         (absMillisecs / 1000) % 60,
                                         absMillisecs % 1000), dontSendNotification);

    positionLabel->setText(quarterNotePositionToBarsBeatsString(ppq, sig),
                           dontSendNotification);

    tempoLabel->setText(String(bpm), dontSendNotification);
}

void TwonkTransport::timerCallback() {
    cpuUsage->setText(String(TwonkPlatform::getCpuUsage()) + "%", dontSendNotification);
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
                 fixedSize="1" initialWidth="316" initialHeight="48">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="152 2 160 44" cornerSize="10.0" fill="linear: 192 0, 192 48, 0=4b000000, 1=91000000"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="linear: 232 48, 232 -8, 0=ff323232, 1=ff4a4a4a"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="Play" id="2c55bb8ca25e0670" memberName="playButton" virtualName=""
                    explicitFocusOrder="0" pos="96 0 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Stop" id="3939c49b154d616b" memberName="stopButton" virtualName=""
                    explicitFocusOrder="0" pos="48 0 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Loop" id="1eb53a8fbe2c1759" memberName="loopButton" virtualName=""
                    explicitFocusOrder="0" pos="0 0 48 48" class="TwonkToolBarButton"
                    params=""/>
  <SLIDER name="Tempo" id="9d6c76ef260baea1" memberName="tempoSlider" virtualName=""
          explicitFocusOrder="0" pos="0 48 312 40" bkgcol="82005179" trackcol="ff00b2ff"
          min="30.0" max="300.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Loop Length" id="653c441302bacde0" memberName="loopLengthSlider"
          virtualName="" explicitFocusOrder="0" pos="0 88 312 40" bkgcol="bf879e00"
          thumbcol="ffb8dc1a" trackcol="edf4ff56" min="4.0" max="64.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Time" id="652beaf6f8698602" memberName="timeLabel" virtualName=""
         explicitFocusOrder="0" pos="232 28 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="00:00:000" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="14.0"
         kerning="-0.074" bold="0" italic="0" justification="36"/>
  <LABEL name="Time" id="1f6e782fb5035eac" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="160 8 80 16" edTextCol="ff000000"
         edBkgCol="0" labelText="00.00.000" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="14.0"
         kerning="-0.065" bold="0" italic="0" justification="33"/>
  <LABEL name="Tempo" id="5485653b957cb88d" memberName="tempoLabel" virtualName=""
         explicitFocusOrder="0" pos="160 29 40 14" textCol="ff42a2c8"
         edTextCol="ff000000" edBkgCol="0" labelText="120" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="14.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="CPU Usage" id="8f8b6394fbbd65c1" memberName="cpuUsage"
         virtualName="" explicitFocusOrder="0" pos="237 8 30 14" edTextCol="ff000000"
         edBkgCol="0" labelText="99%" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Memory Usage" id="94dfb8c0a903d21e" memberName="memUsage"
         virtualName="" explicitFocusOrder="0" pos="264 8 44 14" edTextCol="ff000000"
         edBkgCol="0" labelText="1900MB" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


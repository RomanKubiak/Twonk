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
#include "GraphEditorPanel.h"
#include "TwonkToolBarButton.h"
#include "TwonkToolBarStatus.h"
#include "TwonkMidiKeyboard.h"
#include "MainHostWindow.h"
//[/Headers]

#include "TwonkToolBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkToolBar::TwonkToolBar (GraphEditorPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    buttonConfig.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonConfig.get());
    buttonConfig->setName ("Config");

    buttonConfig->setBounds (0, 40, 64, 64);

    buttonFilters.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonFilters.get());
    buttonFilters->setName ("Filters");

    buttonFilters->setBounds (0, 104, 64, 64);

    buttonPlay.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonPlay.get());
    buttonPlay->setName ("Play");

    buttonPlay->setBounds (0, 232, 64, 64);

    statusItem.reset (new TwonkToolBarStatus());
    addAndMakeVisible (statusItem.get());
    statusItem->setName ("Status");

    statusItem->setBounds (0, 296, 64, 32);

    buttonMidiKeyboard.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonMidiKeyboard.get());
    buttonMidiKeyboard->setName ("Midi Keyboard");

    buttonMidiKeyboard->setBounds (0, 168, 64, 64);

    tempoSlider.reset (new Slider ("Tempo"));
    addAndMakeVisible (tempoSlider.get());
    tempoSlider->setTooltip (TRANS("Tempo"));
    tempoSlider->setRange (60, 240, 1);
    tempoSlider->setSliderStyle (Slider::LinearBarVertical);
    tempoSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    tempoSlider->setColour (Slider::backgroundColourId, Colour (0xff2e7540));
    tempoSlider->setColour (Slider::thumbColourId, Colour (0xff00ff36));
    tempoSlider->setColour (Slider::trackColourId, Colour (0x849e3594));
    tempoSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    tempoSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    tempoSlider->addListener (this);

    tempoSlider->setBounds (0, 360, 32, 136);

    volumeSlider.reset (new Slider ("Volume"));
    addAndMakeVisible (volumeSlider.get());
    volumeSlider->setTooltip (TRANS("Volume"));
    volumeSlider->setRange (0, 100, 1);
    volumeSlider->setSliderStyle (Slider::LinearBarVertical);
    volumeSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    volumeSlider->setColour (Slider::backgroundColourId, Colour (0xff665757));
    volumeSlider->setColour (Slider::thumbColourId, Colour (0xffc84242));
    volumeSlider->setColour (Slider::trackColourId, Colour (0xab035f86));
    volumeSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffd85e5e));
    volumeSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00000000));
    volumeSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    volumeSlider->addListener (this);

    volumeSlider->setBounds (32, 368, 32, 136);

    tempoLabel.reset (new Label (String(),
                                 TRANS("Tempo")));
    addAndMakeVisible (tempoLabel.get());
    tempoLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    tempoLabel->setJustificationType (Justification::centredLeft);
    tempoLabel->setEditable (false, false, false);
    tempoLabel->setColour (TextEditor::textColourId, Colours::black);
    tempoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    tempoLabel->setBounds (0, 336, 56, 16);

    volumeLabel.reset (new Label ("=",
                                  TRANS("Volume")));
    addAndMakeVisible (volumeLabel.get());
    volumeLabel->setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Bold"));
    volumeLabel->setJustificationType (Justification::centredRight);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    volumeLabel->setBounds (0, 512, 64, 16);

    buttonToggle.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonToggle.get());
    buttonToggle->setName ("Toggle ToolBar");

    buttonToggle->setBounds (0, 0, 64, 32);


    //[UserPreSize]
	buttonConfig->setIcon(ImageCache::getFromMemory(BinaryData::icon_audio_dev_png, BinaryData::icon_audio_dev_pngSize));
	buttonConfig->addListener(this);
	buttonFilters->setIcon(ImageCache::getFromMemory(BinaryData::icon_plugin_internal_png, BinaryData::icon_plugin_internal_pngSize));
	buttonFilters->setBaseColour(Colour(BUBBLE_COLOUR_PLUGIN_FX));
	buttonPlay->setBaseColour(Colours::green);
	buttonPlay->setIcon(ImageCache::getFromMemory(BinaryData::icon_play_png, BinaryData::icon_play_pngSize));
	buttonMidiKeyboard->setBaseColour(Colours::aqua);
	buttonMidiKeyboard->setIcon(ImageCache::getFromMemory(BinaryData::icon_piano_png, BinaryData::icon_piano_pngSize));
	buttonMidiKeyboard->addListener(this);
	buttonToggle->setIcon(ImageCache::getFromMemory(BinaryData::icon_min_max_png, BinaryData::icon_min_max_pngSize));
	buttonToggle->setSize(32, 32);
	buttonToggle->addListener(this);

	volumeSlider->setValue(50, sendNotificationAsync);
	tempoSlider->setValue(120, sendNotificationAsync);
    //[/UserPreSize]

    setSize (64, 536);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkToolBar::~TwonkToolBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    buttonConfig = nullptr;
    buttonFilters = nullptr;
    buttonPlay = nullptr;
    statusItem = nullptr;
    buttonMidiKeyboard = nullptr;
    tempoSlider = nullptr;
    volumeSlider = nullptr;
    tempoLabel = nullptr;
    volumeLabel = nullptr;
    buttonToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkToolBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = static_cast<float> (getHeight() - 0);
        Colour fillColour1 = Colour (0x00000000), fillColour2 = Colour (0x49000000);
        Colour strokeColour = Colour (0x56000000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       32.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       32.0f - 0.0f + x,
                                       48.0f - 0.0f + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 1.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 1.000f, 2.000f);
    }

    {
        float x = 0.0f, y = 0.0f, width = 64.0f, height = 32.0f;
        Colour fillColour = Colour (0x21ff8686);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkToolBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	buttonToggle->setBounds(16, 0, 32, 32);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkToolBar::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == tempoSlider.get())
    {
        //[UserSliderCode_tempoSlider] -- add your slider handling code here..
        //[/UserSliderCode_tempoSlider]
    }
    else if (sliderThatWasMoved == volumeSlider.get())
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
        //[/UserSliderCode_volumeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void TwonkToolBar::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	toolbarDragger.startDraggingComponent (this, e);
    //[/UserCode_mouseDown]
}

void TwonkToolBar::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	toolbarDragger.dragComponent (this, e, nullptr);
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkToolBar::positionChanged(const AudioPlayHead::CurrentPositionInfo &positionInfo)
{
	/*if (!positionInfo.isPlaying)
	{
		timeLabel->setText("00:00:00:0.0", dontSendNotification);
		return;
	}

	timeLabel->setText(String::formatted("00:00:00:%.1f", positionInfo.ppqPosition), dontSendNotification);
	*/
}

void TwonkToolBar::transportStopped()
{
}

void TwonkToolBar::buttonClicked(Button *button)
{
	if (button == buttonToggle.get())
	{
		if (getHeight() > 32)
			toolbarAnimator.animateComponent(this, getBounds().withHeight(32), 1.0f, 250, false, 5.0, 1.0);
		else
			toolbarAnimator.animateComponent(this, getBounds().withHeight(532), 1.0f, 250, false, 5.0, 1.0);
	}

	if (button == buttonConfig.get())
	{
		if (auto target = ApplicationCommandManager::findDefaultComponentTarget())
		{
			target->invoke (ApplicationCommandTarget::InvocationInfo(CommandIDs::showAudioSettings), true);
		}
	}

	if (button == buttonMidiKeyboard.get())
	{
		if (auto keys = owner.getTwonkMidiKeyboardComponent())
		{
			keys->setVisible(!keys->isVisible());
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkToolBar" componentName=""
                 parentClasses="public Component, public TwonkClockListener, Button::Listener"
                 constructorParams="GraphEditorPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="64" initialHeight="536">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="1.0" fill="linear: 32 0, 32 48, 0=0, 1=49000000"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: 56000000"/>
    <ROUNDRECT pos="0 0 64 32" cornerSize="5.0" fill="solid: 21ff8686" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="Config" id="d2fe4dda321d3109" memberName="buttonConfig"
                    virtualName="" explicitFocusOrder="0" pos="0 40 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Filters" id="fdd3b341895bc99a" memberName="buttonFilters"
                    virtualName="" explicitFocusOrder="0" pos="0 104 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Play" id="2e128e40245c4550" memberName="buttonPlay" virtualName=""
                    explicitFocusOrder="0" pos="0 232 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Status" id="90f30f12e157b22" memberName="statusItem" virtualName=""
                    explicitFocusOrder="0" pos="0 296 64 32" class="TwonkToolBarStatus"
                    params=""/>
  <GENERICCOMPONENT name="Midi Keyboard" id="ac2e75c6311a26ee" memberName="buttonMidiKeyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 168 64 64" class="TwonkToolBarButton"
                    params=""/>
  <SLIDER name="Tempo" id="517df69ca290377e" memberName="tempoSlider" virtualName=""
          explicitFocusOrder="0" pos="0 360 32 136" tooltip="Tempo" bkgcol="ff2e7540"
          thumbcol="ff00ff36" trackcol="849e3594" textboxbkgd="0" textboxoutline="0"
          min="60.0" max="240.0" int="1.0" style="LinearBarVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Volume" id="acaff02aa6a835a7" memberName="volumeSlider"
          virtualName="" explicitFocusOrder="0" pos="32 368 32 136" tooltip="Volume"
          bkgcol="ff665757" thumbcol="ffc84242" trackcol="ab035f86" rotaryslideroutline="ffd85e5e"
          textboxbkgd="0" textboxoutline="0" min="0.0" max="100.0" int="1.0"
          style="LinearBarVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="" id="59d0af79ee9efd42" memberName="tempoLabel" virtualName=""
         explicitFocusOrder="0" pos="0 336 56 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="=" id="6d12e64054b9c9a3" memberName="volumeLabel" virtualName=""
         explicitFocusOrder="0" pos="0 512 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10.0"
         kerning="0.0" bold="1" italic="0" justification="34" typefaceStyle="Bold"/>
  <GENERICCOMPONENT name="Toggle ToolBar" id="9f2837463eea4df0" memberName="buttonToggle"
                    virtualName="" explicitFocusOrder="0" pos="0 0 64 32" class="TwonkToolBarButton"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


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
#include "TwonkFileMenu.h"
#include "BinaryData.h"
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

    buttonConfig->setBounds (0, 128, 64, 64);

    buttonFilters.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonFilters.get());

    buttonFilters->setBounds (0, 192, 64, 64);

    buttonPlay.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonPlay.get());

    buttonPlay->setBounds (0, 320, 64, 64);

    statusItem.reset (new TwonkToolBarStatus());
    addAndMakeVisible (statusItem.get());
    statusItem->setName ("Status");

    statusItem->setBounds (0, 32, 64, 32);

    buttonMidiKeyboard.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonMidiKeyboard.get());

    buttonMidiKeyboard->setBounds (0, 256, 64, 64);

    buttonToggle.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonToggle.get());

    buttonToggle->setBounds (0, 0, 64, 32);

    buttonFile.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonFile.get());

    buttonFile->setBounds (0, 64, 64, 64);

    twonkFileMenu.reset (new TwonkFileMenu (owner));
    addAndMakeVisible (twonkFileMenu.get());
    twonkFileMenu->setBounds (72, 64, 210, 80);


    //[UserPreSize]
	buttonConfig->setIcon(ImageCache::getFromMemory(BinaryData::icon_audio_dev_png, BinaryData::icon_audio_dev_pngSize));
	buttonConfig->addListener(this);
	buttonConfig->setTooltip("Audio settings");
	buttonFilters->setIcon(ImageCache::getFromMemory(BinaryData::icon_plugin_internal_png, BinaryData::icon_plugin_internal_pngSize));
	buttonFilters->setBaseColour(Colour(BUBBLE_COLOUR_PLUGIN_FX));
	buttonFilters->setTooltip("Plugins and internal filters");
	buttonPlay->setBaseColour(Colours::green);
	buttonPlay->setIcon(ImageCache::getFromMemory(BinaryData::icon_play_png, BinaryData::icon_play_pngSize));
	buttonMidiKeyboard->setBaseColour(Colours::aqua);
	buttonMidiKeyboard->setIcon(ImageCache::getFromMemory(BinaryData::icon_piano_png, BinaryData::icon_piano_pngSize));
	buttonMidiKeyboard->addListener(this);
	buttonMidiKeyboard->setTooltip("Toggle on-screen MIDI keyboard");
	buttonToggle->setIcon(ImageCache::getFromMemory(BinaryData::icon_min_max_png, BinaryData::icon_min_max_pngSize));
	buttonToggle->setSize(32, 32);
	buttonToggle->addListener(this);
	buttonToggle->setTooltip("Toggle toolbar hide/show");
	buttonFile->setIcon(ImageCache::getFromMemory(BinaryData::icon_floppy_png, BinaryData::icon_floppy_pngSize));
	buttonFile->setBaseColour(Colours::lightgreen);
	buttonFile->addListener(this);
	buttonFile->setTooltip("File operations");
    //[/UserPreSize]

    setSize (400, 384);


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
    buttonToggle = nullptr;
    buttonFile = nullptr;
    twonkFileMenu = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkToolBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

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

	if (button == buttonFile.get())
	{
		owner.toggleTwonkFileMenu();
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
                 fixedSize="1" initialWidth="400" initialHeight="384">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="" id="d2fe4dda321d3109" memberName="buttonConfig" virtualName=""
                    explicitFocusOrder="0" pos="0 128 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="" id="fdd3b341895bc99a" memberName="buttonFilters" virtualName=""
                    explicitFocusOrder="0" pos="0 192 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="" id="2e128e40245c4550" memberName="buttonPlay" virtualName=""
                    explicitFocusOrder="0" pos="0 320 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Status" id="90f30f12e157b22" memberName="statusItem" virtualName=""
                    explicitFocusOrder="0" pos="0 32 64 32" class="TwonkToolBarStatus"
                    params=""/>
  <GENERICCOMPONENT name="" id="ac2e75c6311a26ee" memberName="buttonMidiKeyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 256 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="" id="9f2837463eea4df0" memberName="buttonToggle" virtualName=""
                    explicitFocusOrder="0" pos="0 0 64 32" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="" id="face426d9e5a53b" memberName="buttonFile" virtualName=""
                    explicitFocusOrder="0" pos="0 64 64 64" class="TwonkToolBarButton"
                    params=""/>
  <JUCERCOMP name="" id="eb3cc73fd1410a00" memberName="twonkFileMenu" virtualName=""
             explicitFocusOrder="0" pos="72 64 210 80" sourceFile="TwonkFileMenu.cpp"
             constructorParams="owner"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


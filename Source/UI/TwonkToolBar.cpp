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

    buttonConfig->setBounds (0, 0, 64, 64);

    buttonFilters.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonFilters.get());
    buttonFilters->setName ("Filters");

    buttonFilters->setBounds (0, 64, 64, 64);

    buttonMinMax.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonMinMax.get());
    buttonMinMax->setName ("Minimize/Maximize");

    buttonMinMax->setBounds (0, 288, 64, 64);

    buttonPlay.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonPlay.get());
    buttonPlay->setName ("Play");

    buttonPlay->setBounds (0, 192, 64, 64);

    statusItem.reset (new TwonkToolBarStatus());
    addAndMakeVisible (statusItem.get());
    statusItem->setName ("Status");

    statusItem->setBounds (0, 256, 64, 32);

    buttonMidiKeyboard.reset (new TwonkToolBarButton());
    addAndMakeVisible (buttonMidiKeyboard.get());
    buttonMidiKeyboard->setName ("Midi Keyboard");

    buttonMidiKeyboard->setBounds (0, 128, 64, 64);


    //[UserPreSize]
	buttonConfig->setIcon(ImageCache::getFromMemory(BinaryData::iconfinder_Streamline75_185095_png, BinaryData::iconfinder_Streamline75_185095_pngSize));
	buttonFilters->setIcon(ImageCache::getFromMemory(BinaryData::icon_block_64_png, BinaryData::icon_block_64_pngSize));
	buttonFilters->setBaseColour(Colour(BUBBLE_COLOUR_PLUGIN_FX));
	buttonPlay->setBaseColour(Colours::green);
	buttonPlay->setIcon(ImageCache::getFromMemory(BinaryData::iconfinder_iconplay_211876_png, BinaryData::iconfinder_iconplay_211876_pngSize));
	buttonMinMax->setIcon(ImageCache::getFromMemory(BinaryData::iconfinder_minimize2_2561246_png, BinaryData::iconfinder_minimize2_2561246_pngSize));
	buttonMinMax->setBaseColour(Colours::white);
	buttonMidiKeyboard->setBaseColour(Colours::aqua);
	buttonMidiKeyboard->setIcon(ImageCache::getFromMemory(BinaryData::iconfinder_piano_music_instrument_keyboard_musical_4593126_png, BinaryData::iconfinder_piano_music_instrument_keyboard_musical_4593126_pngSize));
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
    buttonMinMax = nullptr;
    buttonPlay = nullptr;
    statusItem = nullptr;
    buttonMidiKeyboard = nullptr;


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
        Colour fillColour1 = Colour (0x58000000), fillColour2 = Colour (0x756d6d6d);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       40.0f - 0.0f + x,
                                       296.0f - 0.0f + y,
                                       fillColour2,
                                       296.0f - 0.0f + x,
                                       264.0f - 0.0f + y,
                                       true));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkToolBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
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

void TwonkToolBar::buttonClicked (Button *b)
{

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkToolBar" componentName=""
                 parentClasses="public Component, public TwonkClockListener, public Button::Listener"
                 constructorParams="GraphEditorPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="64" initialHeight="536">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="0 0 0M 0M" cornerSize="10.0" fill=" radial: 40 296, 296 264, 0=58000000, 1=756d6d6d"
               hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="Config" id="d2fe4dda321d3109" memberName="buttonConfig"
                    virtualName="" explicitFocusOrder="0" pos="0 0 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Filters" id="fdd3b341895bc99a" memberName="buttonFilters"
                    virtualName="" explicitFocusOrder="0" pos="0 64 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Minimize/Maximize" id="4e7c3844d4c9b13f" memberName="buttonMinMax"
                    virtualName="" explicitFocusOrder="0" pos="0 288 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Play" id="2e128e40245c4550" memberName="buttonPlay" virtualName=""
                    explicitFocusOrder="0" pos="0 192 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="Status" id="90f30f12e157b22" memberName="statusItem" virtualName=""
                    explicitFocusOrder="0" pos="0 256 64 32" class="TwonkToolBarStatus"
                    params=""/>
  <GENERICCOMPONENT name="Midi Keyboard" id="ac2e75c6311a26ee" memberName="buttonMidiKeyboard"
                    virtualName="" explicitFocusOrder="0" pos="0 128 64 64" class="TwonkToolBarButton"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


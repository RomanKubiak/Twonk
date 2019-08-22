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

#include "TwonkAudioSettingsMenu.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Twonk.h"
#include "TwonkToolBarButton.h"
#include "GraphEditorPanel.h"
#include "MainHostWindow.h"
#include "BinaryData.h"
//[/MiscUserDefs]

//==============================================================================
TwonkAudioSettingsMenu::TwonkAudioSettingsMenu (GraphEditorPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    settingsPlugins.reset (new TwonkToolBarButton());
    addAndMakeVisible (settingsPlugins.get());
    settingsPlugins->setName ("SAVE");

    settingsPlugins->setBounds (72, 0, 64, 64);

    settingsAudio.reset (new TwonkToolBarButton());
    addAndMakeVisible (settingsAudio.get());
    settingsAudio->setName ("NEW");

    settingsAudio->setBounds (0, 0, 64, 64);


    //[UserPreSize]
	settingsPlugins->setBaseColour(Colours::orangered.brighter(0.2f));
	settingsPlugins->setIcon(IMG(icon_plugin_internal_png));
	settingsAudio->setBaseColour(Colours::bisque.darker(0.2f));
	settingsAudio->setIcon(IMG(icon_audio_dev_png));
	settingsAudio->addListener(this);
	settingsPlugins->addListener(this);
    //[/UserPreSize]

    setSize (136, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkAudioSettingsMenu::~TwonkAudioSettingsMenu()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    settingsPlugins = nullptr;
    settingsAudio = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkAudioSettingsMenu::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkAudioSettingsMenu::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkAudioSettingsMenu::buttonClicked(Button *b)
{
	if (b == settingsAudio.get())
	{
		if (auto target = ApplicationCommandManager::findDefaultComponentTarget())
		{
			target->invoke (ApplicationCommandTarget::InvocationInfo(CommandIDs::showAudioSettings), false);
		}
	}

	if (b == settingsPlugins.get())
	{
		if (auto target = ApplicationCommandManager::findDefaultComponentTarget())
		{
			target->invoke (ApplicationCommandTarget::InvocationInfo(CommandIDs::showPluginListEditor), false);
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

<JUCER_COMPONENT documentType="Component" className="TwonkAudioSettingsMenu" componentName=""
                 parentClasses="public Component, public Button::Listener" constructorParams="GraphEditorPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="136"
                 initialHeight="64">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="SAVE" id="f47128457b7b2ed7" memberName="settingsPlugins"
                    virtualName="" explicitFocusOrder="0" pos="72 0 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="NEW" id="6606329e0f8f9cc5" memberName="settingsAudio" virtualName=""
                    explicitFocusOrder="0" pos="0 0 64 64" class="TwonkToolBarButton"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


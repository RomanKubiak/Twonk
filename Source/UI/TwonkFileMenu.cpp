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

#include "TwonkFileMenu.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Twonk.h"
#include "TwonkToolBarButton.h"
#include "GraphEditorPanel.h"
#include "MainHostWindow.h"
#include "BinaryData.h"
//[/MiscUserDefs]

//==============================================================================
TwonkFileMenu::TwonkFileMenu (GraphEditorPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    programLoad.reset (new TwonkToolBarButton());
    addAndMakeVisible (programLoad.get());
    programLoad->setName ("LOAD");

    programLoad->setBounds (144, 0, 64, 64);

    programSave.reset (new TwonkToolBarButton());
    addAndMakeVisible (programSave.get());
    programSave->setName ("SAVE");

    programSave->setBounds (72, 0, 64, 64);

    programNew.reset (new TwonkToolBarButton());
    addAndMakeVisible (programNew.get());
    programNew->setName ("NEW");

    programNew->setBounds (0, 0, 64, 64);

    label.reset (new Label ("new label",
                            TRANS("new")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (0, 64, 64, 12);

    label2.reset (new Label ("new label",
                             TRANS("save")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (72, 64, 64, 12);

    label3.reset (new Label ("new label",
                             TRANS("load")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (144, 64, 64, 12);


    //[UserPreSize]
	programNew->setIcon(IMG(icon_floppy_png));
	programNew->setBaseColour(Colours::green);
	programNew->setButtonText("New");
	programSave->setIcon(IMG(icon_floppy_png));
	programSave->setBaseColour(Colours::lightpink);
	programLoad->setIcon(IMG(icon_floppy_png));
	programLoad->setBaseColour(Colours::lightgreen);
    //[/UserPreSize]

    setSize (208, 80);


    //[Constructor] You can add your own custom stuff here..
	programLoad->addListener(this);
	programSave->addListener(this);
	programNew->addListener(this);
    //[/Constructor]
}

TwonkFileMenu::~TwonkFileMenu()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    programLoad = nullptr;
    programSave = nullptr;
    programNew = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkFileMenu::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkFileMenu::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkFileMenu::buttonClicked(Button *b)
{
	if (b == programLoad.get())
	{
		owner.toggleProgramMenu();
	}

	if (b == programSave.get())
	{
		SafePointer<DialogWindow> dialogWindow;

		DialogWindow::LaunchOptions options;
		options.content.setOwned (new TwonkSaveFileDialog());
		options.dialogBackgroundColour = Colours::transparentBlack;
		options.escapeKeyTriggersCloseButton = true;
		options.useNativeTitleBar = false;
		options.resizable = false;
		options.runModal();
	}

	if (b == programNew.get())
	{
		if (auto target = ApplicationCommandManager::findDefaultComponentTarget())
		{
			target->invoke (ApplicationCommandTarget::InvocationInfo(CommandIDs::newFile), false);
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

<JUCER_COMPONENT documentType="Component" className="TwonkFileMenu" componentName=""
                 parentClasses="public Component, public Button::Listener" constructorParams="GraphEditorPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="208"
                 initialHeight="80">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="LOAD" id="8de011dfeb6f5ac1" memberName="programLoad" virtualName=""
                    explicitFocusOrder="0" pos="144 0 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="SAVE" id="f47128457b7b2ed7" memberName="programSave" virtualName=""
                    explicitFocusOrder="0" pos="72 0 64 64" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="NEW" id="6606329e0f8f9cc5" memberName="programNew" virtualName=""
                    explicitFocusOrder="0" pos="0 0 64 64" class="TwonkToolBarButton"
                    params=""/>
  <LABEL name="new label" id="a5e711ea0650191f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 64 64 12" edTextCol="ff000000"
         edBkgCol="0" labelText="new" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3e3822b7fd1a8de4" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="72 64 64 12" edTextCol="ff000000"
         edBkgCol="0" labelText="save" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b3c4e84bcd07ffa" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="144 64 64 12" edTextCol="ff000000"
         edBkgCol="0" labelText="load" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


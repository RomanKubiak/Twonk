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

#include "TwonkProgramMenu.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Twonk.h"
#include "TwonkToolBarButton.h"
#include "MainHostWindow.h"
#include "BinaryData.h"
#include "Panel/Editor.h"
//[/MiscUserDefs]

//==============================================================================
TwonkProgramMenu::TwonkProgramMenu (Editor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    programLoad.reset (new TwonkToolBarButton());
    addAndMakeVisible (programLoad.get());
    programLoad->setName ("LOAD");

    programLoad->setBounds (112, 0, 48, 48);

    programSave.reset (new TwonkToolBarButton());
    addAndMakeVisible (programSave.get());
    programSave->setName ("SAVE");

    programSave->setBounds (56, 0, 48, 48);

    programNew.reset (new TwonkToolBarButton());
    addAndMakeVisible (programNew.get());
    programNew->setName ("NEW");

    programNew->setBounds (0, 0, 48, 48);


    //[UserPreSize]
	programNew->setIcon(IMG(icon_floppy_png), 0.2f);
	programNew->setBaseColour(Colours::green);
	programNew->setText("new", Justification::centredTop, 12.0f, 16);
	programSave->setIcon(IMG(icon_floppy_png), 0.2f);
	programSave->setBaseColour(Colours::lightpink);
	programSave->setText("save", Justification::centredTop, 12.0f, 16);
	programLoad->setIcon(IMG(icon_floppy_png), 0.2f);
	programLoad->setBaseColour(Colours::lightgreen);
	programLoad->setText("load", Justification::centredTop, 12.0f, 16);
    //[/UserPreSize]

    setSize (160, 48);


    //[Constructor] You can add your own custom stuff here..
	programLoad->addListener(this);
	programSave->addListener(this);
	programNew->addListener(this);
    //[/Constructor]
}

TwonkProgramMenu::~TwonkProgramMenu()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    programLoad = nullptr;
    programSave = nullptr;
    programNew = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkProgramMenu::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkProgramMenu::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkProgramMenu::buttonClicked(Button *b)
{
	if (b == programLoad.get())
	{
		owner.toggleProgramMenu();
	}

	if (b == programSave.get())
	{
		SafePointer<DialogWindow> dialogWindow;

		DialogWindow::LaunchOptions options;
		std::unique_ptr<TwonkSaveProgramDialog> dialog (new TwonkSaveProgramDialog());
		options.content.setNonOwned (dialog.get());
		options.dialogBackgroundColour = Colours::white.withAlpha(0.5f);
		options.escapeKeyTriggersCloseButton = true;
		options.useNativeTitleBar = false;
		options.resizable = false;
		int possibleProgramType = options.runModal();
		if (possibleProgramType >= 0)
		{
			ProgramType p = (ProgramType)possibleProgramType;
			String descriptor = programTypeDescriptor(p);
			String programName = dialog->getProgramName();
			String fileToSave = programName + "." + descriptor + ".twonk";


			if (GET_TWONK_PROGRAM_DIR().getChildFile(fileToSave).existsAsFile())
			{
				int ret = AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon,
					"Overwrite warning",
					"A program name with that name and type already exists, do you want to overwrite it?");
				if (ret == 0)
					return;
			}
			Result r = owner.graph.saveDocument(GET_TWONK_PROGRAM_DIR().getChildFile(fileToSave));
			owner.updateTwonkDocuments();

			if (r.failed())
			{
				AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Program save", "Can't save program");
			}
		}
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

<JUCER_COMPONENT documentType="Component" className="TwonkProgramMenu" componentName=""
                 parentClasses="public Component, public Button::Listener" constructorParams="GraphEditorPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="160"
                 initialHeight="48">
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="LOAD" id="8de011dfeb6f5ac1" memberName="programLoad" virtualName=""
                    explicitFocusOrder="0" pos="112 0 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="SAVE" id="f47128457b7b2ed7" memberName="programSave" virtualName=""
                    explicitFocusOrder="0" pos="56 0 48 48" class="TwonkToolBarButton"
                    params=""/>
  <GENERICCOMPONENT name="NEW" id="6606329e0f8f9cc5" memberName="programNew" virtualName=""
                    explicitFocusOrder="0" pos="0 0 48 48" class="TwonkToolBarButton"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


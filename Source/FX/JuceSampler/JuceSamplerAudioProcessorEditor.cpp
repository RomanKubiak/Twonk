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

#include "JuceSamplerAudioProcessorEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "JuceSamplerAudioProcessor.h"
#include "Twonk.h"
#include "UI/MainHostWindow.h"
#include "InstrumentButtonsPanel.h"
#include "InstrumentParametersEditor.h"
//[/MiscUserDefs]

//==============================================================================
JuceSamplerAudioProcessorEditor::JuceSamplerAudioProcessorEditor (JucesamplerAudioProcessor &_processor)
    : processor(_processor), AudioProcessorEditor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
	setLookAndFeel (&samplerLookAndFeel);
	programList.setDirectory(GET_TWONK_SAMPLES_DIR(), true, false);
	directoryThread.startThread(1);
	programList.addChangeListener(this);
    //[/Constructor_pre]

    bankListCombo.reset (new ComboBox (String()));
    addAndMakeVisible (bankListCombo.get());
    bankListCombo->setEditableText (false);
    bankListCombo->setJustificationType (Justification::centredLeft);
    bankListCombo->setTextWhenNothingSelected (TRANS("No bank selected"));
    bankListCombo->setTextWhenNoChoicesAvailable (TRANS("No banks in memory"));
    bankListCombo->addListener (this);

    panel.reset (new ConcertinaPanel());
    addAndMakeVisible (panel.get());


    //[UserPreSize]
	sizeConstrainer.reset(new ComponentBoundsConstrainer());
	sizeConstrainer->setMaximumWidth(900);
	sizeConstrainer->setMaximumHeight(500);
	sizeConstrainer->setMinimumHeight(64);
	sizeConstrainer->setMinimumWidth(128);
	cornerResizer.reset(new ResizableCornerComponent(this, sizeConstrainer.get()));
	addAndMakeVisible(cornerResizer.get());
    //[/UserPreSize]

    setSize (714, 240);


    //[Constructor] You can add your own custom stuff here..
	panel->addPanel(0, buttonsPanel = new InstrumentButtonsPanel(*this), true);
	panel->setMaximumPanelSize(panel->getPanel(0), 200);
	panel->getPanel(0)->setName("Instrument selector");
	panel->addPanel(1, new InstrumentParametersEditor(), true);
	panel->setMaximumPanelSize(panel->getPanel(1), 200);
	panel->getPanel(1)->setName("Instrument editor");
    //[/Constructor]
}

JuceSamplerAudioProcessorEditor::~JuceSamplerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
    //[/Destructor_pre]

    bankListCombo = nullptr;
    panel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void JuceSamplerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceSamplerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	cornerResizer->setBounds(getWidth() - 32, getHeight() - 32, 32, 32);
    //[/UserPreResize]

    bankListCombo->setBounds (proportionOfWidth (0.0098f), proportionOfHeight (0.0292f), proportionOfWidth (0.3501f), proportionOfHeight (0.1000f));
    panel->setBounds (proportionOfWidth (0.0098f), proportionOfHeight (0.1500f), proportionOfWidth (0.9804f), proportionOfHeight (0.8000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JuceSamplerAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == bankListCombo.get())
    {
        //[UserComboBoxCode_bankListCombo] -- add your combo box handling code here..
		if (comboBoxThatHasChanged->getSelectedItemIndex() >= 0)
		{
			int item = comboBoxThatHasChanged->getSelectedItemIndex();
			processor.loadBank(programList.getFile(item));
			loadInstrumentsToGui();
		}
        //[/UserComboBoxCode_bankListCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void JuceSamplerAudioProcessorEditor::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...




void JuceSamplerAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == &programList)
	{
		if (programList.isStillLoading())
		{
			bankListCombo->setTextWhenNoChoicesAvailable("Still loading banks");
		}
		else
		{
			for (int i = 0; i < programList.getNumFiles(); i++)
			{
				File f = programList.getFile(i);
				String item = f.getFileNameWithoutExtension().upToFirstOccurrenceOf(".", false, false);
				bankListCombo->addItem(item, i+1);
			}
		}
	}
}

void JuceSamplerAudioProcessorEditor::loadInstrumentsToGui()
{
	int i;
	for (i = 0; i < processor.getInstrumentsArray().size(); i++)
	{
		SamplerInstrument *instrument = processor.getInstrumentsArray()[i];
		buttonsPanel->getButton(i)->setInfo(instrument);
		buttonsPanel->getButton(i)->setAlpha(1.0f);
		if (i > 15)
			break;			
	}

	for (int j = i; j < 16; j++)
		buttonsPanel->getButton(j)->setAlpha(0.3f);

	buttonsPanel->deselectAll();
	buttonsPanel->getButton(0)->setSelected(true);
}

void JuceSamplerAudioProcessorEditor::currentInstrumentSelectionChanged(InstrumentButton *buttonSelected)
{
	if (!buttonSelected->isSelected())
	{
		buttonsPanel->deselectAll();
		buttonSelected->setSelected(true);
	}
	buttonSelected->previewAudio();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JuceSamplerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public ChangeListener"
                 constructorParams="JucesamplerAudioProcessor &amp;_processor"
                 variableInitialisers="processor(_processor), AudioProcessorEditor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="714" initialHeight="240">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <COMBOBOX name="" id="a874eedfa3cfe441" memberName="bankListCombo" virtualName=""
            explicitFocusOrder="0" pos="0.98% 2.917% 35.014% 10%" editable="0"
            layout="33" items="" textWhenNonSelected="No bank selected" textWhenNoItems="No banks in memory"/>
  <GENERICCOMPONENT name="" id="5fa05f23775a82b6" memberName="panel" virtualName=""
                    explicitFocusOrder="0" pos="0.98% 15% 98.039% 80%" class="ConcertinaPanel"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


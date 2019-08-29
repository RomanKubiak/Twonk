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

#include "SimplerEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SimplerProcessor.h"
#include "Twonk.h"
#include "UI/MainHostWindow.h"
#include "InstrumentButtonsPanel.h"
#include "InstrumentParametersEditor.h"
//[/MiscUserDefs]

//==============================================================================
SimplerEditor::SimplerEditor (SimplerProcessor &_processor)
    : processor(_processor), AudioProcessorEditor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
	setLookAndFeel (&samplerLookAndFeel);
	processor.addChangeListener(this);
    //[/Constructor_pre]

    bankListCombo.reset (new ComboBox (String()));
    addAndMakeVisible (bankListCombo.get());
    bankListCombo->setEditableText (false);
    bankListCombo->setJustificationType (Justification::centredLeft);
    bankListCombo->setTextWhenNothingSelected (TRANS("No bank selected"));
    bankListCombo->setTextWhenNoChoicesAvailable (TRANS("No banks in memory"));
    bankListCombo->addListener (this);

    bankListCombo->setBounds (8, 8, 250, 24);

    panel.reset (new ConcertinaPanel());
    addAndMakeVisible (panel.get());

    drawable1 = Drawable::createFromImageData (BinaryData::sampler_bg_jpg, BinaryData::sampler_bg_jpgSize);

    //[UserPreSize]
	sizeConstrainer.reset(new ComponentBoundsConstrainer());
	sizeConstrainer->setMaximumWidth(720);
	sizeConstrainer->setMaximumHeight(450 + 72 + 24);
	sizeConstrainer->setMinimumHeight(250 + 64 + 24);
	sizeConstrainer->setMinimumWidth(128);
	cornerResizer.reset(new ResizableCornerComponent(this, sizeConstrainer.get()));
	addAndMakeVisible(cornerResizer.get());
	bankListCombo->setColour(ComboBox::backgroundColourId, Colours::black);
    //[/UserPreSize]

    setSize (720, 500);


    //[Constructor] You can add your own custom stuff here..
	panel->addPanel(0, buttonsPanel = new InstrumentButtonsPanel(*this), true);
	panel->setMaximumPanelSize(panel->getPanel(0), 200);
	panel->getPanel(0)->setName("Instrument selector");
	panel->addPanel(1, instrumentEditor = new InstrumentParametersEditor(processor), true);
	panel->setMaximumPanelSize(panel->getPanel(1), 250);
	panel->getPanel(1)->setName("Instrument editor");
	loadBanksToCombo();
	loadInstrumentsToGui();
    //[/Constructor]
}

SimplerEditor::~SimplerEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	processor.removeChangeListener(this);
	setLookAndFeel(nullptr);
    //[/Destructor_pre]

    bankListCombo = nullptr;
    panel = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SimplerEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (Colours::black.withAlpha (0.697f));
        jassert (drawable1 != 0);
        if (drawable1 != 0)
            drawable1->drawWithin (g, Rectangle<float> (x, y, width, height),
                                   RectanglePlacement::stretchToFit, 0.697f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SimplerEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	cornerResizer->setBounds(getWidth() - 32, getHeight() - 32, 32, 32);
    //[/UserPreResize]

    panel->setBounds (0, 48, getWidth() - 0, getHeight() - 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SimplerEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == bankListCombo.get())
    {
        //[UserComboBoxCode_bankListCombo] -- add your combo box handling code here..
		if (bankListCombo->getSelectedItemIndex() >= 0)
		{
			processor.loadBank(bankListCombo->getSelectedItemIndex());
		}
        //[/UserComboBoxCode_bankListCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void SimplerEditor::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimplerEditor::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == &processor)
	{
		loadBanksToCombo();
		loadInstrumentsToGui();
	}
}

void SimplerEditor::loadBanksToCombo()
{
	bankListCombo->clear(dontSendNotification);
	if (processor.getBankList().size() > 0)
	{
		for (int i = 0; i < processor.getBankList().size(); i++)
		{
			bankListCombo->addItem(processor.getBankList()[i].getFileNameWithoutExtension(), i + 1);
		}
	}
}

void SimplerEditor::loadInstrumentsToGui()
{
	instrumentEditor->setEditedInstrument(nullptr);
	const OwnedArray<SimplerInstrument> &data = processor.getLoadedInstruments();
	Array<InstrumentButton *> &buttons = buttonsPanel->getAllButtons();
	int allLoaded;
	for (allLoaded = 0; allLoaded < data.size(); allLoaded++)
	{
		buttons[allLoaded]->setCurrentInstrument(data[allLoaded]);
		buttons[allLoaded]->setAlpha(1.0f);
	}

	for (int j = allLoaded; j < 16; j++)
	{
		buttons[j]->setAlpha(0.2f);
	}
}

void SimplerEditor::currentInstrumentSelectionChanged(InstrumentButton *buttonSelected)
{
	if (!buttonSelected->isSelected())
	{
		buttonsPanel->deselectAll();
		buttonSelected->setSelected(true);
	}
	buttonSelected->previewAudio();

	SimplerInstrument *si = buttonSelected->getCurrentInstrument();
	if (si)
	{
		instrumentEditor->setEditedInstrument(si);
	}
}

void SimplerEditor::parameterChanged (const String &parameterID, float newValue)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimplerEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener, public AudioProcessorValueTreeState::Listener"
                 constructorParams="SimplerProcessor &amp;_processor" variableInitialisers="processor(_processor), AudioProcessorEditor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="720" initialHeight="500">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000">
    <IMAGE pos="0 0 0M 0M" resource="BinaryData::sampler_bg_jpg" opacity="0.6970000000000001"
           mode="0"/>
  </BACKGROUND>
  <COMBOBOX name="" id="a874eedfa3cfe441" memberName="bankListCombo" virtualName=""
            explicitFocusOrder="0" pos="8 8 250 24" editable="0" layout="33"
            items="" textWhenNonSelected="No bank selected" textWhenNoItems="No banks in memory"/>
  <GENERICCOMPONENT name="" id="5fa05f23775a82b6" memberName="panel" virtualName=""
                    explicitFocusOrder="0" pos="0 48 0M 48M" class="ConcertinaPanel"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


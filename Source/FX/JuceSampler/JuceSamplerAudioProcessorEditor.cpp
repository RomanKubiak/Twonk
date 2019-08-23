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
//[/MiscUserDefs]

//==============================================================================
JuceSamplerAudioProcessorEditor::JuceSamplerAudioProcessorEditor (JucesamplerAudioProcessor &_processor)
    : processor(_processor), AudioProcessorEditor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
	programList.setDirectory(GET_TWONK_SAMPLES_DIR(), false, true);
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

    bankListCombo->setBounds (352, 8, 240, 24);

    instrumentButton1.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton1.get());
    instrumentButton1->setBounds (16, 232, 64, 72);

    instrumentButton2.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton2.get());
    instrumentButton2->setBounds (80, 232, 64, 72);

    instrumentButton3.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton3.get());
    instrumentButton3->setBounds (144, 232, 64, 72);

    instrumentButton4.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton4.get());
    instrumentButton4->setBounds (208, 232, 64, 72);

    instrumentButton5.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton5.get());
    instrumentButton5->setBounds (272, 232, 64, 72);

    instrumentButton6.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton6.get());
    instrumentButton6->setBounds (336, 232, 64, 72);

    instrumentButton7.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton7.get());
    instrumentButton7->setBounds (400, 232, 64, 72);

    instrumentButton8.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton8.get());
    instrumentButton8->setBounds (464, 232, 64, 72);

    instrumentButton9.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton9.get());
    instrumentButton9->setBounds (528, 232, 64, 72);

    instrumentButton10.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton10.get());
    instrumentButton10->setBounds (16, 315, 64, 72);

    instrumentButton11.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton11.get());
    instrumentButton11->setBounds (80, 315, 64, 72);

    instrumentButton12.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton12.get());
    instrumentButton12->setBounds (144, 315, 64, 72);

    instrumentButton13.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton13.get());
    instrumentButton13->setBounds (208, 315, 64, 72);

    instrumentButton14.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton14.get());
    instrumentButton14->setBounds (272, 315, 64, 72);

    instrumentButton15.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton15.get());
    instrumentButton15->setBounds (336, 315, 64, 72);

    instrumentButton16.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton16.get());
    instrumentButton16->setBounds (400, 315, 64, 72);

    instrumentButton17.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton17.get());
    instrumentButton17->setBounds (464, 315, 64, 72);

    instrumentButton18.reset (new InstrumentButton());
    addAndMakeVisible (instrumentButton18.get());
    instrumentButton18->setBounds (528, 315, 64, 72);

    component.reset (new InstrumentWaveViewer());
    addAndMakeVisible (component.get());
    component->setBounds (16, 8, 312, 208);

    bankInfo.reset (new Label (String(),
                               TRANS("Info")));
    addAndMakeVisible (bankInfo.get());
    bankInfo->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    bankInfo->setJustificationType (Justification::centredLeft);
    bankInfo->setEditable (false, false, false);
    bankInfo->setColour (Label::outlineColourId, Colour (0x5affffff));
    bankInfo->setColour (TextEditor::textColourId, Colours::black);
    bankInfo->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bankInfo->setBounds (352, 40, 240, 48);

    bankUrl.reset (new HyperlinkButton (TRANS("new hyperlink"),
                                        URL (String())));
    addAndMakeVisible (bankUrl.get());
    bankUrl->setButtonText (TRANS("new hyperlink"));

    bankUrl->setBounds (352, 88, 240, 16);


    //[UserPreSize]
	bankInfo->setFont(getDefaultTwonkSansFont().withHeight(16.0f));
	bankUrl->setVisible(false);
    //[/UserPreSize]

    setSize (608, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

JuceSamplerAudioProcessorEditor::~JuceSamplerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bankListCombo = nullptr;
    instrumentButton1 = nullptr;
    instrumentButton2 = nullptr;
    instrumentButton3 = nullptr;
    instrumentButton4 = nullptr;
    instrumentButton5 = nullptr;
    instrumentButton6 = nullptr;
    instrumentButton7 = nullptr;
    instrumentButton8 = nullptr;
    instrumentButton9 = nullptr;
    instrumentButton10 = nullptr;
    instrumentButton11 = nullptr;
    instrumentButton12 = nullptr;
    instrumentButton13 = nullptr;
    instrumentButton14 = nullptr;
    instrumentButton15 = nullptr;
    instrumentButton16 = nullptr;
    instrumentButton17 = nullptr;
    instrumentButton18 = nullptr;
    component = nullptr;
    bankInfo = nullptr;
    bankUrl = nullptr;


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
    //[/UserPreResize]

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
			DBG("JuceSamplerAudioProcessorEditor::comboBoxChanged id:" + String(comboBoxThatHasChanged->getSelectedItemIndex()));
			int item = comboBoxThatHasChanged->getSelectedItemIndex();

			DBG("selected file: " + programList.getFile(item).getFullPathName());
			ZipFile z(programList.getFile(item));
			loadBank(z);
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
void JuceSamplerAudioProcessorEditor::loadBank(ZipFile &z)
{
	const int twonk = z.getIndexOfFileName("twonk.json", true);
	if (twonk > 0)
	{
		std::unique_ptr<InputStream> is (z.createStreamForEntry(twonk));
		var result;
		Result res = JSON::parse(is->readEntireStreamAsString(), result);
		if (res.failed())
		{
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Bank loading failed", "Can't parse the json file inside", "Fuck!");
			return;
		}
		else
		{
			const String name = result.getProperty("info", var()).getDynamicObject()->getProperty("name").toString();
			const String url = result.getProperty("info", var()).getDynamicObject()->getProperty("url").toString();
			bankInfo->setText(name, dontSendNotification);
			if (url.isNotEmpty())
			{
				bankUrl->setVisible(true);
				bankUrl->setURL(url);
				bankUrl->setButtonText(url);
			}
			else
			{
				bankUrl->setVisible(false);
			}
		}
	}
}

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
				String item = f.getFileNameWithoutExtension() + " / " + File::descriptionOfSizeInBytes(f.getSize());
				bankListCombo->addItem(item, i+1);
			}
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

<JUCER_COMPONENT documentType="Component" className="JuceSamplerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public ChangeListener"
                 constructorParams="JucesamplerAudioProcessor &amp;_processor"
                 variableInitialisers="processor(_processor), AudioProcessorEditor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="608" initialHeight="400">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <COMBOBOX name="" id="a874eedfa3cfe441" memberName="bankListCombo" virtualName=""
            explicitFocusOrder="0" pos="352 8 240 24" editable="0" layout="33"
            items="" textWhenNonSelected="No bank selected" textWhenNoItems="No banks in memory"/>
  <JUCERCOMP name="" id="385bc346a935c783" memberName="instrumentButton1"
             virtualName="" explicitFocusOrder="0" pos="16 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="d0e49b1fe17c86bb" memberName="instrumentButton2"
             virtualName="" explicitFocusOrder="0" pos="80 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="57cdc7037a39dba4" memberName="instrumentButton3"
             virtualName="" explicitFocusOrder="0" pos="144 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="11aeaaa16196fb8e" memberName="instrumentButton4"
             virtualName="" explicitFocusOrder="0" pos="208 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="21eb4a8a331bc244" memberName="instrumentButton5"
             virtualName="" explicitFocusOrder="0" pos="272 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="3e6dd1f0b5814ae9" memberName="instrumentButton6"
             virtualName="" explicitFocusOrder="0" pos="336 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="fe7c43ae8a1f505c" memberName="instrumentButton7"
             virtualName="" explicitFocusOrder="0" pos="400 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="b6443c4be411b0fd" memberName="instrumentButton8"
             virtualName="" explicitFocusOrder="0" pos="464 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="286684d0bace1ac6" memberName="instrumentButton9"
             virtualName="" explicitFocusOrder="0" pos="528 232 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="8d9bf0c0562d186b" memberName="instrumentButton10"
             virtualName="" explicitFocusOrder="0" pos="16 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="112e6fd3479ec99f" memberName="instrumentButton11"
             virtualName="" explicitFocusOrder="0" pos="80 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="90511b9b713dd94" memberName="instrumentButton12"
             virtualName="" explicitFocusOrder="0" pos="144 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="10dae6e5a3db4410" memberName="instrumentButton13"
             virtualName="" explicitFocusOrder="0" pos="208 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="4c882f10c4d824cb" memberName="instrumentButton14"
             virtualName="" explicitFocusOrder="0" pos="272 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="9cd77db42c0d69f1" memberName="instrumentButton15"
             virtualName="" explicitFocusOrder="0" pos="336 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="972aee908b201aa3" memberName="instrumentButton16"
             virtualName="" explicitFocusOrder="0" pos="400 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="23e36a2792da8576" memberName="instrumentButton17"
             virtualName="" explicitFocusOrder="0" pos="464 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="73bbfa405efa3af2" memberName="instrumentButton18"
             virtualName="" explicitFocusOrder="0" pos="528 315 64 72" sourceFile="InstrumentButton.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="8cc28a66321fb279" memberName="component" virtualName=""
             explicitFocusOrder="0" pos="16 8 312 208" sourceFile="InstrumentWaveViewer.cpp"
             constructorParams=""/>
  <LABEL name="" id="81bea851b119fd22" memberName="bankInfo" virtualName=""
         explicitFocusOrder="0" pos="352 40 240 48" outlineCol="5affffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Info" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <HYPERLINKBUTTON name="" id="4a34d9493a793927" memberName="bankUrl" virtualName=""
                   explicitFocusOrder="0" pos="352 88 240 16" buttonText="new hyperlink"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


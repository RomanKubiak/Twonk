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
#include "UI/MainHostWindow.h"
//[/Headers]

#include "InstrumentWaveViewer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "SimplerSound.h"
//[/MiscUserDefs]

//==============================================================================
InstrumentWaveViewer::InstrumentWaveViewer (SimplerProcessor &_processor)
    : processor(_processor),
      thumbnailCache (5), thumbnail (8, processor.getFormatManager(), thumbnailCache)
{
    //[Constructor_pre] You can add your own custom stuff here..
	instrumentToShow = nullptr;
	lastSelectedSound = nullptr;
	thumbnail.addChangeListener (this);
    //[/Constructor_pre]

    soundName.reset (new Label (String(),
                                String()));
    addAndMakeVisible (soundName.get());
    soundName->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    soundName->setJustificationType (Justification::centredLeft);
    soundName->setEditable (false, false, false);
    soundName->setColour (TextEditor::textColourId, Colours::black);
    soundName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    soundData.reset (new Label (String(),
                                String()));
    addAndMakeVisible (soundData.get());
    soundData->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    soundData->setJustificationType (Justification::centredLeft);
    soundData->setEditable (false, false, false);
    soundData->setColour (TextEditor::textColourId, Colours::black);
    soundData->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    sampleList.reset (new ComboBox (String()));
    addAndMakeVisible (sampleList.get());
    sampleList->setEditableText (false);
    sampleList->setJustificationType (Justification::centredLeft);
    sampleList->setTextWhenNothingSelected (String());
    sampleList->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sampleList->addListener (this);

    velocityRange.reset (new Slider (String()));
    addAndMakeVisible (velocityRange.get());
    velocityRange->setRange (0, 127, 1);
    velocityRange->setSliderStyle (Slider::TwoValueVertical);
    velocityRange->setTextBoxStyle (Slider::NoTextBox, false, 80, 16);
    velocityRange->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    velocityRange->addListener (this);

    velocityRangeLabel.reset (new Label ("new label",
                                         TRANS("100-127")));
    addAndMakeVisible (velocityRangeLabel.get());
    velocityRangeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    velocityRangeLabel->setJustificationType (Justification::centred);
    velocityRangeLabel->setEditable (false, false, false);
    velocityRangeLabel->setColour (TextEditor::textColourId, Colours::black);
    velocityRangeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
	soundName->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
	soundData->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
	velocityRangeLabel->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
	sampleList->setColour(ComboBox::ColourIds::backgroundColourId, Colours::black);
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentWaveViewer::~InstrumentWaveViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	thumbnail.setSource(nullptr);
    //[/Destructor_pre]

    soundName = nullptr;
    soundData = nullptr;
    sampleList = nullptr;
    velocityRange = nullptr;
    velocityRangeLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentWaveViewer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	g.setFont(getDefaultTwonkSansFont());
    //[/UserPrePaint]

    g.fillAll (Colour (0x42000000));

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour strokeColour = Colour (0x61ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..
	Rectangle<int> thumbnailBounds (2, 26, getWidth()-4-48, getHeight()-18-26);

	if (thumbnail.getNumChannels() == 0)
		paintIfNoFileLoaded (g, thumbnailBounds);
	else
		paintIfFileLoaded (g, thumbnailBounds);
    //[/UserPaint]
}

void InstrumentWaveViewer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    soundName->setBounds (0, getHeight() - 18, proportionOfWidth (0.5000f), 16);
    soundData->setBounds (proportionOfWidth (0.5000f), getHeight() - 18, proportionOfWidth (0.5000f), 16);
    sampleList->setBounds (2, 2, proportionOfWidth (0.4500f), 24);
    velocityRange->setBounds (getWidth() - 48, 2, 39, getHeight() - 8);
    velocityRangeLabel->setBounds (getWidth() - 128, 2, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void InstrumentWaveViewer::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == sampleList.get())
    {
        //[UserComboBoxCode_sampleList] -- add your combo box handling code here..
		lastSelectedSound = instrumentToShow->assosiatedSound[sampleList->getSelectedItemIndex()];
		if (lastSelectedSound)
		{
			loadNewThumbnail(lastSelectedSound);
			setSampleData(lastSelectedSound);
			setVelocityRangeData(lastSelectedSound);
		}
        //[/UserComboBoxCode_sampleList]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void InstrumentWaveViewer::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == velocityRange.get())
    {
        //[UserSliderCode_velocityRange] -- add your slider handling code here..
        //[/UserSliderCode_velocityRange]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void InstrumentWaveViewer::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.eventComponent == this && lastSelectedSound)
	{
	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentWaveViewer::paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour (Colours::white);
	g.drawFittedText ("No data yet", thumbnailBounds, Justification::centred, 1.0f);
}

void InstrumentWaveViewer::paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour (Colour(0xd343ff00));
	thumbnail.drawChannels (g, thumbnailBounds.withTrimmedBottom(8), 0.0, thumbnail.getTotalLength(), 1.0f);
}

void InstrumentWaveViewer::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == &thumbnail)
		thumbnailChanged();
}

void InstrumentWaveViewer::thumbnailChanged()
{
	repaint();
}

void InstrumentWaveViewer::loadNewThumbnail(SimplerSound *sound)
{
	AudioBuffer<float> *data = sound->getAudioData();
	thumbnail.reset(1, sound->getSampleRate(), sound->getLength());
	thumbnail.addBlock(0, *data, 0, data->getNumSamples());
}

void InstrumentWaveViewer::setSampleData(SimplerSound *sound)
{
	soundName->setText(sound->getName(), dontSendNotification);
	String strData = String::formatted("len:%.2fs samples:%.0f", (float)(sound->getLength() / sound->getSampleRate()), sound->getLength());
	soundData->setText(strData, dontSendNotification);
}

void InstrumentWaveViewer::fillSampleCombo(SimplerInstrument *instrumentToShow)
{
	sampleList->clear(dontSendNotification);
	for (int i = 0; i < instrumentToShow->assosiatedSound.size(); i++)
	{
		File sampleFile = instrumentToShow->assosiatedSound[i]->getSampleFile();
		sampleList->addItem(sampleFile.getFileName(), i + 1);
	}
	sampleList->setSelectedItemIndex(0, dontSendNotification);
}

void InstrumentWaveViewer::setVelocityRangeData(SimplerSound *sound)
{
	NormalisableRange<int> &r = sound->getVelocityRange();
	velocityRange->setMinAndMaxValues(r.start, r.end-1, dontSendNotification);
	velocityRangeLabel->setText(String::formatted("%d-%d", r.start, r.end-1), dontSendNotification);
}

void InstrumentWaveViewer::setSoundToShow(SimplerInstrument *instrument)
{
	instrumentToShow = instrument;
	if (instrumentToShow == nullptr)
	{
		thumbnail.clear();
		soundName->setText("", dontSendNotification);
		soundData->setText("", dontSendNotification);
		velocityRangeLabel->setText("", dontSendNotification);
		sampleList->clear(dontSendNotification);
	}
	else
	{
		fillSampleCombo(instrumentToShow);
		if (instrumentToShow->assosiatedSound[0])
		{
			loadNewThumbnail(instrumentToShow->assosiatedSound[0]);
			setSampleData(instrumentToShow->assosiatedSound[0]);
			setVelocityRangeData(instrumentToShow->assosiatedSound[0]);
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

<JUCER_COMPONENT documentType="Component" className="InstrumentWaveViewer" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="SimplerProcessor &amp;_processor"
                 variableInitialisers="processor(_processor),&#10;thumbnailCache (5), thumbnail (8, processor.getFormatManager(), thumbnailCache)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="200">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="42000000">
    <RECT pos="0 0 0M 0M" fill="solid: 0" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: 61ffffff"/>
  </BACKGROUND>
  <LABEL name="" id="513f4bb407ef3af1" memberName="soundName" virtualName=""
         explicitFocusOrder="0" pos="0 18R 50% 16" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="bddb45a6d3d6f811" memberName="soundData" virtualName=""
         explicitFocusOrder="0" pos="50% 18R 50% 16" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="2ee4fb804dfd2a26" memberName="sampleList" virtualName=""
            explicitFocusOrder="0" pos="2 2 45% 24" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="1dd6eac09a26d26" memberName="velocityRange" virtualName=""
          explicitFocusOrder="0" pos="48R 2 39 8M" textboxoutline="0" min="0.0"
          max="127.0" int="1.0" style="TwoValueVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="3d4eecfb0e8066e7" memberName="velocityRangeLabel"
         virtualName="" explicitFocusOrder="0" pos="128R 2 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="100-127" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


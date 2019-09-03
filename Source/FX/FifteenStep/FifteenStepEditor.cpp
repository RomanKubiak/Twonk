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
#include "FifteenStepProcessor.h"
#include "FifteenStepRowHolder.h"
//[/Headers]

#include "FifteenStepEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Twonk.h"
#include "UI/MainHostWindow.h"
//[/MiscUserDefs]

//==============================================================================
FifteenStepEditor::FifteenStepEditor (FifteenStepProcessor &_processor)
    : AudioProcessorEditor(_processor), processor(_processor)
{
    //[Constructor_pre] You can add your own custom stuff here..
	lastPlayStep = 0;

    //[/Constructor_pre]

    timeInfoLabel.reset (new Label ("Time Info",
                                    TRANS("label text")));
    addAndMakeVisible (timeInfoLabel.get());
    timeInfoLabel->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    timeInfoLabel->setJustificationType (Justification::topLeft);
    timeInfoLabel->setEditable (false, false, false);
    timeInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    timeInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rowViewport.reset (new Viewport (String("Rows")));
    addAndMakeVisible (rowViewport.get());
    rowViewport->setName ("Rows");


    //[UserPreSize]
	rowViewport->setViewedComponent(new FifteenStepRowHolder(*this), true);
	rowViewport->setScrollBarsShown(false, false, true, true);
	timeInfoLabel->setFont(getDefaultTwonkMonoFont().withHeight(14.0f));
    //[/UserPreSize]

    setSize (768, 300);


    //[Constructor] You can add your own custom stuff here..
	startTimerHz(60);
    //[/Constructor]
}

FifteenStepEditor::~FifteenStepEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    timeInfoLabel = nullptr;
    rowViewport = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FifteenStepEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xff2d2d2d), fillColour2 = Colour (0xff121212);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       768.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       192.0f - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FifteenStepEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    timeInfoLabel->setBounds (0, proportionOfHeight (0.9500f), proportionOfWidth (0.5000f), proportionOfHeight (0.0500f));
    rowViewport->setBounds (16, 16, proportionOfWidth (0.8000f), proportionOfHeight (0.9000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FifteenStepEditor::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    //[/UserCode_mouseMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void FifteenStepEditor::timerCallback()
{
	AudioPlayHead::CurrentPositionInfo pos = processor.lastPosInfo;
	double getPlayHeadColPrecise = processor.getPlayHeadColPrecise();
	if (lastPlayStep != processor.getLastStep())
	{
		lastPlayStep = processor.getLastStep();
		sendChangeMessage();
	}
	auto quarterNotesPerBar = (pos.timeSigNumerator * 4 / pos.timeSigDenominator);
	auto beats = (fmod (pos.ppqPosition, quarterNotesPerBar) / quarterNotesPerBar) * pos.timeSigNumerator;

	auto bar = ((int)pos.ppqPosition) / quarterNotesPerBar + 1;
	auto beat = ((int)beats) + 1;
	auto ticks = ((int)(fmod (beats, 1.0) * 960.0 + 0.5));

	String timeInfo = quarterNotePositionToBarsBeatsString (pos.ppqPosition, pos.timeSigNumerator, pos.timeSigDenominator);
	timeInfo << " step: " + String(lastPlayStep);
	timeInfo << " stepPrecise: " + String(getPlayHeadColPrecise, 2);
	timeInfoLabel->setText(timeInfo, dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FifteenStepEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer, public ChangeBroadcaster"
                 constructorParams="FifteenStepProcessor &amp;_processor" variableInitialisers="AudioProcessorEditor(_processor), processor(_processor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="768" initialHeight="300">
  <METHODS>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <RECT pos="0 0 0M 0M" fill="linear: 768 0, 8 192, 0=ff2d2d2d, 1=ff121212"
          hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="Time Info" id="4c8facc535076b60" memberName="timeInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="0 95% 50% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="9"/>
  <GENERICCOMPONENT name="Rows" id="8aab353265ddbad6" memberName="rowViewport" virtualName=""
                    explicitFocusOrder="0" pos="16 16 79.948% 90%" class="Viewport"
                    params="String(&quot;Rows&quot;)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


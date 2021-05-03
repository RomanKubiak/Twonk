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

#include "TwonkFilterPopupProperties.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Twonk.h"
#include "BinaryData.h"
//[/MiscUserDefs]

//==============================================================================
TwonkFilterPopupProperties::TwonkFilterPopupProperties (Editor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    disconnectAllSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (disconnectAllSegment.get());
    deleteFilterSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (deleteFilterSegment.get());
    toggleBypassSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (toggleBypassSegment.get());
    toggleGUISegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (toggleGUISegment.get());
    configureAudioSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (configureAudioSegment.get());
    showParametersSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (showParametersSegment.get());
    showAllProgramsSegment.reset (new TwonkFilterPopupPropertiesSegment());
    addAndMakeVisible (showAllProgramsSegment.get());

    //[UserPreSize]
	deleteFilterSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS, 128.0f, 128.0f));
	deleteFilterSegment->setIcon(IMG(icon_delete_png), 24.0f, 1.0f);
	deleteFilterSegment->addChangeListener(this);

	toggleBypassSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS*2, 128.0f, 128.0f));
	toggleBypassSegment->setBaseColour(Colours::lightgrey);
	toggleBypassSegment->setIcon(IMG(icon_bypass2_png), 24.0f, 1.0f);
	toggleBypassSegment->addChangeListener(this);

	toggleGUISegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS * 3, 128.0f, 128.0f));
	toggleGUISegment->setBaseColour(Colours::yellow);
	toggleGUISegment->setIcon(IMG(icon_gui_png), 24.0f, 1.0f);
	toggleGUISegment->addChangeListener(this);

	configureAudioSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS * 4, 128.0f, 128.0f));
	configureAudioSegment->setBaseColour(Colours::turquoise);
	configureAudioSegment->setIcon(IMG(audio_input_png), 16.0f, 1.0f);
	configureAudioSegment->addChangeListener(this);

	showParametersSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS * 5, 128.0f, 128.0f));
	showParametersSegment->setBaseColour(Colours::lightgreen);
	showParametersSegment->setIcon(IMG(icon_parameters_png), 24.0f, 1.0f);
	showParametersSegment->addChangeListener(this);

	showAllProgramsSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS * 6, 128.0f, 128.0f));
	showAllProgramsSegment->setBaseColour(Colours::darkgreen);
	showAllProgramsSegment->setIcon(IMG(icon_programs2_png), 16.0f, 1.0f);
	showAllProgramsSegment->addChangeListener(this);

	disconnectAllSegment->setTransform(AffineTransform::rotation(SEGMENT_RADIUS * 7, 128.0f, 128.0f));
	disconnectAllSegment->setBaseColour(Colours::palevioletred);
	disconnectAllSegment->setIcon(IMG(icon_disconnect_png), 24.0f, 1.0f);
	disconnectAllSegment->addChangeListener(this);
    //[/UserPreSize]

    setSize (256, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkFilterPopupProperties::~TwonkFilterPopupProperties()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    disconnectAllSegment = nullptr;
    deleteFilterSegment = nullptr;
    toggleBypassSegment = nullptr;
    toggleGUISegment = nullptr;
    configureAudioSegment = nullptr;
    showParametersSegment = nullptr;
    showAllProgramsSegment = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkFilterPopupProperties::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkFilterPopupProperties::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    disconnectAllSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    deleteFilterSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    toggleBypassSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    toggleGUISegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    configureAudioSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    showParametersSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    showAllProgramsSegment->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkFilterPopupProperties::setFilter(struct Editor::Processor *_filter)
{
	filter = _filter;
}

void TwonkFilterPopupProperties::changeListenerCallback (ChangeBroadcaster* source)
{
	DBG("TwonkFilterPopupProperties::changeListenerCallback");
	TwonkFilterPopupPropertiesSegment *segment = dynamic_cast<TwonkFilterPopupPropertiesSegment *>(source);
	if (segment == nullptr)
		owner.menuForFilterClicked(-1);

	if (segment == deleteFilterSegment.get())
		owner.menuForFilterClicked(1);

	if (segment == toggleGUISegment.get())
		owner.menuForFilterClicked(10);

	if (segment == disconnectAllSegment.get())
		owner.menuForFilterClicked(2);

	if (segment == configureAudioSegment.get())
		owner.menuForFilterClicked(20);

	if (segment == showAllProgramsSegment.get())
		owner.menuForFilterClicked(11);

	if (segment == showParametersSegment.get())
		owner.menuForFilterClicked(12);

	if (segment == toggleBypassSegment.get())
		owner.menuForFilterClicked(3);

	owner.menuForFilterClicked(-1);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkFilterPopupProperties"
                 componentName="" parentClasses="public Component, public ChangeListener"
                 constructorParams="GraphEditorPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="256" initialHeight="256">
  <BACKGROUND backgroundColour="0"/>
  <JUCERCOMP name="Disconnect all pins" id="81c3abbc7afab64" memberName="disconnectAllSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Delete filter" id="89d973553475af2f" memberName="deleteFilterSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Toggle bypass" id="341f73630d829984" memberName="toggleBypassSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Toggle GUI for filter" id="a58a2a3b3762b9d6" memberName="toggleGUISegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Configure Audio Buses" id="56caf835bb296eb0" memberName="configureAudioSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Show all parameters" id="5dbea1e64c102aef" memberName="showParametersSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
  <JUCERCOMP name="Show all programs" id="2e31d4e522210953" memberName="showAllProgramsSegment"
             virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="TwonkFilterPopupPropertiesSegment.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


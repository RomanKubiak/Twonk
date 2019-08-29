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
#include "SimplerEditor.h"
//[/Headers]

#include "InstrumentButtonsPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InstrumentButtonsPanel::InstrumentButtonsPanel (SimplerEditor &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    ins1.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins1.get());
    ins2.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins2.get());
    ins3.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins3.get());
    ins4.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins4.get());
    ins5.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins5.get());
    ins6.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins6.get());
    ins7.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins7.get());
    ins8.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins8.get());
    ins9.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins9.get());
    ins10.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins10.get());
    ins11.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins11.get());
    ins12.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins12.get());
    ins13.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins13.get());
    ins14.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins14.get());
    ins15.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins15.get());
    ins16.reset (new InstrumentButton (owner));
    addAndMakeVisible (ins16.get());

    //[UserPreSize]
	buttons.add(ins1.get());
	buttons.add(ins2.get());
	buttons.add(ins3.get());
	buttons.add(ins4.get());
	buttons.add(ins5.get());
	buttons.add(ins6.get());
	buttons.add(ins7.get());
	buttons.add(ins8.get());

	buttons.add(ins9.get());
	buttons.add(ins10.get());
	buttons.add(ins11.get());
	buttons.add(ins12.get());
	buttons.add(ins13.get());
	buttons.add(ins14.get());
	buttons.add(ins15.get());
	buttons.add(ins16.get());
    //[/UserPreSize]

    setSize (700, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InstrumentButtonsPanel::~InstrumentButtonsPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ins1 = nullptr;
    ins2 = nullptr;
    ins3 = nullptr;
    ins4 = nullptr;
    ins5 = nullptr;
    ins6 = nullptr;
    ins7 = nullptr;
    ins8 = nullptr;
    ins9 = nullptr;
    ins10 = nullptr;
    ins11 = nullptr;
    ins12 = nullptr;
    ins13 = nullptr;
    ins14 = nullptr;
    ins15 = nullptr;
    ins16 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InstrumentButtonsPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InstrumentButtonsPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ins1->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins2->setBounds (proportionOfWidth (0.1300f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins3->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins4->setBounds (proportionOfWidth (0.3700f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins5->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins6->setBounds (proportionOfWidth (0.6200f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins7->setBounds (proportionOfWidth (0.7400f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins8->setBounds (proportionOfWidth (0.8600f), proportionOfHeight (0.0500f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins9->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins10->setBounds (proportionOfWidth (0.1300f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins11->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins12->setBounds (proportionOfWidth (0.3700f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins13->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins14->setBounds (proportionOfWidth (0.6200f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins15->setBounds (proportionOfWidth (0.7400f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    ins16->setBounds (proportionOfWidth (0.8600f), proportionOfHeight (0.5300f), proportionOfWidth (0.1100f), proportionOfHeight (0.3900f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InstrumentButtonsPanel::deselectAll()
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->setSelected(false);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InstrumentButtonsPanel" componentName=""
                 parentClasses="public Component" constructorParams="SimplerEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="700"
                 initialHeight="200">
  <BACKGROUND backgroundColour="0"/>
  <JUCERCOMP name="0" id="f12d18913e756524" memberName="ins1" virtualName=""
             explicitFocusOrder="0" pos="1% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="1" id="70b0ead9bfc15e69" memberName="ins2" virtualName=""
             explicitFocusOrder="0" pos="13% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="2" id="7f8fe2f2a9c7d876" memberName="ins3" virtualName=""
             explicitFocusOrder="0" pos="25% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="3" id="82da82b0a9eeb8ab" memberName="ins4" virtualName=""
             explicitFocusOrder="0" pos="37% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="4" id="c371e1009f76ab0" memberName="ins5" virtualName=""
             explicitFocusOrder="0" pos="50% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="5" id="6d369df0d772b140" memberName="ins6" virtualName=""
             explicitFocusOrder="0" pos="62% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="6" id="a843a87a624ce69a" memberName="ins7" virtualName=""
             explicitFocusOrder="0" pos="74% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="7" id="6bac93bb880fb56a" memberName="ins8" virtualName=""
             explicitFocusOrder="0" pos="86% 5% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="8" id="4e348bc152b730d9" memberName="ins9" virtualName=""
             explicitFocusOrder="0" pos="1% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="9" id="f28e5caf0c8ac087" memberName="ins10" virtualName=""
             explicitFocusOrder="0" pos="13% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="10" id="a6676b9e12b77983" memberName="ins11" virtualName=""
             explicitFocusOrder="0" pos="25% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="11" id="db76b9d83253e78c" memberName="ins12" virtualName=""
             explicitFocusOrder="0" pos="37% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="12" id="bcdcbaed35b55551" memberName="ins13" virtualName=""
             explicitFocusOrder="0" pos="50% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="13" id="9a1dd930aa2536f8" memberName="ins14" virtualName=""
             explicitFocusOrder="0" pos="62% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="14" id="f0390a38ede96498" memberName="ins15" virtualName=""
             explicitFocusOrder="0" pos="74% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="15" id="924c7360102924be" memberName="ins16" virtualName=""
             explicitFocusOrder="0" pos="86% 53% 11% 39%" sourceFile="InstrumentButton.cpp"
             constructorParams="owner"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


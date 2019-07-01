/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TwonkBubbleComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkBubbleComponent::TwonkBubbleComponent (FilterGraph &g, const AudioProcessorGraph::NodeID id)
    : graph(g), pluginID(id)
{
    //[Constructor_pre] You can add your own custom stuff here..
	fillColour = Colours::red;
	stroke = Colours::red;
    //[/Constructor_pre]

    removeButton.reset (new TextButton ("new button"));
    addAndMakeVisible (removeButton.get());
    removeButton->setButtonText (TRANS("Remove"));
    removeButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    removeButton->addListener (this);
    removeButton->setColour (TextButton::buttonColourId, Colour (0xffff2121));

    bypassButton.reset (new TextButton ("new button"));
    addAndMakeVisible (bypassButton.get());
    bypassButton->setButtonText (TRANS("Bypass"));
    bypassButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    bypassButton->addListener (this);
    bypassButton->setColour (TextButton::buttonColourId, Colour (0xff20d7d7));

    label.reset (new TwonkBubbleComponentLabel (*this));
    addAndMakeVisible (label.get());

    //[UserPreSize]
	removeButton->setAlwaysOnTop(true);
	bypassButton->setAlwaysOnTop(true);
	toggleOptions(false);
	label->addMouseListener(this, true);
    //[/UserPreSize]

    setSize (128, 96);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkBubbleComponent::~TwonkBubbleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    removeButton = nullptr;
    bypassButton = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkBubbleComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = static_cast<float> (proportionOfWidth (0.01f)), y = static_cast<float> (proportionOfHeight (0.33f)), width = static_cast<float> (proportionOfWidth (0.98f)), height = static_cast<float> (proportionOfHeight (0.33f));
        Colour fillColour1 = Colour (0x00000000), fillColour2 = Colour (0x46000000);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.33f)) - static_cast<float> (proportionOfWidth (0.01f)) + x,
                                       static_cast<float> (proportionOfHeight (0.33f)) - static_cast<float> (proportionOfHeight (0.33f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.3125f)) - static_cast<float> (proportionOfWidth (0.01f)) + x,
                                       static_cast<float> (proportionOfHeight (0.66f)) - static_cast<float> (proportionOfHeight (0.33f)) + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 10.0f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.0f, 2.0f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkBubbleComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    removeButton->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.0f), proportionOfWidth (1.0f), proportionOfHeight (0.3958f));
    bypassButton->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.6042f), proportionOfWidth (1.0f), proportionOfHeight (0.3958f));
    label->setBounds (proportionOfWidth (0.0f), proportionOfHeight (0.3333f), proportionOfWidth (1.0f), proportionOfHeight (0.3333f));
    //[UserResized] Add your own custom resize handling here..
	//Font f = Typeface::createSystemTypefaceFor (BinaryData::_60sekuntia_ttf, BinaryData::_60sekuntia_ttfSize);
	//f.setHeight(proportionOfHeight (0.15f));
	//label->setFont(f);
    //[/UserResized]
}

void TwonkBubbleComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == removeButton.get())
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..
		graph.graph.removeNode (pluginID);
        //[/UserButtonCode_removeButton]
    }
    else if (buttonThatWasClicked == bypassButton.get())
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        //[/UserButtonCode_bypassButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkBubbleComponent::mouseDown (const MouseEvent& e)
{
	DBG("TwonkBubbleComponent::mouseDown");
	myDragger.startDraggingComponent (this, e);
}

void TwonkBubbleComponent::mouseDrag (const MouseEvent& e)
{
	myDragger.dragComponent (this, e, nullptr);
}

void TwonkBubbleComponent::setComponentName(const String &newName)
{
	label->setText(newName);
}

void TwonkBubbleComponent::setBypassed(const bool isBypassed)
{
	//componentName->setColour(Label::backgroundColourId, isBypassed ? Colours::white.withAlpha(0.5f) : Colours::black);
	//componentName->setColour(Label::outlineColourId, isBypassed ? Colours::black : Colours::white);
}

void TwonkBubbleComponent::toggleOptions(const bool shouldBeVisible)
{
	removeButton->setVisible(shouldBeVisible);
	bypassButton->setVisible(shouldBeVisible);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkBubbleComponent" componentName=""
                 parentClasses="public Component" constructorParams="FilterGraph &amp;g, const AudioProcessorGraph::NodeID id"
                 variableInitialisers="graph(g), pluginID(id)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.33" fixedSize="1"
                 initialWidth="128" initialHeight="96">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="1% 33% 98% 33%" cornerSize="10.0" fill="linear: 33% 33%, 31.25% 66%, 0=0, 1=46000000"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffffffff"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="796884a9cba9bda" memberName="removeButton"
              virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 39.583%"
              bgColOff="ffff2121" buttonText="Remove" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5c7943a6f46993ef" memberName="bypassButton"
              virtualName="" explicitFocusOrder="0" pos="0% 60.417% 100% 39.583%"
              bgColOff="ff20d7d7" buttonText="Bypass" connectedEdges="15" needsCallback="1"
              radioGroupId="0"/>
  <JUCERCOMP name="" id="49f0fc13431e884" memberName="label" virtualName=""
             explicitFocusOrder="0" pos="0% 33.333% 100% 33.333%" sourceFile="TwonkBubbleComponentLabel.cpp"
             constructorParams="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

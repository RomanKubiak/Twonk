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
TwonkBubbleComponent::TwonkBubbleComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	fillColour = Colours::red;
	stroke = Colours::red;
    //[/Constructor_pre]

    componentName.reset (new Label ("new label",
                                    TRANS("CH")));
    addAndMakeVisible (componentName.get());
    componentName->setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
    componentName->setJustificationType (Justification::centred);
    componentName->setEditable (false, false, false);
    componentName->setColour (TextEditor::textColourId, Colours::black);
    componentName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
	componentName->addMouseListener(this, true);
    //[/UserPreSize]

    setSize (128, 128);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkBubbleComponent::~TwonkBubbleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    componentName = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkBubbleComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = static_cast<float> (proportionOfWidth (0.25f)), y = static_cast<float> (proportionOfHeight (0.25f)), width = static_cast<float> (proportionOfWidth (0.5f)), height = static_cast<float> (proportionOfHeight (0.5f));
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawEllipse (x, y, width, height, 2.0f);
    }

    {
        float x = static_cast<float> (proportionOfWidth (0.1f)), y = static_cast<float> (proportionOfHeight (0.1f)), width = static_cast<float> (proportionOfWidth (0.8f)), height = static_cast<float> (proportionOfHeight (0.8f));
        Colour strokeColour = Colour (0x46ffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawEllipse (x, y, width, height, 1.0f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkBubbleComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    componentName->setBounds (proportionOfWidth (0.25f), proportionOfHeight (0.375f), proportionOfWidth (0.5f), proportionOfHeight (0.25f));
    //[UserResized] Add your own custom resize handling here..
	Font f = Typeface::createSystemTypefaceFor (BinaryData::_60sekuntia_ttf, BinaryData::_60sekuntia_ttfSize);
	f.setHeight(proportionOfHeight (0.1f));
	componentName->setFont(f);
    //[/UserResized]
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
	componentName->setText(newName.replace(" ", "\n", true), NotificationType::sendNotificationAsync);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkBubbleComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="1" initialWidth="128" initialHeight="128">
  <BACKGROUND backgroundColour="0">
    <ELLIPSE pos="25% 25% 50% 50%" fill="solid: a52a83" hasStroke="1" stroke="2, mitered, butt"
             strokeColour="solid: ffffffff"/>
    <ELLIPSE pos="10% 10% 80% 80%" fill="solid: a52a83" hasStroke="1" stroke="1, mitered, butt"
             strokeColour="solid: 46ffffff"/>
  </BACKGROUND>
  <LABEL name="new label" id="9aa4a2de4ff90afd" memberName="componentName"
         virtualName="" explicitFocusOrder="0" pos="25% 37.5% 50% 25%"
         edTextCol="ff000000" edBkgCol="0" labelText="CH" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

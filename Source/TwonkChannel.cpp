/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "TwonkChannel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "TwonkMain.h"
//[/MiscUserDefs]

//==============================================================================
TwonkChannel::TwonkChannel (TwonkMain *_parent, uint8_t _idx)
    : parent(_parent), idx(_idx)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    comboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox.get());
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addListener (this);

    comboBox2.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox2.get());
    comboBox2->setEditableText (false);
    comboBox2->setJustificationType (Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected (String());
    comboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox2->addListener (this);

    comboBox3.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox3.get());
    comboBox3->setEditableText (false);
    comboBox3->setJustificationType (Justification::centredLeft);
    comboBox3->setTextWhenNothingSelected (String());
    comboBox3->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox3->addListener (this);

    comboBox4.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox4.get());
    comboBox4->setEditableText (false);
    comboBox4->setJustificationType (Justification::centredLeft);
    comboBox4->setTextWhenNothingSelected (String());
    comboBox4->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox4->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (256, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkChannel::~TwonkChannel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    comboBox = nullptr;
    comboBox2 = nullptr;
    comboBox3 = nullptr;
    comboBox4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TwonkChannel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = static_cast<float> (proportionOfWidth (0.0100f)), y = static_cast<float> (proportionOfHeight (0.0100f)), width = static_cast<float> (proportionOfWidth (0.9800f)), height = static_cast<float> (proportionOfHeight (0.9800f));
        Colour fillColour1 = Colour (0x80000000), fillColour2 = Colour (0x65000000);
        Colour strokeColour1 = Colour (0x77000000), strokeColour2 = Colour (0x8f353500);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> ((getWidth() / 2)) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       static_cast<float> ((getHeight() / 2)) - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                       fillColour2,
                                       static_cast<float> (getWidth()) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       0.0f - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                       true));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setGradientFill (ColourGradient (strokeColour1,
                                       static_cast<float> ((getWidth() / 2)) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       static_cast<float> ((getHeight() / 2)) - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                       strokeColour2,
                                       static_cast<float> (getWidth()) - static_cast<float> (proportionOfWidth (0.0100f)) + x,
                                       0.0f - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                       false));
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
	g.setColour (Colours::white.withAlpha(0.5f));
	Typeface::Ptr ptr = Typeface::createSystemTypefaceFor(BinaryData::_60sekuntia_ttf, BinaryData::_60sekuntia_ttfSize);
	Font f = Font(ptr);
	f.setHeight(proportionOfHeight (0.5f));
	g.setFont (f);
	g.drawText (String(idx), proportionOfWidth (0.25f), proportionOfHeight (0.25f), proportionOfWidth (0.5f), proportionOfHeight (0.5f),
		Justification::centred, true);
    //[/UserPaint]
}

void TwonkChannel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    comboBox->setBounds (proportionOfWidth (0.0195f), proportionOfHeight (0.0200f), proportionOfWidth (0.4609f), proportionOfHeight (0.1000f));
    comboBox2->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.0200f), proportionOfWidth (0.4609f), proportionOfHeight (0.1000f));
    comboBox3->setBounds (proportionOfWidth (0.0195f), proportionOfHeight (0.8800f), proportionOfWidth (0.4609f), proportionOfHeight (0.1000f));
    comboBox4->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.8800f), proportionOfWidth (0.4609f), proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkChannel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2.get())
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == comboBox3.get())
    {
        //[UserComboBoxCode_comboBox3] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox3]
    }
    else if (comboBoxThatHasChanged == comboBox4.get())
    {
        //[UserComboBoxCode_comboBox4] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox4]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkChannel" componentName=""
                 parentClasses="public Component" constructorParams="TwonkMain *_parent, uint8_t _idx"
                 variableInitialisers="parent(_parent), idx(_idx)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="256" initialHeight="300">
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="1% 1% 98% 98%" cornerSize="10.0" fill=" radial: 0C 0C, 0R 0, 0=80000000, 1=65000000"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="linear: 0C 0C, 0R 0, 0=77000000, 1=8f353500"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="d06d966b01369606" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="1.953% 2% 46.094% 10%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="92ed9c1aa084a8e8" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="50% 2% 46.094% 10%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="211840dd155349fa" memberName="comboBox3"
            virtualName="" explicitFocusOrder="0" pos="1.953% 88% 46.094% 10%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="7e43f24a8707e761" memberName="comboBox4"
            virtualName="" explicitFocusOrder="0" pos="50% 88% 46.094% 10%"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


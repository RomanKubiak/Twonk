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

#include "TwonkMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TwonkMain::TwonkMain ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	LookAndFeel::setDefaultLookAndFeel(&twonkLookAndFeel);
	uiManagerThread.reset(new TimeSliceThread("ui thread"));
	uiManagerThread->startThread(2);

	setAudioChannels (1, 0);  // we want a couple of input channels but no outputs
	setOpaque (true);

	defaultTypeface = Typeface::createSystemTypefaceFor(BinaryData::RobotoMedium_ttf, BinaryData::RobotoMedium_ttfSize);
	LookAndFeel &lf = getLookAndFeel();
	lf.setDefaultSansSerifTypeface(defaultTypeface);
    //[/Constructor_pre]

    ch1.reset (new TwonkChannel (this, 0));
    addAndMakeVisible (ch1.get());
    ch2.reset (new TwonkChannel (this, 1));
    addAndMakeVisible (ch2.get());
    ch3.reset (new TwonkChannel (this, 2));
    addAndMakeVisible (ch3.get());
    ch4.reset (new TwonkChannel (this, 3));
    addAndMakeVisible (ch4.get());
    ch5.reset (new TwonkChannel (this, 4));
    addAndMakeVisible (ch5.get());
    ch6.reset (new TwonkChannel (this, 5));
    addAndMakeVisible (ch6.get());
    ch7.reset (new TwonkChannel (this, 6));
    addAndMakeVisible (ch7.get());
    ch8.reset (new TwonkChannel (this, 7));
    addAndMakeVisible (ch8.get());
    toolbar.reset (new TwonkToolbar());
    addAndMakeVisible (toolbar.get());

    //[UserPreSize]
	//uiManagerThread->addTimeSliceClient (drowScope.get());
	//uiManagerThread->addTimeSliceClient (drowBar.get());
    //[/UserPreSize]

    setSize (1024, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TwonkMain::~TwonkMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	shutdownAudio();
	uiManagerThread->removeAllClients();
    //[/Destructor_pre]

    ch1 = nullptr;
    ch2 = nullptr;
    ch3 = nullptr;
    ch4 = nullptr;
    ch5 = nullptr;
    ch6 = nullptr;
    ch7 = nullptr;
    ch8 = nullptr;
    toolbar = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	uiManagerThread = nullptr;
    //[/Destructor]
}

//==============================================================================
void TwonkMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0x6a000000), fillColour2 = Colour (0x9800b0ff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       static_cast<float> (getWidth()) - 0.0f + x,
                                       static_cast<float> (getHeight()) - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TwonkMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ch1->setBounds (0, proportionOfHeight (0.1000f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch2->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.1000f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch3->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.1000f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch4->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.1000f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch5->setBounds (0, proportionOfHeight (0.5500f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch6->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.5500f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch7->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.5500f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    ch8->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.5500f), proportionOfWidth (0.2500f), proportionOfHeight (0.4500f));
    toolbar->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TwonkMain::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}

void TwonkMain::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    //[/UserCode_mouseWheelMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TwonkMain::prepareToPlay (int, double)
{

}

void TwonkMain::releaseResources()
{

}

void TwonkMain::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TwonkMain" componentName=""
                 parentClasses="public AudioAppComponent" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="1024" initialHeight="600">
  <METHODS>
    <METHOD name="mouseWheelMove (const MouseEvent&amp; e, const MouseWheelDetails&amp; wheel)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 0R 0R, 0=6a000000, 1=9800b0ff"
          hasStroke="0"/>
  </BACKGROUND>
  <JUCERCOMP name="" id="447b20729ad0d1ec" memberName="ch1" virtualName=""
             explicitFocusOrder="0" pos="0 10% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 0"/>
  <JUCERCOMP name="" id="955cdb7f122ab433" memberName="ch2" virtualName=""
             explicitFocusOrder="0" pos="25% 10% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 1"/>
  <JUCERCOMP name="" id="fa47a0bd90143f39" memberName="ch3" virtualName=""
             explicitFocusOrder="0" pos="50% 10% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 2"/>
  <JUCERCOMP name="" id="b45592675f5e3273" memberName="ch4" virtualName=""
             explicitFocusOrder="0" pos="75% 10% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 3"/>
  <JUCERCOMP name="" id="b75cabc4ad3d324c" memberName="ch5" virtualName=""
             explicitFocusOrder="0" pos="0 55% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 4"/>
  <JUCERCOMP name="" id="2f32036001489d9c" memberName="ch6" virtualName=""
             explicitFocusOrder="0" pos="25% 55% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 5"/>
  <JUCERCOMP name="" id="c28d91323daa42f2" memberName="ch7" virtualName=""
             explicitFocusOrder="0" pos="50% 55% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 6"/>
  <JUCERCOMP name="" id="54e1b3008d039734" memberName="ch8" virtualName=""
             explicitFocusOrder="0" pos="75% 55% 25% 45%" sourceFile="TwonkChannel.cpp"
             constructorParams="this, 7"/>
  <JUCERCOMP name="" id="a2d9166279d37b07" memberName="toolbar" virtualName=""
             explicitFocusOrder="0" pos="0 0 100% 10%" sourceFile="TwonkToolbar.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


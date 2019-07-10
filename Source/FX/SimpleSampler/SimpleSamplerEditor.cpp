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

#include "SimpleSamplerEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SimpleSamplerEditor::SimpleSamplerEditor (SimpleSamplerProcessor &p)
    : processor(p), AudioProcessorEditor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
	sound1.reset (new SamplerSoundEditor(1,p));
	addAndMakeVisible (sound1.get());
	sound2.reset (new SamplerSoundEditor(2,p));
	addAndMakeVisible (sound2.get());
	sound3.reset (new SamplerSoundEditor(3,p));
	addAndMakeVisible (sound3.get());
	sound4.reset (new SamplerSoundEditor(4,p));
	addAndMakeVisible (sound4.get());
	sound5.reset (new SamplerSoundEditor(5,p));
	addAndMakeVisible (sound5.get());
	sound6.reset (new SamplerSoundEditor(6,p));
	addAndMakeVisible (sound6.get());
	sound7.reset (new SamplerSoundEditor(7,p));
	addAndMakeVisible (sound7.get());
	sound8.reset (new SamplerSoundEditor(8,p));
	addAndMakeVisible (sound8.get());
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (580, 448);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SimpleSamplerEditor::~SimpleSamplerEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	sound1 = nullptr;
	sound2 = nullptr;
	sound3 = nullptr;
	sound4 = nullptr;
	sound5 = nullptr;
	sound6 = nullptr;
	sound7 = nullptr;
	sound8 = nullptr;
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SimpleSamplerEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SimpleSamplerEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	sound1->setBounds (0, 0, getWidth() - 0, 50);
	sound2->setBounds (0, 56, getWidth() - 0, 50);
	sound3->setBounds (0, 112, getWidth() - 0, 50);
	sound4->setBounds (0, 168, getWidth() - 0, 50);
	sound5->setBounds (0, 224, getWidth() - 0, 50);
	sound6->setBounds (0, 280, getWidth() - 0, 50);
	sound7->setBounds (0, 336, getWidth() - 0, 50);
	sound8->setBounds (0, 392, getWidth() - 0, 50);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimpleSamplerEditor" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="SimpleSamplerProcessor &amp;p"
                 variableInitialisers="processor(p), AudioProcessorEditor (p),"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="580" initialHeight="448">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


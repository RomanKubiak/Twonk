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
#include "SequencerLinearProcessor.h"
//[/Headers]

#include "SequencerLinearEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void SequencerLinearLook::drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	Colour c;
	if (button.getToggleState())
		c = Colours::aqua.withAlpha(0.7f);
	else
		c = Colours::black.withAlpha(0.2f);
	g.setColour(c);
	g.fillRect(button.getLocalBounds().reduced(2));

	g.setColour(c.brighter(0.9f));
	g.drawRect(button.getLocalBounds().reduced(1));
}

void SequencerLinearLook::drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
	g.setColour (slider.findColour (Slider::trackColourId));
	g.fillRect (slider.isHorizontal() ?
		Rectangle<float> (x, y        , sliderPos - x, height) :
		Rectangle<float> (x, sliderPos, width        , y + (height - sliderPos))
	);
}
//[/MiscUserDefs]

//==============================================================================
SequencerLinearEditor::SequencerLinearEditor (SequencerLinearProcessor &p)
    : processor(p), AudioProcessorEditor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
	lf = new SequencerLinearLook();
	setLookAndFeel(lf);
    //[/Constructor_pre]

    slider.reset (new Slider ("new slider"));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 200, 1);
    slider->setSliderStyle (Slider::LinearVertical);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 32, 0);
    slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider->addListener (this);

    slider->setBounds (0, 32, 40, 160);

    slider2.reset (new Slider ("new slider"));
    addAndMakeVisible (slider2.get());
    slider2->setRange (0, 200, 1);
    slider2->setSliderStyle (Slider::LinearVertical);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 32, 0);
    slider2->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider2->addListener (this);

    slider2->setBounds (40, 32, 40, 160);

    slider3.reset (new Slider ("new slider"));
    addAndMakeVisible (slider3.get());
    slider3->setRange (0, 200, 1);
    slider3->setSliderStyle (Slider::LinearVertical);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 32, 0);
    slider3->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider3->addListener (this);

    slider3->setBounds (80, 32, 40, 160);

    slider4.reset (new Slider ("new slider"));
    addAndMakeVisible (slider4.get());
    slider4->setRange (0, 200, 1);
    slider4->setSliderStyle (Slider::LinearVertical);
    slider4->setTextBoxStyle (Slider::NoTextBox, false, 32, 0);
    slider4->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider4->addListener (this);

    slider4->setBounds (120, 32, 40, 160);

    slider5.reset (new Slider ("new slider"));
    addAndMakeVisible (slider5.get());
    slider5->setRange (0, 200, 1);
    slider5->setSliderStyle (Slider::LinearVertical);
    slider5->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider5->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider5->addListener (this);

    slider5->setBounds (160, 32, 40, 160);

    slider6.reset (new Slider ("new slider"));
    addAndMakeVisible (slider6.get());
    slider6->setRange (0, 200, 1);
    slider6->setSliderStyle (Slider::LinearVertical);
    slider6->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider6->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider6->addListener (this);

    slider6->setBounds (200, 32, 40, 160);

    slider7.reset (new Slider ("new slider"));
    addAndMakeVisible (slider7.get());
    slider7->setRange (0, 200, 1);
    slider7->setSliderStyle (Slider::LinearVertical);
    slider7->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider7->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider7->addListener (this);

    slider7->setBounds (240, 32, 40, 160);

    slider8.reset (new Slider ("new slider"));
    addAndMakeVisible (slider8.get());
    slider8->setRange (0, 200, 1);
    slider8->setSliderStyle (Slider::LinearVertical);
    slider8->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider8->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider8->addListener (this);

    slider8->setBounds (280, 32, 40, 160);

    slider9.reset (new Slider ("new slider"));
    addAndMakeVisible (slider9.get());
    slider9->setRange (0, 200, 1);
    slider9->setSliderStyle (Slider::LinearVertical);
    slider9->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider9->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider9->addListener (this);

    slider9->setBounds (320, 32, 40, 160);

    slider10.reset (new Slider ("new slider"));
    addAndMakeVisible (slider10.get());
    slider10->setRange (0, 200, 1);
    slider10->setSliderStyle (Slider::LinearVertical);
    slider10->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider10->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider10->addListener (this);

    slider10->setBounds (360, 32, 40, 160);

    slider11.reset (new Slider ("new slider"));
    addAndMakeVisible (slider11.get());
    slider11->setRange (0, 200, 1);
    slider11->setSliderStyle (Slider::LinearVertical);
    slider11->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider11->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider11->addListener (this);

    slider11->setBounds (400, 32, 40, 160);

    slider12.reset (new Slider ("new slider"));
    addAndMakeVisible (slider12.get());
    slider12->setRange (0, 200, 1);
    slider12->setSliderStyle (Slider::LinearVertical);
    slider12->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider12->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider12->addListener (this);

    slider12->setBounds (440, 32, 40, 160);

    slider13.reset (new Slider ("new slider"));
    addAndMakeVisible (slider13.get());
    slider13->setRange (0, 200, 1);
    slider13->setSliderStyle (Slider::LinearVertical);
    slider13->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider13->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider13->addListener (this);

    slider13->setBounds (480, 32, 40, 160);

    slider14.reset (new Slider ("new slider"));
    addAndMakeVisible (slider14.get());
    slider14->setRange (0, 200, 1);
    slider14->setSliderStyle (Slider::LinearVertical);
    slider14->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider14->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider14->addListener (this);

    slider14->setBounds (520, 32, 40, 160);

    slider15.reset (new Slider ("new slider"));
    addAndMakeVisible (slider15.get());
    slider15->setRange (0, 200, 1);
    slider15->setSliderStyle (Slider::LinearVertical);
    slider15->setTextBoxStyle (Slider::NoTextBox, false, 32, 16);
    slider15->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    slider15->addListener (this);

    slider15->setBounds (560, 32, 40, 160);

    toggleButton.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton.get());
    toggleButton->setButtonText (String());
    toggleButton->addListener (this);

    toggleButton->setBounds (0, 192, 40, 40);

    toggleButton2.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton2.get());
    toggleButton2->setButtonText (String());
    toggleButton2->addListener (this);

    toggleButton2->setBounds (40, 192, 40, 40);

    toggleButton3.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton3.get());
    toggleButton3->setButtonText (String());
    toggleButton3->addListener (this);

    toggleButton3->setBounds (80, 192, 40, 40);

    toggleButton4.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton4.get());
    toggleButton4->setButtonText (String());
    toggleButton4->addListener (this);

    toggleButton4->setBounds (120, 192, 40, 40);

    toggleButton5.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton5.get());
    toggleButton5->setButtonText (String());
    toggleButton5->addListener (this);

    toggleButton5->setBounds (160, 192, 40, 40);

    toggleButton6.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton6.get());
    toggleButton6->setButtonText (String());
    toggleButton6->addListener (this);

    toggleButton6->setBounds (200, 192, 40, 40);

    toggleButton7.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton7.get());
    toggleButton7->setButtonText (String());
    toggleButton7->addListener (this);

    toggleButton7->setBounds (240, 192, 40, 40);

    toggleButton8.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton8.get());
    toggleButton8->setButtonText (String());
    toggleButton8->addListener (this);

    toggleButton8->setBounds (280, 192, 40, 40);

    toggleButton9.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton9.get());
    toggleButton9->setButtonText (String());
    toggleButton9->addListener (this);

    toggleButton9->setBounds (320, 192, 40, 40);

    toggleButton10.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton10.get());
    toggleButton10->setButtonText (String());
    toggleButton10->addListener (this);

    toggleButton10->setBounds (360, 192, 40, 40);

    toggleButton11.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton11.get());
    toggleButton11->setButtonText (String());
    toggleButton11->addListener (this);

    toggleButton11->setBounds (400, 192, 40, 40);

    toggleButton12.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton12.get());
    toggleButton12->setButtonText (String());
    toggleButton12->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    toggleButton12->addListener (this);

    toggleButton12->setBounds (440, 192, 40, 40);

    toggleButton13.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton13.get());
    toggleButton13->setButtonText (String());
    toggleButton13->addListener (this);

    toggleButton13->setBounds (480, 192, 40, 40);

    toggleButton14.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton14.get());
    toggleButton14->setButtonText (String());
    toggleButton14->addListener (this);

    toggleButton14->setBounds (520, 192, 40, 40);

    toggleButton15.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (toggleButton15.get());
    toggleButton15->setButtonText (String());
    toggleButton15->addListener (this);

    toggleButton15->setBounds (560, 192, 40, 40);

    textButton2.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton2.get());
    textButton2->setButtonText (String());
    textButton2->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton2->addListener (this);
    textButton2->setColour (TextButton::buttonColourId, Colour (0x7de0ff55));
    textButton2->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton2->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton2->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton2->setBounds (0, 8, 40, 8);

    textButton3.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton3.get());
    textButton3->setButtonText (String());
    textButton3->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton3->addListener (this);
    textButton3->setColour (TextButton::buttonColourId, Colour (0x0082ff55));
    textButton3->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton3->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton3->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton3->setBounds (40, 8, 40, 8);

    textButton4.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton4.get());
    textButton4->setButtonText (String());
    textButton4->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton4->addListener (this);
    textButton4->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton4->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton4->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton4->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton4->setBounds (40, 8, 40, 8);

    textButton5.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton5.get());
    textButton5->setButtonText (String());
    textButton5->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton5->addListener (this);
    textButton5->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton5->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton5->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton5->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton5->setBounds (80, 8, 40, 8);

    textButton6.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton6.get());
    textButton6->setButtonText (String());
    textButton6->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton6->addListener (this);
    textButton6->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton6->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton6->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton6->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton6->setBounds (120, 8, 40, 8);

    textButton7.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton7.get());
    textButton7->setButtonText (String());
    textButton7->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton7->addListener (this);
    textButton7->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton7->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton7->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton7->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton7->setBounds (160, 8, 40, 8);

    textButton8.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton8.get());
    textButton8->setButtonText (String());
    textButton8->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton8->addListener (this);
    textButton8->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton8->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton8->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton8->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton8->setBounds (200, 8, 40, 8);

    textButton9.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton9.get());
    textButton9->setButtonText (String());
    textButton9->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton9->addListener (this);
    textButton9->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton9->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton9->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton9->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton9->setBounds (240, 8, 40, 8);

    textButton10.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton10.get());
    textButton10->setButtonText (String());
    textButton10->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton10->addListener (this);
    textButton10->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton10->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton10->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton10->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton10->setBounds (280, 8, 40, 8);

    textButton11.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton11.get());
    textButton11->setButtonText (String());
    textButton11->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton11->addListener (this);
    textButton11->setColour (TextButton::buttonColourId, Colour (0x7de0ff55));
    textButton11->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton11->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton11->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton11->setBounds (320, 8, 40, 8);

    textButton12.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton12.get());
    textButton12->setButtonText (String());
    textButton12->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton12->addListener (this);
    textButton12->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton12->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton12->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton12->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton12->setBounds (360, 8, 40, 8);

    textButton13.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton13.get());
    textButton13->setButtonText (String());
    textButton13->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton13->addListener (this);
    textButton13->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton13->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton13->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton13->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton13->setBounds (400, 8, 40, 8);

    textButton14.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton14.get());
    textButton14->setButtonText (String());
    textButton14->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton14->addListener (this);
    textButton14->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton14->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton14->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton14->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton14->setBounds (440, 8, 40, 8);

    textButton15.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton15.get());
    textButton15->setButtonText (String());
    textButton15->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton15->addListener (this);
    textButton15->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton15->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton15->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton15->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton15->setBounds (480, 8, 40, 8);

    textButton16.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton16.get());
    textButton16->setButtonText (String());
    textButton16->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton16->addListener (this);
    textButton16->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton16->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton16->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton16->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton16->setBounds (520, 8, 40, 8);

    textButton17.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton17.get());
    textButton17->setButtonText (String());
    textButton17->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    textButton17->addListener (this);
    textButton17->setColour (TextButton::buttonColourId, Colour (0x7d82ff55));
    textButton17->setColour (TextButton::buttonOnColourId, Colour (0x00000000));
    textButton17->setColour (TextButton::textColourOffId, Colour (0x00000000));
    textButton17->setColour (TextButton::textColourOnId, Colour (0x00000000));

    textButton17->setBounds (560, 8, 40, 8);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 240);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SequencerLinearEditor::~SequencerLinearEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	setLookAndFeel(nullptr);
	deleteAndZero(lf);
    //[/Destructor_pre]

    slider = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;
    slider4 = nullptr;
    slider5 = nullptr;
    slider6 = nullptr;
    slider7 = nullptr;
    slider8 = nullptr;
    slider9 = nullptr;
    slider10 = nullptr;
    slider11 = nullptr;
    slider12 = nullptr;
    slider13 = nullptr;
    slider14 = nullptr;
    slider15 = nullptr;
    toggleButton = nullptr;
    toggleButton2 = nullptr;
    toggleButton3 = nullptr;
    toggleButton4 = nullptr;
    toggleButton5 = nullptr;
    toggleButton6 = nullptr;
    toggleButton7 = nullptr;
    toggleButton8 = nullptr;
    toggleButton9 = nullptr;
    toggleButton10 = nullptr;
    toggleButton11 = nullptr;
    toggleButton12 = nullptr;
    toggleButton13 = nullptr;
    toggleButton14 = nullptr;
    toggleButton15 = nullptr;
    textButton2 = nullptr;
    textButton3 = nullptr;
    textButton4 = nullptr;
    textButton5 = nullptr;
    textButton6 = nullptr;
    textButton7 = nullptr;
    textButton8 = nullptr;
    textButton9 = nullptr;
    textButton10 = nullptr;
    textButton11 = nullptr;
    textButton12 = nullptr;
    textButton13 = nullptr;
    textButton14 = nullptr;
    textButton15 = nullptr;
    textButton16 = nullptr;
    textButton17 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SequencerLinearEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff0e374c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SequencerLinearEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SequencerLinearEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2.get())
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3.get())
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4.get())
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }
    else if (sliderThatWasMoved == slider5.get())
    {
        //[UserSliderCode_slider5] -- add your slider handling code here..
        //[/UserSliderCode_slider5]
    }
    else if (sliderThatWasMoved == slider6.get())
    {
        //[UserSliderCode_slider6] -- add your slider handling code here..
        //[/UserSliderCode_slider6]
    }
    else if (sliderThatWasMoved == slider7.get())
    {
        //[UserSliderCode_slider7] -- add your slider handling code here..
        //[/UserSliderCode_slider7]
    }
    else if (sliderThatWasMoved == slider8.get())
    {
        //[UserSliderCode_slider8] -- add your slider handling code here..
        //[/UserSliderCode_slider8]
    }
    else if (sliderThatWasMoved == slider9.get())
    {
        //[UserSliderCode_slider9] -- add your slider handling code here..
        //[/UserSliderCode_slider9]
    }
    else if (sliderThatWasMoved == slider10.get())
    {
        //[UserSliderCode_slider10] -- add your slider handling code here..
        //[/UserSliderCode_slider10]
    }
    else if (sliderThatWasMoved == slider11.get())
    {
        //[UserSliderCode_slider11] -- add your slider handling code here..
        //[/UserSliderCode_slider11]
    }
    else if (sliderThatWasMoved == slider12.get())
    {
        //[UserSliderCode_slider12] -- add your slider handling code here..
        //[/UserSliderCode_slider12]
    }
    else if (sliderThatWasMoved == slider13.get())
    {
        //[UserSliderCode_slider13] -- add your slider handling code here..
        //[/UserSliderCode_slider13]
    }
    else if (sliderThatWasMoved == slider14.get())
    {
        //[UserSliderCode_slider14] -- add your slider handling code here..
        //[/UserSliderCode_slider14]
    }
    else if (sliderThatWasMoved == slider15.get())
    {
        //[UserSliderCode_slider15] -- add your slider handling code here..
        //[/UserSliderCode_slider15]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SequencerLinearEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButton.get())
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }
    else if (buttonThatWasClicked == toggleButton2.get())
    {
        //[UserButtonCode_toggleButton2] -- add your button handler code here..
        //[/UserButtonCode_toggleButton2]
    }
    else if (buttonThatWasClicked == toggleButton3.get())
    {
        //[UserButtonCode_toggleButton3] -- add your button handler code here..
        //[/UserButtonCode_toggleButton3]
    }
    else if (buttonThatWasClicked == toggleButton4.get())
    {
        //[UserButtonCode_toggleButton4] -- add your button handler code here..
        //[/UserButtonCode_toggleButton4]
    }
    else if (buttonThatWasClicked == toggleButton5.get())
    {
        //[UserButtonCode_toggleButton5] -- add your button handler code here..
        //[/UserButtonCode_toggleButton5]
    }
    else if (buttonThatWasClicked == toggleButton6.get())
    {
        //[UserButtonCode_toggleButton6] -- add your button handler code here..
        //[/UserButtonCode_toggleButton6]
    }
    else if (buttonThatWasClicked == toggleButton7.get())
    {
        //[UserButtonCode_toggleButton7] -- add your button handler code here..
        //[/UserButtonCode_toggleButton7]
    }
    else if (buttonThatWasClicked == toggleButton8.get())
    {
        //[UserButtonCode_toggleButton8] -- add your button handler code here..
        //[/UserButtonCode_toggleButton8]
    }
    else if (buttonThatWasClicked == toggleButton9.get())
    {
        //[UserButtonCode_toggleButton9] -- add your button handler code here..
        //[/UserButtonCode_toggleButton9]
    }
    else if (buttonThatWasClicked == toggleButton10.get())
    {
        //[UserButtonCode_toggleButton10] -- add your button handler code here..
        //[/UserButtonCode_toggleButton10]
    }
    else if (buttonThatWasClicked == toggleButton11.get())
    {
        //[UserButtonCode_toggleButton11] -- add your button handler code here..
        //[/UserButtonCode_toggleButton11]
    }
    else if (buttonThatWasClicked == toggleButton12.get())
    {
        //[UserButtonCode_toggleButton12] -- add your button handler code here..
        //[/UserButtonCode_toggleButton12]
    }
    else if (buttonThatWasClicked == toggleButton13.get())
    {
        //[UserButtonCode_toggleButton13] -- add your button handler code here..
        //[/UserButtonCode_toggleButton13]
    }
    else if (buttonThatWasClicked == toggleButton14.get())
    {
        //[UserButtonCode_toggleButton14] -- add your button handler code here..
        //[/UserButtonCode_toggleButton14]
    }
    else if (buttonThatWasClicked == toggleButton15.get())
    {
        //[UserButtonCode_toggleButton15] -- add your button handler code here..
        //[/UserButtonCode_toggleButton15]
    }
    else if (buttonThatWasClicked == textButton2.get())
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }
    else if (buttonThatWasClicked == textButton3.get())
    {
        //[UserButtonCode_textButton3] -- add your button handler code here..
        //[/UserButtonCode_textButton3]
    }
    else if (buttonThatWasClicked == textButton4.get())
    {
        //[UserButtonCode_textButton4] -- add your button handler code here..
        //[/UserButtonCode_textButton4]
    }
    else if (buttonThatWasClicked == textButton5.get())
    {
        //[UserButtonCode_textButton5] -- add your button handler code here..
        //[/UserButtonCode_textButton5]
    }
    else if (buttonThatWasClicked == textButton6.get())
    {
        //[UserButtonCode_textButton6] -- add your button handler code here..
        //[/UserButtonCode_textButton6]
    }
    else if (buttonThatWasClicked == textButton7.get())
    {
        //[UserButtonCode_textButton7] -- add your button handler code here..
        //[/UserButtonCode_textButton7]
    }
    else if (buttonThatWasClicked == textButton8.get())
    {
        //[UserButtonCode_textButton8] -- add your button handler code here..
        //[/UserButtonCode_textButton8]
    }
    else if (buttonThatWasClicked == textButton9.get())
    {
        //[UserButtonCode_textButton9] -- add your button handler code here..
        //[/UserButtonCode_textButton9]
    }
    else if (buttonThatWasClicked == textButton10.get())
    {
        //[UserButtonCode_textButton10] -- add your button handler code here..
        //[/UserButtonCode_textButton10]
    }
    else if (buttonThatWasClicked == textButton11.get())
    {
        //[UserButtonCode_textButton11] -- add your button handler code here..
        //[/UserButtonCode_textButton11]
    }
    else if (buttonThatWasClicked == textButton12.get())
    {
        //[UserButtonCode_textButton12] -- add your button handler code here..
        //[/UserButtonCode_textButton12]
    }
    else if (buttonThatWasClicked == textButton13.get())
    {
        //[UserButtonCode_textButton13] -- add your button handler code here..
        //[/UserButtonCode_textButton13]
    }
    else if (buttonThatWasClicked == textButton14.get())
    {
        //[UserButtonCode_textButton14] -- add your button handler code here..
        //[/UserButtonCode_textButton14]
    }
    else if (buttonThatWasClicked == textButton15.get())
    {
        //[UserButtonCode_textButton15] -- add your button handler code here..
        //[/UserButtonCode_textButton15]
    }
    else if (buttonThatWasClicked == textButton16.get())
    {
        //[UserButtonCode_textButton16] -- add your button handler code here..
        //[/UserButtonCode_textButton16]
    }
    else if (buttonThatWasClicked == textButton17.get())
    {
        //[UserButtonCode_textButton17] -- add your button handler code here..
        //[/UserButtonCode_textButton17]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SequencerLinearEditor" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="SequencerLinearProcessor &amp;p"
                 variableInitialisers="processor(p), AudioProcessorEditor (p),"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="240">
  <BACKGROUND backgroundColour="ff0e374c"/>
  <SLIDER name="new slider" id="c34f5fc5ed0b7510" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="0 32 40 160" textboxoutline="0" min="0.0"
          max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="0" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="f36d18d2c5e3ea2c" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="40 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="0" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="882b66a2f705eb4" memberName="slider3" virtualName=""
          explicitFocusOrder="0" pos="80 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="0" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="181ea2eed58fe3a0" memberName="slider4"
          virtualName="" explicitFocusOrder="0" pos="120 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="0" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="c5fa72773b8ac631" memberName="slider5"
          virtualName="" explicitFocusOrder="0" pos="160 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="7cb616d589aeb9bb" memberName="slider6"
          virtualName="" explicitFocusOrder="0" pos="200 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="50203b6dd4ca09ca" memberName="slider7"
          virtualName="" explicitFocusOrder="0" pos="240 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="d2d2c474e516428a" memberName="slider8"
          virtualName="" explicitFocusOrder="0" pos="280 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="9129f157da0383c5" memberName="slider9"
          virtualName="" explicitFocusOrder="0" pos="320 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="725631db397e992f" memberName="slider10"
          virtualName="" explicitFocusOrder="0" pos="360 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="26d3a984310fc400" memberName="slider11"
          virtualName="" explicitFocusOrder="0" pos="400 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="e94c053bc72409c3" memberName="slider12"
          virtualName="" explicitFocusOrder="0" pos="440 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="100d872a6d9c1c6e" memberName="slider13"
          virtualName="" explicitFocusOrder="0" pos="480 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="ea8c6ceaf4d92fb1" memberName="slider14"
          virtualName="" explicitFocusOrder="0" pos="520 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="c61213e029314f92" memberName="slider15"
          virtualName="" explicitFocusOrder="0" pos="560 32 40 160" textboxoutline="0"
          min="0.0" max="200.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="16" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="435a011ab6448edc" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="0 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="77215b7851ec74ed" memberName="toggleButton2"
                virtualName="" explicitFocusOrder="0" pos="40 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c6992e629935b55f" memberName="toggleButton3"
                virtualName="" explicitFocusOrder="0" pos="80 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="b58472e043fba67a" memberName="toggleButton4"
                virtualName="" explicitFocusOrder="0" pos="120 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="9873adcbf736defa" memberName="toggleButton5"
                virtualName="" explicitFocusOrder="0" pos="160 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d56b883dbb2d8505" memberName="toggleButton6"
                virtualName="" explicitFocusOrder="0" pos="200 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="b87025bf4b5b537c" memberName="toggleButton7"
                virtualName="" explicitFocusOrder="0" pos="240 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="cfed38a675442093" memberName="toggleButton8"
                virtualName="" explicitFocusOrder="0" pos="280 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ac6078b971cfb9a3" memberName="toggleButton9"
                virtualName="" explicitFocusOrder="0" pos="320 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="7ce260173f67283e" memberName="toggleButton10"
                virtualName="" explicitFocusOrder="0" pos="360 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a5835257a5f8b484" memberName="toggleButton11"
                virtualName="" explicitFocusOrder="0" pos="400 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c33191f16a8938b4" memberName="toggleButton12"
                virtualName="" explicitFocusOrder="0" pos="440 192 40 40" buttonText=""
                connectedEdges="15" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ed3ea7dbd34e9a05" memberName="toggleButton13"
                virtualName="" explicitFocusOrder="0" pos="480 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="9ce1217790b87ab6" memberName="toggleButton14"
                virtualName="" explicitFocusOrder="0" pos="520 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d179c8ab58897964" memberName="toggleButton15"
                virtualName="" explicitFocusOrder="0" pos="560 192 40 40" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="new button" id="d7f9a38b53a6c9d4" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="0 8 40 8" bgColOff="7de0ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="28e82fa305720b76" memberName="textButton3"
              virtualName="" explicitFocusOrder="0" pos="40 8 40 8" bgColOff="82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="8224b3cf206b6ac8" memberName="textButton4"
              virtualName="" explicitFocusOrder="0" pos="40 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="29847c263cd1fd56" memberName="textButton5"
              virtualName="" explicitFocusOrder="0" pos="80 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="eec16c7e1d81bcc6" memberName="textButton6"
              virtualName="" explicitFocusOrder="0" pos="120 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="b9a219f37bb5fb27" memberName="textButton7"
              virtualName="" explicitFocusOrder="0" pos="160 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2634aaf5e493369d" memberName="textButton8"
              virtualName="" explicitFocusOrder="0" pos="200 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="1922ac93c523ff54" memberName="textButton9"
              virtualName="" explicitFocusOrder="0" pos="240 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="f91677fd0169c8b1" memberName="textButton10"
              virtualName="" explicitFocusOrder="0" pos="280 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="edd2ec435b0d19ca" memberName="textButton11"
              virtualName="" explicitFocusOrder="0" pos="320 8 40 8" bgColOff="7de0ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="e8668062e4fbd118" memberName="textButton12"
              virtualName="" explicitFocusOrder="0" pos="360 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="16eef181bafb6f6b" memberName="textButton13"
              virtualName="" explicitFocusOrder="0" pos="400 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c1f31177ca209e1d" memberName="textButton14"
              virtualName="" explicitFocusOrder="0" pos="440 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2dac7991b87c648a" memberName="textButton15"
              virtualName="" explicitFocusOrder="0" pos="480 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="bef32591aa62c0bf" memberName="textButton16"
              virtualName="" explicitFocusOrder="0" pos="520 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5e193af879b59770" memberName="textButton17"
              virtualName="" explicitFocusOrder="0" pos="560 8 40 8" bgColOff="7d82ff55"
              bgColOn="0" textCol="0" textColOn="0" buttonText="" connectedEdges="15"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


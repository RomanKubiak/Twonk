/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "PizLooper.h"
#include "common/ClickableLabel.h"
#include "PianoRoll.h"
#include "VSTSlider.h"
#include "LookAndFeel.h"

class KeySelector : public MidiKeyboardComponent
{
public:
    KeySelector(MidiKeyboardState &state)
		: MidiKeyboardComponent(state,MidiKeyboardComponent::horizontalKeyboard)
	{
		s=&state;
		this->setColour(MidiKeyboardComponent::textLabelColourId,Colours::transparentBlack);
	}
	~KeySelector(){}
private:
    bool mouseDownOnKey(int midiNoteNumber, const MouseEvent &e)
	{
        if (s->isNoteOn(this->getMidiChannel(),midiNoteNumber)) {
            s->noteOff(this->getMidiChannel(),midiNoteNumber,0.0f);
        }
        else {
            s->noteOn(this->getMidiChannel(),midiNoteNumber,1.f);
        }
        return false;
	}
    MidiKeyboardState* s;
};



//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PizLooperEditor  : public AudioProcessorEditor,
                         public ChangeListener,
                         public FileDragAndDropTarget,
                         public ClickableLabelListener,
                         public Timer,
                         public MidiKeyboardStateListener,
                         public Button::Listener,
                         public ComboBox::Listener,
                         public Slider::Listener,
                         public Label::Listener
{
public:
    //==============================================================================
    PizLooperEditor (PizLooper* const ownerFilter);
    ~PizLooperEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback (ChangeBroadcaster* source);
    bool isInterestedInFileDrag (const StringArray& files);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
//    void sliderDragStarted (Slider* slider); //slider mousedown
//    void sliderDragEnded (Slider* slider); //slider mouseup
	void timerCallback();
	void buttonStateChanged(Button* button);
    void mouseDrag (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
	void clickableLabelMouseDown(ClickableLabel *label, const MouseEvent &e) {}
	void clickableLabelMouseDoubleClick(ClickableLabel *label, const MouseEvent &e) {if (label==nameLabel.get()) label->edit();}
	void handleNoteOn(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void labelTextChanged (Label* labelThatHasChanged) override;

    // Binary resources:
    static const char* piznew40_png;
    static const int piznew40_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TooltipWindow tooltipWindow;
    void updateParametersFromFilter();
	void updateControls(int param, float value, bool forCurProgram);
	void updateSlotButtons();
    ComponentBoundsConstrainer resizeLimits;
	TextButton* getButtonForSlot(int slot);
	int getButtonIndex(Component* button);
	int lastActiveLoop;
    PianoRoll* pianoRoll;
	bool noSnap;
	int loopDragStart;
	MidiKeyboardState keySelectorState;
	MidiKeyboardComponent* keyboard;
	int counter;
	int demo;
    Path internalPath1;
    Path internalPath2;

    // handy wrapper method to avoid having to cast the filter to a PizLooper
    // every time we need it..
    PizLooper* getFilter() const throw() { return (PizLooper*) getAudioProcessor(); }
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> label;
    std::unique_ptr<Timeline> timeline;
    std::unique_ptr<TextButton> textButton1;
    std::unique_ptr<TextButton> textButton2;
    std::unique_ptr<TextButton> textButton3;
    std::unique_ptr<TextButton> textButton4;
    std::unique_ptr<TextButton> textButton5;
    std::unique_ptr<TextButton> textButton6;
    std::unique_ptr<TextButton> textButton7;
    std::unique_ptr<TextButton> textButton8;
    std::unique_ptr<TextButton> textButton9;
    std::unique_ptr<TextButton> textButton10;
    std::unique_ptr<TextButton> textButton11;
    std::unique_ptr<TextButton> textButton12;
    std::unique_ptr<TextButton> textButton13;
    std::unique_ptr<TextButton> textButton14;
    std::unique_ptr<TextButton> textButton15;
    std::unique_ptr<TextButton> textButton16;
    std::unique_ptr<TextButton> b_Play;
    std::unique_ptr<TextButton> b_Record;
    std::unique_ptr<TextButton> b_Overdub;
    std::unique_ptr<TextButton> b_Thru;
    std::unique_ptr<TextButton> b_Clear;
    std::unique_ptr<ComboBox> stepsizeBox;
    std::unique_ptr<VSTSlider> s_Transpose;
    std::unique_ptr<VSTSlider> s_Octave;
    std::unique_ptr<VSTSlider> s_Velocity;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Label> label5;
    std::unique_ptr<VSTSlider> s_Start;
    std::unique_ptr<Label> label6;
    std::unique_ptr<VSTSlider> s_End;
    std::unique_ptr<Label> label7;
    std::unique_ptr<VSTSlider> s_Stretch;
    std::unique_ptr<Label> label8;
    std::unique_ptr<ComboBox> loopmodeBox;
    std::unique_ptr<ComboBox> notetriggerBox;
    std::unique_ptr<ComboBox> syncmodeBox;
    std::unique_ptr<VSTSlider> s_Root;
    std::unique_ptr<Label> label9;
    std::unique_ptr<VSTSlider> s_Low;
    std::unique_ptr<Label> label10;
    std::unique_ptr<VSTSlider> s_High;
    std::unique_ptr<Label> label11;
    std::unique_ptr<VSTSlider> s_TrigChan;
    std::unique_ptr<Label> label12;
    std::unique_ptr<TextButton> b_Reload;
    std::unique_ptr<ComboBox> quantizeBox;
    std::unique_ptr<Label> label21;
    std::unique_ptr<VSTSlider> s_Shift;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Label> label23;
    std::unique_ptr<ClickableLabel> nameLabel;
    std::unique_ptr<TextButton> b_Save;
    std::unique_ptr<Label> label22;
    std::unique_ptr<Label> label18;
    std::unique_ptr<Label> loopinfoLabel;
    std::unique_ptr<Label> loopinfoLabel2;
    std::unique_ptr<Label> label17;
    std::unique_ptr<VSTSlider> s_Channel;
    std::unique_ptr<Label> label19;
    std::unique_ptr<Label> label20;
    std::unique_ptr<VSTSlider> s_FixedLength;
    std::unique_ptr<TextButton> b_Filt;
    std::unique_ptr<PianoPort> viewport;
    std::unique_ptr<ResizableCornerComponent> resizer;
    std::unique_ptr<TextButton> b_NoteToggle;
    std::unique_ptr<VSTSlider> s_PlayGroup;
    std::unique_ptr<Label> label13;
    std::unique_ptr<VSTSlider> s_MuteGroup;
    std::unique_ptr<Label> label14;
    std::unique_ptr<ToggleButton> b_Snap;
    std::unique_ptr<ComboBox> quantizeBox2;
    std::unique_ptr<ToggleButton> b_ForceToKey;
    std::unique_ptr<KeySelector> keySelector;
    std::unique_ptr<TextButton> b_ShiftUp;
    std::unique_ptr<TextButton> b_ShiftDown;
    std::unique_ptr<ToggleButton> b_SingleLoop;
    std::unique_ptr<VSTSlider> s_MasterVelocity;
    std::unique_ptr<Label> label15;
    std::unique_ptr<ImageButton> aboutButton;
    std::unique_ptr<TextButton> b_Triplet;
    std::unique_ptr<TextButton> b_Dotted;
    std::unique_ptr<TextButton> b_ZoomOut;
    std::unique_ptr<TextButton> b_ZoomIn;
    std::unique_ptr<Label> numerator;
    std::unique_ptr<Label> denominator;
    std::unique_ptr<Label> loopinfoLabel3;
    std::unique_ptr<ToggleButton> b_UseScaleChannel;
    std::unique_ptr<VSTSlider> s_ScaleChannel;
    std::unique_ptr<Label> label25;
    std::unique_ptr<VSTSlider> s_MasterTranspose;
    std::unique_ptr<Label> label26;
    std::unique_ptr<ToggleButton> b_WaitForBar;
    std::unique_ptr<ComboBox> midiOutDeviceBox;
    std::unique_ptr<Label> label27;
    std::unique_ptr<ToggleButton> b_UseTrChannel;
    std::unique_ptr<ToggleButton> b_ImmediateTranspose;
    std::unique_ptr<VSTSlider> s_NumLoops;
    std::unique_ptr<VSTSlider> s_NextSlot;
    std::unique_ptr<Label> label16;
    std::unique_ptr<ComboBox> forceModeBox;
    std::unique_ptr<Viewport> kbport;
    std::unique_ptr<TextButton> b_RemoveBar;
    std::unique_ptr<TextButton> b_AddBar;
    std::unique_ptr<Label> LengthLabel;
    std::unique_ptr<TextButton> textButton17;
    std::unique_ptr<TextButton> textButton18;
    std::unique_ptr<TextButton> textButton19;
    std::unique_ptr<TextButton> textButton20;
    std::unique_ptr<TextButton> textButton21;
    std::unique_ptr<TextButton> textButton22;
    std::unique_ptr<TextButton> textButton23;
    std::unique_ptr<TextButton> textButton24;
    std::unique_ptr<TextButton> textButton25;
    std::unique_ptr<TextButton> textButton26;
    std::unique_ptr<TextButton> textButton27;
    std::unique_ptr<TextButton> textButton28;
    std::unique_ptr<TextButton> textButton29;
    std::unique_ptr<TextButton> textButton30;
    std::unique_ptr<TextButton> textButton31;
    std::unique_ptr<TextButton> textButton32;
    std::unique_ptr<TextButton> textButton33;
    std::unique_ptr<TextButton> textButton34;
    std::unique_ptr<TextButton> textButton35;
    std::unique_ptr<TextButton> textButton36;
    std::unique_ptr<TextButton> textButton37;
    std::unique_ptr<TextButton> textButton38;
    std::unique_ptr<TextButton> textButton39;
    std::unique_ptr<TextButton> textButton40;
    std::unique_ptr<TextButton> textButton41;
    std::unique_ptr<TextButton> textButton42;
    std::unique_ptr<TextButton> textButton43;
    std::unique_ptr<TextButton> textButton44;
    std::unique_ptr<TextButton> textButton45;
    std::unique_ptr<TextButton> textButton46;
    std::unique_ptr<TextButton> textButton47;
    std::unique_ptr<TextButton> textButton48;
    std::unique_ptr<TextButton> textButton49;
    std::unique_ptr<TextButton> textButton50;
    std::unique_ptr<TextButton> textButton51;
    std::unique_ptr<TextButton> textButton52;
    std::unique_ptr<TextButton> textButton53;
    std::unique_ptr<TextButton> textButton54;
    std::unique_ptr<TextButton> textButton55;
    std::unique_ptr<TextButton> textButton56;
    std::unique_ptr<TextButton> textButton57;
    std::unique_ptr<TextButton> textButton58;
    std::unique_ptr<TextButton> textButton59;
    std::unique_ptr<TextButton> textButton60;
    std::unique_ptr<TextButton> textButton61;
    std::unique_ptr<TextButton> textButton62;
    std::unique_ptr<TextButton> textButton63;
    std::unique_ptr<TextButton> textButton64;
    std::unique_ptr<TextButton> textButton65;
    std::unique_ptr<TextButton> textButton66;
    std::unique_ptr<TextButton> textButton67;
    std::unique_ptr<TextButton> textButton68;
    std::unique_ptr<TextButton> textButton69;
    std::unique_ptr<TextButton> textButton70;
    std::unique_ptr<TextButton> textButton71;
    std::unique_ptr<TextButton> textButton72;
    std::unique_ptr<TextButton> textButton73;
    std::unique_ptr<TextButton> textButton74;
    std::unique_ptr<TextButton> textButton75;
    std::unique_ptr<TextButton> textButton76;
    std::unique_ptr<TextButton> textButton77;
    std::unique_ptr<TextButton> textButton78;
    std::unique_ptr<TextButton> textButton79;
    std::unique_ptr<TextButton> textButton80;
    std::unique_ptr<TextButton> textButton81;
    std::unique_ptr<TextButton> textButton82;
    std::unique_ptr<TextButton> textButton83;
    std::unique_ptr<TextButton> textButton84;
    std::unique_ptr<TextButton> textButton85;
    std::unique_ptr<TextButton> textButton86;
    std::unique_ptr<TextButton> textButton87;
    std::unique_ptr<TextButton> textButton88;
    std::unique_ptr<TextButton> textButton89;
    std::unique_ptr<TextButton> textButton90;
    std::unique_ptr<TextButton> textButton91;
    std::unique_ptr<TextButton> textButton92;
    std::unique_ptr<TextButton> textButton93;
    std::unique_ptr<TextButton> textButton94;
    std::unique_ptr<TextButton> textButton95;
    std::unique_ptr<TextButton> textButton96;
    std::unique_ptr<TextButton> textButton97;
    std::unique_ptr<TextButton> textButton98;
    std::unique_ptr<TextButton> textButton99;
    std::unique_ptr<TextButton> textButton100;
    std::unique_ptr<TextButton> textButton101;
    std::unique_ptr<TextButton> textButton102;
    std::unique_ptr<TextButton> textButton103;
    std::unique_ptr<TextButton> textButton104;
    std::unique_ptr<TextButton> textButton105;
    std::unique_ptr<TextButton> textButton106;
    std::unique_ptr<TextButton> textButton107;
    std::unique_ptr<TextButton> textButton108;
    std::unique_ptr<TextButton> textButton109;
    std::unique_ptr<TextButton> textButton110;
    std::unique_ptr<TextButton> textButton111;
    std::unique_ptr<TextButton> textButton112;
    std::unique_ptr<TextButton> textButton113;
    std::unique_ptr<TextButton> textButton114;
    std::unique_ptr<TextButton> textButton115;
    std::unique_ptr<TextButton> textButton116;
    std::unique_ptr<TextButton> textButton117;
    std::unique_ptr<TextButton> textButton118;
    std::unique_ptr<TextButton> textButton119;
    std::unique_ptr<TextButton> textButton120;
    std::unique_ptr<TextButton> textButton121;
    std::unique_ptr<TextButton> textButton122;
    std::unique_ptr<TextButton> textButton123;
    std::unique_ptr<TextButton> textButton124;
    std::unique_ptr<TextButton> textButton125;
    std::unique_ptr<TextButton> textButton126;
    std::unique_ptr<TextButton> textButton127;
    std::unique_ptr<TextButton> textButton128;
    std::unique_ptr<TextButton> b_Transpose10;
    std::unique_ptr<ToggleButton> b_KeepLength;
    std::unique_ptr<VSTSlider> s_RecCC;
    std::unique_ptr<VSTSlider> s_PlayCC;
    std::unique_ptr<VSTSlider> s_VelocitySens;
    std::unique_ptr<Label> label24;
    std::unique_ptr<TextButton> b_Monitor;
    std::unique_ptr<VSTSlider> s_TransposeChannel;
    std::unique_ptr<Label> label28;
    Image cachedImage_piznew40_png_1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PizLooperEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

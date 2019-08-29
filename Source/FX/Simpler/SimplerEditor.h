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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "InstrumentButton.h"
#include "UI/MainHostWindow.h"

class SimplerProcessor;
class InstrumentButtonsPanel;
class InstrumentParametersEditor;

class SamplerLookAndFeel : public LookAndFeel_V4
{
	void drawConcertinaPanelHeader (Graphics& g, const Rectangle<int>& area,
		bool isMouseOver, bool /*isMouseDown*/,
		ConcertinaPanel& concertina, Component& panel)
	{
		auto bounds = area.toFloat().reduced (0.5f);
		auto cornerSize = 4.0f;
		auto isTopPanel = (concertina.getPanel (0) == &panel);

		Path p;
		p.addRoundedRectangle (bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(),
			cornerSize, cornerSize, isTopPanel, isTopPanel, false, false);

		g.setGradientFill (ColourGradient::vertical (Colours::white.withAlpha (isMouseOver ? 0.4f : 0.2f), static_cast<float> (area.getY()),
			Colours::darkgrey.withAlpha (0.1f), static_cast<float> (area.getBottom())));
		g.fillPath (p);
		g.setColour(Colours::white);
		g.setFont(getDefaultTwonkSansFont().withHeight(bounds.getHeight() * 0.7f));
		g.drawText(panel.getName(), bounds.withLeft(8), Justification::left);
	}
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SimplerEditor  : public AudioProcessorEditor,
                       public ChangeListener,
                       public AudioProcessorValueTreeState::Listener,
                       public ComboBox::Listener
{
public:
    //==============================================================================
    SimplerEditor (SimplerProcessor &_processor);
    ~SimplerEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	void loadInstrumentsToGui();
	void currentInstrumentSelectionChanged(InstrumentButton *buttonSelected);
	void loadBanksToCombo();
	SimplerProcessor &getNamedAudioProcessor() { return (processor); }
	void parameterChanged (const String &parameterID, float newValue);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	SimplerProcessor &processor;
	InstrumentParametersEditor *instrumentEditor;
	std::unique_ptr<ResizableCornerComponent> cornerResizer;
	std::unique_ptr<ComponentBoundsConstrainer> sizeConstrainer;
	SamplerLookAndFeel samplerLookAndFeel;
	InstrumentButtonsPanel *buttonsPanel;
	std::unique_ptr< AudioProcessorValueTreeState::ComboBoxAttachment> bankListLink;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> bankListCombo;
    std::unique_ptr<ConcertinaPanel> panel;
    std::unique_ptr<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplerEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


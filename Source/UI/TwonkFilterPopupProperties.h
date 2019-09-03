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
#include "../../JuceLibraryCode/JuceHeader.h"
#include "GraphEditorPanel.h"
//[/Headers]

#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"
#include "TwonkFilterPopupPropertiesSegment.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TwonkFilterPopupProperties  : public Component,
                                    public ChangeListener
{
public:
    //==============================================================================
    TwonkFilterPopupProperties (GraphEditorPanel &_owner);
    ~TwonkFilterPopupProperties();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setFilter(struct GraphEditorPanel::PluginComponent *_filter);
	struct GraphEditorPanel::PluginComponent *getFilter() { return (filter); }
	void changeListenerCallback (ChangeBroadcaster* source);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	struct GraphEditorPanel::PluginComponent *filter = nullptr;
	GraphEditorPanel &owner;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> disconnectAllSegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> deleteFilterSegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> toggleBypassSegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> toggleGUISegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> configureAudioSegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> showParametersSegment;
    std::unique_ptr<TwonkFilterPopupPropertiesSegment> showAllProgramsSegment;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterPopupProperties)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma once

#include "../Filters/FilterGraph.h"

class MainHostWindow;
class TwonkFilterComponent;
class TwonkFilterConnector;
class TwonkFilterComponentPinWrapper;
//==============================================================================
/**
    A panel that displays and edits a FilterGraph.
*/
class GraphEditorPanel   : public Component,
                           public ChangeListener,
                           private Timer
{
public:
    GraphEditorPanel (FilterGraph& graph);
    ~GraphEditorPanel() override;

    void createNewPlugin (const PluginDescription&, Point<int> position);

    void paint (Graphics&) override;
    void resized() override;

    void mouseDown (const MouseEvent&) override;
    void mouseUp   (const MouseEvent&) override;
    void mouseDrag (const MouseEvent&) override;
	void mouseDoubleClick(const MouseEvent &) override;
    void changeListenerCallback (ChangeBroadcaster*) override;

    //==============================================================================
    void updateComponents();

    //==============================================================================
    void showPopupMenu (Point<int> position);

    //==============================================================================
    void beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                             AudioProcessorGraph::NodeAndChannel dest,
                             const MouseEvent&);
    void dragConnector (const MouseEvent&);
    void endDraggingConnector (const MouseEvent&);
	void timerCallback() override;
    //==============================================================================
    FilterGraph& graph;

private:
    OwnedArray<TwonkFilterComponent> nodes;
    OwnedArray<TwonkFilterConnector> connectors;
	std::unique_ptr <TwonkFilterConnector> draggingConnector;
    std::unique_ptr<PopupMenu> menu;

public:
    TwonkFilterComponent* getComponentForFilter (AudioProcessorGraph::NodeID) const;
	TwonkFilterConnector* getComponentForConnection (const AudioProcessorGraph::Connection&) const;
    TwonkFilterComponentPinWrapper* findPinAt (Point<float>) const;
	
	Image bgImage;
    Point<int> originalTouchPos;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphEditorPanel)
};




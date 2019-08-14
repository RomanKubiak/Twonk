/*
  ==============================================================================

    FilterConnector.h
    Created: 12 Jun 2019 10:14:20pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include "GraphEditorPanel.h"
#include "Filters/PluginGraph.h"
//==============================================================================
class TwonkFilterConnector : public Component, public SettableTooltipClient
{
	public:
		TwonkFilterConnector (GraphEditorPanel& p);
		void setInput (AudioProcessorGraph::NodeAndChannel newSource);
		void setOutput (AudioProcessorGraph::NodeAndChannel newDest);
		void dragStart (Point<float> pos);
		void dragEnd (Point<float> pos);
		void update();
		void resizeToFit();
		void getPoints (Point<float>& p1, Point<float>& p2) const;
		void paint (Graphics& g) override;
		bool hitTest (int x, int y) override;
		void mouseDown (const MouseEvent&) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		void resized() override;
		void getDistancesFromEnds (Point<float> p, double& distanceFromStart, double& distanceFromEnd) const;
		GraphEditorPanel& panel;
		PluginGraph& filterGraph;
		AudioProcessorGraph::Connection connection {{ {}, 0 }, { {}, 0 }};
		Point<float> lastInputPos, lastOutputPos;
		Path linePath, hitPath;
		bool dragging = false;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkFilterConnector)
};
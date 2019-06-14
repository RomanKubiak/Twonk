#pragma once
#include "../Filters/FilterGraph.h"
#include "TwonkFilterComponentPin.h"
#include "GraphEditorPanel.h"
#include "TwonkBubbleComponent.h"

//==============================================================================
class TwonkFilterComponent : public TwonkBubbleComponent, public Timer, private AudioProcessorParameter::Listener
{
	public:
		TwonkFilterComponent (GraphEditorPanel& p, AudioProcessorGraph::NodeID id);
		TwonkFilterComponent (const TwonkFilterComponent&) = delete;
		TwonkFilterComponent& operator= (const TwonkFilterComponent&) = delete;
		~TwonkFilterComponent() override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		// bool hitTest (int x, int y) override;
		//void paint (Graphics& g) override;
		//void resized() override;
		Point<float> getPinPos (int index, bool isInput) const;
		void update();
		AudioProcessor* getProcessor() const;
		void showPopupMenu();
		void testStateSaveLoad();
		void showWindow (PluginWindow::Type type);
		void timerCallback() override;
		void parameterValueChanged (int, float) override;
		void parameterGestureChanged (int, bool) override {}
	
		GraphEditorPanel& panel;
		FilterGraph& graph;
		const AudioProcessorGraph::NodeID pluginID;
		OwnedArray<TwonkFilterComponentPin> pins;
		int numInputs = 0, numOutputs = 0;
		int pinSize = 32;
		Point<int> originalPos;
		Font font {"Liberation Sans", 12.0f, Font::bold};
		int numIns = 0, numOuts = 0;
		DropShadowEffect shadow;
		std::unique_ptr<PopupMenu> menu;
		bool isSelected = false;
};
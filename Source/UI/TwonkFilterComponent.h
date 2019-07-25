#pragma once
#include "../Filters/FilterGraph.h"
#include "TwonkFilterComponentPin.h"
#include "GraphEditorPanel.h"
#include "Filters/InternalFilters.h"
//==============================================================================
class TwonkFilterComponent : public Component, public Timer, private AudioProcessorParameter::Listener, public Button::Listener
{
	public:
		TwonkFilterComponent (GraphEditorPanel& p, AudioProcessorGraph::NodeID id);
		TwonkFilterComponent (const TwonkFilterComponent&) = delete;
		TwonkFilterComponent& operator= (const TwonkFilterComponent&) = delete;
		~TwonkFilterComponent() override;
		void mouseDown (const MouseEvent& e) override;
		void mouseDrag (const MouseEvent& e) override;
		void mouseUp (const MouseEvent& e) override;
		//bool hitTest (int x, int y) override;
		void paint (Graphics& g) override;
		void resized() override;
		Point<float> getPinPos (int index, bool isInput) const;
		void update();
		AudioProcessor* getProcessor() const;
		void showPopupMenu();
		void testStateSaveLoad();
		void showWindow (PluginWindow::Type type);
		void timerCallback() override;
		void parameterValueChanged (int, float) override;
		void parameterGestureChanged (int, bool) override {}

		const AudioProcessorGraph::NodeID pluginID;
		Point<int> originalPos;
		
	private:
		Colour baseColour;
		void setType();
		void buttonClicked (Button* buttonThatWasClicked) override;
		void toggleOptions(const bool shouldBeVisible);
		ComponentDragger myDragger;
		std::unique_ptr<TextButton> removeButton;
		std::unique_ptr<TextButton> bypassButton;
		GraphEditorPanel& panel;
		OwnedArray<TwonkFilterComponentPinWrapper> wrappingPins;
		int numInputs = 0, numOutputs = 0;
		int pinSize;
		bool hitTest (int x, int y) override;
		int numIns = 0, numOuts = 0;
		std::unique_ptr<PopupMenu> menu;
		bool isSelected = false;
		bool isInternalIO;
		AudioProcessorGraph::AudioGraphIOProcessor::IODeviceType ioDeviceType;
		GlowEffect ge;
		Path roundingHexagon;
		Array <Point<float>> nodes;
};
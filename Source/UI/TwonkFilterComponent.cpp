#include "TwonkFilterComponent.h"

//==============================================================================
TwonkFilterComponent::TwonkFilterComponent(GraphEditorPanel& p, AudioProcessorGraph::NodeID id) 
	: panel (p), TwonkBubbleComponent(p.graph , id)
{
	if (auto f = graph.graph.getNodeForId (pluginID))
	{
		if (auto* processor = f->getProcessor())
		{
			if (auto* bypassParam = processor->getBypassParameter())
				bypassParam->addListener (this);
		}
	}

	setSize (200, 160);
}

TwonkFilterComponent::~TwonkFilterComponent()
{
		if (auto f = graph.graph.getNodeForId (pluginID))
		{
			if (auto* processor = f->getProcessor())
			{
				if (auto* bypassParam = processor->getBypassParameter())
					bypassParam->removeListener (this);
			}
		}
	}

void TwonkFilterComponent::mouseDown (const MouseEvent& e)
{
	originalPos = localPointToGlobal (Point<int>());

	toFront (true);

	if (e.mods.isPopupMenu())
		showPopupMenu();

	startTimer(450);
}

void TwonkFilterComponent::timerCallback()
{
	stopTimer();
	if (isMouseButtonDown(true))
	{
		toggleOptions(true);
		startTimer(2500);
	}
	else
	{
		toggleOptions(false);
		stopTimer();
	}
}

void TwonkFilterComponent::mouseDrag (const MouseEvent& e)
{
	stopTimer();
	if (!e.mods.isPopupMenu())
	{
		auto pos = originalPos + e.getOffsetFromDragStart();

		if (getParentComponent() != nullptr)
			pos = getParentComponent()->getLocalPoint (nullptr, pos);

		pos += getLocalBounds().getCentre();

		graph.setNodePosition (pluginID, {pos.x / (double)getParentWidth(), pos.y / (double)getParentHeight()});

		panel.updateComponents();
	}
}

void TwonkFilterComponent::mouseUp (const MouseEvent& e)
{
	if (e.mouseWasDraggedSinceMouseDown())
	{
		graph.setChangedFlag (true);
	}
	else if (e.getNumberOfClicks() == 2)
	{
		if (auto f = graph.graph.getNodeForId (pluginID))
			if (auto* w = graph.getOrCreateWindowFor (f, PluginWindow::Type::normal))
				w->toFront (true);
	}
	else if (e.getNumberOfClicks() == 2)
	{
		isSelected = !isSelected;
		repaint();
	}
}

void TwonkFilterComponent::resized()
{
	pinSize = _BASE * 0.25;
	if (auto f = graph.graph.getNodeForId (pluginID))
	{
		if (auto* processor = f->getProcessor())
		{
			for (auto* pin : pins)
			{
				const bool isInput = pin->isInput;
				auto channelIndex = pin->pin.channelIndex;
				int busIdx = 0;
				processor->getOffsetInBusBufferForAbsoluteChannelIndex (isInput, channelIndex, busIdx);

				const int total = isInput ? numIns : numOuts;
				const int index = pin->pin.isMIDI() ? (total - 1) : channelIndex;

				auto totalSpaces = static_cast<float> (total) + (static_cast<float> (jmax (0, processor->getBusCount (isInput) - 1)) * 0.5f);
				auto indexPos = static_cast<float> (index) + (static_cast<float> (busIdx) * 0.5f);

				pin->setBounds (proportionOfWidth ((1.0f + indexPos) / (totalSpaces + 1.0f)) - pinSize / 2,
					pin->isInput ? 0 : (getHeight() - pinSize),
					pinSize, pinSize);
			}
		}
	}
}

Point<float> TwonkFilterComponent::getPinPos (int index, bool isInput) const
{
	for (auto* pin : pins)
		if (pin->pin.channelIndex == index && isInput == pin->isInput)
			return getPosition().toFloat() + pin->getBounds().getCentre().toFloat();

	return {};
}

void TwonkFilterComponent::update()
{
	const AudioProcessorGraph::Node::Ptr f (graph.graph.getNodeForId (pluginID));
	jassert (f != nullptr);

	numIns = f->getProcessor()->getTotalNumInputChannels();
	if (f->getProcessor()->acceptsMidi())
		++numIns;

	numOuts = f->getProcessor()->getTotalNumOutputChannels();
	if (f->getProcessor()->producesMidi())
		++numOuts;

	int w = _BASE;
	int h = _BASE * 0.75f;

	w = jmax (w, (jmax (numIns, numOuts) + 1) * 20);

	//const int textWidth = font.getStringWidth (f->getProcessor()->getName());
	//w = jmax (w, 16 + jmin (textWidth, 300));
	//if (textWidth > 300)
	//	h = 100;

	setSize (w, h);

	setComponentName (f->getProcessor()->getName());
	setBypassed(f->isBypassed());
	{
		auto p = graph.getNodePosition (pluginID);
		setCentreRelative ((float)p.x, (float)p.y);
	}

	if (numIns != numInputs || numOuts != numOutputs)
	{
		numInputs = numIns;
		numOutputs = numOuts;

		pins.clear();

		for (int i = 0; i < f->getProcessor()->getTotalNumInputChannels(); ++i)
			addAndMakeVisible (pins.add (new TwonkFilterComponentPin (panel, {pluginID, i}, true)));

		if (f->getProcessor()->acceptsMidi())
			addAndMakeVisible (pins.add (new TwonkFilterComponentPin (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, true)));

		for (int i = 0; i < f->getProcessor()->getTotalNumOutputChannels(); ++i)
			addAndMakeVisible (pins.add (new TwonkFilterComponentPin (panel, {pluginID, i}, false)));

		if (f->getProcessor()->producesMidi())
			addAndMakeVisible (pins.add (new TwonkFilterComponentPin (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, false)));

		resized();
	}
}

AudioProcessor* TwonkFilterComponent::getProcessor() const
{
	if (auto node = graph.graph.getNodeForId (pluginID))
		return node->getProcessor();

	return {};
}

void TwonkFilterComponent::showPopupMenu()
{
	menu.reset (new PopupMenu);
	menu->addItem (1, "Delete this filter");
	menu->addItem (2, "Disconnect all pins");
	menu->addItem (3, "Toggle Bypass");

	if (getProcessor()->hasEditor())
	{
		menu->addSeparator();
		menu->addItem (10, "Show plugin GUI");
		menu->addItem (11, "Show all programs");
		menu->addItem (12, "Show all parameters");
		menu->addItem (14, "Show debug log");
	}

	menu->addSeparator();
	menu->addItem (20, "Configure Audio I/O");
	menu->addItem (21, "Test state save/load");

	menu->showMenuAsync ({}, ModalCallbackFunction::create
	([this](int r) {
		switch (r)
		{
		case 1:   graph.graph.removeNode (pluginID); break;
		case 2:   graph.graph.disconnectNode (pluginID); break;
		case 3:
		{
			if (auto* node = graph.graph.getNodeForId (pluginID))
				node->setBypassed (!node->isBypassed());

			repaint();
			update();
			resized();

			break;
		}
		case 10:  showWindow (PluginWindow::Type::normal); break;
		case 11:  showWindow (PluginWindow::Type::programs); break;
		case 12:  showWindow (PluginWindow::Type::generic); break;
		case 14:  showWindow (PluginWindow::Type::debug); break;
		case 20:  showWindow (PluginWindow::Type::audioIO); break;
		case 21:  testStateSaveLoad(); break;

		default:  break;
		}
	}));
}

void TwonkFilterComponent::testStateSaveLoad()
{
	if (auto* processor = getProcessor())
	{
		MemoryBlock state;
		processor->getStateInformation (state);
		processor->setStateInformation (state.getData(), (int)state.getSize());
	}
}

void TwonkFilterComponent::showWindow (PluginWindow::Type type)
{
	if (auto node = graph.graph.getNodeForId (pluginID))
		if (auto* w = graph.getOrCreateWindowFor (node, type))
			w->toFront (true);
}

void TwonkFilterComponent::parameterValueChanged (int, float)
{
	repaint();
}
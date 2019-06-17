#include "TwonkFilterComponent.h"

//==============================================================================
TwonkFilterComponent::TwonkFilterComponent(GraphEditorPanel& p, AudioProcessorGraph::NodeID id) 
	: panel (p), graph (p.graph), pluginID (id)
{
	// shadow.setShadowProperties (DropShadow (Colours::black.withAlpha (0.5f), 3, {0, 1}));
	// setComponentEffect (&shadow);

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
	DBG("TwonkFilterComponent::mouseDown");
	originalPos = localPointToGlobal (Point<int>());

	toFront (true);

	if (e.mods.isPopupMenu())
		showPopupMenu();	
}

void TwonkFilterComponent::mouseDrag (const MouseEvent& e)
{
	DBG("TwonkFilterComponent::mouseDrag");
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
	DBG("TwonkFilterComponent::mouseUp");
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

/*bool TwonkFilterComponent::hitTest (int x, int y)
{
	for (auto* child : getChildren())
		if (child->getBounds().contains (x, y))
			return true;

	return x >= 3 && x < getWidth() - 6 && y >= pinSize && y < getHeight() - pinSize;
}
*/

/*void TwonkFilterComponent::paint (Graphics& g)
{
	auto boxArea = getLocalBounds().reduced (4, pinSize);
	bool isBypassed = false;

	if (auto* f = graph.graph.getNodeForId (pluginID))
		isBypassed = f->isBypassed();

	auto boxColour = Colours::black.withAlpha(0.9f);

	if (isBypassed)
		boxColour = boxColour.brighter();

	if (isSelected)
		boxColour = boxColour.overlaidWith(Colours::aqua);


	g.setColour (boxColour.brighter(0.5f));
	g.drawRoundedRectangle (boxArea.toFloat(), 8.0f, 4.0f);

	g.setColour (boxColour);
	g.fillRoundedRectangle (boxArea.toFloat(), 8.0f);

	g.setColour (Colours::white);
	g.setFont (font);
	g.drawFittedText (getName(), boxArea, Justification::centred, 2);
}*/

void TwonkFilterComponent::resized()
{
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

	int w = 128;
	int h = 128;

	w = jmax (w, (jmax (numIns, numOuts) + 1) * 20);

	//const int textWidth = font.getStringWidth (f->getProcessor()->getName());
	//w = jmax (w, 16 + jmin (textWidth, 300));
	//if (textWidth > 300)
	//	h = 100;

	setSize (w, h);

	setComponentName (f->getProcessor()->getName());

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

void TwonkFilterComponent::timerCallback()
{
}

void TwonkFilterComponent::parameterValueChanged (int, float)
{
	repaint();
}
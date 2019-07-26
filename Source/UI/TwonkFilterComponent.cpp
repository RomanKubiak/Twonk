#include "TwonkFilterComponent.h"
#include "Twonk.h"

//==============================================================================
TwonkFilterComponent::TwonkFilterComponent(GraphEditorPanel& p, AudioProcessorGraph::NodeID id) 
	: panel (p), pluginID(id)
{
	if (auto f = panel.graph.graph.getNodeForId (pluginID))
	{
		if (auto* processor = f->getProcessor())
		{
			if (auto* bypassParam = processor->getBypassParameter())
				bypassParam->addListener (this);
		}
	}

	removeButton.reset (new TextButton ("new button"));
	addAndMakeVisible (removeButton.get());
	removeButton->setButtonText (TRANS("Remove"));
	removeButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
	removeButton->addListener (this);
	removeButton->setColour (TextButton::buttonColourId, Colour (0xffff2121));

	bypassButton.reset (new TextButton ("new button"));
	addAndMakeVisible (bypassButton.get());
	bypassButton->setButtonText (TRANS("Bypass"));
	bypassButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
	bypassButton->addListener (this);
	bypassButton->setColour (TextButton::buttonColourId, Colour (0xff20d7d7));

	setSize (BUBBLE_SIZE, BUBBLE_SIZE);
	ge.setGlowProperties(BUBBLE_SIZE * 0.06f, Colours::red.withAlpha(0.5f));
	//setComponentEffect(&ge);

	removeButton->setAlwaysOnTop(true);
	bypassButton->setAlwaysOnTop(true);
	toggleOptions(false);
	setType();
}

void TwonkFilterComponent::setType()
{
	isInternalIO = false;
	baseColour = Colours::white;
	AudioProcessorGraph::Node *node = panel.graph.graph.getNodeForId(pluginID);
	if (node)
	{
		AudioProcessor *processor = node->getProcessor();
		if (processor)
		{
			{
				AudioProcessorGraph::AudioGraphIOProcessor *internalIO = dynamic_cast<AudioProcessorGraph::AudioGraphIOProcessor *>(processor);
				if (internalIO)
				{
					baseColour = Colours::red;
					isInternalIO = true;
					ioDeviceType = internalIO->getType();
				}
			}
		}
	}
}
TwonkFilterComponent::~TwonkFilterComponent()
{
		if (auto f = panel.graph.graph.getNodeForId (pluginID))
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
	myDragger.startDraggingComponent (this, e);
	startTimer(450);
}

void TwonkFilterComponent::mouseDrag (const MouseEvent& e)
{
	myDragger.dragComponent (this, e, nullptr);

	auto pos = originalPos + e.getOffsetFromDragStart();

	if (getParentComponent() != nullptr)
		pos = getParentComponent()->getLocalPoint (nullptr, pos);

	pos += getLocalBounds().getCentre();

	panel.graph.setNodePosition (pluginID, { pos.x / (double)getParentWidth(), pos.y / (double)getParentHeight() });

	panel.updateComponents();
	stopTimer();
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

void TwonkFilterComponent::paint(Graphics &g)
{
	g.setColour(Colours::white);
	g.drawRect(getLocalBounds(), 1.0f);
	g.setColour(baseColour.withAlpha(0.3f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(BUBBLE_SIZE * 0.02f));
}


void TwonkFilterComponent::mouseUp (const MouseEvent& e)
{
	if (e.mouseWasDraggedSinceMouseDown())
	{
		panel.graph.setChangedFlag (true);
	}
	else if (e.getNumberOfClicks() == 2)
	{
		if (auto f = panel.graph.graph.getNodeForId (pluginID))
			if (auto* w = panel.graph.getOrCreateWindowFor (f, PluginWindow::Type::normal))
				w->toFront (true);
	}
	else if (e.getNumberOfClicks() == 2)
	{
		isSelected = !isSelected;
		repaint();
	}
}

void TwonkFilterComponent::buttonClicked (Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == removeButton.get())
	{
		panel.graph.graph.removeNode (pluginID);
	}
	else if (buttonThatWasClicked == bypassButton.get())
	{
	}
}

void TwonkFilterComponent::resized()
{
	pinSize = BUBBLE_SIZE * 0.25;

	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, BUBBLE_SIZE * 0.35f, float_Pi*0.5f);

	int l = roundingHexagon.getLength();
	nodes[0] = roundingHexagon.getPointAlongPath(l / 12.0f).translated(BUBBLE_SIZE * 0.1f, BUBBLE_SIZE * 0.1f);
	nodes[1] = roundingHexagon.getPointAlongPath((l / 12.0f) * 3).translated(0, BUBBLE_SIZE * 0.1f);
	nodes[2] = roundingHexagon.getPointAlongPath((l / 12.0f) * 5).translated(-BUBBLE_SIZE * 0.1f, BUBBLE_SIZE * 0.1f);
	nodes[3] = roundingHexagon.getPointAlongPath((l / 12.0f) * 7).translated(-BUBBLE_SIZE * 0.1f, -BUBBLE_SIZE * 0.1f);
	nodes[4] = roundingHexagon.getPointAlongPath((l / 12.0f) * 9).translated(0, -BUBBLE_SIZE * 0.1f);
	nodes[5] = roundingHexagon.getPointAlongPath((l / 12.0f) * 11).translated(BUBBLE_SIZE * 0.1f, -BUBBLE_SIZE * 0.1f);

	if (auto f = panel.graph.graph.getNodeForId (pluginID))
	{
		if (auto* processor = f->getProcessor())
		{
			for (auto* pin : wrappingPins)
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

	removeButton->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.3958f));
	bypassButton->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6042f), proportionOfWidth (1.0000f), proportionOfHeight (0.3958f));
}

Point<float> TwonkFilterComponent::getPinPos (int index, bool isInput) const
{
	for (auto* pin : wrappingPins)
		if (pin->pin.channelIndex == index && isInput == pin->isInput)
			return getPosition().toFloat() + pin->getBounds().getCentre().toFloat();

	return {};
}

bool TwonkFilterComponent::hitTest (int x, int y)
{
	for (auto* child : getChildren())
		if (child->getBounds().contains (x, y))
			return true;

	return x >= 3 && x < getWidth() - 6 && y >= pinSize && y < getHeight() - pinSize;
}

void TwonkFilterComponent::update()
{
	const AudioProcessorGraph::Node::Ptr f (panel.graph.graph.getNodeForId (pluginID));
	jassert (f != nullptr);

	numIns = f->getProcessor()->getTotalNumInputChannels();
	if (f->getProcessor()->acceptsMidi())
		++numIns;

	numOuts = f->getProcessor()->getTotalNumOutputChannels();
	if (f->getProcessor()->producesMidi())
		++numOuts;

	int w = BUBBLE_SIZE;
	int h = BUBBLE_SIZE;

	w = jmax (w, (jmax (numIns, numOuts) + 1) * 20);

	setSize (w, h);

	{
		auto p = panel.graph.getNodePosition (pluginID);
		setCentreRelative ((float)p.x, (float)p.y);
	}

	if (numIns != numInputs || numOuts != numOutputs)
	{
		numInputs = numIns;
		numOutputs = numOuts;

		wrappingPins.clear();

		for (int i = 0; i < f->getProcessor()->getTotalNumInputChannels(); ++i)
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, i}, true)));

		if (f->getProcessor()->acceptsMidi())
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, true)));

		for (int i = 0; i < f->getProcessor()->getTotalNumOutputChannels(); ++i)
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, i}, false)));

		if (f->getProcessor()->producesMidi())
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, false)));
		
		resized();
	}
}

AudioProcessor* TwonkFilterComponent::getProcessor() const
{
	if (auto node = panel.graph.graph.getNodeForId (pluginID))
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
		case 1:   panel.graph.graph.removeNode (pluginID); break;
		case 2:   panel.graph.graph.disconnectNode (pluginID); break;
		case 3:
		{
			if (auto* node = panel.graph.graph.getNodeForId (pluginID))
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
	if (auto node = panel.graph.graph.getNodeForId (pluginID))
		if (auto* w = panel.graph.getOrCreateWindowFor (node, type))
			w->toFront (true);
}

void TwonkFilterComponent::parameterValueChanged (int, float)
{
	repaint();
}
void TwonkFilterComponent::toggleOptions(const bool shouldBeVisible)
{
	removeButton->setVisible(shouldBeVisible);
	bypassButton->setVisible(shouldBeVisible);
}

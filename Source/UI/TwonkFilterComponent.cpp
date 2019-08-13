#include "TwonkFilterComponent.h"
#include "Twonk.h"

//==============================================================================
TwonkFilterComponent::TwonkFilterComponent(GraphEditorPanel& p, AudioProcessorGraph::NodeID id) 
	: panel (p), pluginID(id), componentSize(BUBBLE_SIZE)
{
	if (auto f = panel.graph->graph.getNodeForId (pluginID))
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

	ge.setGlowProperties(BUBBLE_SIZE * 0.06f, Colours::red.withAlpha(0.5f));
	//setComponentEffect(&ge);
	
	removeButton->setAlwaysOnTop(true);
	bypassButton->setAlwaysOnTop(true);
	toggleOptions(false);
	setType();
	update();

	if (!isInternalIO)
	{
		filterImage = ImageCache::getFromMemory(BinaryData::icon_block_64_png, BinaryData::icon_block_64_pngSize);
		const AudioProcessorGraph::Node::Ptr f (panel.graph->graph.getNodeForId (pluginID));
		jassert (f != nullptr);
		numIns = f->getProcessor()->getTotalNumInputChannels();
		if (f->getProcessor()->acceptsMidi())
			++numIns;

		numOuts = f->getProcessor()->getTotalNumOutputChannels();
		if (f->getProcessor()->producesMidi())
			++numOuts;
		setName(f->getProcessor()->getName());
		if (f->getProcessor()->getTotalNumInputChannels() > 0)
			pinAudioInput.reset(new TwonkFilterComponentPinWrapper(*this, p, AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode));

		if (f->getProcessor()->getTotalNumOutputChannels() > 0)
			pinAudioOutput.reset(new TwonkFilterComponentPinWrapper(*this, p, AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode));

		if (f->getProcessor()->acceptsMidi())
			pinMIDIInput.reset(new TwonkFilterComponentPinWrapper(*this, p, AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode));

		if (f->getProcessor()->producesMidi())
			pinMIDIOutput.reset(new TwonkFilterComponentPinWrapper(*this, p, AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode));

		addAndMakeVisible(pinAudioInput.get());
		addAndMakeVisible(pinAudioOutput.get());
		addAndMakeVisible(pinMIDIInput.get());
		addAndMakeVisible(pinMIDIOutput.get());
	}
	else
	{
		if (ioDeviceType == AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode
			|| ioDeviceType == AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode)
		{
			filterImage = ImageCache::getFromMemory(BinaryData::icon_midi_64_png, BinaryData::icon_midi_64_pngSize);
		}
		else
		{
			filterImage = ImageCache::getFromMemory(BinaryData::icon_speaker_64_png, BinaryData::icon_speaker_64_pngSize);
		}
	}
}

TwonkFilterComponent::~TwonkFilterComponent()
{
	if (auto f = panel.graph->graph.getNodeForId (pluginID))
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

	panel.graph->setNodePosition (pluginID, { pos.x / (double)getParentWidth(), pos.y / (double)getParentHeight() });

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
	g.setColour(baseColour.contrasting(0.5f));
	g.setFont(getDefaultTwonkSansFont());
	g.drawText(getName(), getLocalBounds(), Justification::centredBottom, true);
	g.setColour(baseColour.contrasting(0.1f));
	g.drawImage(filterImage, getLocalBounds().toFloat().reduced(BUBBLE_SIZE * 0.35f), RectanglePlacement::stretchToFit, true);
	g.setColour(baseColour.withAlpha(0.3f));
	g.fillPath(roundingHexagon);
	g.setColour(baseColour);
	g.strokePath(roundingHexagon, PathStrokeType(BUBBLE_SIZE * 0.02f));
}


void TwonkFilterComponent::mouseUp (const MouseEvent& e)
{
	if (e.mouseWasDraggedSinceMouseDown())
	{
		panel.graph->setChangedFlag (true);
	}
	else if (e.getNumberOfClicks() == 2)
	{
		if (auto f = panel.graph->graph.getNodeForId (pluginID))
			if (auto* w = panel.graph->getOrCreateWindowFor (f, PluginWindow::Type::normal))
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
		panel.graph->graph.removeNode (pluginID);
	}
	else if (buttonThatWasClicked == bypassButton.get())
	{
	}
}

void TwonkFilterComponent::setType()
{
	isInternalIO = false;
	baseColour = Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_OUT);
	AudioProcessorGraph::Node *node = panel.graph->graph.getNodeForId(pluginID);
	if (node)
	{
		AudioProcessor *processor = node->getProcessor();
		if (processor)
		{
			{
				AudioProcessorGraph::AudioGraphIOProcessor *internalIO = dynamic_cast<AudioProcessorGraph::AudioGraphIOProcessor *>(processor);
				if (internalIO)
				{					
					isInternalIO = true;
					ioDeviceType = internalIO->getType();

					if (internalIO->acceptsMidi())
						baseColour = Colour(BUBBLE_COLOUR_INTERNAL_MIDI_IN);
					if (internalIO->producesMidi())
						baseColour = Colour(BUBBLE_COLOUR_INTERNAL_MIDI_OUT);
					if (internalIO->getTotalNumOutputChannels()>0)
						baseColour = Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_OUT);
					if (internalIO->getTotalNumInputChannels() > 0)
						baseColour = Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_IN);
				}
				else
				{
					if (processor->getTotalNumInputChannels() > 0)
						baseColour = Colour(BUBBLE_COLOUR_PLUGIN_FX);
					else
						baseColour = Colour(BUBBLE_COLOUR_PLUGIN_SYNTH);

					isInternalIO = false;
				}
			}
		}
	}
}

void TwonkFilterComponent::resized()
{
	roundingHexagon.clear();
	roundingHexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, BUBBLE_SIZE * 0.3f, float_Pi*0.5f);
	if (!isInternalIO)
	{
		float offset = NODE_SIZE * 0.5f;
		if (pinAudioInput)
			pinAudioInput->setCentrePosition(offset, getHeight() - offset);
		if (pinMIDIInput)
			pinMIDIInput->setCentrePosition(offset, offset);
		if (pinMIDIOutput)
			pinMIDIOutput->setCentrePosition(getWidth() - offset, offset);
		if (pinAudioOutput)
			pinAudioOutput->setCentrePosition(getWidth() - offset, getHeight() - offset);
	}
		
	removeButton->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.3958f));
	bypassButton->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6042f), proportionOfWidth (1.0000f), proportionOfHeight (0.3958f));
}

Point<float> TwonkFilterComponent::getPinPos (int index, bool isInput) const
{
	if (isInput)
	{
		if (index == 0)
			return pinAudioInput->getBounds().getCentre().toFloat();
		if (index == 1)
			return pinMIDIInput->getBounds().getCentre().toFloat();
	}
	else
	{
		if (index == 0)
			return pinAudioOutput->getBounds().getCentre().toFloat();
		if (index == 1)
			return pinMIDIOutput->getBounds().getCentre().toFloat();
	}
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
	const AudioProcessorGraph::Node::Ptr f (panel.graph->graph.getNodeForId (pluginID));
	jassert (f != nullptr);

	numIns = f->getProcessor()->getTotalNumInputChannels();
	if (f->getProcessor()->acceptsMidi())
		++numIns;

	numOuts = f->getProcessor()->getTotalNumOutputChannels();
	if (f->getProcessor()->producesMidi())
		++numOuts;

	int w = componentSize;
	int h = componentSize;

	if (!isInternalIO)
		w = jmax (w, (jmax (numIns, numOuts) + 1) * 20);

	setSize (w, h);

	{
		auto p = panel.graph->getNodePosition (pluginID);
		setCentreRelative ((float)p.x, (float)p.y);
	}

	if (numIns != numInputs || numOuts != numOutputs)
	{
		numInputs = numIns;
		numOutputs = numOuts;
		
		/*for (int i = 0; i < f->getProcessor()->getTotalNumInputChannels(); ++i)
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, i}, true)));

		if (f->getProcessor()->acceptsMidi())
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, true)));

		for (int i = 0; i < f->getProcessor()->getTotalNumOutputChannels(); ++i)
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, i}, false)));

		if (f->getProcessor()->producesMidi())
			addAndMakeVisible (wrappingPins.add (new TwonkFilterComponentPinWrapper (panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, false)));
		*/
		
	}
	resized();
}

AudioProcessor* TwonkFilterComponent::getProcessor() const
{
	if (auto node = panel.graph->graph.getNodeForId (pluginID))
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
		case 1:   panel.graph->graph.removeNode (pluginID); break;
		case 2:   panel.graph->graph.disconnectNode (pluginID); break;
		case 3:
		{
			if (auto* node = panel.graph->graph.getNodeForId (pluginID))
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
	if (auto node = panel.graph->graph.getNodeForId (pluginID))
		if (auto* w = panel.graph->getOrCreateWindowFor (node, type))
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

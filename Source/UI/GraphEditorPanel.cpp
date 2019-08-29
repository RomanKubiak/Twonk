#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphEditorPanel.h"
#include "../Filters/InternalPlugins.h"
#include "MainHostWindow.h"
#include "TwonkToolBar.h"
#include "TwonkToolBarButton.h"
#include "TwonkFilterComponent.h"
#include "TwonkProgramMenu.h"
#include "Twonk.h"
#include "TwonkProgramList.h"
/**
  GraphEditorPanel
 */
struct GraphEditorPanel::PinComponent   : public Component,
                                          public SettableTooltipClient
{
    PinComponent (GraphEditorPanel& p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn)
        : panel (p), graph (p.graph), pin (pinToUse), isInput (isIn)
    {
        if (auto node = graph.graph.getNodeForId (pin.nodeID))
        {
            String tip;

            if (pin.isMIDI())
            {
				if (isInput)
					baseColour = Colours::red;
				else
					baseColour = Colours::red.brighter(0.5f);

                tip = isInput ? "MIDI Input"
                              : "MIDI Output";
				
            }
            else
            {
				if (isInput)
					baseColour = Colours::green;
				else
					baseColour = Colours::green.brighter(0.5f);

                auto& processor = *node->getProcessor();
                auto channel = processor.getOffsetInBusBufferForAbsoluteChannelIndex (isInput, pin.channelIndex, busIdx);

                if (auto* bus = processor.getBus (isInput, busIdx))
                    tip = bus->getName() + ": " + AudioChannelSet::getAbbreviatedChannelTypeName (bus->getCurrentLayout().getTypeOfChannel (channel));
                else
                    tip = (isInput ? "Main Input: "
                                   : "Main Output: ") + String (pin.channelIndex + 1);

            }

            setTooltip (tip);
        }

        setSize (16, 16);
    }

    void paint (Graphics& g) override
    {
		Path hexagon;
		hexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.5f, float_Pi*0.5f);
		g.setColour(baseColour.contrasting(0.1f));
		g.setFont(getDefaultTwonkMonoFont().withHeight((float)(NODE_SIZE * 0.7f)));
		g.drawText(text, getLocalBounds(), Justification::centred, false);
		g.setColour(baseColour.withAlpha(0.4f));
		g.fillPath(hexagon);
		g.setColour(baseColour.withAlpha(0.5f));
		g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.1f));
    }

	void setText(const String &_text)
	{
		text = _text;
		repaint();
	}

    void mouseDown (const MouseEvent& e) override
    {
        AudioProcessorGraph::NodeAndChannel dummy { {}, 0 };

        panel.beginConnectorDrag (isInput ? dummy : pin,
                                  isInput ? pin : dummy,
                                  e);
    }

    void mouseDrag (const MouseEvent& e) override
    {
        panel.dragConnector (e);
    }

    void mouseUp (const MouseEvent& e) override
    {
        panel.endDraggingConnector (e);
    }

    GraphEditorPanel& panel;
    PluginGraph& graph;
    AudioProcessorGraph::NodeAndChannel pin;
    const bool isInput;
    int busIdx = 0;
	Colour baseColour;
	Image pinImage;
	String text;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PinComponent)
};

/**
  GraphEditorPanel::PluginComponent
 */
struct GraphEditorPanel::PluginComponent   : public Component,
                                             public Timer,
                                             private AudioProcessorParameter::Listener
{
    PluginComponent (GraphEditorPanel& p, AudioProcessorGraph::NodeID id)  : panel (p), graph (p.graph), pluginID (id)
    {
        shadow.setShadowProperties (DropShadow (Colours::black.withAlpha (0.5f), 3, { 0, 1 }));
        setComponentEffect (&shadow);

        if (auto f = graph.graph.getNodeForId (pluginID))
        {
            if (auto* processor = f->getProcessor())
            {
                if (auto* bypassParam = processor->getBypassParameter())
                    bypassParam->addListener (this);
            }
        }

        setSize (150, 60);
    }

    PluginComponent (const PluginComponent&) = delete;
    PluginComponent& operator= (const PluginComponent&) = delete;

    ~PluginComponent() override
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

    void mouseDown (const MouseEvent& e) override
    {
        originalPos = localPointToGlobal (Point<int>());

        toFront (true);

        if (isOnTouchDevice())
        {
            startTimer (750);
        }
        else
        {
            if (e.mods.isPopupMenu())
                showPopupMenu();
        }
    }

    void mouseDrag (const MouseEvent& e) override
    {
        if (isOnTouchDevice() && e.getDistanceFromDragStart() > 5)
            stopTimer();

        if (! e.mods.isPopupMenu())
        {
            auto pos = originalPos + e.getOffsetFromDragStart();

            if (getParentComponent() != nullptr)
                pos = getParentComponent()->getLocalPoint (nullptr, pos);

            pos += getLocalBounds().getCentre();

            graph.setNodePosition (pluginID,
                                   { pos.x / (double) getParentWidth(),
                                     pos.y / (double) getParentHeight() });

            panel.updateComponents();
        }
    }

    void mouseUp (const MouseEvent& e) override
    {
        if (isOnTouchDevice())
        {
            stopTimer();
            callAfterDelay (250, []() { PopupMenu::dismissAllActiveMenus(); });
        }

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
    }

	Path getHexagonPath(Rectangle<int> area)
	{
		Path hexagon;
		hexagon.addPolygon(area.getCentre().toFloat(), 6, area.getWidth() * 0.28f, float_Pi*0.5f);

		return (hexagon);
	}

    bool hitTest (int x, int y) override
    {
        for (auto* child : getChildren())
            if (child->getBounds().contains (x, y))
                return true;

        return x >= 3 && x < getWidth() - 6 && y >= pinSize && y < getHeight() - pinSize;
    }

	FilterType getFilterType(AudioProcessorGraph::Node *node)
	{
		FilterType type;
		if (auto *processor = node->getProcessor())
		{
			if (auto internalIO = dynamic_cast<AudioProcessorGraph::AudioGraphIOProcessor *>(processor))
			{
				auto ioDeviceType = internalIO->getType();
				switch (ioDeviceType)
				{
				case  AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode:
					type = InternalAudioInput;
					break;
				case AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode:
					type = InternalAudioOutput;
					break;
				case AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode:
					type = InternalMidiInput;
					break;
				case AudioProcessorGraph::AudioGraphIOProcessor::midiOutputNode:
					type = InternalMidiOutpout;
					break;
				default:
					type = FuckIfIKnow;
					break;
				}
			}

			if (processor->isMidiEffect())
			{
				type = PluginMidiEffect;
			}
			else if (processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() > 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynthWithInput;
			}
			else if (processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() == 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynthWithInput;
			}
			else if (!processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() > 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginAudioEffect;
			}

			else if (processor->acceptsMidi() &&
				processor->producesMidi() &&
				processor->getTotalNumInputChannels() == 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynth;
			}
			else
			{
				type = FuckIfIKnow;
			}
		}

		return (type);
	}

	Colour getColourForFilterType(FilterType type)
	{
		switch (type)
		{
			case InternalAudioInput:
				return (Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_IN));
			case InternalAudioOutput:
				return (Colour(BUBBLE_COLOUR_INTERNAL_AUDIO_OUT));
			case InternalMidiInput:
				return (Colour(BUBBLE_COLOUR_INTERNAL_MIDI_IN));
			case InternalMidiOutpout:
				return (Colour(BUBBLE_COLOUR_INTERNAL_MIDI_OUT));
			case InternalEffect:
				return (Colour(BUBBLE_COLOUR_INTERNAL_PLUGIN_FX));
			case InternalSynth:
				return (Colour(BUBBLE_COLOUR_INTERNAL_SYNTH));
			case PluginAudioEffect:
				return (Colour(BUBBLE_COLOUR_PLUGIN_FX));
			case PluginSynth:
				return (Colour(BUBBLE_COLOUR_PLUGIN_SYNTH));
			case PluginSynthWithInput:
				return (Colour(BUBBLE_COLOUR_PLUGIN_SYNTH_WITH_INPUT));
			default:
				return (Colours::violet);
		}
	}

	Image getImageForFilter(FilterType type)
	{

		switch (type)
		{
		case InternalAudioInput:
			return (IMG(audio_input_png));
		case InternalAudioOutput:
			return (IMG(audio_output_png));
		case InternalMidiInput:
			return (IMG(midi_input_png));
		case InternalMidiOutpout:
			return (IMG(midi_output_png));
		case InternalEffect:
			return (IMG(icon_plugin_internal_png));
		case InternalSynth:
			return (IMG(icon_synth_png));
		case PluginAudioEffect:
			return (IMG(icon_effect_png));
		case PluginSynth:
			return (IMG(icon_synth_png));
		case PluginSynthWithInput:
			return (IMG(icon_synth_png));
		case PluginMidiEffect:
			return (IMG(icon_plugin_midi_png));
		case FuckIfIKnow:
			return(IMG(icon_plugin_external_png));
		default:
			return (IMG(icon_question_jpg));
		}
	}

    void paint (Graphics& g) override
    {
		auto boxArea = getLocalBounds();
        bool isBypassed = false;
		Colour boxColour;

		FilterType ft;
		if (auto* f = graph.graph.getNodeForId (pluginID))
		{
			isBypassed = f->isBypassed();
			ft = getFilterType(f);
		}

		if (auto* f = graph.graph.getNodeForId (pluginID))
		{
			boxColour = getColourForFilterType (ft);

			if (isBypassed)
				boxColour = boxColour.overlaidWith(Colours::white).brighter();

			g.setColour (boxColour);
		}
		//g.setColour(Colours::red);
		//g.drawRect(getLocalBounds(), 1.0f);
		g.setColour (Colours::white);
		g.setFont (getDefaultTwonkSansFont());
		g.drawFittedText (getName(), boxArea, Justification::centredBottom, 2);
		g.setColour(boxColour.contrasting(0.1f));

		g.drawImage(getImageForFilter(ft), boxArea.reduced(getWidth() * 0.35f).toFloat(), RectanglePlacement::onlyReduceInSize, true);
		Path hexagon = getHexagonPath(boxArea);
		g.setColour(boxColour.withAlpha(0.3f));
		g.fillPath(hexagon);
		g.setColour(boxColour);
		g.strokePath(hexagon, PathStrokeType(1.0f));
    }

    void resized() override
    {
		bool hasMidiInputPin = false;
		bool hasMidiOutputPin = false;
        if (auto f = graph.graph.getNodeForId (pluginID))
        {
            if (auto* processor = f->getProcessor())
            {
                for (auto* pin : pins)
                {
					if (pin->pin.isMIDI())
					{
						if (pin->isInput)
						{
							pin->setBounds(0, 0, NODE_SIZE, NODE_SIZE);
						}
						else
						{
							pin->setBounds(BUBBLE_SIZE - NODE_SIZE, BUBBLE_SIZE - NODE_SIZE, NODE_SIZE, NODE_SIZE);
						}
					}
					else
					{
						if (processor->isMidiEffect())
						{
							pin->setVisible(false);
							continue;
						}

						auto channelIndex = pin->pin.channelIndex;
						pin->setText(String(channelIndex));

						if (pin->isInput)
						{
							if (processor->getTotalNumInputChannels() <= 4)
							{
								pin->setBounds(0, processor->acceptsMidi() ? (NODE_SIZE * (channelIndex + 1)) : (NODE_SIZE * (channelIndex)), NODE_SIZE, NODE_SIZE);
							}
						}
						else
						{
							if (processor->getTotalNumOutputChannels() <= 4)
							{
								pin->setBounds(BUBBLE_SIZE - NODE_SIZE, processor->producesMidi() ? 0 : (BUBBLE_SIZE - (NODE_SIZE * (channelIndex+1))), NODE_SIZE, NODE_SIZE);
							}
							else if (processor->getTotalNumOutputChannels() > 4)
							{
								if (channelIndex < 4)
								{
									pin->setBounds(BUBBLE_SIZE - NODE_SIZE, processor->producesMidi() ? 0 : (BUBBLE_SIZE - (NODE_SIZE * (channelIndex + 1))), NODE_SIZE, NODE_SIZE);
								}
								else if (channelIndex < 6)
									pin->setBounds((channelIndex - 3)*NODE_SIZE, BUBBLE_SIZE - NODE_SIZE, NODE_SIZE, NODE_SIZE);
								else if (channelIndex < 8)
									pin->setBounds((channelIndex - 5)*NODE_SIZE, 0, NODE_SIZE, NODE_SIZE);
							}
						}
					}
                }
            }
        }
    }

    Point<float> getPinPos (int index, bool isInput) const
    {
        for (auto* pin : pins)
            if (pin->pin.channelIndex == index && isInput == pin->isInput)
                return getPosition().toFloat() + pin->getBounds().getCentre().toFloat();

        return {};
    }

    void update()
    {
        const AudioProcessorGraph::Node::Ptr f (graph.graph.getNodeForId (pluginID));
        jassert (f != nullptr);

        numIns = f->getProcessor()->getTotalNumInputChannels();
        if (f->getProcessor()->acceptsMidi())
            ++numIns;

        numOuts = f->getProcessor()->getTotalNumOutputChannels();
        if (f->getProcessor()->producesMidi())
            ++numOuts;

		int w = BUBBLE_SIZE;
		int h = BUBBLE_SIZE;

        setSize (w, h);

        setName (f->getProcessor()->getName());

        {
            auto p = graph.getNodePosition (pluginID);
            setCentreRelative ((float) p.x, (float) p.y);
        }

        if (numIns != numInputs || numOuts != numOutputs)
        {
            numInputs = numIns;
            numOutputs = numOuts;

            pins.clear();

            for (int i = 0; i < f->getProcessor()->getTotalNumInputChannels(); ++i)
                addAndMakeVisible (pins.add (new PinComponent (panel, { pluginID, i }, true)));

            if (f->getProcessor()->acceptsMidi())
                addAndMakeVisible (pins.add (new PinComponent (panel, { pluginID, AudioProcessorGraph::midiChannelIndex }, true)));

            for (int i = 0; i < f->getProcessor()->getTotalNumOutputChannels(); ++i)
                addAndMakeVisible (pins.add (new PinComponent (panel, { pluginID, i }, false)));

            if (f->getProcessor()->producesMidi())
                addAndMakeVisible (pins.add (new PinComponent (panel, { pluginID, AudioProcessorGraph::midiChannelIndex }, false)));

            resized();
        }
    }

    AudioProcessor* getProcessor() const
    {
        if (auto node = graph.graph.getNodeForId (pluginID))
            return node->getProcessor();

        return {};
    }

    void showPopupMenu()
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
           #if JUCE_WINDOWS && JUCE_WIN_PER_MONITOR_DPI_AWARE
            auto isTicked = false;
            if (auto* node = graph.graph.getNodeForId (pluginID))
                isTicked = node->properties["DPIAware"];

            menu->addItem (13, "Enable DPI awareness", true, isTicked);
           #endif
            menu->addItem (14, "Show debug log");
        }

        menu->addSeparator();
        menu->addItem (20, "Configure Audio I/O");
        menu->addItem (21, "Test state save/load");

        menu->showMenuAsync ({}, ModalCallbackFunction::create
                             ([this] (int r) {
        switch (r)
        {
            case 1:   graph.graph.removeNode (pluginID); break;
            case 2:   graph.graph.disconnectNode (pluginID); break;
            case 3:
            {
                if (auto* node = graph.graph.getNodeForId (pluginID))
                    node->setBypassed (! node->isBypassed());

                repaint();

                break;
            }
            case 10:  showWindow (PluginWindow::Type::normal); break;
            case 11:  showWindow (PluginWindow::Type::programs); break;
            case 12:  showWindow (PluginWindow::Type::generic)  ; break;
            case 13:
            {
                if (auto* node = graph.graph.getNodeForId (pluginID))
                    node->properties.set ("DPIAware", ! node->properties ["DPIAware"]);
                break;
            }
            case 14:  showWindow (PluginWindow::Type::debug); break;
            case 20:  showWindow (PluginWindow::Type::audioIO); break;
            case 21:  testStateSaveLoad(); break;

            default:  break;
        }
        }));
    }

    void testStateSaveLoad()
    {
        if (auto* processor = getProcessor())
        {
            MemoryBlock state;
            processor->getStateInformation (state);
            processor->setStateInformation (state.getData(), (int) state.getSize());
        }
    }

    void showWindow (PluginWindow::Type type)
    {
        if (auto node = graph.graph.getNodeForId (pluginID))
            if (auto* w = graph.getOrCreateWindowFor (node, type))
                w->toFront (true);
    }

    void timerCallback() override
    {
        // this should only be called on touch devices
        jassert (isOnTouchDevice());

        stopTimer();
        showPopupMenu();
    }

    void parameterValueChanged (int, float) override
    {
        repaint();
    }

    void parameterGestureChanged (int, bool) override  {}

    GraphEditorPanel& panel;
    PluginGraph& graph;
    const AudioProcessorGraph::NodeID pluginID;
    OwnedArray<PinComponent> pins;
    int numInputs = 0, numOutputs = 0;
    int pinSize = 16;
    Point<int> originalPos;
    Font font { 13.0f, Font::bold };
    int numIns = 0, numOuts = 0;
    DropShadowEffect shadow;
    std::unique_ptr<PopupMenu> menu;
};

/**
GraphEditorPanel::ConnectorComponent
*/
struct GraphEditorPanel::ConnectorComponent   : public Component,
                                                public SettableTooltipClient
{
    ConnectorComponent (GraphEditorPanel& p) : panel (p), graph (p.graph)
    {
        setAlwaysOnTop (true);
    }

    void setInput (AudioProcessorGraph::NodeAndChannel newSource)
    {
        if (connection.source != newSource)
        {
            connection.source = newSource;
            update();
        }
    }

    void setOutput (AudioProcessorGraph::NodeAndChannel newDest)
    {
        if (connection.destination != newDest)
        {
            connection.destination = newDest;
            update();
        }
    }

    void dragStart (Point<float> pos)
    {
        lastInputPos = pos;
        resizeToFit();
    }

    void dragEnd (Point<float> pos)
    {
        lastOutputPos = pos;
        resizeToFit();
    }

    void update()
    {
        Point<float> p1, p2;
        getPoints (p1, p2);

        if (lastInputPos != p1 || lastOutputPos != p2)
            resizeToFit();
    }

    void resizeToFit()
    {
        Point<float> p1, p2;
        getPoints (p1, p2);

        auto newBounds = Rectangle<float> (p1, p2).expanded (4.0f).getSmallestIntegerContainer();

        if (newBounds != getBounds())
            setBounds (newBounds);
        else
            resized();

        repaint();
    }

    void getPoints (Point<float>& p1, Point<float>& p2) const
    {
        p1 = lastInputPos;
        p2 = lastOutputPos;

        if (auto* src = panel.getComponentForPlugin (connection.source.nodeID))
            p1 = src->getPinPos (connection.source.channelIndex, false);

        if (auto* dest = panel.getComponentForPlugin (connection.destination.nodeID))
            p2 = dest->getPinPos (connection.destination.channelIndex, true);
    }

    void paint (Graphics& g) override
    {
        if (connection.source.isMIDI() || connection.destination.isMIDI())
            g.setColour (Colours::red);
        else
            g.setColour (Colours::green);

        g.fillPath (linePath);
    }

    bool hitTest (int x, int y) override
    {
        auto pos = Point<int> (x, y).toFloat();

        if (hitPath.contains (pos))
        {
            double distanceFromStart, distanceFromEnd;
            getDistancesFromEnds (pos, distanceFromStart, distanceFromEnd);

            // avoid clicking the connector when over a pin
            return distanceFromStart > 7.0 && distanceFromEnd > 7.0;
        }

        return false;
    }

    void mouseDown (const MouseEvent&) override
    {
        dragging = false;
    }

    void mouseDrag (const MouseEvent& e) override
    {
        if (dragging)
        {
            panel.dragConnector (e);
        }
        else if (e.mouseWasDraggedSinceMouseDown())
        {
            dragging = true;

            graph.graph.removeConnection (connection);

            double distanceFromStart, distanceFromEnd;
            getDistancesFromEnds (getPosition().toFloat() + e.position, distanceFromStart, distanceFromEnd);
            const bool isNearerSource = (distanceFromStart < distanceFromEnd);

            AudioProcessorGraph::NodeAndChannel dummy { {}, 0 };

            panel.beginConnectorDrag (isNearerSource ? dummy : connection.source,
                                      isNearerSource ? connection.destination : dummy,
                                      e);
        }
    }

    void mouseUp (const MouseEvent& e) override
    {
        if (dragging)
            panel.endDraggingConnector (e);
    }

    void resized() override
    {
        Point<float> p1, p2;
        getPoints (p1, p2);

        lastInputPos = p1;
        lastOutputPos = p2;

        p1 -= getPosition().toFloat();
        p2 -= getPosition().toFloat();

        linePath.clear();
        linePath.startNewSubPath (p1);
        linePath.cubicTo (p1.x, p1.y + (p2.y - p1.y) * 0.33f,
                          p2.x, p1.y + (p2.y - p1.y) * 0.66f,
                          p2.x, p2.y);

        PathStrokeType wideStroke (8.0f);
        wideStroke.createStrokedPath (hitPath, linePath);

        PathStrokeType stroke (2.5f);
        stroke.createStrokedPath (linePath, linePath);

        auto arrowW = 5.0f;
        auto arrowL = 4.0f;

        Path arrow;
        arrow.addTriangle (-arrowL, arrowW,
                           -arrowL, -arrowW,
                           arrowL, 0.0f);

        arrow.applyTransform (AffineTransform()
                                .rotated (MathConstants<float>::halfPi - (float) atan2 (p2.x - p1.x, p2.y - p1.y))
                                .translated ((p1 + p2) * 0.5f));

        linePath.addPath (arrow);
        linePath.setUsingNonZeroWinding (true);
    }

    void getDistancesFromEnds (Point<float> p, double& distanceFromStart, double& distanceFromEnd) const
    {
        Point<float> p1, p2;
        getPoints (p1, p2);

        distanceFromStart = p1.getDistanceFrom (p);
        distanceFromEnd   = p2.getDistanceFrom (p);
    }

    GraphEditorPanel& panel;
    PluginGraph& graph;
    AudioProcessorGraph::Connection connection { { {}, 0 }, { {}, 0 } };
    Point<float> lastInputPos, lastOutputPos;
    Path linePath, hitPath;
    bool dragging = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConnectorComponent)
};

/**
GraphEditorPanel
*/
GraphEditorPanel::GraphEditorPanel (PluginGraph& g, AudioDeviceManager &_dm)
	: graph (g), dm(_dm),
	directoryListThread("Twonk programs lister"),
	twonkDocumentFileFilter("*.twonk", "", "Twonk programs"),
	directoryContentsList(&twonkDocumentFileFilter, directoryListThread),
	twonkProgramListWrapper(directoryContentsList, g)
{
	bgImage = IMG(bg1_jpg);
	toolBar.reset(new TwonkToolBar(*this));
	addAndMakeVisible(toolBar.get());
	toolBar->setVisible(true);
	toolBar->setBounds(16, 64, 64, 532);
	toolBar->setAlwaysOnTop(true);
	
    graph.addChangeListener (this);
    setOpaque (true);
	directoryContentsList.setDirectory(GET_TWONK_PROGRAM_DIR(), false, true);
	directoryListThread.startThread(1);

	addAndMakeVisible(twonkProgramListWrapper);
	twonkProgramListWrapper.list.setVisible(true);
	twonkProgramListWrapper.list.addListener(this);
	twonkProgramListWrapper.list.setColour(ListBox::backgroundColourId, Colours::white.withAlpha(0.5f));
	twonkProgramListWrapper.list.setRowHeight(48);
	twonkProgramListWrapper.setVisible(false);
}

GraphEditorPanel::~GraphEditorPanel()
{
    graph.removeChangeListener (this);
    draggingConnector = nullptr;
    nodes.clear();
    connectors.clear();
}

void GraphEditorPanel::paint (Graphics& g)
{
	g.drawImage(bgImage, getLocalBounds().toFloat(), RectanglePlacement::centred);
}

void GraphEditorPanel::mouseDown (const MouseEvent& e)
{
    if (isOnTouchDevice())
    {
        originalTouchPos = e.position.toInt();
        startTimer (750);
    }

    if (e.mods.isPopupMenu())
        showPopupMenu (e.position.toInt());
}

void GraphEditorPanel::mouseUp (const MouseEvent&)
{
    if (isOnTouchDevice())
    {
        stopTimer();
        callAfterDelay (250, []() { PopupMenu::dismissAllActiveMenus(); });
    }
}

void GraphEditorPanel::mouseDrag (const MouseEvent& e)
{
    if (isOnTouchDevice() && e.getDistanceFromDragStart() > 5)
        stopTimer();
}

void GraphEditorPanel::createNewPlugin (const PluginDescription& desc, Point<int> position)
{
    graph.addPlugin (desc, position.toDouble() / Point<double> ((double) getWidth(), (double) getHeight()));
}

GraphEditorPanel::PluginComponent* GraphEditorPanel::getComponentForPlugin (AudioProcessorGraph::NodeID nodeID) const
{
    for (auto* fc : nodes)
       if (fc->pluginID == nodeID)
            return fc;

    return nullptr;
}

GraphEditorPanel::ConnectorComponent* GraphEditorPanel::getComponentForConnection (const AudioProcessorGraph::Connection& conn) const
{
    for (auto* cc : connectors)
        if (cc->connection == conn)
            return cc;

    return nullptr;
}

GraphEditorPanel::PinComponent* GraphEditorPanel::findPinAt (Point<float> pos) const
{
    for (auto* fc : nodes)
    {
        // NB: A Visual Studio optimiser error means we have to put this Component* in a local
        // variable before trying to cast it, or it gets mysteriously optimised away..
        auto* comp = fc->getComponentAt (pos.toInt() - fc->getPosition());

        if (auto* pin = dynamic_cast<PinComponent*> (comp))
            return pin;
    }

    return nullptr;
}

void GraphEditorPanel::resized()
{
    updateComponents();
}

void GraphEditorPanel::changeListenerCallback (ChangeBroadcaster*)
{
    updateComponents();
}

void GraphEditorPanel::updateComponents()
{
	twonkProgramListWrapper.setBounds(getWidth() - 300, 16, 300, getHeight() - 32);

    for (int i = nodes.size(); --i >= 0;)
        if (graph.graph.getNodeForId (nodes.getUnchecked(i)->pluginID) == nullptr)
            nodes.remove (i);

    for (int i = connectors.size(); --i >= 0;)
        if (! graph.graph.isConnected (connectors.getUnchecked(i)->connection))
            connectors.remove (i);

    for (auto* fc : nodes)
        fc->update();

    for (auto* cc : connectors)
        cc->update();

    for (auto* f : graph.graph.getNodes())
    {
        if (getComponentForPlugin (f->nodeID) == nullptr)
        {
			PluginComponent* comp = nodes.add (new PluginComponent (*this, f->nodeID));
            addAndMakeVisible (comp);
            comp->update();
        }
    }

    for (auto& c : graph.graph.getConnections())
    {
        if (getComponentForConnection (c) == nullptr)
        {
            auto* comp = connectors.add (new ConnectorComponent (*this));
            addAndMakeVisible (comp);

            comp->setInput (c.source);
            comp->setOutput (c.destination);
        }
    }
}

void GraphEditorPanel::showPopupMenu (Point<int> mousePos)
{
    menu.reset (new PopupMenu);

    if (auto* mainWindow = findParentComponentOfClass<MainHostWindow>())
    {
        mainWindow->addPluginsToMenu (*menu);

        menu->showMenuAsync ({},
                             ModalCallbackFunction::create ([this, mousePos] (int r)
                                                            {
                                                                if (r > 0)
                                                                    if (auto* mainWin = findParentComponentOfClass<MainHostWindow>())
                                                                        createNewPlugin (mainWin->getChosenType (r), mousePos);
                                                            }));
    }
}

void GraphEditorPanel::beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                                           AudioProcessorGraph::NodeAndChannel dest,
                                           const MouseEvent& e)
{
    auto* c = dynamic_cast<ConnectorComponent*> (e.originalComponent);
    connectors.removeObject (c, false);
    draggingConnector.reset (c);

    if (draggingConnector == nullptr)
        draggingConnector.reset (new ConnectorComponent (*this));

    draggingConnector->setInput (source);
    draggingConnector->setOutput (dest);

    addAndMakeVisible (draggingConnector.get());
    draggingConnector->toFront (false);

    dragConnector (e);
}

void GraphEditorPanel::dragConnector (const MouseEvent& e)
{
    auto e2 = e.getEventRelativeTo (this);

    if (draggingConnector != nullptr)
    {
        draggingConnector->setTooltip ({});

        auto pos = e2.position;

        if (auto* pin = findPinAt (pos))
        {
            auto connection = draggingConnector->connection;

            if (connection.source.nodeID == AudioProcessorGraph::NodeID() && ! pin->isInput)
            {
                connection.source = pin->pin;
            }
            else if (connection.destination.nodeID == AudioProcessorGraph::NodeID() && pin->isInput)
            {
                connection.destination = pin->pin;
            }

            if (graph.graph.canConnect (connection))
            {
                pos = (pin->getParentComponent()->getPosition() + pin->getBounds().getCentre()).toFloat();
                draggingConnector->setTooltip (pin->getTooltip());
            }
        }

        if (draggingConnector->connection.source.nodeID == AudioProcessorGraph::NodeID())
            draggingConnector->dragStart (pos);
        else
            draggingConnector->dragEnd (pos);
    }
}

void GraphEditorPanel::endDraggingConnector (const MouseEvent& e)
{
    if (draggingConnector == nullptr)
        return;

    draggingConnector->setTooltip ({});

    auto e2 = e.getEventRelativeTo (this);
    auto connection = draggingConnector->connection;

    draggingConnector = nullptr;

    if (auto* pin = findPinAt (e2.position))
    {
        if (connection.source.nodeID == AudioProcessorGraph::NodeID())
        {
            if (pin->isInput)
                return;

            connection.source = pin->pin;
        }
        else
        {
            if (! pin->isInput)
                return;

            connection.destination = pin->pin;
        }

        graph.graph.addConnection (connection);
    }
}

void GraphEditorPanel::timerCallback()
{
    // this should only be called on touch devices
    jassert (isOnTouchDevice());

    stopTimer();
    showPopupMenu (originalTouchPos);
}

void GraphEditorPanel::toggleProgramMenu()
{
	twonkProgramListWrapper.setVisible(!twonkProgramListWrapper.isVisible());
}

void GraphEditorPanel::selectionChanged()
{

}

void GraphEditorPanel::fileClicked(const File &file, const MouseEvent &e)
{

}

void GraphEditorPanel::fileDoubleClicked(const File &file)
{
}

/*
 * GraphDocumentComponent
 */
GraphDocumentComponent::GraphDocumentComponent (AudioPluginFormatManager& fm, AudioDeviceManager& dm, KnownPluginList& kpl)
    : graph (new PluginGraph (fm, *this)),
      deviceManager (dm),
      pluginList (kpl),
      graphPlayer (getAppProperties().getUserSettings()->getBoolValue ("doublePrecisionProcessing", false))
{
    init();

    deviceManager.addChangeListener (graphPanel.get());
    deviceManager.addAudioCallback (&graphPlayer);
    deviceManager.addMidiInputDeviceCallback ({}, &graphPlayer.getMidiMessageCollector());
}

void GraphDocumentComponent::init()
{
    graphPanel.reset (new GraphEditorPanel (*graph, deviceManager));
    addAndMakeVisible (graphPanel.get());
	
    graphPlayer.setProcessor (&graph->graph);
    graphPanel->updateComponents();
}

GraphDocumentComponent::~GraphDocumentComponent()
{
    releaseGraph();
}

void GraphDocumentComponent::resized()
{
    graphPanel->setBounds (getLocalBounds());
}

void GraphDocumentComponent::createNewPlugin (const PluginDescription& desc, Point<int> pos)
{
    graphPanel->createNewPlugin (desc, pos);
}

void GraphDocumentComponent::releaseGraph()
{
    deviceManager.removeAudioCallback (&graphPlayer);
    deviceManager.removeMidiInputDeviceCallback ({}, &graphPlayer.getMidiMessageCollector());

    if (graphPanel != nullptr)
    {
        deviceManager.removeChangeListener (graphPanel.get());
        graphPanel = nullptr;
    }

    graphPlayer.setProcessor (nullptr);
    graph = nullptr;
}

bool GraphDocumentComponent::isInterestedInDragSource (const SourceDetails& details)
{
    return ((dynamic_cast<ListBox*> (details.sourceComponent.get()) != nullptr)
            && details.description.toString().startsWith ("PLUGIN"));
}

void GraphDocumentComponent::itemDropped (const SourceDetails& details)
{
    auto pluginTypeIndex = details.description.toString()
                                 .fromFirstOccurrenceOf ("PLUGIN: ", false, false)
                                 .getIntValue();

    // must be a valid index!
    jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

    createNewPlugin (pluginList.getTypes()[pluginTypeIndex], details.localPosition);
}

void GraphDocumentComponent::setDoublePrecision (bool doublePrecision)
{
    graphPlayer.setDoublePrecisionProcessing (doublePrecision);
}

bool GraphDocumentComponent::closeAnyOpenPluginWindows()
{
    return graphPanel->graph.closeAnyOpenPluginWindows();
}

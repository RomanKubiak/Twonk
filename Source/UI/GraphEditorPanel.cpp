#include "../JuceLibraryCode/JuceHeader.h"
#include "GraphEditorPanel.h"
#include "../Filters/InternalPlugins.h"
#include "MainHostWindow.h"
#include "TwonkToolBar.h"
#include "TwonkToolBarButton.h"
#include "TwonkMidiKeyboard.h"
#include "TwonkFilterComponent.h"
#include "TwonkFileMenu.h"
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
                tip = isInput ? "MIDI Input"
                              : "MIDI Output";
            }
            else
            {
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
        /*auto w = (float) getWidth();
        auto h = (float) getHeight();

        Path p;
        p.addEllipse (w * 0.25f, h * 0.25f, w * 0.5f, h * 0.5f);
        p.addRectangle (w * 0.4f, isInput ? (0.5f * h) : 0.0f, w * 0.2f, h * 0.5f);

        auto colour = (pin.isMIDI() ? Colours::red : Colours::green);

        g.setColour (colour.withRotatedHue (busIdx / 5.0f));
        g.fillPath (p);*/

		Path hexagon;
		hexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.45f, float_Pi*0.5f);
		g.setColour(currentColour.contrasting(0.1f));
		g.drawImage(pinImage, getLocalBounds().toFloat().reduced(NODE_SIZE * 0.15f), RectanglePlacement::stretchToFit, true);
		g.setColour(currentColour.withAlpha(0.3f));
		g.fillPath(hexagon);
		g.setColour(currentColour);
		g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.1f));
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
	Colour currentColour;
	Image pinImage;
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
		hexagon.addPolygon(area.getCentre().toFloat(), 6, area.getWidth() * 0.3f, float_Pi*0.5f);

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
					type = UnknownNode;
					break;
				}
			}

			if (processor->acceptsMidi() &&
				processor->producesMidi() &&
				processor->getTotalNumInputChannels() == 0 &&
				processor->getTotalNumOutputChannels() == 0)
			{
				type = PluginMidiEffect;
			}
			if (processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() > 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynthWithInput;
			}
			if (processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() == 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynthWithInput;
			}
			if (!processor->acceptsMidi() &&
				!processor->producesMidi() &&
				processor->getTotalNumInputChannels() > 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginAudioEffect;
			}

			if (processor->acceptsMidi() &&
				processor->producesMidi() &&
				processor->getTotalNumInputChannels() == 0 &&
				processor->getTotalNumOutputChannels() > 0)
			{
				type = PluginSynth;
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
			return (ImageCache::getFromMemory(BinaryData::audio_input_png, BinaryData::audio_input_pngSize));
		case InternalAudioOutput:
			return (ImageCache::getFromMemory(BinaryData::audio_output_png, BinaryData::audio_output_pngSize));
		case InternalMidiInput:
			return (ImageCache::getFromMemory(BinaryData::midi_input_png, BinaryData::midi_input_pngSize));
		case InternalMidiOutpout:
			return (ImageCache::getFromMemory(BinaryData::midi_output_png, BinaryData::midi_output_pngSize));
		case InternalEffect:
			return (ImageCache::getFromMemory(BinaryData::icon_plugin_internal_png, BinaryData::icon_plugin_internal_pngSize));
		case InternalSynth:
			return (ImageCache::getFromMemory(BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize));
		case PluginAudioEffect:
			return (ImageCache::getFromMemory(BinaryData::icon_effect_png, BinaryData::icon_effect_pngSize));
		case PluginSynth:
			return (ImageCache::getFromMemory(BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize));
		case PluginSynthWithInput:
			return (ImageCache::getFromMemory(BinaryData::icon_synth_png, BinaryData::icon_synth_pngSize));
		default:
			return (ImageCache::getFromMemory(BinaryData::icon_question_jpg, BinaryData::icon_question_jpgSize));
		}
	}

    void paint (Graphics& g) override
    {
        auto boxArea = getLocalBounds().reduced (4, pinSize);
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
				boxColour = boxColour.brighter();

			g.setColour (boxColour);
		}
		
		g.setColour(boxColour.contrasting(0.1f));
		g.drawImage(getImageForFilter(ft), boxArea.toFloat(), RectanglePlacement::onlyReduceInSize, true);
		Path hexagon = getHexagonPath(boxArea);
		g.setColour(boxColour.withAlpha(0.3f));
		g.fillPath(hexagon);
		g.setColour(boxColour);
		g.strokePath(hexagon, PathStrokeType(1.0f));

        /*g.setColour (findColour (TextEditor::textColourId));
        g.setFont (font);
        g.drawFittedText (getName(), boxArea, Justification::centred, 2);*/
    }

    void resized() override
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

        int w = 100;
        int h = 60;

        w = jmax (w, (jmax (numIns, numOuts) + 1) * 20);

        const int textWidth = font.getStringWidth (f->getProcessor()->getName());
        w = jmax (w, 16 + jmin (textWidth, 300));
        if (textWidth > 300)
            h = 100;

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
GraphEditorPanel::GraphEditorPanel (PluginGraph& g)
	: graph (g), keyboardComponent(nullptr),
	directoryListThread("Twonk programs lister"),
	twonkDocumentFileFilter("*.twonk", "", "Twonk programs"),
	directoryContentsList(&twonkDocumentFileFilter, directoryListThread),
	twonkProgramListWrapper(directoryContentsList, g)
{
	bgImage = ImageCache::getFromMemory(BinaryData::bg3_jpg, BinaryData::bg3_jpgSize);
	toolBar.reset(new TwonkToolBar(*this));
	addAndMakeVisible(toolBar.get());
	toolBar->setVisible(true);
	toolBar->setBounds(16, 64, 64, 532);
	toolBar->setAlwaysOnTop(true);
	
    graph.addChangeListener (this);
    setOpaque (true);
	directoryContentsList.setDirectory(File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk"), false, true);
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
	if (keyboardComponent)
		keyboardComponent->setBounds(90, 300, 400, 150);

	twonkProgramListWrapper.setBounds(getWidth() - 248, 16, 248, getHeight() - 32);

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

void GraphEditorPanel::setKeyboardComponent(TwonkMidiKeyboard *_keyboardComponent)
{
	keyboardComponent = _keyboardComponent;
	addAndMakeVisible(keyboardComponent);
	keyboardComponent->setVisible(true);
	
	updateComponents();
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

void GraphEditorPanel::toggleTwonkFileMenu()
{
	if (toolBar->getWidth() == 400)
		toolBar->setSize(64, 384);
	else
		toolBar->setSize(400, 384);
}
/*
 * GraphDocumentComponent
 */
struct GraphDocumentComponent::TooltipBar   : public Component,
                                              private Timer
{
    TooltipBar()
    {
        startTimer (100);
    }

    void paint (Graphics& g) override
    {
        g.setFont (Font (getHeight() * 0.7f, Font::bold));
        g.setColour (Colours::black);
        g.drawFittedText (tip, 10, 0, getWidth() - 12, getHeight(), Justification::centredLeft, 1);
    }

    void timerCallback() override
    {
        String newTip;

        if (auto* underMouse = Desktop::getInstance().getMainMouseSource().getComponentUnderMouse())
            if (auto* ttc = dynamic_cast<TooltipClient*> (underMouse))
                if (! (underMouse->isMouseButtonDown() || underMouse->isCurrentlyBlockedByAnotherModalComponent()))
                    newTip = ttc->getTooltip();

        if (newTip != tip)
        {
            tip = newTip;
            repaint();
        }
    }

    String tip;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TooltipBar)
};

class GraphDocumentComponent::TitleBarComponent    : public Component,
                                                     private Button::Listener
{
public:
    TitleBarComponent (GraphDocumentComponent& graphDocumentComponent)
        : owner (graphDocumentComponent)
    {
        static const unsigned char burgerMenuPathData[]
            = { 110,109,0,0,128,64,0,0,32,65,108,0,0,224,65,0,0,32,65,98,254,212,232,65,0,0,32,65,0,0,240,65,252,
                169,17,65,0,0,240,65,0,0,0,65,98,0,0,240,65,8,172,220,64,254,212,232,65,0,0,192,64,0,0,224,65,0,0,
                192,64,108,0,0,128,64,0,0,192,64,98,16,88,57,64,0,0,192,64,0,0,0,64,8,172,220,64,0,0,0,64,0,0,0,65,
                98,0,0,0,64,252,169,17,65,16,88,57,64,0,0,32,65,0,0,128,64,0,0,32,65,99,109,0,0,224,65,0,0,96,65,108,
                0,0,128,64,0,0,96,65,98,16,88,57,64,0,0,96,65,0,0,0,64,4,86,110,65,0,0,0,64,0,0,128,65,98,0,0,0,64,
                254,212,136,65,16,88,57,64,0,0,144,65,0,0,128,64,0,0,144,65,108,0,0,224,65,0,0,144,65,98,254,212,232,
                65,0,0,144,65,0,0,240,65,254,212,136,65,0,0,240,65,0,0,128,65,98,0,0,240,65,4,86,110,65,254,212,232,
                65,0,0,96,65,0,0,224,65,0,0,96,65,99,109,0,0,224,65,0,0,176,65,108,0,0,128,64,0,0,176,65,98,16,88,57,
                64,0,0,176,65,0,0,0,64,2,43,183,65,0,0,0,64,0,0,192,65,98,0,0,0,64,254,212,200,65,16,88,57,64,0,0,208,
                65,0,0,128,64,0,0,208,65,108,0,0,224,65,0,0,208,65,98,254,212,232,65,0,0,208,65,0,0,240,65,254,212,
                200,65,0,0,240,65,0,0,192,65,98,0,0,240,65,2,43,183,65,254,212,232,65,0,0,176,65,0,0,224,65,0,0,176,
                65,99,101,0,0 };

        static const unsigned char pluginListPathData[]
            = { 110,109,193,202,222,64,80,50,21,64,108,0,0,48,65,0,0,0,0,108,160,154,112,65,80,50,21,64,108,0,0,48,65,80,
                50,149,64,108,193,202,222,64,80,50,21,64,99,109,0,0,192,64,251,220,127,64,108,160,154,32,65,165,135,202,
                64,108,160,154,32,65,250,220,47,65,108,0,0,192,64,102,144,10,65,108,0,0,192,64,251,220,127,64,99,109,0,0,
                128,65,251,220,127,64,108,0,0,128,65,103,144,10,65,108,96,101,63,65,251,220,47,65,108,96,101,63,65,166,135,
                202,64,108,0,0,128,65,251,220,127,64,99,109,96,101,79,65,148,76,69,65,108,0,0,136,65,0,0,32,65,108,80,
                77,168,65,148,76,69,65,108,0,0,136,65,40,153,106,65,108,96,101,79,65,148,76,69,65,99,109,0,0,64,65,63,247,
                95,65,108,80,77,128,65,233,161,130,65,108,80,77,128,65,125,238,167,65,108,0,0,64,65,51,72,149,65,108,0,0,64,
                65,63,247,95,65,99,109,0,0,176,65,63,247,95,65,108,0,0,176,65,51,72,149,65,108,176,178,143,65,125,238,167,65,
                108,176,178,143,65,233,161,130,65,108,0,0,176,65,63,247,95,65,99,109,12,86,118,63,148,76,69,65,108,0,0,160,
                64,0,0,32,65,108,159,154,16,65,148,76,69,65,108,0,0,160,64,40,153,106,65,108,12,86,118,63,148,76,69,65,99,
                109,0,0,0,0,63,247,95,65,108,62,53,129,64,233,161,130,65,108,62,53,129,64,125,238,167,65,108,0,0,0,0,51,
                72,149,65,108,0,0,0,0,63,247,95,65,99,109,0,0,32,65,63,247,95,65,108,0,0,32,65,51,72,149,65,108,193,202,190,
                64,125,238,167,65,108,193,202,190,64,233,161,130,65,108,0,0,32,65,63,247,95,65,99,101,0,0 };

        {
            Path p;
            p.loadPathFromData (burgerMenuPathData, sizeof (burgerMenuPathData));
            burgerButton.setShape (p, true, true, false);
        }

        {
            Path p;
            p.loadPathFromData (pluginListPathData, sizeof (pluginListPathData));
            pluginButton.setShape (p, true, true, false);
        }

        burgerButton.addListener (this);
        addAndMakeVisible (burgerButton);

        pluginButton.addListener (this);
        addAndMakeVisible (pluginButton);

        titleLabel.setJustificationType (Justification::centredLeft);
        addAndMakeVisible (titleLabel);

        setOpaque (true);
    }

private:
    void paint (Graphics& g) override
    {
        auto titleBarBackgroundColour = getLookAndFeel().findColour (ResizableWindow::backgroundColourId).darker();

        g.setColour (titleBarBackgroundColour);
        g.fillRect (getLocalBounds());
    }

    void resized() override
    {
        auto r = getLocalBounds();

        burgerButton.setBounds (r.removeFromLeft (40).withSizeKeepingCentre (20, 20));

        pluginButton.setBounds (r.removeFromRight (40).withSizeKeepingCentre (20, 20));

        titleLabel.setFont (Font (static_cast<float> (getHeight()) * 0.5f, Font::plain));
        titleLabel.setBounds (r);
    }

    void buttonClicked (Button* b) override
    {
        owner.showSidePanel (b == &burgerButton);
    }

    GraphDocumentComponent& owner;

    Label titleLabel {"titleLabel", "Plugin Host"};
    ShapeButton burgerButton {"burgerButton", Colours::lightgrey, Colours::lightgrey, Colours::white};
    ShapeButton pluginButton {"pluginButton", Colours::lightgrey, Colours::lightgrey, Colours::white};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBarComponent)
};

struct GraphDocumentComponent::PluginListBoxModel    : public ListBoxModel,
                                                       public ChangeListener,
                                                       public MouseListener
{
    PluginListBoxModel (ListBox& lb, KnownPluginList& kpl)
        : owner (lb),
          knownPlugins (kpl)
    {
        knownPlugins.addChangeListener (this);
        owner.addMouseListener (this, true);

       #if JUCE_IOS
        scanner.reset (new AUScanner (knownPlugins));
       #endif
    }

    int getNumRows() override
    {
        return knownPlugins.getNumTypes();
    }

    void paintListBoxItem (int rowNumber, Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {
        g.fillAll (rowIsSelected ? Colour (0xff42A2C8)
                                 : Colour (0xff263238));

        g.setColour (rowIsSelected ? Colours::black : Colours::white);

        if (rowNumber < knownPlugins.getNumTypes())
            g.drawFittedText (knownPlugins.getTypes()[rowNumber].name, { 0, 0, width, height - 2 }, Justification::centred, 1);

        g.setColour (Colours::black.withAlpha (0.4f));
        g.drawRect (0, height - 1, width, 1);
    }

    var getDragSourceDescription (const SparseSet<int>& selectedRows) override
    {
        if (! isOverSelectedRow)
            return var();

        return String ("PLUGIN: " + String (selectedRows[0]));
    }

    void changeListenerCallback (ChangeBroadcaster*) override
    {
        owner.updateContent();
    }

    void mouseDown (const MouseEvent& e) override
    {
        isOverSelectedRow = owner.getRowPosition (owner.getSelectedRow(), true)
                                 .contains (e.getEventRelativeTo (&owner).getMouseDownPosition());
    }

    ListBox& owner;
    KnownPluginList& knownPlugins;

    bool isOverSelectedRow = false;

   #if JUCE_IOS
    std::unique_ptr<AUScanner> scanner;
   #endif

    JUCE_DECLARE_NON_COPYABLE (PluginListBoxModel)
};

GraphDocumentComponent::GraphDocumentComponent (AudioPluginFormatManager& fm, AudioDeviceManager& dm, KnownPluginList& kpl)
    : graph (new PluginGraph (fm)),
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
    graphPanel.reset (new GraphEditorPanel (*graph));
    addAndMakeVisible (graphPanel.get());
	
    graphPlayer.setProcessor (&graph->graph);

	keyState.addListener (&graphPlayer.getMidiMessageCollector());
	keyboardComp.reset (new TwonkMidiKeyboard (keyState, MidiKeyboardComponent::horizontalKeyboard));
	addAndMakeVisible (keyboardComp.get());
	
	graphPanel->setKeyboardComponent(keyboardComp.get());
    statusBar.reset (new TooltipBar());
    addAndMakeVisible (statusBar.get());
	tooltipWindow.reset(new TooltipWindow(this, 300));
    graphPanel->updateComponents();

    if (isOnTouchDevice())
    {
        if (isOnTouchDevice())
        {
            titleBarComponent.reset (new TitleBarComponent (*this));
            addAndMakeVisible (titleBarComponent.get());
        }

        pluginListBoxModel.reset (new PluginListBoxModel (pluginListBox, pluginList));

        pluginListBox.setModel (pluginListBoxModel.get());
        pluginListBox.setRowHeight (40);

        pluginListSidePanel.setContent (&pluginListBox, false);

        mobileSettingsSidePanel.setContent (new AudioDeviceSelectorComponent (deviceManager,
                                                                              0, 2, 0, 2,
                                                                              true, true, true, false));

        if (isOnTouchDevice())
        {
            addAndMakeVisible (pluginListSidePanel);
            addAndMakeVisible (mobileSettingsSidePanel);
        }
    }
}

GraphDocumentComponent::~GraphDocumentComponent()
{
    releaseGraph();
    keyState.removeListener (&graphPlayer.getMidiMessageCollector());
}

void GraphDocumentComponent::resized()
{
    auto r = getLocalBounds();
    const int titleBarHeight = 40;
    const int keysHeight = 60;
    const int statusHeight = 20;

    if (isOnTouchDevice())
        titleBarComponent->setBounds (r.removeFromTop(titleBarHeight));

    //keyboardComp->setBounds (r.removeFromBottom (keysHeight));
    //statusBar->setBounds (r.removeFromBottom (statusHeight));
    graphPanel->setBounds (r);

    checkAvailableWidth();
}

void GraphDocumentComponent::createNewPlugin (const PluginDescription& desc, Point<int> pos)
{
    graphPanel->createNewPlugin (desc, pos);
}

void GraphDocumentComponent::unfocusKeyboardComponent()
{
    keyboardComp->unfocusAllComponents();
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

    keyboardComp = nullptr;
    statusBar = nullptr;

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
    // don't allow items to be dropped behind the sidebar
    if (pluginListSidePanel.getBounds().contains (details.localPosition))
        return;

    auto pluginTypeIndex = details.description.toString()
                                 .fromFirstOccurrenceOf ("PLUGIN: ", false, false)
                                 .getIntValue();

    // must be a valid index!
    jassert (isPositiveAndBelow (pluginTypeIndex, pluginList.getNumTypes()));

    createNewPlugin (pluginList.getTypes()[pluginTypeIndex], details.localPosition);
}

void GraphDocumentComponent::showSidePanel (bool showSettingsPanel)
{
    if (showSettingsPanel)
        mobileSettingsSidePanel.showOrHide (true);
    else
        pluginListSidePanel.showOrHide (true);

    checkAvailableWidth();

    lastOpenedSidePanel = showSettingsPanel ? &mobileSettingsSidePanel
                                            : &pluginListSidePanel;
}

void GraphDocumentComponent::hideLastSidePanel()
{
    if (lastOpenedSidePanel != nullptr)
        lastOpenedSidePanel->showOrHide (false);

    if      (mobileSettingsSidePanel.isPanelShowing())    lastOpenedSidePanel = &mobileSettingsSidePanel;
    else if (pluginListSidePanel.isPanelShowing())        lastOpenedSidePanel = &pluginListSidePanel;
    else                                                  lastOpenedSidePanel = nullptr;
}

void GraphDocumentComponent::checkAvailableWidth()
{
    if (mobileSettingsSidePanel.isPanelShowing() && pluginListSidePanel.isPanelShowing())
    {
        if (getWidth() - (mobileSettingsSidePanel.getWidth() + pluginListSidePanel.getWidth()) < 150)
            hideLastSidePanel();
    }
}

void GraphDocumentComponent::setDoublePrecision (bool doublePrecision)
{
    graphPlayer.setDoublePrecisionProcessing (doublePrecision);
}

bool GraphDocumentComponent::closeAnyOpenPluginWindows()
{
    return graphPanel->graph.closeAnyOpenPluginWindows();
}

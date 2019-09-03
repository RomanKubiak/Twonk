#include "Processor.h"
#include "Pin.h"
#include "Editor.h"
#include "MainHostWindow.h"

Editor::Processor::Processor(Editor &p, AudioProcessorGraph::NodeID id) : panel(p), graph(p.graph),
                                                                          pluginID(id) {
    if (auto f = graph.graph.getNodeForId(pluginID)) {
        if (auto *processor = f->getProcessor()) {
            if (auto *bypassParam = processor->getBypassParameter())
                bypassParam->addListener(this);
        }
    }

    setSize(150, 60);
}

Editor::Processor::~Processor() {
    if (auto f = graph.graph.getNodeForId(pluginID)) {
        if (auto *processor = f->getProcessor()) {
            if (auto *bypassParam = processor->getBypassParameter())
                bypassParam->removeListener(this);
        }
    }
}

void Editor::Processor::mouseDown(const MouseEvent &e) {
    originalPos = localPointToGlobal(Point<int>());

    toFront(true);

    if (isOnTouchDevice()) {
        startTimer(750);
    } else {
        if (e.mods.isPopupMenu())
            showPopupMenu();
    }
}

void Editor::Processor::mouseDrag(const MouseEvent &e) {
    if (isOnTouchDevice() && e.getDistanceFromDragStart() > 5)
        stopTimer();

    if (!e.mods.isPopupMenu()) {
        auto pos = originalPos + e.getOffsetFromDragStart();

        if (getParentComponent() != nullptr)
            pos = getParentComponent()->getLocalPoint(nullptr, pos);

        pos += getLocalBounds().getCentre();

        graph.setNodePosition(pluginID,
                              {pos.x / (double) getParentWidth(),
                               pos.y / (double) getParentHeight()});

        panel.updateComponents();
    }
}

void Editor::Processor::mouseUp(const MouseEvent &e) {
    if (isOnTouchDevice()) {
        stopTimer();
        callAfterDelay(250, []() { PopupMenu::dismissAllActiveMenus(); });
    }

    if (e.mouseWasDraggedSinceMouseDown()) {
        graph.setChangedFlag(true);
    } else if (e.getNumberOfClicks() == 2) {
        if (auto f = graph.graph.getNodeForId(pluginID))
            if (auto *w = graph.getOrCreateWindowFor(f, PluginWindow::Type::normal))
                w->toFront(true);
    }
}

Path Editor::Processor::getHexagonPath(Rectangle<int> area) {
    Path hexagon;
    hexagon.addPolygon(area.getCentre().toFloat(), 6, area.getWidth() * 0.28f, float_Pi * 0.5f);

    return (hexagon);
}

bool Editor::Processor::hitTest(int x, int y) {
    for (auto *child : getChildren())
        if (child->getBounds().contains(x, y))
            return true;

    return x >= 3 && x < getWidth() - 6 && y >= pinSize && y < getHeight() - pinSize;
}

Editor::FilterType Editor::Processor::getFilterType(AudioProcessorGraph::Node *node) {
    FilterType type;
    if (auto *processor = node->getProcessor()) {
        if (auto internalIO = dynamic_cast<AudioProcessorGraph::AudioGraphIOProcessor *>(processor)) {
            auto ioDeviceType = internalIO->getType();
            switch (ioDeviceType) {
                case AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode:
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
            }

            return (type);
        }

        if (processor->isMidiEffect()) {
            type = PluginMidiEffect;
        } else if (processor->acceptsMidi() &&
                   !processor->producesMidi() &&
                   processor->getTotalNumInputChannels() > 0 &&
                   processor->getTotalNumOutputChannels() > 0) {
            type = PluginSynthWithInput;
        } else if (processor->acceptsMidi() &&
                   !processor->producesMidi() &&
                   processor->getTotalNumInputChannels() == 0 &&
                   processor->getTotalNumOutputChannels() > 0) {
            type = PluginSynthWithInput;
        } else if (!processor->acceptsMidi() &&
                   !processor->producesMidi() &&
                   processor->getTotalNumInputChannels() > 0 &&
                   processor->getTotalNumOutputChannels() > 0) {
            type = PluginAudioEffect;
        } else if (processor->acceptsMidi() &&
                   processor->producesMidi() &&
                   processor->getTotalNumInputChannels() == 0 &&
                   processor->getTotalNumOutputChannels() > 0) {
            type = PluginSynth;
        } else {
            type = FuckIfIKnow;
        }
    }

    return (type);
}

Colour Editor::Processor::getColourForFilterType(FilterType type) {
    switch (type) {
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

Image Editor::Processor::getImageForFilter(FilterType type) {
    switch (type) {
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
            return (IMG(icon_plugin_external_png));
        default:
            return (IMG(icon_question_jpg));
    }
}

void Editor::Processor::paint(Graphics &g) {
    auto boxArea = getLocalBounds();
    bool isBypassed = false;
    Colour boxColour;

    FilterType ft;
    if (auto *f = graph.graph.getNodeForId(pluginID)) {
        isBypassed = f->isBypassed();
        ft = getFilterType(f);
    }

    if (auto *f = graph.graph.getNodeForId(pluginID)) {
        boxColour = getColourForFilterType(ft);

        if (isBypassed)
            boxColour = boxColour.overlaidWith(Colours::white).brighter();

        g.setColour(boxColour);
    }
    //g.setColour(Colours::red);
    //g.drawRect(getLocalBounds(), 1.0f);
    g.setColour(Colours::white);
    g.setFont(getDefaultTwonkSansFont());
    g.drawFittedText(getName(), boxArea, Justification::centredBottom, 2);

    Path hexagon = getHexagonPath(boxArea);
    g.setColour(boxColour);
    g.fillPath(hexagon);
    g.setColour(boxColour);
    g.strokePath(hexagon, PathStrokeType(1.0f));

    g.setColour(boxColour.contrasting(0.5f));
    g.drawImage(getImageForFilter(ft), boxArea.reduced(getWidth() * 0.35f).toFloat(),
                RectanglePlacement::onlyReduceInSize, true);
}

void Editor::Processor::resized() {
    bool hasMidiInputPin = false;
    bool hasMidiOutputPin = false;
    if (auto f = graph.graph.getNodeForId(pluginID)) {
        if (auto *processor = f->getProcessor()) {
            for (auto *pin : pins) {
                if (pin->pin.isMIDI()) {
                    if (pin->isInput) {
                        pin->setBounds(0, 0, NODE_SIZE, NODE_SIZE);
                    } else {
                        pin->setBounds(BUBBLE_SIZE - NODE_SIZE, BUBBLE_SIZE - NODE_SIZE, NODE_SIZE, NODE_SIZE);
                    }
                } else {
                    if (processor->isMidiEffect()) {
                        pin->setVisible(false);
                        continue;
                    }

                    auto channelIndex = pin->pin.channelIndex;
                    pin->setText(String(channelIndex));

                    if (pin->isInput) {
                        if (processor->getTotalNumInputChannels() <= 4) {
                            pin->setBounds(0, processor->acceptsMidi() ? (NODE_SIZE * (channelIndex + 1)) : (NODE_SIZE *
                                                                                                             (channelIndex)),
                                           NODE_SIZE, NODE_SIZE);
                        }
                    } else {
                        if (processor->getTotalNumOutputChannels() <= 4) {
                            pin->setBounds(BUBBLE_SIZE - NODE_SIZE, processor->producesMidi() ? 0 : (BUBBLE_SIZE -
                                                                                                     (NODE_SIZE *
                                                                                                      (channelIndex +
                                                                                                       1))), NODE_SIZE,
                                           NODE_SIZE);
                        } else if (processor->getTotalNumOutputChannels() > 4) {
                            if (channelIndex < 4) {
                                pin->setBounds(BUBBLE_SIZE - NODE_SIZE, processor->producesMidi() ? 0 : (BUBBLE_SIZE -
                                                                                                         (NODE_SIZE *
                                                                                                          (channelIndex +
                                                                                                           1))),
                                               NODE_SIZE, NODE_SIZE);
                            } else if (channelIndex < 6)
                                pin->setBounds((channelIndex - 3) * NODE_SIZE, BUBBLE_SIZE - NODE_SIZE, NODE_SIZE,
                                               NODE_SIZE);
                            else if (channelIndex < 8)
                                pin->setBounds((channelIndex - 5) * NODE_SIZE, 0, NODE_SIZE, NODE_SIZE);
                        }
                    }
                }
            }
        }
    }
}

Point<float> Editor::Processor::getPinPos(int index, bool isInput) const {
    for (auto *pin : pins)
        if (pin->pin.channelIndex == index && isInput == pin->isInput)
            return getPosition().toFloat() + pin->getBounds().getCentre().toFloat();

    return {};
}

void Editor::Processor::update() {
    const AudioProcessorGraph::Node::Ptr f(graph.graph.getNodeForId(pluginID));
    jassert (f != nullptr);

    numIns = f->getProcessor()->getTotalNumInputChannels();
    if (f->getProcessor()->acceptsMidi())
        ++numIns;

    numOuts = f->getProcessor()->getTotalNumOutputChannels();
    if (f->getProcessor()->producesMidi())
        ++numOuts;

    int w = BUBBLE_SIZE;
    int h = BUBBLE_SIZE;

    setSize(w, h);

    setName(f->getProcessor()->getName());

    {
        auto p = graph.getNodePosition(pluginID);
        setCentreRelative((float) p.x, (float) p.y);
    }

    if (numIns != numInputs || numOuts != numOutputs) {
        numInputs = numIns;
        numOutputs = numOuts;

        pins.clear();

        for (int i = 0; i < f->getProcessor()->getTotalNumInputChannels(); ++i)
            addAndMakeVisible(pins.add(new Editor::Pin(panel, {pluginID, i}, true)));

        if (f->getProcessor()->acceptsMidi())
            addAndMakeVisible(
                    pins.add(new Editor::Pin(panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, true)));

        for (int i = 0; i < f->getProcessor()->getTotalNumOutputChannels(); ++i)
            addAndMakeVisible(pins.add(new Editor::Pin(panel, {pluginID, i}, false)));

        if (f->getProcessor()->producesMidi())
            addAndMakeVisible(
                    pins.add(new Editor::Pin(panel, {pluginID, AudioProcessorGraph::midiChannelIndex}, false)));

        resized();
    }
}

AudioProcessor *Editor::Processor::getProcessor() const {
    if (auto node = graph.graph.getNodeForId(pluginID))
        return node->getProcessor();

    return {};
}

void Editor::Processor::showPopupMenu() {
    panel.showMenuForFilter(this);
}

void Editor::Processor::testStateSaveLoad() {
    if (auto *processor = getProcessor()) {
        MemoryBlock state;
        processor->getStateInformation(state);
        processor->setStateInformation(state.getData(), (int) state.getSize());
    }
}

void Editor::Processor::showWindow(PluginWindow::Type type) {
    if (auto node = graph.graph.getNodeForId(pluginID))
        if (auto *w = graph.getOrCreateWindowFor(node, type))
            w->toFront(true);
}

void Editor::Processor::timerCallback() {
// this should only be called on touch devices
    jassert (isOnTouchDevice());

    stopTimer();

    showPopupMenu();

}

void Editor::Processor::parameterValueChanged(int, float) {
    repaint();
}

void Editor::Processor::parameterGestureChanged(int, bool) {

}

void Editor::Processor::moved() {
    panel.filterMoved(this);
}

void Editor::Processor::mouseEnter(const MouseEvent &e)
{
    FilterType type;
    if (auto *f = graph.graph.getNodeForId(pluginID)) {
        if (auto *processor = f->getProcessor()) {
            if (auto internalIO = dynamic_cast<AudioProcessorGraph::AudioGraphIOProcessor *>(processor)) {
                auto ioDeviceType = internalIO->getType();
                _TXT("we are of internal type %d", ioDeviceType);
            }
        }
    }
}

void Editor::Processor::mouseExit(const MouseEvent &e)
{
    FilterType ft;
    if (auto *f = graph.graph.getNodeForId(pluginID)) {
        ft = getFilterType(f);
    }
    _TXT("%s %d", getName().toUTF8(), (uint8_t) ft);
}
#include "Pin.h"
#include "MainHostWindow.h"

Editor::Pin::Pin(Editor &p, AudioProcessorGraph::NodeAndChannel pinToUse, bool isIn)
        : panel(p), graph(p.graph), pin(pinToUse), isInput(isIn) {
    if (auto node = graph.graph.getNodeForId(pin.nodeID)) {
        String tip;

        if (pin.isMIDI()) {
            if (isInput)
                baseColour = Colours::red;
            else
                baseColour = Colours::red.brighter(0.5f);

            tip = isInput ? "MIDI Input"
                          : "MIDI Output";

        } else {
            if (isInput)
                baseColour = Colours::green;
            else
                baseColour = Colours::green.brighter(0.5f);

            auto &processor = *node->getProcessor();
            setName(processor.getName());
            auto channel = processor.getOffsetInBusBufferForAbsoluteChannelIndex(isInput, pin.channelIndex, busIdx);

            if (auto *bus = processor.getBus(isInput, busIdx))
                tip = bus->getName() + ": " +
                      AudioChannelSet::getAbbreviatedChannelTypeName(bus->getCurrentLayout().getTypeOfChannel(channel));
            else
                tip = (isInput ? "Main Input: "
                               : "Main Output: ") + String(pin.channelIndex + 1);

        }

        setTooltip(tip);
    }

    setSize(16, 16);
}

void Editor::Pin::paint(Graphics &g) {
    Path hexagon;
    hexagon.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.5f, float_Pi * 0.5f);
    g.setColour(baseColour.contrasting(0.1f));
    g.setFont(getDefaultTwonkMonoFont().withHeight((float) (NODE_SIZE * 0.7f)));
    g.drawText(text, getLocalBounds(), Justification::centred, false);
    g.setColour(baseColour.withAlpha(0.4f));
    g.fillPath(hexagon);
    g.setColour(baseColour.withAlpha(0.5f));
    g.strokePath(hexagon, PathStrokeType(NODE_SIZE * 0.1f));
}

void Editor::Pin::setText(const String &_text) {
    text = _text;
    repaint();
}

void Editor::Pin::mouseDown(const MouseEvent &e) {
    AudioProcessorGraph::NodeAndChannel dummy{{}, 0};

    panel.beginConnectorDrag(isInput ? dummy : pin,
                             isInput ? pin : dummy,
                             e);
}

void Editor::Pin::mouseDrag(const MouseEvent &e) {
    panel.dragConnector(e);
}

void Editor::Pin::mouseUp(const MouseEvent &e) {
    panel.endDraggingConnector(e);
}

#include "Connector.h"
#include "Editor.h"
#include "Processor.h"

Editor::Connector::Connector(Editor &p) : panel(p), graph(p.graph) {
    setAlwaysOnTop(true);
}

void Editor::Connector::setInput(AudioProcessorGraph::NodeAndChannel newSource) {
    if (connection.source != newSource) {
        connection.source = newSource;
        update();
    }
}

void Editor::Connector::setOutput(AudioProcessorGraph::NodeAndChannel newDest) {
    if (connection.destination != newDest) {
        connection.destination = newDest;
        update();
    }
}

void Editor::Connector::dragStart(Point<float> pos) {
    lastInputPos = pos;
    resizeToFit();
}

void Editor::Connector::dragEnd(Point<float> pos) {
    lastOutputPos = pos;
    resizeToFit();
}

void Editor::Connector::update() {
    Point<float> p1, p2;
    getPoints(p1, p2);

    if (lastInputPos != p1 || lastOutputPos != p2)
        resizeToFit();
}

void Editor::Connector::resizeToFit() {
    Point<float> p1, p2;
    getPoints(p1, p2);

    auto newBounds = Rectangle<float>(p1, p2).expanded(4.0f).getSmallestIntegerContainer();

    if (newBounds != getBounds())
        setBounds(newBounds);
    else
        resized();

    repaint();
}

void Editor::Connector::getPoints(Point<float> &p1, Point<float> &p2) const {
    p1 = lastInputPos;
    p2 = lastOutputPos;

    if (auto *src = panel.getComponentForPlugin(connection.source.nodeID)) {
        p1 = src->getPinPos(connection.source.channelIndex, false);
    }

    if (auto *dest = panel.getComponentForPlugin(connection.destination.nodeID)) {
        p2 = dest->getPinPos(connection.destination.channelIndex, true);
    }
}

void Editor::Connector::paint(Graphics &g) {
    if (connection.source.isMIDI() || connection.destination.isMIDI())
        g.setColour(Colours::red);
    else
        g.setColour(Colours::green);

    g.fillPath(linePath);
}

bool Editor::Connector::hitTest(int x, int y) {
    auto pos = Point<int>(x, y).toFloat();

    if (hitPath.
            contains(pos)
            ) {
        double distanceFromStart, distanceFromEnd;
        getDistancesFromEnds(pos, distanceFromStart, distanceFromEnd
        );

// avoid clicking the connector when over a pin
        return distanceFromStart > 7.0 && distanceFromEnd > 7.0;
    }

    return false;
}

void Editor::Connector::mouseDown(const MouseEvent &) {
    dragging = false;
}

void Editor::Connector::mouseDrag(const MouseEvent &e) {
    if (dragging) {
        panel.dragConnector(e);
    } else if (e.mouseWasDraggedSinceMouseDown()) {
        dragging = true;

        graph.graph.removeConnection(connection);

        double distanceFromStart, distanceFromEnd;
        getDistancesFromEnds(getPosition().toFloat() + e.position, distanceFromStart, distanceFromEnd);
        const bool isNearerSource = (distanceFromStart < distanceFromEnd);
        DBG("mouseDrag isNearerSource:" + String(isNearerSource ? 1 : 0));
        AudioProcessorGraph::NodeAndChannel dummy{{}, 0};

        panel.beginConnectorDrag(isNearerSource ? dummy : connection.source,
                                 isNearerSource ? connection.destination : dummy,
                                 e);
    }
}

void Editor::Connector::mouseUp(const MouseEvent &e) {
    if (dragging)
        panel.endDraggingConnector(e);
}

void Editor::Connector::resized() {
    Point<float> p1, p2;
    getPoints(p1, p2
    );

    lastInputPos = p1;
    lastOutputPos = p2;

    p1 -= getPosition().toFloat();
    p2 -= getPosition().toFloat();
    linePath.clear();
    linePath.startNewSubPath(p1);
    linePath.cubicTo(p1.x, p1.y + (p2.y - p1.y) * 0.33f,
                     p2.x, p1.y + (p2.y - p1.y) * 0.66f,
                     p2.x, p2.y);

    PathStrokeType wideStroke(8.0f);
    wideStroke.createStrokedPath(hitPath, linePath);

    PathStrokeType stroke(2.5f);
    stroke.createStrokedPath(linePath, linePath);

    auto arrowW = 5.0f;
    auto arrowL = 4.0f;

    Path arrow;
    arrow.addTriangle(-arrowL, arrowW,
                      -arrowL, -arrowW,
                      arrowL, 0.0f);
    arrow.applyTransform(AffineTransform().rotated(
            MathConstants<float>::halfPi - (float) atan2(p2.x - p1.x, p2.y - p1.y)).translated((p1 + p2) * 0.5f));

    linePath.addPath(arrow);
    linePath.setUsingNonZeroWinding(true);
}

void Editor::Connector::getDistancesFromEnds(Point<float> p, double &distanceFromStart, double &distanceFromEnd) const {
    Point<float> p1, p2;
    getPoints(p1, p2);

    distanceFromStart = p1.getDistanceFrom(p);
    distanceFromEnd = p2.getDistanceFrom(p);
}
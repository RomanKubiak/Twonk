#include "TwonkFilterConnector.h"
#include "TwonkFilterComponent.h"

TwonkFilterConnector::TwonkFilterConnector (GraphEditorPanel& p) : panel (p), graph (*p.graph.get())
{
	setAlwaysOnTop (true);
}

void TwonkFilterConnector::setInput (AudioProcessorGraph::NodeAndChannel newSource)
{
	if (connection.source != newSource)
	{
		connection.source = newSource;
		update();
	}
}

void TwonkFilterConnector::setOutput (AudioProcessorGraph::NodeAndChannel newDest)
{
	if (connection.destination != newDest)
	{
		connection.destination = newDest;
		update();
	}
}

void TwonkFilterConnector::dragStart (Point<float> pos)
{
	lastInputPos = pos;
	resizeToFit();
}

void TwonkFilterConnector::dragEnd (Point<float> pos)
{
	lastOutputPos = pos;
	resizeToFit();
}

void TwonkFilterConnector::update()
{
	Point<float> p1, p2;
	getPoints (p1, p2);

	if (lastInputPos != p1 || lastOutputPos != p2)
		resizeToFit();
}

void TwonkFilterConnector::resizeToFit()
{
	Point<float> p1, p2;
	getPoints (p1, p2);

	auto newBounds = Rectangle<float> (p1, p2).expanded (24.0f).getSmallestIntegerContainer();

	if (newBounds != getBounds())
		setBounds (newBounds);
	else
		resized();

	repaint();
}

void TwonkFilterConnector::getPoints (Point<float>& p1, Point<float>& p2) const
{
	p1 = lastInputPos;
	p2 = lastOutputPos;

	if (auto* src = panel.getComponentForFilter (connection.source.nodeID))
		p1 = src->getPinPos (connection.source.channelIndex, false);

	if (auto* dest = panel.getComponentForFilter (connection.destination.nodeID))
		p2 = dest->getPinPos (connection.destination.channelIndex, true);
}

void TwonkFilterConnector::paint (Graphics& g)
{
	if (connection.source.isMIDI() || connection.destination.isMIDI())
		g.setColour (Colours::red);
	else
		g.setColour (Colours::green);

	g.fillPath (linePath);
}

bool TwonkFilterConnector::hitTest (int x, int y)
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

void TwonkFilterConnector::mouseDown (const MouseEvent&)
{
	dragging = false;
}

void TwonkFilterConnector::mouseDrag (const MouseEvent& e)
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

		AudioProcessorGraph::NodeAndChannel dummy {{}, 0};

		panel.beginConnectorDrag (isNearerSource ? dummy : connection.source,
			isNearerSource ? connection.destination : dummy,
			e);
	}
}

void TwonkFilterConnector::mouseUp (const MouseEvent& e)
{
	if (dragging)
		panel.endDraggingConnector (e);
}

void TwonkFilterConnector::resized()
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

	PathStrokeType stroke (6.5f);
	stroke.createStrokedPath (linePath, linePath);

	auto arrowW = 12.0f;
	auto arrowL = 12.0f;

	Path arrow;
	arrow.addTriangle (-arrowL, arrowW,
		-arrowL, -arrowW,
		arrowL, 0.0f);

	arrow.applyTransform (AffineTransform()
		.rotated (MathConstants<float>::halfPi - (float)atan2 (p2.x - p1.x, p2.y - p1.y))
		.translated ((p1 + p2) * 0.5f));

	linePath.addPath (arrow);
	linePath.setUsingNonZeroWinding (true);
}

void TwonkFilterConnector::getDistancesFromEnds (Point<float> p, double& distanceFromStart, double& distanceFromEnd) const
{
	Point<float> p1, p2;
	getPoints (p1, p2);

	distanceFromStart = p1.getDistanceFrom (p);
	distanceFromEnd = p2.getDistanceFrom (p);
}
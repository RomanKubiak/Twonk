#include "Editor.h"
#include "Processor.h"
#include "Connector.h"
#include "Processor.h"
#include "Pin.h"

#include "TwonkToolBar.h"
#include "TwonkFilterPopupProperties.h"
#include "MainHostWindow.h"

Editor::Editor (PluginGraph& g, AudioDeviceManager &_dm, TwonkPlayHead &_twonkPlayHead)
        : graph (g), dm(_dm), twonkPlayHead(_twonkPlayHead),
          directoryListThread("Twonk programs lister"),
          twonkDocumentFileFilter("*.twonk", "", "Twonk programs"),
          directoryContentsList(&twonkDocumentFileFilter, directoryListThread),
          twonkProgramListWrapper(directoryContentsList, g)
{
    toolBar.reset(new TwonkToolBar(*this));
    addAndMakeVisible(toolBar.get());
    toolBar->setVisible(true);
    toolBar->setBounds(16, 64, 64, 196);
    toolBar->setAlwaysOnTop(true);

    twonkTransport.reset(new TwonkTransport(twonkPlayHead));
    addAndMakeVisible(twonkTransport.get());
    twonkTransport->setVisible(true);
    twonkTransport->setAlwaysOnTop(true);
    twonkTransport->setTopLeftPosition(312, 0);

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

    filterPropertiesPopup.reset (new TwonkFilterPopupProperties(*this));
    addAndMakeVisible(filterPropertiesPopup.get());
    filterPropertiesPopup->setVisible(false);

    pinConnectionHint.reset(new BubbleMessageComponent());
    addChildComponent(pinConnectionHint.get());
    pinConnectionHint->setAlwaysOnTop(true);
    setSize(1024, 600);
}

Editor::~Editor()
{
    graph.removeChangeListener (this);
    draggingConnector = nullptr;
    filterPropertiesPopup = nullptr;
    nodes.clear();
    connectors.clear();
}

void Editor::paint (Graphics& g)
{
    auto im = IMG(background_jpg);
    g.drawImageAt(im, 0, 0, false);
    // g.fillAll(Colours::darkgrey);
}

void Editor::mouseDown (const MouseEvent& e)
{
    if (filterPropertiesPopup->isVisible())
        filterPropertiesPopup->setVisible(false);

    if (isOnTouchDevice())
    {
        originalTouchPos = e.position.toInt();
        startTimer (750);
    }

    if (e.mods.isPopupMenu())
        showPopupMenu (e.position.toInt());
}

void Editor::mouseUp (const MouseEvent&)
{
    if (isOnTouchDevice())
    {
        stopTimer();
        callAfterDelay (250, []() { PopupMenu::dismissAllActiveMenus(); });
    }
}

void Editor::mouseDrag (const MouseEvent& e)
{
    if (isOnTouchDevice() && e.getDistanceFromDragStart() > 5)
        stopTimer();
}

void Editor::createNewPlugin (const PluginDescription& desc, Point<int> position)
{
    graph.addPlugin (desc, position.toDouble() / Point<double> ((double) getWidth(), (double) getHeight()));
}

Editor::Processor* Editor::getComponentForPlugin (AudioProcessorGraph::NodeID nodeID) const
{
    for (auto* fc : nodes)
        if (fc->pluginID == nodeID)
            return fc;

    return nullptr;
}

Editor::Connector* Editor::getComponentForConnection (const AudioProcessorGraph::Connection& conn) const
{
    for (auto* cc : connectors)
        if (cc->connection == conn)
            return cc;

    return nullptr;
}

Editor::Pin* Editor::findPinAt (Point<float> pos) const
{
    for (auto* fc : nodes)
    {
        // NB: A Visual Studio optimiser error means we have to put this Component* in a local
        // variable before trying to cast it, or it gets mysteriously optimised away..
        auto* comp = fc->getComponentAt (pos.toInt() - fc->getPosition());

        if (auto* pin = dynamic_cast<Editor::Pin *> (comp))
            return pin;
    }

    return nullptr;
}

void Editor::resized()
{
    updateComponents();
}

void Editor::changeListenerCallback (ChangeBroadcaster*)
{
    updateComponents();
}

void Editor::updateComponents()
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
            Editor::Processor* comp = nodes.add (new Editor::Processor (*this, f->nodeID));
            addAndMakeVisible (comp);
            comp->update();
        }
    }

    for (auto& c : graph.graph.getConnections())
    {
        if (getComponentForConnection (c) == nullptr)
        {
            auto* comp = connectors.add (new Editor::Connector (*this));
            addAndMakeVisible (comp);

            comp->setInput (c.source);
            comp->setOutput (c.destination);
        }
    }
}

void Editor::showPopupMenu (Point<int> mousePos)
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

void Editor::beginConnectorDrag (AudioProcessorGraph::NodeAndChannel source,
                                           AudioProcessorGraph::NodeAndChannel dest,
                                           const MouseEvent& e)
{
    auto* c = dynamic_cast<Editor::Connector*> (e.originalComponent);
    connectors.removeObject (c, false);
    draggingConnector.reset (c);

    if (draggingConnector == nullptr)
        draggingConnector.reset (new Editor::Connector (*this));

    draggingConnector->setInput (source);
    draggingConnector->setOutput (dest);

    addAndMakeVisible (draggingConnector.get());
    draggingConnector->toFront (false);

    dragConnector (e);
}

void Editor::dragConnector (const MouseEvent& e)
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
                AttributedString as;
                as.append("Connect to: ", getDefaultTwonkSansFont(), Colours::white);
                as.append(pin->getTooltip(), getDefaultTwonkSansFont().boldened(), Colours::white);
                pinConnectionHint->showAt(pin, as, 1200, true, false);
            }
        }

        if (draggingConnector->connection.source.nodeID == AudioProcessorGraph::NodeID())
            draggingConnector->dragStart (pos);
        else
            draggingConnector->dragEnd (pos);
    }
}

void Editor::endDraggingConnector (const MouseEvent& e)
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

void Editor::timerCallback()
{
    // this should only be called on touch devices
    jassert (isOnTouchDevice());

    stopTimer();
    showPopupMenu (originalTouchPos);
}

void Editor::toggleProgramMenu()
{
    twonkProgramListWrapper.setVisible(!twonkProgramListWrapper.isVisible());
}

void Editor::selectionChanged()
{

}

void Editor::fileClicked(const File &file, const MouseEvent &e)
{

}

void Editor::fileDoubleClicked(const File &file)
{
}

void Editor::showMenuForFilter(struct Editor::Processor *filter)
{
    filterPropertiesPopup->setVisible(true);
    filterPropertiesPopup->setFilter(filter);
    filterPropertiesPopup->setCentrePosition(filter->getBounds().getCentre());
}

void Editor::filterMoved (struct Editor::Processor *filter)
{
    if (filterPropertiesPopup->isVisible() && filter == filterPropertiesPopup->getFilter())
    {
        filterPropertiesPopup->setCentrePosition(filter->getBounds().getCentre());
    }
}

void Editor::menuForFilterClicked(const int r)
{
    struct Editor::Processor *filter = filterPropertiesPopup->getFilter();
    filterPropertiesPopup->setVisible(false);
    filterPropertiesPopup->setFilter(nullptr);

    switch (r)
    {
        case 1:   graph.graph.removeNode (filter->pluginID); break;
        case 2:   graph.graph.disconnectNode (filter->pluginID); break;
        case 3:
        {
            if (auto* node = graph.graph.getNodeForId (filter->pluginID))
                node->setBypassed (!node->isBypassed());

            repaint();

            break;
        }
        case 10:  filter->showWindow (PluginWindow::Type::normal); break;
        case 11:  filter->showWindow (PluginWindow::Type::programs); break;
        case 12:  filter->showWindow (PluginWindow::Type::generic); break;
        case 20:  filter->showWindow (PluginWindow::Type::audioIO); break;

        default:  break;
    }
}

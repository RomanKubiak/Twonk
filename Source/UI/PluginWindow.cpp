/*
  ==============================================================================

    PluginWindow.cpp
    Created: 10 Aug 2019 3:40:23pm
    Author:  atom

  ==============================================================================
*/

#include "PluginWindow.h"
#include "Filters/PluginGraph.h"
#include "UI/GraphEditorPanel.h"

PluginWindow::PluginWindow (AudioProcessorGraph::Node* n, Type t, OwnedArray<PluginWindow>& windowList, PluginGraph &_owner)
	: DocumentWindow (n->getProcessor()->getName(),
		LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
		DocumentWindow::minimiseButton | DocumentWindow::closeButton, false),
		activeWindowList (windowList),
		node (n), type (t), owner(_owner)
{	
	int lastWidth=-1, lastHeight=-1;
	bool lastSticky;
	if (auto* ui = createProcessorEditor (*node->getProcessor(), type))
	{
		DBG("PluginWindow::ctor" + String((int)node->properties.getWithDefault(getLastStickyProp (type), -1)));
		lastSticky = (int)node->properties.getWithDefault(getLastStickyProp (type), -1) ? true : false;

		if ((int)node->properties.getWithDefault(getLastWidthProp (type), -1) != -1)
			lastWidth = node->properties.getWithDefault(getLastWidthProp (type), -1);

		if ((int)node->properties.getWithDefault(getLastHeightProp (type), -1) != -1)
			lastHeight = node->properties.getWithDefault(getLastHeightProp (type), -1);

		if (lastWidth > 0 && lastHeight > 0)
			ui->setSize(lastWidth, lastHeight - getTitleBarHeight());

		setContentOwned (ui, true);
	}

	int possibleX = owner.getDocumentOwner().getScreenBounds().getCentreX();
	int possibleY = owner.getDocumentOwner().getScreenBounds().getCentreY();
	setTopLeftPosition (node->properties.getWithDefault (getLastXProp (type), possibleX),
		node->properties.getWithDefault (getLastYProp (type), possibleY));
	
	node->properties.set (getOpenProp (type), true);
	setAlwaysOnTop(lastSticky);
	setLookAndFeel(&lf);
	addToDesktop();
	setVisible (true);
}

PluginWindow::~PluginWindow()
{
	setLookAndFeel(nullptr);
	clearContentComponent();
}

void PluginWindow::moved()
{
	node->properties.set (getLastXProp (type), getX());
	node->properties.set (getLastYProp (type), getY());
	node->properties.set (getLastWidthProp (type), getWidth());
	node->properties.set (getLastHeightProp (type), getHeight());
	node->properties.set (getLastStickyProp (type), isAlwaysOnTop());
	owner.setChangedFlag(true);
}

void PluginWindow::closeButtonPressed()
{
	node->properties.set (getOpenProp (type), false);
	activeWindowList.removeObject (this);
}
	
String PluginWindow::getLastStickyProp (Type type)
{
	return "uiLastSicky_" + getTypeName(type);
}

String PluginWindow::getLastXProp (Type type)
{
	return "uiLastX_" + getTypeName (type);
}

String PluginWindow::getLastYProp (Type type)
{
	return "uiLastY_" + getTypeName (type);
}

String PluginWindow::getLastWidthProp (Type type)
{
	return "uiLastWidth_" + getTypeName (type);
}

String PluginWindow::getLastHeightProp (Type type)
{
	return "uiLastHeight_" + getTypeName (type);
}

String PluginWindow::getOpenProp  (Type type)
{
	return "uiopen_" + getTypeName (type);
}

float PluginWindow::getDesktopScaleFactor() const
{
	return 1.0f;
}

AudioProcessorEditor* PluginWindow::createProcessorEditor (AudioProcessor& processor, PluginWindow::Type type)
{
	DBG("PluginWindow::createProcessorEditor");
	if (type == PluginWindow::Type::normal)
	{
		if (auto* ui = processor.createEditorIfNeeded())
			return ui;

		type = PluginWindow::Type::generic;
	}

	if (type == PluginWindow::Type::generic)  return new GenericAudioProcessorEditor (processor);
	if (type == PluginWindow::Type::audioIO)  return new IOConfigurationWindow (processor);

	jassertfalse;
	return {};
}

String PluginWindow::getTypeName (Type type)
{
	switch (type)
	{
		case Type::normal:     return "Normal";
		case Type::generic:    return "Generic";
		case Type::programs:   return "Programs";
		case Type::audioIO:    return "IO";
		case Type::debug:      return "Debug";
		default:               return {};
	}
}

int PluginWindow::getDesktopWindowStyleFlags () const
{
	int flags = DocumentWindow::getDesktopWindowStyleFlags();
	flags &= ~(ComponentPeer::windowAppearsOnTaskbar);
	return (flags);
}
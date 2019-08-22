/*
  ==============================================================================

    PluginWindow.cpp
    Created: 10 Aug 2019 3:40:23pm
    Author:  atom

  ==============================================================================
*/

#include "PluginWindow.h"
#include "Filters/PluginGraph.h"

PluginWindow::PluginWindow (AudioProcessorGraph::Node* n, Type t, OwnedArray<PluginWindow>& windowList, PluginGraph &_owner)
	: DocumentWindow (n->getProcessor()->getName(),
		LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
		DocumentWindow::minimiseButton | DocumentWindow::closeButton, false),
		activeWindowList (windowList),
		node (n), type (t), owner(_owner)
{	
	if (auto* ui = createProcessorEditor (*node->getProcessor(), type))
	{
		ui->setSize(node->properties.getWithDefault(getLastWidthProp (type), 400),
			(int)node->properties.getWithDefault(getLastHeightProp (type), 200) - getTitleBarHeight());
		setContentOwned (ui, true);
	}

	DBG("PluginWindow::ctor lastWidth: " + node->properties.getWithDefault(getLastWidthProp (type), -1).toString());
	setTopLeftPosition (node->properties.getWithDefault (getLastXProp (type), Random::getSystemRandom().nextInt (500)),
		node->properties.getWithDefault (getLastYProp (type), Random::getSystemRandom().nextInt (500)));

	node->properties.set (getOpenProp (type), true);
	addToDesktop();
	setVisible (true);
}

PluginWindow::~PluginWindow()
{
	clearContentComponent();
}

void PluginWindow::moved()
{
	DBG("PluginWindow::moved");
	node->properties.set (getLastXProp (type), getX());
	node->properties.set (getLastYProp (type), getY());
	node->properties.set (getLastWidthProp (type), getWidth());
	node->properties.set (getLastHeightProp (type), getHeight());
	owner.setChangedFlag(true);
}

void PluginWindow::closeButtonPressed()
{
	node->properties.set (getOpenProp (type), false);
	activeWindowList.removeObject (this);
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
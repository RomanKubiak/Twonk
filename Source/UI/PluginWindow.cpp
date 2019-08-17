/*
  ==============================================================================

    PluginWindow.cpp
    Created: 10 Aug 2019 3:40:23pm
    Author:  atom

  ==============================================================================
*/

#include "PluginWindow.h"

PluginWindow::PluginWindow (AudioProcessorGraph::Node* n, Type t, OwnedArray<PluginWindow>& windowList)
	: DocumentWindow (n->getProcessor()->getName(),
		LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
		DocumentWindow::minimiseButton | DocumentWindow::closeButton),
		activeWindowList (windowList),
		node (n), type (t)
{
	setSize (400, 300);
	DBG("create plugin window");
	
	if (auto* ui = createProcessorEditor (*node->getProcessor(), type))
		setContentOwned (ui, true);

	setTopLeftPosition (node->properties.getWithDefault (getLastXProp (type), Random::getSystemRandom().nextInt (500)),
		node->properties.getWithDefault (getLastYProp (type), Random::getSystemRandom().nextInt (500)));

	node->properties.set (getOpenProp (type), true);

	setVisible (true);
}

PluginWindow::~PluginWindow()
{
	clearContentComponent();
}

void PluginWindow::moved()
{
	node->properties.set (getLastXProp (type), getX());
	node->properties.set (getLastYProp (type), getY());
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
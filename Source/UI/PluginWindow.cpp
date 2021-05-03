#include "PluginWindow.h"
#include "Filters/PluginGraph.h"
#include "Panel/Editor.h"
#include "MainHostWindow.h"

PluginWindowLookAndFeel::PluginWindowLookAndFeel() : owner(nullptr)
{
	stickyButton.reset(new ImageButton("STicky"));
	stickyButton->setClickingTogglesState(true);
	stickyButton->setImages(true, true, true,
		IMG(icon_pin_png), 0.200f, Colour (0x00000000),
		IMG(icon_pin_png), 0.661f, Colour (0xffffffff),
		IMG(icon_pin_png), 1.000f, Colour (0xffffffff));
}

void PluginWindowLookAndFeel::buttonClicked(Button *b)
{
	if (owner)
	{
		owner->setAlwaysOnTop(stickyButton->getToggleState());
	}
}
void PluginWindowLookAndFeel::drawDocumentWindowTitleBar (DocumentWindow& window, Graphics& g,
	int w, int h, int titleSpaceX, int titleSpaceW,
	const Image* icon, bool drawTitleTextOnLeft)
{
	if (w * h == 0)
		return;

	auto isActive = window.isActiveWindow();

	g.setColour (getCurrentColourScheme().getUIColour (ColourScheme::widgetBackground));
	g.fillAll();

	Font font = getDefaultTwonkSansFont().withHeight(h * 0.65f);
	g.setFont (font);

	auto textW = font.getStringWidth (window.getName());
	auto iconW = 0;
	auto iconH = 0;

	if (icon != nullptr)
	{
		iconH = static_cast<int> (font.getHeight());
		iconW = icon->getWidth() * iconH / icon->getHeight() + 4;
	}

	textW = jmin (titleSpaceW, textW + iconW);
	auto textX = drawTitleTextOnLeft ? titleSpaceX
		: jmax (titleSpaceX, (w - textW) / 2);

	if (textX + textW > titleSpaceX + titleSpaceW)
		textX = titleSpaceX + titleSpaceW - textW;

	if (icon != nullptr)
	{
		g.setOpacity (isActive ? 1.0f : 0.6f);
		g.drawImageWithin (*icon, textX, (h - iconH) / 2, iconW, iconH,
			RectanglePlacement::centred, false);
		textX += iconW;
		textW -= iconW;
	}

	if (window.isColourSpecified (DocumentWindow::textColourId) || isColourSpecified (DocumentWindow::textColourId))
		g.setColour (window.findColour (DocumentWindow::textColourId));
	else
		g.setColour (getCurrentColourScheme().getUIColour (ColourScheme::defaultText));

	g.drawText (window.getName(), textX, 0, textW, h, Justification::centredLeft, true);
	Component *c = dynamic_cast<Component*>(&window);
	owner = &window;
	stickyButton->setBounds(0, 0, 24, 24);
	stickyButton->addListener(this);
	if (owner->isAlwaysOnTop())
	{
		stickyButton->setToggleState(true, dontSendNotification);
	}

	c->addAndMakeVisible(stickyButton.get());
}

/**
	Window that holds the plugin editor
*/
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
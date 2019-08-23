#pragma once
#include "../Filters/IOConfigurationWindow.h"
#include "TwonkLookAndFeel.h"
#include "BinaryData.h"
#include "Twonk.h"
class PluginGraph;

class PluginWindowLookAndFeel : public LookAndFeel_V4, public Button::Listener
{
private:
	std::unique_ptr<ImageButton> stickyButton;
	DocumentWindow *owner;
public:
	PluginWindowLookAndFeel() : owner(nullptr)
	{
		stickyButton.reset(new ImageButton("STicky"));
		stickyButton->setClickingTogglesState(true);
		stickyButton->setImages(true, true, true,
			IMG(icon_pin_png), 0.200f, Colour (0x00000000),
			IMG(icon_pin_png), 0.661f, Colour (0x00000000),
			IMG(icon_pin_png), 1.000f, Colour (0x00000000));
	}

	void buttonClicked(Button *b)
	{
		if (owner)
		{
			owner->setAlwaysOnTop(stickyButton->getToggleState());
		}
	}
	void drawDocumentWindowTitleBar (DocumentWindow& window, Graphics& g,
		int w, int h, int titleSpaceX, int titleSpaceW,
		const Image* icon, bool drawTitleTextOnLeft)
	{
		if (w * h == 0)
			return;

		auto isActive = window.isActiveWindow();

		g.setColour (getCurrentColourScheme().getUIColour (ColourScheme::widgetBackground));
		g.fillAll();

		Font font (h * 0.65f, Font::plain);
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
};

class PluginWindow : public DocumentWindow
{
	public:
		enum class Type
		{
			normal = 0,
			generic,
			programs,
			audioIO,
			debug,
			numTypes
		};

		PluginWindow (AudioProcessorGraph::Node* n, Type t, OwnedArray<PluginWindow>& windowList, PluginGraph &_owner);
		~PluginWindow() override;
		void moved() override;
		void closeButtonPressed() override;
		static String getLastXProp (Type type);
		static String getLastYProp (Type type);
		static String getLastWidthProp (Type type);
		static String getLastHeightProp (Type type);
		static String getLastStickyProp (Type type);
		static String getOpenProp  (Type type);
		int getDesktopWindowStyleFlags () const override;
		OwnedArray<PluginWindow>& activeWindowList;
		const AudioProcessorGraph::Node::Ptr node;
		const Type type;

	private:
		float getDesktopScaleFactor() const override;
		static AudioProcessorEditor* createProcessorEditor (AudioProcessor& processor, PluginWindow::Type type);
		static String getTypeName (Type type);
		PluginGraph &owner;
		PluginWindowLookAndFeel lf;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWindow)
};
#pragma once
#include "../Filters/IOConfigurationWindow.h"
#include "TwonkLookAndFeel.h"
#include "BinaryData.h"
#include "Twonk.h"
class PluginGraph;

class PluginWindowLookAndFeel : public LookAndFeel_V4, public Button::Listener
{
	public:
		PluginWindowLookAndFeel();
		void drawDocumentWindowTitleBar (DocumentWindow& window, Graphics& g,
			int w, int h, int titleSpaceX, int titleSpaceW,
			const Image* icon, bool drawTitleTextOnLeft);
		void buttonClicked(Button *b);
	private:
		std::unique_ptr<ImageButton> stickyButton;
		DocumentWindow *owner;
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
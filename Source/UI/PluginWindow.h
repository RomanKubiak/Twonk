#pragma once
#include "../Filters/IOConfigurationWindow.h"
#include "TwonkLookAndFeel.h"
class PluginGraph;
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
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWindow)
};
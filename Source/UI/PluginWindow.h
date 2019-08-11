/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma once

#include "../Filters/FilterIOConfiguration.h"
#include "TwonkFilterPropertiesEditor.h"

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

		PluginWindow (AudioProcessorGraph::Node* n, Type t, OwnedArray<PluginWindow>& windowList);
		~PluginWindow() override;
		void moved() override;
		void closeButtonPressed() override;
		static String getLastXProp (Type type);
		static String getLastYProp (Type type);
		static String getOpenProp  (Type type);
		OwnedArray<PluginWindow>& activeWindowList;
		const AudioProcessorGraph::Node::Ptr node;
		const Type type;

	private:
		float getDesktopScaleFactor() const override;
		static AudioProcessorEditor* createProcessorEditor (AudioProcessor& processor, PluginWindow::Type type);
		static String getTypeName (Type type);
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWindow)
};
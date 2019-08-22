/*
  ==============================================================================

	PluginListWindow.cpp
	Created: 21 Aug 2019 4:15:14pm
	Author:  rkubiak

  ==============================================================================
*/

#include "Twonk.h"
class MainHostWindow;

static String getPluginDescription (const PluginDescription& desc)
{
	StringArray items;

	if (desc.descriptiveName != desc.name)
		items.add (desc.descriptiveName);

	items.add (desc.version);

	items.removeEmptyStrings();
	return items.joinIntoString (" - ");
}

class PluginListModel : public TableListBoxModel
{
	public:
		PluginListModel(PluginListComponent &_pluginListComponent, KnownPluginList &_knownPluginList);
		int getNumRows() override;
		void paintRowBackground (Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
		void paintCell (Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
		void cellClicked (int rowNumber, int columnId, const juce::MouseEvent& e) override;
		void sortOrderChanged (int newSortColumnId, bool isForwards) override;
	private:
		PluginListComponent &pluginListComponent;
		KnownPluginList &knownPluginList;
};

class PluginListWindow : public DocumentWindow
{
	public:
		PluginListWindow (MainHostWindow& mw, AudioPluginFormatManager& pluginFormatManager);
		~PluginListWindow() override;
		void closeButtonPressed() override;

	private:
		std::auto_ptr<PluginListComponent> pluginListComponent;
		MainHostWindow& owner;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginListWindow)
};
/*
  ==============================================================================

    PluginListWindow.cpp
    Created: 21 Aug 2019 4:15:14pm
    Author:  rkubiak

  ==============================================================================
*/

#include "PluginListWindow.h"
#include "MainHostWindow.h"

PluginListModel::PluginListModel(PluginListComponent &_pluginListComponent, KnownPluginList &_knownPluginList)
	: pluginListComponent(_pluginListComponent), knownPluginList(_knownPluginList)
{

}
int PluginListModel::getNumRows()
{
	return knownPluginList.getNumTypes() + knownPluginList.getBlacklistedFiles().size();
}

void PluginListModel::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	const auto defaultColour = pluginListComponent.findColour (ListBox::backgroundColourId);
	const auto c = rowIsSelected ? defaultColour.interpolatedWith (pluginListComponent.findColour (ListBox::textColourId), 0.5f)
		: defaultColour;

	g.fillAll (c);
}

enum
{
	nameCol = 1,
	typeCol = 2,
	categoryCol = 3,
	manufacturerCol = 4,
	descCol = 5
};

void PluginListModel::paintCell (Graphics &g, int row, int columnId, int width, int height, bool rowIsSelected)
{
	String text;
	bool isBlacklisted = row >= knownPluginList.getNumTypes();

	if (isBlacklisted)
	{
		if (columnId == nameCol)
			text = knownPluginList.getBlacklistedFiles()[row - knownPluginList.getNumTypes()];
		else if (columnId == descCol)
			text = TRANS("Deactivated after failing to initialise correctly");
	}
	else
	{
		auto desc = knownPluginList.getTypes()[row];

		switch (columnId)
		{
		case nameCol:         text = desc.name; break;
		case typeCol:         text = desc.pluginFormatName; break;
		case categoryCol:     text = desc.category.isNotEmpty() ? desc.category : "-"; break;
		case manufacturerCol: text = desc.manufacturerName; break;
		case descCol:         text = getPluginDescription (desc); break;

		default: jassertfalse; break;
		}
	}

	if (text.isNotEmpty())
	{
		const auto defaultTextColour = pluginListComponent.findColour (ListBox::textColourId);
		g.setColour (isBlacklisted ? Colours::red
			: columnId == nameCol ? defaultTextColour
			: defaultTextColour.interpolatedWith (Colours::transparentBlack, 0.3f));
		g.setFont (Font (height * 0.7f, Font::bold));
		g.drawFittedText (text, 4, 0, width - 6, height, Justification::centredLeft, 1, 0.9f);
	}
}

void PluginListModel::cellClicked (int rowNumber, int columnId, const juce::MouseEvent& e)
{
	TableListBoxModel::cellClicked (rowNumber, columnId, e);

	if (rowNumber >= 0 && rowNumber < getNumRows() && e.mods.isPopupMenu())
		pluginListComponent.createMenuForRow (rowNumber).showMenuAsync (PopupMenu::Options().withDeletionCheck (pluginListComponent));
}

void PluginListModel::sortOrderChanged (int newSortColumnId, bool isForwards)
{
	switch (newSortColumnId)
	{
	case nameCol:         knownPluginList.sort (KnownPluginList::sortAlphabetically, isForwards); break;
	case typeCol:         knownPluginList.sort (KnownPluginList::sortByFormat, isForwards); break;
	case categoryCol:     knownPluginList.sort (KnownPluginList::sortByCategory, isForwards); break;
	case manufacturerCol: knownPluginList.sort (KnownPluginList::sortByManufacturer, isForwards); break;
	case descCol:         break;

	default: jassertfalse; break;
	}
}

PluginListWindow::PluginListWindow (MainHostWindow& mw, AudioPluginFormatManager& pluginFormatManager)
		:   DocumentWindow ("Available Plugins",
			LookAndFeel::getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
			DocumentWindow::minimiseButton | DocumentWindow::closeButton), owner (mw)
{
		auto deadMansPedalFile = getAppProperties().getUserSettings()->getFile().getSiblingFile ("RecentlyCrashedPluginsList");
		pluginListComponent.reset(new PluginListComponent (pluginFormatManager,
			owner.knownPluginList,
			deadMansPedalFile,
			getAppProperties().getUserSettings(), true));
		setContentNonOwned (pluginListComponent.get(), true);

		//pluginListComponent->getOptionsButton().setVisible(false);
		//pluginListComponent->setTableModel(new PluginListModel(*pluginListComponent, owner.knownPluginList));
		setResizable (true, false);
		setResizeLimits (400, 450, 800, 550);
		centreAroundComponent(&mw, 600, 600);
		restoreWindowStateFromString (getAppProperties().getUserSettings()->getValue ("listWindowPos"));
		setVisible (true);
	}

PluginListWindow::~PluginListWindow()
{
	getAppProperties().getUserSettings()->setValue ("listWindowPos", getWindowStateAsString());
		clearContentComponent();
}

void PluginListWindow::closeButtonPressed()
{
	owner.pluginListWindow = nullptr;
}
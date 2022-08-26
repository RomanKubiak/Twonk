/*
  ==============================================================================

    TwonkProgramList.h
    Created: 18 Aug 2019 7:39:48pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class PluginGraph;
class TwonkToolBarButton;

class TwonkProgramList :	public ListBox,
							public DirectoryContentsDisplayComponent,
							private ListBoxModel,
							private ChangeListener
{
	public:
		TwonkProgramList(DirectoryContentsList& listToShow, PluginGraph &g);
		/** Destructor. */
		~TwonkProgramList() override;

		//==============================================================================
		/** Returns the number of files the user has got selected.
			@see getSelectedFile
		*/
		int getNumSelectedFiles() const override;

		/** Returns one of the files that the user has currently selected.
			The index should be in the range 0 to (getNumSelectedFiles() - 1).
			@see getNumSelectedFiles
		*/
		File getSelectedFile (int index = 0) const override;

		/** Deselects any files that are currently selected. */
		void deselectAllFiles() override;

		/** Scrolls to the top of the list. */
		void scrollToTop() override;

		/** If the specified file is in the list, it will become the only selected item
			(and if the file isn't in the list, all other items will be deselected). */
		void setSelectedFile (const File&) override;
		void sendDoubleClickMessage(const File &);
		void refresh();
	private:
		File lastDirectory, fileWaitingToBeSelected;
		class ItemComponent;
		// need this for loading files
		PluginGraph &pluginGraph;
		void changeListenerCallback (ChangeBroadcaster*) override;
		int getNumRows() override;
		void paintListBoxItem (int, Graphics&, int, int, bool) override;
		Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component*) override;
		void selectedRowsChanged (int row) override;
		void listBoxItemDoubleClicked (int row, const MouseEvent &) override;
		void deleteKeyPressed (int currentSelectedRow) override;
		void returnKeyPressed (int currentSelectedRow) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkProgramList)
};

class TwonkProgramListWrapper : public Component, public Button::Listener
{
	public:
		TwonkProgramListWrapper(DirectoryContentsList& listToShow, PluginGraph &g);
		~TwonkProgramListWrapper();
		void resized();
		void paint(Graphics &g);
		void buttonClicked(Button *);
		TwonkProgramList list;

	private:
		std::unique_ptr<TwonkToolBarButton> closeButton;
		std::unique_ptr<TwonkToolBarButton> deleteProgramButton;
		std::unique_ptr<TwonkToolBarButton> renameProgramButton;
};
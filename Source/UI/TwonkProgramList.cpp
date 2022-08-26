/*
  ==============================================================================

    TwonkProgramList.cpp
    Created: 18 Aug 2019 7:39:48pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkProgramList.h"
#include "TwonkToolBarButton.h"
#include "MainHostWindow.h"
#include "Filters/PluginGraph.h"
#include "Twonk.h"

TwonkProgramList::TwonkProgramList(DirectoryContentsList& listToShow, PluginGraph &g)
	:	ListBox ({}, nullptr),
		DirectoryContentsDisplayComponent (listToShow),
		lastDirectory (listToShow.getDirectory()),
		pluginGraph(g)
{
	setModel (this);
	directoryContentsList.addChangeListener (this);
}

TwonkProgramList::~TwonkProgramList()
{
	directoryContentsList.removeChangeListener (this);
}

void TwonkProgramList::refresh()
{
	directoryContentsList.refresh();
}

int TwonkProgramList::getNumSelectedFiles() const
{
	return getNumSelectedRows();
}

File TwonkProgramList::getSelectedFile (int index) const
{
	return directoryContentsList.getFile (getSelectedRow (index));
}

void TwonkProgramList::deselectAllFiles()
{
	deselectAllRows();
}

void TwonkProgramList::scrollToTop()
{
	getVerticalScrollBar().setCurrentRangeStart (0);
}

void TwonkProgramList::setSelectedFile (const File& f)
{
	for (int i = directoryContentsList.getNumFiles(); --i >= 0;)
	{
		if (directoryContentsList.getFile(i) == f)
		{
			fileWaitingToBeSelected = File();

			selectRow (i);
			return;
		}
	}

	deselectAllRows();
	fileWaitingToBeSelected = f;
}

void TwonkProgramList::changeListenerCallback (ChangeBroadcaster*)
{
	updateContent();

	if (lastDirectory != directoryContentsList.getDirectory())
	{
		fileWaitingToBeSelected = File();
		lastDirectory = directoryContentsList.getDirectory();
		deselectAllRows();
	}

	if (fileWaitingToBeSelected != File())
		setSelectedFile (fileWaitingToBeSelected);
}

void TwonkProgramList::sendDoubleClickMessage(const File &file)
{
	pluginGraph.loadDocument(file);
}
class TwonkProgramList::ItemComponent : public Component,
	private TimeSliceClient,
	private AsyncUpdater
{
public:
	ItemComponent (TwonkProgramList& fc, TimeSliceThread& t)
		: owner (fc), thread (t)
	{
	}

	~ItemComponent() override
	{
		thread.removeTimeSliceClient (this);
	}

	//==============================================================================
	void paint (Graphics& g) override
	{
		Font fontToDrawWith = getDefaultTwonkSansFont().withHeight(20.0f);
		String nameToDraw = file.getFileNameWithoutExtension().upToFirstOccurrenceOf(".", false, false);
		String type = file.getFileNameWithoutExtension().fromFirstOccurrenceOf(".", false, false);
		icon = getIconForType(descriptorToProgramType(type));
		Colour baseColour = Colours::black;
		g.drawImage (icon, Rectangle<float>(4, 4, 40, 40));

		if (fontToDrawWith.getStringWidth(nameToDraw) < getWidth() - 48)
		{
			g.setFont(fontToDrawWith.withHeight(14.0f));
			g.drawText (nameToDraw, 48, 1, getWidth() - 48, 34, Justification::centred, false);
		}
		else
		{
			g.drawMultiLineText(nameToDraw, 48, 16, getWidth() - 48, Justification::left);
			//g.drawText (file.getFileNameWithoutExtension(), 48, 2, getWidth() - 48, 30, Justification::centred, false);
		}
		g.setFont(getDefaultTwonkSansFont().withHeight(14.0f));
		g.setColour(baseColour.brighter());

		g.drawText (modTime + "  (" + fileSize + ")", 48, 34, getWidth() - 48, 14, Justification::centred);
	}

	void mouseDown (const MouseEvent& e) override
	{
		owner.selectRowsBasedOnModifierKeys (index, e.mods, true);
		owner.sendMouseClickMessage (file, e);
	}

	void mouseDoubleClick (const MouseEvent&) override
	{
		owner.sendDoubleClickMessage (file);
	}

	void update (const File& root, const DirectoryContentsList::FileInfo* fileInfo,
		int newIndex, bool nowHighlighted)
	{
		thread.removeTimeSliceClient (this);

		if (nowHighlighted != highlighted || newIndex != index)
		{
			index = newIndex;
			highlighted = nowHighlighted;
			repaint();
		}

		File newFile;
		String newFileSize, newModTime;

		if (fileInfo != nullptr)
		{
			newFile = root.getChildFile (fileInfo->filename);
			newFileSize = File::descriptionOfSizeInBytes (fileInfo->fileSize);
			newModTime = fileInfo->modificationTime.formatted ("%d %b '%y %H:%M");
		}

		if (newFile != file
			|| fileSize != newFileSize
			|| modTime != newModTime)
		{
			file = newFile;
			fileSize = newFileSize;
			modTime = newModTime;
			icon = Image();
			isDirectory = fileInfo != nullptr && fileInfo->isDirectory;

			repaint();
		}

		if (file != File() && icon.isNull() && !isDirectory)
		{
			updateIcon (true);

			if (!icon.isValid())
				thread.addTimeSliceClient (this);
		}
	}

	int useTimeSlice() override
	{
		updateIcon (false);
		return -1;
	}

	void handleAsyncUpdate() override
	{
		repaint();
	}

private:
	//==============================================================================
	TwonkProgramList& owner;
	TimeSliceThread& thread;
	File file;
	String fileSize, modTime;
	Image icon;
	int index = 0;
	bool highlighted = false, isDirectory = false;

	void updateIcon (const bool onlyUpdateIfCached)
	{
		if (icon.isNull())
		{
			auto hashCode = (file.getFullPathName() + "_iconCacheSalt").hashCode();
			auto im = ImageCache::getFromHashCode (hashCode);

			if (im.isNull() && !onlyUpdateIfCached)
			{
				im = IMG(icon_project_png);

				if (im.isValid())
					ImageCache::addImageToCache (im, hashCode);
			}

			if (im.isValid())
			{
				icon = im;
				triggerAsyncUpdate();
			}
		}
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ItemComponent)
};

//==============================================================================
int TwonkProgramList::getNumRows()
{
	return directoryContentsList.getNumFiles();
}

void TwonkProgramList::paintListBoxItem (int row, Graphics &g, int w, int h, bool selected)
{
	if (selected)
	{
		g.fillAll(Colours::aqua.withAlpha(0.5f));
	}
}

Component* TwonkProgramList::refreshComponentForRow (int row, bool isSelected, Component* existingComponentToUpdate)
{
	jassert (existingComponentToUpdate == nullptr || dynamic_cast<ItemComponent*> (existingComponentToUpdate) != nullptr);

	auto comp = static_cast<ItemComponent*> (existingComponentToUpdate);

	if (comp == nullptr)
		comp = new ItemComponent (*this, directoryContentsList.getTimeSliceThread());

	DirectoryContentsList::FileInfo fileInfo;
	comp->update (directoryContentsList.getDirectory(),
		directoryContentsList.getFileInfo (row, fileInfo) ? &fileInfo : nullptr,
		row, isSelected);

	return comp;
}

void TwonkProgramList::selectedRowsChanged (int /*lastRowSelected*/)
{
	sendSelectionChangeMessage();
}

void TwonkProgramList::deleteKeyPressed (int /*currentSelectedRow*/)
{
}

void TwonkProgramList::listBoxItemDoubleClicked (int row, const MouseEvent &e)
{
	File fileToLoad = directoryContentsList.getFile (row);
	pluginGraph.loadDocument(fileToLoad);
}

void TwonkProgramList::returnKeyPressed (int currentSelectedRow)
{
	sendDoubleClickMessage (directoryContentsList.getFile (currentSelectedRow));
}

/**
  wrap the list so it has some kind of close button
 */
TwonkProgramListWrapper::TwonkProgramListWrapper(DirectoryContentsList& listToShow, PluginGraph &g)
	: list(listToShow, g)
{
	addAndMakeVisible(&list);
	closeButton.reset(new TwonkToolBarButton());
	closeButton->setIcon(IMG(icon_close_png));
	closeButton->setBaseColour(Colours::black);
	closeButton->setTooltip("Close list");
	addAndMakeVisible(closeButton.get());
	closeButton->addListener(this);

	deleteProgramButton.reset(new TwonkToolBarButton());
	deleteProgramButton->setIcon(IMG(icon_delete_png));
	deleteProgramButton->setBaseColour(Colours::black);
	deleteProgramButton->setTooltip("Delete selected program");
	addAndMakeVisible(deleteProgramButton.get());
	deleteProgramButton->addListener(this);

	renameProgramButton.reset(new TwonkToolBarButton());
	renameProgramButton->setIcon(IMG(icon_rename_png));
	renameProgramButton->setTooltip("Rename selected program");
	renameProgramButton->setBaseColour(Colours::black);
	addAndMakeVisible(renameProgramButton.get());
	renameProgramButton->addListener(this);
}

TwonkProgramListWrapper::~TwonkProgramListWrapper()
{
}

void TwonkProgramListWrapper::buttonClicked(Button *b)
{
	if (b == closeButton.get())
	{
		if (auto target = ApplicationCommandManager::findDefaultComponentTarget())
		{
			target->invoke (ApplicationCommandTarget::InvocationInfo(CommandIDs::toggleProgramPanel), false);
		}
	}
}
void TwonkProgramListWrapper::paint(Graphics &g)
{
	g.setColour(list.findColour(ListBox::backgroundColourId).brighter());
	g.fillRect(0, 0, 48, 140);
}

void TwonkProgramListWrapper::resized()
{
	list.setBounds(48, 0, getWidth()-48, getHeight());
	closeButton->setBounds(8, 8, 32, 32);
	deleteProgramButton->setBounds(8, 48, 32, 32);
	renameProgramButton->setBounds(8, 88, 32, 32);
}
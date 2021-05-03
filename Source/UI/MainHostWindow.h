#pragma once

#include "Filters/PluginGraph.h"
#include "Panel/Editor.h"
#include "Panel/Document.h"
#include "TwonkLookAndFeel.h"
#include "BinaryData.h"

class PluginListWindow;

static const Font getDefaultTwonkSansFont()
{
	Typeface::Ptr t = Typeface::createSystemTypefaceFor(BinaryData::LiberationSansRegular_ttf, BinaryData::LiberationSansBold_ttfSize);
	return (Font(t));
}

static const Font getDefaultTwonkMonoFont()
{
	Typeface::Ptr t = Typeface::createSystemTypefaceFor(BinaryData::terminus_ttf, BinaryData::terminus_ttfSize);
	return (Font(t));
}

static const Result checkIfExistsAndCreateIfNot(const File &path)
{
	if (!path.isDirectory())
	{
		if (!path.createDirectory())
		{
			return (Result::fail("Can't make this directory"));
		}

		if (path.existsAsFile())
		{
			return (Result::fail("This path exists as a file"));
		}
	}
	return (Result::ok());
}

//==============================================================================
namespace CommandIDs
{
   #if ! (JUCE_IOS || JUCE_ANDROID)
    static const int open                   = 0x30000;
    static const int save                   = 0x30001;
    static const int saveAs                 = 0x30002;
    static const int newFile                = 0x30003;
   #endif
    static const int showPluginListEditor   = 0x30100;
    static const int showAudioSettings      = 0x30200;
    static const int aboutBox               = 0x30300;
    static const int allWindowsForward      = 0x30400;
    static const int toggleDoublePrecision  = 0x30500;
	static const int toggleProgramPanel		= 0x30600;
}

ApplicationCommandManager& getCommandManager();
ApplicationProperties& getAppProperties();
bool isOnTouchDevice();

//==============================================================================
class MainHostWindow    : public DocumentWindow,
                          public ApplicationCommandTarget,
                          public ChangeListener,
                          public FileDragAndDropTarget
{
public:
    //==============================================================================
    MainHostWindow();
    ~MainHostWindow() override;

    //==============================================================================
    void closeButtonPressed() override;
    void changeListenerCallback (ChangeBroadcaster*) override;
    bool isInterestedInFileDrag (const StringArray& files) override;
    void fileDragEnter (const StringArray& files, int, int) override;
    void fileDragMove (const StringArray& files, int, int) override;
    void fileDragExit (const StringArray& files) override;
    void filesDropped (const StringArray& files, int, int) override;
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands (Array<CommandID>&) override;
    void getCommandInfo (CommandID, ApplicationCommandInfo&) override;
    bool perform (const InvocationInfo&) override;
	void initPaths();
    void tryToQuitApplication();
    void createPlugin (const PluginDescription&, Point<int> pos);
    void addPluginsToMenu (PopupMenu&);
    PluginDescription getChosenType (int menuID) const;
    bool isDoublePrecisionProcessing();
    void updatePrecisionMenuItem (ApplicationCommandInfo& info);
    void setKioskMode();
    std::unique_ptr<Document> graphHolder;
	KnownPluginList knownPluginList;
	std::unique_ptr<PluginListWindow> pluginListWindow;

private:
    //==============================================================================
    AudioDeviceManager deviceManager;
    AudioPluginFormatManager formatManager;
    Array<PluginDescription> internalTypes;
	Array<PluginDescription> twonkTypes;
    KnownPluginList::SortMethod pluginSortMethod;
    Array<PluginDescription> pluginDescriptions;
	TwonkLookAndFeel twonkLookAndFeel;
    void showAudioSettings();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainHostWindow)
};

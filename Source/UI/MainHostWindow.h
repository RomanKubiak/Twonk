#pragma once

#include "../Filters/PluginGraph.h"
#include "GraphEditorPanel.h"
#include "TwonkLookAndFeel.h"
#include "BinaryData.h"

static const Font getDefaultTwonkSansFont()
{
	Typeface::Ptr t = Typeface::createSystemTypefaceFor(BinaryData::LiberationSansRegular_ttf, BinaryData::LiberationSansBold_ttfSize);
	return (Font(t));
}

static const Font getDefaultTwonkMonoFont()
{
	Typeface::Ptr t = Typeface::createSystemTypefaceFor(BinaryData::terminess_ttf, BinaryData::terminess_ttfSize);
	return (Font(t));
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
                          public MenuBarModel,
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

    void menuBarActivated (bool isActive) override;

    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands (Array<CommandID>&) override;
    void getCommandInfo (CommandID, ApplicationCommandInfo&) override;
    bool perform (const InvocationInfo&) override;

    void tryToQuitApplication();

    void createPlugin (const PluginDescription&, Point<int> pos);

    void addPluginsToMenu (PopupMenu&);
    PluginDescription getChosenType (int menuID) const;

    bool isDoublePrecisionProcessing();
    void updatePrecisionMenuItem (ApplicationCommandInfo& info);

    std::unique_ptr<GraphDocumentComponent> graphHolder;

private:
    //==============================================================================
    AudioDeviceManager deviceManager;
    AudioPluginFormatManager formatManager;
    Array<PluginDescription> internalTypes;
	Array<PluginDescription> twonkTypes;
	KnownPluginList knownPluginList;
    KnownPluginList::SortMethod pluginSortMethod;
    Array<PluginDescription> pluginDescriptions;
	TwonkLookAndFeel twonkLookAndFeel;
    class PluginListWindow;
    std::unique_ptr<PluginListWindow> pluginListWindow;
	
    void showAudioSettings();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainHostWindow)
};

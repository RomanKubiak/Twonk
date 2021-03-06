#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/MainHostWindow.h"
#include "Filters/InternalPlugins.h"
#include "Twonk.h"
#if ! (JUCE_PLUGINHOST_VST || JUCE_PLUGINHOST_VST3 || JUCE_PLUGINHOST_AU)
 #error "If you're building the audio plugin host, you probably want to enable VST and/or AU support"
#endif


//==============================================================================
class PluginHostApp  : public JUCEApplication,
                       private AsyncUpdater
{
public:
    PluginHostApp() {}

    void initialise (const String &commandToRunAfterStart) override
    {
        // initialise our settings file..

        PropertiesFile::Options options;
        options.applicationName     = "Twonk";
        options.filenameSuffix      = "settings";
        options.osxLibrarySubFolder = "Preferences";

        appProperties.reset (new ApplicationProperties());
        appProperties->setStorageParameters (options);
		appProperties->getUserSettings()->setValue("lastPluginScanPath_VST", GET_TWONK_PLUGINS_DIR().getFullPathName());
        mainWindow.reset (new MainHostWindow());

		mainWindow->setUsingNativeTitleBar (true);

        commandManager.registerAllCommandsForTarget (this);
        commandManager.registerAllCommandsForTarget (mainWindow.get());

        // Important note! We're going to use an async update here so that if we need
        // to re-open a file and instantiate some plugins, it will happen AFTER this
        // initialisation method has returned.
        // On Windows this probably won't make a difference, but on OSX there's a subtle event loop
        // issue that can happen if a plugin runs one of those irritating modal dialogs while it's
        // being loaded. If that happens inside this method, the OSX event loop seems to be in some
        // kind of special "initialisation" mode and things get confused. But if we load the plugin
        // later when the normal event loop is running, everything's fine.
#if defined (__linux__)
		/*
--- cut here
#!/bin/bash
wid=`xdotool search Twonk 2>/dev/null`
xdotool windowmove $wid 0 0
--- cut here
something like that needs to be executed cause JUCE is dumb
and can't position itself without a window manager

the below code is to allow execution of such script or any other
stuff that might be needed
		*/
		ChildProcess child;
		child.start(commandToRunAfterStart);
		if (!child.waitForProcessToFinish(500))
		{
			child.kill();
		}
#endif
        triggerAsyncUpdate();
    }

    void handleAsyncUpdate() override
    {
        File fileToOpen;
		
        if (! fileToOpen.existsAsFile())
        {
            RecentlyOpenedFilesList recentFiles;
            recentFiles.restoreFromString (getAppProperties().getUserSettings()->getValue ("recentFilterGraphFiles"));

			if (recentFiles.getNumFiles() > 0)
			{
				fileToOpen = recentFiles.getFile (0);
			}
        }

		if (fileToOpen.existsAsFile())
		{
			if (auto* graph = mainWindow->graphHolder.get())
			{
				if (auto* ioGraph = graph->graph.get())
				{
					ioGraph->loadFrom (fileToOpen, true);
				}
			}
		}
		else
		{
			fileToOpen = GET_TWONK_PROGRAM_DIR().getChildFile("Program.generic.twonk");

			if (!fileToOpen.existsAsFile())
			{
				fileToOpen.replaceWithData(BinaryData::Default_generic_twonk, BinaryData::Default_generic_twonkSize);
			}

			if (auto* graph = mainWindow->graphHolder.get())
			{
				if (auto* ioGraph = graph->graph.get())
				{
					ioGraph->loadFrom (fileToOpen, true);
				}
			}
		}
	}

    void shutdown() override
    {
        mainWindow = nullptr;
        appProperties = nullptr;
        LookAndFeel::setDefaultLookAndFeel (nullptr);
    }

    void suspended() override
    {
       #if JUCE_ANDROID || JUCE_IOS
        if (auto graph = mainWindow->graphHolder.get())
            if (auto ioGraph = graph->graph.get())
                ioGraph->saveDocument (PluginGraph::getDefaultGraphDocumentOnMobile());
       #endif
    }

    void systemRequestedQuit() override
    {
        if (mainWindow != nullptr)
            mainWindow->tryToQuitApplication();
        else
            JUCEApplicationBase::quit();
    }

    void backButtonPressed() override
    {
    }

    const String getApplicationName() override       { return "Twonk"; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    ApplicationCommandManager commandManager;
    std::unique_ptr<ApplicationProperties> appProperties;

private:
    std::unique_ptr<MainHostWindow> mainWindow;
};

static PluginHostApp& getApp()                    { return *dynamic_cast<PluginHostApp*>(JUCEApplication::getInstance()); }

ApplicationProperties& getAppProperties()         { return *getApp().appProperties; }
ApplicationCommandManager& getCommandManager()    { return getApp().commandManager; }

bool isOnTouchDevice()
{
	if (SystemStats::getOperatingSystemType() == SystemStats::Linux)
		return (true);

	return (false);
	//return Desktop::getInstance().getMainMouseSource().isTouch();
}

// This kicks the whole thing off..
START_JUCE_APPLICATION (PluginHostApp)

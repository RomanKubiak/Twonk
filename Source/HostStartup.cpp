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

    static const StringArray getParameters(const String &cli)
    {
        StringArray tokens;
        StringArray ret;
        tokens.addTokens (cli, " ", "\'\"");

        for (int i=0; i<tokens.size(); i++)
        {
            ret.add (tokens[i].fromFirstOccurrenceOf ("--", false, false).upToFirstOccurrenceOf("=", false, true));
        }

        return (ret);
    }

    static const String getParameterValue(const String &cli, const String &parameter)
    {
        StringArray tokens;
        StringArray ret;
        tokens.addTokens (cli, " ", "\'\"");

        for (int i=0; i<tokens.size(); i++)
        {
            if (tokens[i].fromFirstOccurrenceOf("--", false, false) == parameter)
                return tokens[i].fromFirstOccurrenceOf ("=", false, false).unquoted().trim();
        }

        return "";
    }

    void initialise (const String &cliParams) override
    {
        // initialise our settings file..
        StringArray parameters		= getParameters(cliParams);

        _TXT("primary display: dpi=%f area=%s", Desktop::getInstance().getDisplays().getPrimaryDisplay()->dpi,
             Desktop::getInstance().getDisplays().getPrimaryDisplay()->totalArea.toString().toUTF8());
        PropertiesFile::Options options;
        options.applicationName     = "Twonk";
        options.filenameSuffix      = "settings";
        options.osxLibrarySubFolder = "Preferences";

        appProperties.reset (new ApplicationProperties());
        appProperties->setStorageParameters (options);
		appProperties->getUserSettings()->setValue("lastPluginScanPath_VST", GET_TWONK_PLUGINS_DIR().getFullPathName());
        mainWindow.reset (new MainHostWindow());

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
		_TXT("cliParams: %s", cliParams.toUTF8());
		if (getParameterValue(cliParams, "runAfterStart") != "") {
            ChildProcess child;
            child.start(getParameterValue(cliParams, "runAfterStart"));
            if (!child.waitForProcessToFinish(500)) {
                child.kill();
            }
        }

		if (parameters.contains("kiosk")) {
		    startInKioskMode = true;
		}

        if (parameters.contains("resizeToDisplay")) {
            resizeToDisplay = true;
        }

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

		if (startInKioskMode) {
		    _TXT("set kiosk mode");
		    mainWindow->setKioskMode();
		}

		if (resizeToDisplay) {
            _TXT("resize to display");
		    Rectangle<int> r = Desktop::getInstance().getDisplays().getPrimaryDisplay()->totalArea;
		    _TXT("display area: %s", r.toString().toUTF8());
		    mainWindow->setTitleBarHeight(0);
		    mainWindow->setResizable(false, false);
		    mainWindow->setTopLeftPosition(0,0);
		    mainWindow->setSize(r.getWidth(), r.getHeight());
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

    const String getApplicationName() override       { return "Twonk"; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }
    bool startInKioskMode = false;
    bool resizeToDisplay = false;
    ApplicationCommandManager commandManager;
    std::unique_ptr<ApplicationProperties> appProperties;

private:
    std::unique_ptr<MainHostWindow> mainWindow;
};

static PluginHostApp& getApp()                    { return *dynamic_cast<PluginHostApp*>(JUCEApplication::getInstance()); }

ApplicationProperties& getAppProperties()         { return *getApp().appProperties; }
ApplicationCommandManager& getCommandManager()    { return getApp().commandManager; }

// This kicks the whole thing off..
START_JUCE_APPLICATION (PluginHostApp)

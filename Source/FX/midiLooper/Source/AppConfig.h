/*

	IMPORTANT! This file is auto-generated each time you save your
	project - if you alter its contents, your changes may be overwritten!

	There's a section below where you can add your own custom code safely, and the
	Introjucer will preserve the contents of that block, but the best way to change
	any of these definitions is by using the Introjucer's project settings.

	Any commented-out settings will assume their default values.

*/

#ifndef __JUCE_APPCONFIG_FFQIFG__
#define __JUCE_APPCONFIG_FFQIFG__
#define JUCE_COMPILER_SUPPORTS_NOEXCEPT 1
//==============================================================================
// [BEGIN_USER_CODE_SECTION]

// (You can add your own code in this section, and the Introjucer will not overwrite it)
enum OperatingSystemType
{
	MacOSX_10_4 = 0x1004,
	MacOSX_10_5 = 0x1005,
	MacOSX_10_6 = 0x1006,
	MacOSX_10_7 = 0x1007,
	MacOSX_10_8 = 0x1008,
};
// [END_USER_CODE_SECTION]

//==============================================================================
#define JUCE_MODULE_AVAILABLE_juce_audio_basics             1
#define JUCE_MODULE_AVAILABLE_juce_audio_devices            1
#define JUCE_MODULE_AVAILABLE_juce_audio_formats            1
#define JUCE_MODULE_AVAILABLE_juce_audio_plugin_client      1
#define JUCE_MODULE_AVAILABLE_juce_audio_processors         1
#define JUCE_MODULE_AVAILABLE_juce_audio_utils              1
#define JUCE_MODULE_AVAILABLE_juce_core                     1
#define JUCE_MODULE_AVAILABLE_juce_cryptography             1
#define JUCE_MODULE_AVAILABLE_juce_data_structures          1
#define JUCE_MODULE_AVAILABLE_juce_events                   1
#define JUCE_MODULE_AVAILABLE_juce_graphics                 1
#define JUCE_MODULE_AVAILABLE_juce_gui_basics               1
#define JUCE_MODULE_AVAILABLE_juce_gui_extra                1

//==============================================================================
// juce_audio_devices flags:

#ifndef    JUCE_ASIO
#define   JUCE_ASIO 0
#endif

#ifndef    JUCE_WASAPI
#define   JUCE_WASAPI 0
#endif

#ifndef    JUCE_DIRECTSOUND
#define   JUCE_DIRECTSOUND 0
#endif

#ifndef    JUCE_ALSA
#define   JUCE_ALSA 0
#endif

#ifndef    JUCE_JACK
#define   JUCE_JACK 0
#endif

#ifndef    JUCE_USE_ANDROID_OPENSLES
#define   JUCE_USE_ANDROID_OPENSLES 0
#endif

#ifndef    JUCE_USE_CDREADER
#define   JUCE_USE_CDREADER 0
#endif

#ifndef    JUCE_USE_CDBURNER
#define   JUCE_USE_CDBURNER 0
#endif

//==============================================================================
// juce_audio_formats flags:

#ifndef    JUCE_USE_FLAC
#define   JUCE_USE_FLAC 0
#endif

#ifndef    JUCE_USE_OGGVORBIS
#define   JUCE_USE_OGGVORBIS 0
#endif

#ifndef    JUCE_USE_MP3AUDIOFORMAT
#define   JUCE_USE_MP3AUDIOFORMAT 0
#endif

#ifndef    JUCE_USE_WINDOWS_MEDIA_FORMAT
#define   JUCE_USE_WINDOWS_MEDIA_FORMAT 0
#endif

//==============================================================================
// juce_audio_processors flags:

#ifndef    JUCE_PLUGINHOST_VST
#define   JUCE_PLUGINHOST_VST 0
#endif

#ifndef    JUCE_PLUGINHOST_AU
#define   JUCE_PLUGINHOST_AU 0
#endif

//==============================================================================
// juce_core flags:

#ifndef    JUCE_FORCE_DEBUG
 //#define JUCE_FORCE_DEBUG
#endif

#ifndef    JUCE_LOG_ASSERTIONS
 //#define JUCE_LOG_ASSERTIONS
#endif

#ifndef    JUCE_CHECK_MEMORY_LEAKS
 //#define JUCE_CHECK_MEMORY_LEAKS
#endif

#ifndef    JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES
 //#define JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES
#endif

//==============================================================================
// juce_graphics flags:

#ifndef    JUCE_USE_COREIMAGE_LOADER
 //#define JUCE_USE_COREIMAGE_LOADER
#endif

#ifndef    JUCE_USE_DIRECTWRITE
 #define JUCE_USE_DIRECTWRITE
#endif

//==============================================================================
// juce_gui_basics flags:

#ifndef    JUCE_ENABLE_REPAINT_DEBUGGING
 //#define JUCE_ENABLE_REPAINT_DEBUGGING
#endif

#ifndef    JUCE_USE_XSHM
 //#define JUCE_USE_XSHM
#endif

#ifndef    JUCE_USE_XRENDER
 //#define JUCE_USE_XRENDER
#endif

#ifndef    JUCE_USE_XCURSOR
 //#define JUCE_USE_XCURSOR
#endif

//==============================================================================
// juce_gui_extra flags:

#ifndef    JUCE_WEB_BROWSER
#define   JUCE_WEB_BROWSER 0
#endif
#ifndef JucePlugin_Build_Standalone
#define JucePlugin_Build_Standalone 0
#endif

#if ! JucePlugin_Build_Standalone
#define JucePlugin_Build_VST            1
#define JucePlugin_Build_RTAS           0
#define JucePlugin_Build_AU             0
#endif
//==============================================================================
//==============================================================================
/*                          Plugin Formats to build                           */

#ifndef JucePlugin_Build_Standalone
#define JucePlugin_Build_Standalone 0
#endif

#if ! JucePlugin_Build_Standalone
#define JucePlugin_Build_VST            1
#define JucePlugin_Build_RTAS           0
#define JucePlugin_Build_AU             0
#endif

//==============================================================================
/*                              Generic settings                              */
#define JucePlugin_NoEditor                 0
#define JucePlugin_Name                     "midiLooper"
#define JucePlugin_Desc                     "MIDI looper/sampler"
#define JucePlugin_Manufacturer             "Insert Piz Here"
#define JucePlugin_ManufacturerCode         'IPHz'
#define JucePlugin_PluginCode               'L0OP'
#define PIZMIDI										1
#define JucePlugin_MaxNumInputChannels              2
#define JucePlugin_MaxNumOutputChannels             2
#define JucePlugin_PreferredChannelConfigurations   { 2, 2 }
#define JucePlugin_TailLengthSeconds				0
#define JucePlugin_IsSynth                          1
#define JucePlugin_WantsMidiInput                   1
#define JucePlugin_ProducesMidiOutput               1
#define JucePlugin_SilenceInProducesSilenceOut      0
#define JucePlugin_EditorRequiresKeyboardFocus      1
#define JucePlugin_VersionCode              0x0001040a
#define JucePlugin_VersionString            "1.4.10"

//==============================================================================
/*                                VST settings                                */
#define JUCE_USE_VSTSDK_2_4                 1
#define JucePlugin_VSTUniqueID              JucePlugin_PluginCode
#if JucePlugin_IsSynth
#define JucePlugin_VSTCategory            kPlugCategSynth
#else
#define JucePlugin_VSTCategory            kPlugCategEffect
#endif

//==============================================================================
/*                              AudioUnit settings                            */
#if JucePlugin_IsSynth
#define JucePlugin_AUMainType             kAudioUnitType_MusicEffect
#else
#define JucePlugin_AUMainType             kAudioUnitType_Effect
#endif
#define JucePlugin_AUSubType                JucePlugin_PluginCode
#define JucePlugin_AUExportPrefix           midiLooperAU
#define JucePlugin_AUExportPrefixQuoted     "midiLooperAU"
#define JucePlugin_AUManufacturerCode       JucePlugin_ManufacturerCode
#define JucePlugin_CFBundleIdentifier       "org.thepiz.midiLooper"

//==============================================================================
/*                                RTAS settings                               */
#if JucePlugin_IsSynth
#define JucePlugin_RTASCategory           ePlugInCategory_SWGenerators
#else
#define JucePlugin_RTASCategory           ePlugInCategory_None
#endif
#define JucePlugin_RTASManufacturerCode     JucePlugin_ManufacturerCode
#define JucePlugin_RTASProductId            JucePlugin_PluginCode

#endif  // __JUCE_APPCONFIG_FFQIFG__

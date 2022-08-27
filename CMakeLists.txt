cmake_minimum_required(VERSION 3.23)

if(APPLE)
	set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "")
	set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
endif(APPLE)

project(Twonk VERSION 5.7.1)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
	${CMAKE_SOURCE_DIR}/config
	${CMAKE_SOURCE_DIR}/config/platform
)

add_subdirectory(JUCE)

if (APPLE)
	juce_set_vst2_sdk_path(/Users/atom/devel/vst2sdk)
elseif(UNIX)
	juce_set_vst2_sdk_path(/home/kbar/devel/vst2sdk)
elseif(WIN32)
	juce_set_vst2_sdk_path(c:/Users/atom/devel/vst2sdk)
endif(APPLE)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

juce_add_gui_app(Twonk PRODUCT_NAME "Twonk")
add_subdirectory(Source/Resources)
juce_generate_juce_header(${PROJECT_NAME})

target_sources(Twonk PUBLIC
		Source/UI/PluginWindow.cpp
		Source/UI/TwonkSaveProgramDialog.cpp
		Source/UI/TwonkFilterPopupPropertiesSegment.cpp
		Source/UI/TwonkFileMenu.cpp
		Source/UI/TwonkAudioSettingsMenu.cpp
		Source/UI/PluginDefaultEditor.cpp
		Source/UI/TwonkFilterConnector.cpp
		Source/UI/MainHostWindow.cpp
		Source/UI/TwonkProgramList.cpp
		Source/UI/TwonkToolBarButton.cpp
		Source/UI/TwonkMidiKeyboard.cpp
		Source/UI/TwonkToolBar.cpp
		Source/UI/TwonkFilterPopupProperties.cpp
		Source/UI/PluginListWindow.cpp
		Source/UI/TwonkProgramMenu.cpp
		Source/UI/TwonkFilterPropertiesEditor.cpp
		Source/UI/TwonkLookAndFeel.cpp
		Source/UI/Panel/Document.cpp
		Source/UI/Panel/Processor.cpp
		Source/UI/Panel/Connector.cpp
		Source/UI/Panel/Editor.cpp
		Source/UI/Panel/Pin.cpp
		Source/UI/TwonkToolBarHeader.cpp
		Source/UI/TwonkTransport.cpp
		Source/Platform/TwonkPlatformSpecific.cpp
		Source/Platform/Windows/CpuUsage.cpp
		Source/FX/DebugInfo/TwonkDebugInfoEditor.cpp
		Source/FX/DebugInfo/TwonkDebugInfoProcessor.cpp
		"Source/FX/Pitch Shift/TwonkPSEditor.cpp"
		"Source/FX/Pitch Shift/TwonkPSProcessor.cpp"
		Source/FX/Wah-Wah/TwonkWWProcessor.cpp
		Source/FX/Wah-Wah/TwonkWWEditor.cpp
		Source/FX/FifteenStep/FifteenStepHexRow.cpp
		Source/FX/FifteenStep/FifteenStepHexStep.cpp
		Source/FX/FifteenStep/FifteenStep.cpp
		Source/FX/FifteenStep/FifteenStepEditor.cpp
		Source/FX/FifteenStep/FifteenStepRowHolder.cpp
		Source/FX/FifteenStep/FifteenStepProcessor.cpp
		Source/FX/Robotization-Whisperization/TwonkRWProcessor.cpp
		Source/FX/Robotization-Whisperization/TwonkRWEditor.cpp
		Source/FX/Simpler/SimplerSound.cpp
		Source/FX/Simpler/SimplerProcessor.cpp
		Source/FX/Simpler/SimplerEditor.cpp
		Source/FX/Simpler/InstrumentButtonsPanel.cpp
		Source/FX/Simpler/SimplerVoice.cpp
		Source/FX/Simpler/SimplerSynthesiser.cpp
		Source/FX/Simpler/InstrumentButton.cpp
		Source/FX/Simpler/InstrumentWaveViewer.cpp
		Source/FX/Simpler/InstrumentParametersEditor.cpp
		Source/FX/SineWaveSynth/SineWaveSynth.cpp
		"Source/FX/Ring Modulator/TwonkRMEditor.cpp"
		"Source/FX/Ring Modulator/TwonkRMProcessor.cpp"
		Source/FX/Compressor/TwonkCEEditor.cpp
		Source/FX/Compressor/TwonkCEProcessor.cpp
		"Source/FX/MIDI Controller/MidiControllerEditor.cpp"
		"Source/FX/MIDI Controller/MidiControllerProcessor.cpp"
		"Source/FX/MIDI Controller/PianoKeys.cpp"
		"Source/FX/MIDI Controller/HexagonController.cpp"
		Source/FX/Phaser/TwonkPhaserEditor.cpp
		Source/FX/Phaser/TwonkPhaserProcessor.cpp
		"Source/FX/Ping-Pong Delay/TwonkPPDelayEditor.cpp"
		"Source/FX/Ping-Pong Delay/TwonkPPDelayProcessor.cpp"
		Source/FX/Distortion/TwonkDistortionProcessor.cpp
		Source/FX/Distortion/TwonkDistortionEditor.cpp
		Source/FX/Tremolo/TwonkTremoloEditor.cpp
		Source/FX/Tremolo/TwonkTremoloProcessor.cpp
		Source/FX/Flanger/TwonkFlangerEditor.cpp
		Source/FX/Flanger/TwonkFlangerProcessor.cpp
		Source/FX/SFZ/ClickableLabel.cpp
		Source/FX/SFZ/SFZero/SFZero.cpp
		Source/FX/SFZ/SFZeroAudioProcessor.cpp
		Source/FX/SFZ/SFZeroEditor.cpp
		Source/FX/TwonkFilters.cpp
		Source/Filters/IOConfigurationWindow.cpp
		Source/Filters/InternalPlugins.cpp
		Source/Filters/PluginGraph.cpp
		Source/TwonkPlayHead.cpp
		Source/HostStartup.cpp
)

target_compile_options(Twonk PUBLIC "-w")

target_compile_definitions(Twonk
	PRIVATE
	JUCE_WEB_BROWSER=0
	JUCE_USE_CURL=0
	JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Twonk,JUCE_PRODUCT_NAME>"
	JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Twonk,JUCE_VERSION>"
	JUCE_VST3_CAN_REPLACE_VST2=1
	JUCE_DEBUG=1
	JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
	JUCE_PLUGINHOST_LADSPA=1
	JUCE_PLUGINHOST_VST=1
	JUCE_PLUGINHOST_VST3=1
	JUCE_MODAL_LOOPS_PERMITTED=1
	JUCE_TARGET_HAS_BINARY_DATA=1
)

target_include_directories(Twonk
	PUBLIC
	Source/
	Source/Filters
	Source/FX
	Source/UI
	Source/FX/SFZ
	${CMAKE_CURRENT_BINARY_DIR})

if(UNIX AND NOT APPLE)
	list(APPEND TwonkLibs "X11")
	list(APPEND TwonkLibs "z")
	list(APPEND TwonkLibs "udev")
	list(APPEND TwonkLibs "bfd")
endif()

target_link_libraries(Twonk
		PRIVATE
			juce::juce_gui_extra
			juce::juce_audio_basics
			juce::juce_audio_devices
			juce::juce_audio_formats
			juce::juce_audio_processors
			juce::juce_audio_plugin_client
			juce::juce_audio_utils
			juce::juce_cryptography
			juce::juce_data_structures
			juce::juce_dsp
			juce::juce_core
			juce::juce_graphics
			juce::juce_gui_basics
			juce::juce_gui_extra
			${TwonkLibs}
			TwonkResources
		PUBLIC
			juce::juce_recommended_config_flags
			juce::juce_recommended_lto_flags
			juce::juce_recommended_warning_flags
	)
cmake_minimum_required (VERSION 3.0)
project (midiLooper)
include_directories(../../Source ../../JuceLibraryCode/ ../../Source/common /usr/include/freetype2/ ../../JuceLibraryCode/modules /root/Twonk/vst2sdk)
add_definitions(-D_NDEBUG=1 -DLINUX=1 -DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1 -DJucePlugin_Build_VST=1)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-w -Os -std=c++14 -march=native -fpermissive -fPIC -fvisibility=hidden)

FILE(GLOB midiLooperSources ../../Source/*.cpp)

add_library(midiLooper SHARED ${midiLooperSources}
../../JuceLibraryCode/modules/juce_core/juce_core.cpp
../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
../../JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
../../JuceLibraryCode/modules/juce_events/juce_events.cpp
../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp
../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
../../JuceLibraryCode/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp)

target_link_libraries(midiLooper LINK_PUBLIC -L/usr/X11R6/lib/ -shared -Wl,--no-undefined -lasound -lfreetype -lX11 -lXext -lXinerama -lcurl -lpthread -ldl)

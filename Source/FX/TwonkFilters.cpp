/*
  ==============================================================================

    TwonkFilters.cpp
    Created: 3 Jun 2019 4:29:20pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkFilters.h"
#include "Tremolo/TwonkTremoloProcessor.h"
#include "Ring Modulator/TwonkRMProcessor.h"
#include "Compressor/TwonkCEProcessor.h"
#include "Pitch Shift/TwonkPSProcessor.h"
#include "Distortion/TwonkDistortionProcessor.h"
#include "Wah-Wah/TwonkWWProcessor.h"
#include "Robotization-Whisperization/TwonkRWProcessor.h"
#include "Flanger/TwonkFlangerProcessor.h"
#include "Ping-Pong Delay/TwonkPPDelayProcessor.h"
#include "Phaser/TwonkPhaserProcessor.h"
#include "DebugInfo/TwonkDebugInfoProcessor.h"
#include "SequencerLinear/SequencerLinearProcessor.h"
#include "MIDI Controller/MidiControllerProcessor.h"

void TwonkFilters::getAllTypes(Array<PluginDescription>& results)
{
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Tremolo", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Pitch Shift", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Ring Modulator", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Compressor", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Distortion", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("WahWah", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Robot Whisper", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Flanger", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Ping-Pong Delay", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Phaser", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("Debug Info", false, true)));
	results.add (PluginDescription (TwonkPlugin::getPluginDescription("MIDI Controller", true, true)));
}

std::unique_ptr<AudioPluginInstance> TwonkFilters::createInstance (const String& name)
{
	DBG("TwonkFilters::createInstance trying to create instance for \"" + name + "\"");
	if (name == "Tremolo") 
		return std::make_unique<TremoloAudioProcessor> (TwonkPlugin::getPluginDescription("Tremolo", false, true));
	if (name == "Ring Modulator") 
		return std::make_unique <RingModulationAudioProcessor> (TwonkPlugin::getPluginDescription("Ring Modulator", false, true));
	if (name == "Compressor") 
		return std::make_unique <CompressorExpanderAudioProcessor> (TwonkPlugin::getPluginDescription("Compressor", false, true));
	if (name == "Pitch Shift")
		return  std::make_unique <PitchShiftAudioProcessor> (TwonkPlugin::getPluginDescription("Pitch Shift", false, true));
	if (name == "Distortion")
		return std::make_unique <DistortionAudioProcessor> (TwonkPlugin::getPluginDescription("Distortion", false, true));
	if (name == "WahWah")
		return std::make_unique <WahWahAudioProcessor> (TwonkPlugin::getPluginDescription("WahWah", false, true));
	if (name == "Robot Whisper")
		return std::make_unique <RobotizationWhisperizationAudioProcessor> (TwonkPlugin::getPluginDescription("Robot Whisper", false, true));
	if (name == "Flanger")
		return std::make_unique <FlangerAudioProcessor> (TwonkPlugin::getPluginDescription("Flanger", false, true));
	if (name == "Ping-Pong Delay")
		return std::make_unique <PingPongDelayAudioProcessor> (TwonkPlugin::getPluginDescription("Ping-Pong Delay", false, true));
	if (name == "Phaser")
		return std::make_unique <PhaserAudioProcessor> (TwonkPlugin::getPluginDescription("Phaser", false, true));
	if (name == "Debug Info")
		return std::make_unique <DebugInfoProcessor> (TwonkPlugin::getPluginDescription("Debug Info", false, true));
	if (name == "MIDI Controller")
		return std::make_unique <MidiControllerProcessor> (TwonkPlugin::getPluginDescription("MIDI Controller", true, true));

	DBG("TwonkFilters::createInstance don't know how to create instance for: " + name);
	return nullptr;
}
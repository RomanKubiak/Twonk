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
#include "SFZ/SFZeroAudioProcessor.h"
#include "midiLooper/PizLooper.h"
void TwonkFilters::getAllTypes(OwnedArray<PluginDescription>& results)
{
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Tremolo", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Pitch Shift", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Ring Modulator", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Compressor", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Distortion", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("WahWah", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Robot Whisper", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Flanger", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Ping-Pong Delay", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Phaser", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Debug Info", false, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("Sequencer", true, true)));
	results.add (new PluginDescription (InternalPlugin::getPluginDescriptionForTwonk("SFZ", true, true)));
}

std::unique_ptr<AudioPluginInstance> TwonkFilters::createInstance (const String& name)
{
	if (name == "Tremolo") return std::make_unique<TremoloAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Tremolo", false, true));
	if (name == "Ring Modulator") return std::make_unique <RingModulationAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Ring Modulator", false, true));
	if (name == "Compressor") return std::make_unique <CompressorExpanderAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Compressor", false, true));
	if (name == "Pitch Shift")return  std::make_unique <PitchShiftAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Pitch Shift", false, true));
	if (name == "Distortion") return std::make_unique <DistortionAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Distortion", false, true));
	if (name == "WahWah") return std::make_unique <WahWahAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("WahWah", false, true));
	if (name == "Robot Whisper") return std::make_unique <RobotizationWhisperizationAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Robot Whisper", false, true));
	if (name == "Flanger") return std::make_unique <FlangerAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Flanger", false, true));
	if (name == "Ping-Pong Delay") return std::make_unique <PingPongDelayAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Ping-Pong Delay", false, true));
	if (name == "Phaser") return std::make_unique <PhaserAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Phaser", false, true));
	if (name == "Debug Info") return std::make_unique <DebugInfoProcessor> (InternalPlugin::getPluginDescriptionForTwonk("Debug Info", false, true));
	if (name == "Sequencer") return std::make_unique <PizLooper> (InternalPlugin::getPluginDescriptionForTwonk("Sequencer", true, true));
	if (name == "SFZ") return std::make_unique <sfzero::SFZeroAudioProcessor> (InternalPlugin::getPluginDescriptionForTwonk("SFZ", true, true));
	
	return nullptr;
}
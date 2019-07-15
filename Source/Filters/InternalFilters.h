/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma once

#include "FilterGraph.h"
class TwonkPlayHead;
class InternalPlugin : public AudioPluginInstance
{
protected:
	InternalPlugin (const PluginDescription& descr, bool _weHaveOurEditor = false,
		const AudioChannelSet& channelSetToUse = AudioChannelSet::stereo())
		: AudioPluginInstance (getBusProperties (descr.numInputChannels == 0, channelSetToUse)),
		name  (descr.fileOrIdentifier.upToFirstOccurrenceOf (":", false, false)),
		state (descr.fileOrIdentifier.fromFirstOccurrenceOf (":", false, false)),
		isGenerator (descr.numInputChannels == 0),
		hasMidi (descr.isInstrument),
		channelSet (channelSetToUse)
	{
		jassert (channelSetToUse.size() == descr.numOutputChannels);
		weHaveOurEditor = _weHaveOurEditor;
	}
	
public:
	//==============================================================================
	const String getName() const override { return name; }
	double getTailLengthSeconds() const override { return 0.0; }
	bool acceptsMidi() const override { return hasMidi; }
	bool producesMidi() const override { return hasMidi; }
	int getNumPrograms() override { return 0; }
	int getCurrentProgram() override { return 0; }
	void setCurrentProgram (int) override {}
	const String getProgramName (int) override { return {}; }
	void changeProgramName (int, const String&) override {}
	void getStateInformation (juce::MemoryBlock&) override {}
	void setStateInformation (const void*, int) override {}
	bool isBusesLayoutSupported (const BusesLayout& layout) const override { return false; }

	//==============================================================================
	void fillInPluginDescription (PluginDescription& description) const override
	{
		description = getPluginDescription (name + ":" + state,
			isGenerator,
			hasMidi,
			channelSet);
	}

	static PluginDescription getPluginDescription (const String& identifier,
		bool registerAsGenerator,
		bool acceptsMidi,
		const AudioChannelSet& channelSetToUse
		= AudioChannelSet::stereo())
	{
		PluginDescription descr;
		auto pluginName = identifier.upToFirstOccurrenceOf (":", false, false);
		auto pluginState = identifier.fromFirstOccurrenceOf (":", false, false);

		descr.name = pluginName;
		descr.descriptiveName = pluginName;
		descr.pluginFormatName = "Internal";
		descr.category = (registerAsGenerator ? (acceptsMidi ? "Synth" : "Generator") : "Effect");
		descr.manufacturerName = "JUCE";
		descr.version = ProjectInfo::versionString;
		descr.fileOrIdentifier = pluginName + ":" + pluginState;
		descr.uid = pluginName.hashCode();
		descr.isInstrument = (acceptsMidi && registerAsGenerator);
		descr.numInputChannels = (registerAsGenerator ? 0 : channelSetToUse.size());
		descr.numOutputChannels = channelSetToUse.size();

		return descr;
	}

	static PluginDescription getPluginDescriptionForTwonk (const String& identifier,
		bool registerAsGenerator,
		bool acceptsMidi,
		const AudioChannelSet& channelSetToUse
		= AudioChannelSet::stereo())
	{
		PluginDescription descr;
		auto pluginName = identifier.upToFirstOccurrenceOf (":", false, false);
		auto pluginState = identifier.fromFirstOccurrenceOf (":", false, false).upToLastOccurrenceOf(":", false, false);

		descr.name = pluginName;
		descr.descriptiveName = pluginName;
		descr.pluginFormatName = "Internal";
		descr.category = (registerAsGenerator ? (acceptsMidi ? "Synth" : "Generator") : "Effect");
		descr.manufacturerName = "Instigator";
		descr.fileOrIdentifier = pluginName + ":" + pluginState + ":Twonk";
		descr.uid = pluginName.hashCode();
		descr.isInstrument = (acceptsMidi && registerAsGenerator);
		descr.numInputChannels = (registerAsGenerator ? 0 : channelSetToUse.size());
		descr.numOutputChannels = channelSetToUse.size();

		return descr;
	}
private:
	static BusesProperties getBusProperties (bool registerAsGenerator,
		const AudioChannelSet& channelSetToUse)
	{
		return registerAsGenerator ? BusesProperties().withOutput ("Output", channelSetToUse)
			: BusesProperties().withInput  ("Input", channelSetToUse)
			.withOutput ("Output", channelSetToUse);
	}

	//==============================================================================
	String name, state;
	bool isGenerator, hasMidi;
	AudioChannelSet channelSet;
	bool weHaveOurEditor;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InternalPlugin)
};


//==============================================================================
/**
    Manages the internal plugin types.
*/
class InternalPluginFormat   : public AudioPluginFormat
{
public:
    //==============================================================================
    InternalPluginFormat(TwonkPlayHead &_twonkPlayHead);
    ~InternalPluginFormat() override {}

    //==============================================================================
    PluginDescription audioInDesc, audioOutDesc, midiInDesc, midiDesc;

    void getAllTypes (OwnedArray<PluginDescription>&);

    //==============================================================================
    String getName() const override                                                     { return "Internal"; }
    bool fileMightContainThisPluginType (const String&) override                        { return true; }
    FileSearchPath getDefaultLocationsToSearch() override                               { return {}; }
    bool canScanForPlugins() const override                                             { return false; }
    void findAllTypesForFile (OwnedArray <PluginDescription>&, const String&) override  {}
    bool doesPluginStillExist (const PluginDescription&) override                       { return true; }
    String getNameOfPluginFromIdentifier (const String& fileOrIdentifier) override      { return fileOrIdentifier; }
    bool pluginNeedsRescanning (const PluginDescription&) override                      { return false; }
    StringArray searchPathsForPlugins (const FileSearchPath&, bool, bool) override      { return {}; }

private:
	TwonkPlayHead &twonkPlayHead;
    //==============================================================================
    void createPluginInstance (const PluginDescription&, double initialSampleRate, int initialBufferSize,
                               void* userData, PluginCreationCallback) override;
    AudioPluginInstance* createInstance (const String& name);

    bool requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const noexcept override;
};
#pragma once

#include "PluginGraph.h"
#include "UI/TwonkLookAndFeel.h"

class InternalPluginFormat   : public AudioPluginFormat
{
public:
    //==============================================================================
    InternalPluginFormat();
    ~InternalPluginFormat() override {}

    //==============================================================================
    PluginDescription audioInDesc, audioOutDesc, midiInDesc;
    void getAllTypes (Array<PluginDescription>&);

    //==============================================================================
    String getName() const override                                                     { return "Internal"; }
    bool fileMightContainThisPluginType (const String&) override                        { return true; }
    FileSearchPath getDefaultLocationsToSearch() override                               { return {}; }
    bool canScanForPlugins() const override                                             { return false; }
    bool isTrivialToScan() const override                                               { return true; }
    void findAllTypesForFile (OwnedArray<PluginDescription>&, const String&) override   {}
    bool doesPluginStillExist (const PluginDescription&) override                       { return true; }
    String getNameOfPluginFromIdentifier (const String& fileOrIdentifier) override      { return fileOrIdentifier; }
    bool pluginNeedsRescanning (const PluginDescription&) override                      { return false; }
    StringArray searchPathsForPlugins (const FileSearchPath&, bool, bool) override      { return {}; }

private:
    //==============================================================================
    void createPluginInstance (const PluginDescription&,
                               double initialSampleRate, int initialBufferSize,
                               PluginCreationCallback) override;

    std::unique_ptr<AudioPluginInstance> createInstance (const String& name);

    bool requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const override;
};

class TwonkPluginFormat : public AudioPluginFormat
{
public:
	//==============================================================================
	TwonkPluginFormat();
	~TwonkPluginFormat() override {}

	//==============================================================================
	PluginDescription audioInDesc, audioOutDesc, midiInDesc;
	void getAllTypes (Array<PluginDescription>&);

	//==============================================================================
	String getName() const override { return "Twonk"; }
	bool fileMightContainThisPluginType (const String&) override { return true; }
	FileSearchPath getDefaultLocationsToSearch() override { return {}; }
	bool canScanForPlugins() const override { return false; }
	bool isTrivialToScan() const override { return true; }
	void findAllTypesForFile (OwnedArray<PluginDescription>&, const String&) override {}
	bool doesPluginStillExist (const PluginDescription&) override { return true; }
	String getNameOfPluginFromIdentifier (const String& fileOrIdentifier) override { return fileOrIdentifier; }
	bool pluginNeedsRescanning (const PluginDescription&) override { return false; }
	StringArray searchPathsForPlugins (const FileSearchPath&, bool, bool) override { return {}; }

private:
	//==============================================================================
	void createPluginInstance (const PluginDescription&,
		double initialSampleRate, int initialBufferSize,
		PluginCreationCallback) override;

	std::unique_ptr<AudioPluginInstance> createInstance (const String& name);

	bool requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const override;
};

class InternalPlugin : public AudioPluginInstance
{
protected:
	InternalPlugin (const PluginDescription& descr,
		const AudioChannelSet& channelSetToUse = AudioChannelSet::stereo())
		: AudioPluginInstance (getBusProperties (descr.numInputChannels == 0, channelSetToUse)),
		name  (descr.fileOrIdentifier.upToFirstOccurrenceOf (":", false, false)),
		state (descr.fileOrIdentifier.fromFirstOccurrenceOf (":", false, false)),
		isGenerator (descr.numInputChannels == 0),
		hasMidi (descr.isInstrument),
		channelSet (channelSetToUse)
	{
		jassert (channelSetToUse.size() == descr.numOutputChannels);
	}

public:
	//==============================================================================
	const String getName() const override { return name; }
	double getTailLengthSeconds() const override { return 0.0; }
	bool acceptsMidi() const override { return hasMidi; }
	bool producesMidi() const override { return hasMidi; }
	AudioProcessorEditor* createEditor() override { return nullptr; }
	bool hasEditor() const override { return false; }
	int getNumPrograms() override { return 0; }
	int getCurrentProgram() override { return 0; }
	void setCurrentProgram (int) override {}
	const String getProgramName (int) override { return {}; }
	void changeProgramName (int, const String&) override {}
	void getStateInformation (juce::MemoryBlock&) override {}
	void setStateInformation (const void*, int) override {}

	//==============================================================================
	bool isBusesLayoutSupported (const BusesLayout& layout) const override
	{
		if (!isGenerator)
			if (layout.getMainOutputChannelSet() != channelSet)
				return false;

		if (layout.getMainInputChannelSet() != channelSet)
			return false;

		return true;
	}

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

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InternalPlugin)
};

class TwonkPlugin : public AudioPluginInstance
{
protected:
	TwonkPlugin (const PluginDescription& descr,
		const AudioChannelSet& channelSetToUse = AudioChannelSet::stereo())
		: AudioPluginInstance (getBusProperties (descr.numInputChannels == 0, channelSetToUse)),
		name  (descr.fileOrIdentifier.upToFirstOccurrenceOf (":", false, false)),
		state (descr.fileOrIdentifier.fromFirstOccurrenceOf (":", false, false)),
		isGenerator (descr.numInputChannels == 0),
		hasMidi (descr.isInstrument),
		channelSet (channelSetToUse)
	{
		jassert (channelSetToUse.size() == descr.numOutputChannels);
	}

public:
	//==============================================================================
	const String getName() const override { return name; }
	double getTailLengthSeconds() const override { return 0.0; }
	bool acceptsMidi() const override { return hasMidi; }
	bool producesMidi() const override { return hasMidi; }
	AudioProcessorEditor* createEditor() override { return nullptr; }
	bool hasEditor() const override { return false; }
	int getNumPrograms() override { return 0; }
	int getCurrentProgram() override { return 0; }
	void setCurrentProgram (int) override {}
	const String getProgramName (int) override { return {}; }
	void changeProgramName (int, const String&) override {}
	void getStateInformation (juce::MemoryBlock&) override {}
	void setStateInformation (const void*, int) override {}

	//==============================================================================
	bool isBusesLayoutSupported (const BusesLayout& layout) const override
	{
		if (!isGenerator)
			if (layout.getMainOutputChannelSet() != channelSet)
				return false;

		if (layout.getMainInputChannelSet() != channelSet)
			return false;

		return true;
	}

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
		descr.pluginFormatName = "Twonk";
		descr.category = (registerAsGenerator ? (acceptsMidi ? "Synth" : "Generator") : "Effect");
		descr.manufacturerName = "Twonk";
		descr.version = ProjectInfo::versionString;
		descr.fileOrIdentifier = pluginName + ":" + pluginState;
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

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkPlugin)
};
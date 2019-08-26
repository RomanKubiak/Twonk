/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "JucesamplerAudioProcessor.h"
#include "JucesamplerAudioProcessorEditor.h"
static String doubleToString(double val) { return String(val); }
static double stringToDouble(String s){return std::stod(s.toStdString());}

static String boolToString(float val) { return (val == 1.0f) ? "active" : "inactive"; }
static bool stringToBool(String s) { return (s == "active") ? true : false; }

static String intToString(int val) { return String(val); }
static int stringToInt(String s) { return std::stoi(s.toStdString()); }

//==============================================================================
JucesamplerAudioProcessor::JucesamplerAudioProcessor(const PluginDescription& descr)
     : TwonkPlugin (descr, BusesProperties()
						   .withOutput ("Output", AudioChannelSet::stereo(), true)
						   .withOutput ("Output", AudioChannelSet::stereo(), true)
						   .withOutput ("Output", AudioChannelSet::stereo(), true)
						   .withOutput ("Output", AudioChannelSet::stereo(), true)),
	sampler(instrumentsLoaded)
{
	undoManager = new UndoManager();
	valueTree = new AudioProcessorValueTreeState(*this, undoManager);
	
	//Initialising Sampler
	sampler.init();
	//Adding all Parameters to the Value Tree
	for(int i = 0; i < sampler.getNumVoices(); i++)
	{
		valueTree->createAndAddParameter(String("ampEnvAttack" + String(i)), "ampEnvAttack", "", NormalisableRange<float>(0.0f, 500.0f), 0.0f, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvDecay" + String(i)), "ampEnvDecay", "", NormalisableRange<float>(0.0f, 1000.0f), 0.0f, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvSustain" + String(i)), "ampEnvSustain", "", NormalisableRange<float>(0.0f, 1.0f), 1, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("ampEnvRelease" + String(i)), "ampEnvRelease", "", NormalisableRange<float>(0.0f, 5000.0f), 1000.0f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("Filter ON/OFF" + String(i)), "Filter ON/OFF", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("filterCutoff" + String(i)), "filterCutoff", "", NormalisableRange<float>(40, 18000.0f, 0, 0.199f), 18000.0f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("Distortion ON/OFF" + String(i)), "Distortion ON/OFF", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("distortionVal" + String(i)), "distortionVal", "", NormalisableRange<float>(0.2f, 5.0f), 0.2f, doubleToString, stringToDouble);

		valueTree->createAndAddParameter(String("pitchVal" + String(i)), "pitchVal", "", NormalisableRange<float>(-12, 12, 1), 0, intToString, stringToInt);

		valueTree->createAndAddParameter(String("vf" + String(i)), "vf", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("vu" + String(i)), "vu", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
		valueTree->createAndAddParameter(String("amp" + String(i)), "amplitude", "", NormalisableRange<float>(0.0f, 1.0f), 1, doubleToString, stringToDouble);
		valueTree->createAndAddParameter(String("pan" + String(i)), "Pan", "", NormalisableRange<float>(-1.0f, 1.0f), 0, doubleToString, stringToDouble);

		if(auto* voice = dynamic_cast<CTAGSamplerVoice*>(sampler.getVoice(i)))
		{
			valueTree->addParameterListener(String("ampEnvAttack" + String(i)) , voice);
			valueTree->addParameterListener(String("ampEnvDecay" + String(i)), voice);
			valueTree->addParameterListener(String("ampEnvSustain" + String(i)), voice);
			valueTree->addParameterListener(String("ampEnvRelease" + String(i)), voice);

			valueTree->addParameterListener(String("Filter ON/OFF" + String(i)), voice);
			valueTree->addParameterListener(String("filterCutoff" + String(i)), voice);

			valueTree->addParameterListener(String("Distortion ON/OFF" + String(i)), voice);
			valueTree->addParameterListener(String("distortionVal" + String(i)), voice);

			valueTree->addParameterListener(String("pitchVal" + String(i)), voice);

			valueTree->addParameterListener(String("vf" + String(i)), voice);
			valueTree->addParameterListener(String("vu" + String(i)), voice);
			valueTree->addParameterListener(String("amp" + String(i)), voice);
			valueTree->addParameterListener(String("pan" + String(i)), voice);
		}
		
	}

	valueTree->createAndAddParameter(String("Choke ON/OFF"), "Choke ON/OFF", "", NormalisableRange<float>(0, 1, 1), 0, boolToString, stringToBool);
	valueTree->addParameterListener(String("Choke ON/OFF"), &sampler);
	valueTree->state = ValueTree("CTAGSamplerParameters");
}

JucesamplerAudioProcessor::~JucesamplerAudioProcessor()
{
	undoManager = nullptr;
	valueTree = nullptr;
}

//==============================================================================
const String JucesamplerAudioProcessor::getName() const
{
    return "Sampler";
}

bool JucesamplerAudioProcessor::acceptsMidi() const
{
    return true;
}

bool JucesamplerAudioProcessor::producesMidi() const
{
    return false;
}

bool JucesamplerAudioProcessor::isMidiEffect() const
{
    return false;
}

double JucesamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JucesamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JucesamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JucesamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String JucesamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void JucesamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JucesamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	sampler.setCurrentPlaybackSampleRate(sampleRate);

	for (int i = 0; i < sampler.getNumVoices(); i++)
	{
		if (auto* voice = dynamic_cast<CTAGSamplerVoice*>(sampler.getVoice(i)))
		{
			voice->getEnvelope().setSampleRate(sampleRate);
			voice->getFilterLeft().setSampleRate(sampleRate);
			voice->getFilterRight().setSampleRate(sampleRate);
		}
	}
}

void JucesamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JucesamplerAudioProcessor::loadBank(const File &bank)
{
	if (bank.getChildFile("info.json").existsAsFile())
	{
		var result;
		Result res = JSON::parse(bank.getChildFile("info.json").loadFileAsString(), result);
		if (res.failed())
		{
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Bank loading failed", "Can't parse the json file inside", "Fuck!");
			return;
		}
		else
		{
			if (res.wasOk())
			{
				// this is a known bank so we can parse the rest of the json and assign
				// samples as described in it
				loadSamples(bank, result);
			}
			else
			{
				// this is just a directory of samples, hopefuly it has subdirectories
				// treat each subdirectory with the extension .instrument as a set of samples
				// for one drum sound
				// if not just load the first 16 found samples
				// TODO
			}
		}
	}
}

Result JucesamplerAudioProcessor::loadSamples(const File &bank, var &bankJsonInfo)
{
	DBG("JucesamplerAudioProcessor::loadSamples:");
	if (!bankJsonInfo.getProperty("bank", var()).isArray())
		return Result::fail("Can't parse the bank array in json");

	clearInstruments();

	for (int i = 0; i < bankJsonInfo.getProperty("bank", var()).getArray()->size(); i++)
	{
		bool firstInstrument = true;
		var instrument = bankJsonInfo.getProperty("bank", var()).getArray()->getReference(i);
		String instrumentWildcard = instrument.getDynamicObject()->getProperty("files").toString();
		String instrumentName = instrument.getDynamicObject()->getProperty("name").toString();
		String instrumentVelocityCurve = instrument.getDynamicObject()->getProperty("velocity").toString();
		int midiNoteNumber = instrument.getDynamicObject()->getProperty("midiNote");
		int midiChannel = instrument.getDynamicObject()->getProperty("midiChannel");
		int audioOutputChannel = instrument.getDynamicObject()->getProperty("audioOutputChannel");

		DBG("name: " + instrumentName);
		DBG("\tvelocityCurve: " + instrumentVelocityCurve);
		DBG("\tfilenameWildcard: " + instrumentWildcard);
		DBG("\tmidiNote: " + String(midiNoteNumber));
		{
			DirectoryIterator it (bank, false, instrumentWildcard);
			SamplerInstrument *instrument = new SamplerInstrument;
			instrument->name = instrumentName;
			instrument->midiNote = midiNoteNumber;
			instrument->velocityCurve = instrumentVelocityCurve;
			instrument->midiChannel = midiChannel;
			instrument->audioOutputChannel = audioOutputChannel;
			while (it.next())
			{
				instrument->fileList.add(it.getFile());
			}

			getInstrumentsArray().add(instrument);
		}
	}

	reloadInstruments();
	return Result::ok();
}

void JucesamplerAudioProcessor::clearInstruments()
{
	sampler.clearSounds();
	sampler.clearVoices();
	sampler.init();
	instrumentsLoaded.clear();
}

void JucesamplerAudioProcessor::reloadInstruments()
{
	sampler.reloadInstruments();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JucesamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::create7point1())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JucesamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	midiMessages.addEvents(additionalMessagesToConsider, 0, buffer.getNumSamples(), 0);

	if (midiMessages.getNumEvents() > 0)
	{
		MidiMessage m;
		int samplePosition;
		MidiBuffer::Iterator it(midiMessages);
		while (it.getNextEvent(m, samplePosition))
		{
			DBG(String::formatted("note:%d velo:%d", m.getNoteNumber(), m.getVelocity()));
		}
	}

	sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	additionalMessagesToConsider.clear();
}

//==============================================================================
bool JucesamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JucesamplerAudioProcessor::createEditor()
{
    return new JuceSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void JucesamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	MemoryOutputStream stream(destData, false);
	valueTree->state.writeToStream(stream);
}

void JucesamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if(tree.isValid())
	{
		if(tree.hasType("CTAGSamplerParameters"))
		{
			valueTree->state = tree;
		}
	}
}
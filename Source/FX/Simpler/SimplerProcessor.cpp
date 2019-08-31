#include "SimplerProcessor.h"
#include "SimplerEditor.h"
#include "UI/MainHostWindow.h"
#include "SimplerVoice.h"
#include "Utils.h"

SimplerProcessor::SimplerProcessor(const PluginDescription& descr)
		: TwonkPlugin (descr), processorState(*this, nullptr)
{
	std::function<String(int, int)> bankIndexToName = [&](int index, int maxLen)
	{
		const Array<File> list = getBankList();
		return list[index].getFullPathName();
	};

	std::function<int(String)> bankNameToIndex = [&](String bankName)
	{
		File f = File(bankName);
		if (f.isDirectory())
		{
			const Array<File> list = getBankList();
			return (list.indexOf(f));
		}
		else
		{
			return (0);
		}
	};

	formatManager.registerBasicFormats();
	for (int i = 0; i < VOICES; i++)
	{
		sampler.addVoice(new SimplerVoice(i));
	}

	processorState.createAndAddParameter(std::make_unique<AudioParameterInt>
		("bank", "bank", 0, GET_TWONK_SAMPLES_DIR().getNumberOfChildFiles(File::findDirectories, "*.twonk") - 1, 0, "bank", 
			bankIndexToName, bankNameToIndex));

	processorState.createAndAddParameter("", "ampEnvAttack", "", NormalisableRange<float>(0.0f, 500.0f), 0.0f, doubleToString, stringToDouble);

	processorState.state = ValueTree("Simpler");
	
	// this will tell us to load the last bank
	processorState.addParameterListener("bank", this);

	programList.setDirectory(GET_TWONK_SAMPLES_DIR(), true, false);
	directoryThread.startThread(1);
	programList.addChangeListener(this);
}

SimplerProcessor::~SimplerProcessor()
{
}

void SimplerProcessor::prepareToPlay (double newSampleRate, int samplesPerBlock)
{
	ignoreUnused (samplesPerBlock);
	sampler.setCurrentPlaybackSampleRate (newSampleRate);
}

void SimplerProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiBuffer)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear (i, 0, buffer.getNumSamples());

	
	midiBuffer.addEvents(additionalMessagesToConsider, 0, buffer.getNumSamples(), 0);
	sampler.renderNextBlock(buffer, midiBuffer, 0, buffer.getNumSamples());
	additionalMessagesToConsider.clear();
}

AudioProcessorEditor* SimplerProcessor::createEditor()
{
	return new SimplerEditor(*this);
}

void SimplerProcessor::getStateInformation (MemoryBlock &destData)
{
	MemoryOutputStream stream(destData, false);
	processorState.state.writeToStream(stream);
}

void SimplerProcessor::setStateInformation (const void *data, int sizeInBytes)
{
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if (tree.isValid())
	{
		if (tree.hasType("Simpler"))
		{
			processorState.state = tree;
		}
	}
}

const String SimplerProcessor::createJsonFor(const File &bank)
{
	DBG("JucesamplerAudioProcessor::createJsonFor " + bank.getFullPathName());
	String json = ("{\n\t\"bank\":\n\t[\n");

	if (bank.containsSubDirectories())
	{
		int midiNote = 35;
		DirectoryIterator bankDirIterator(bank, false, "*", File::findDirectories);
		while (bankDirIterator.next())
		{
			json << createJsonForDirWithSubDirs(bankDirIterator.getFile(), midiNote);
		}
		json = json.upToLastOccurrenceOf(",", false, false);
	}
	else
	{
		json << createJsonForDirWithSamples(bank);
	}

	json << "\n\t]\n}";
	DBG(json);
	return (json);
}

void SimplerProcessor::loadBank(const File &bank)
{
	lastLoadedBank = bank;
	DBG("loading bank: " + bank.getFullPathName());
	if (bank.getChildFile("info.json").existsAsFile())
	{
		var result;
		Result res = JSON::parse(bank.getChildFile("info.json").loadFileAsString(), result);
		if (res.wasOk())
		{
			// this is a known bank so we can parse the rest of the json and assign
			// samples as described in it
			loadSamples(bank, result);
		}
	}
	else if (bank.containsSubDirectories() || bank.getNumberOfChildFiles(File::findFiles, "*") > 0)
	{
		const String json = createJsonFor(bank);
		var parsedJson;
		const Result parsingResult = JSON::parse(json, parsedJson);

		if (parsingResult.wasOk())
		{
			File jsonInfo = bank.getChildFile("info.json");
			if (jsonInfo.hasWriteAccess())
			{
				jsonInfo.replaceWithText(json);
				loadBank(bank);
			}
			else
			{
				loadSamples(bank, parsedJson);
			}
		}
		else
		{
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Bank creation failure", "Can't create a valid json description for directory: " + bank.getFileName());
		}
	}
}

Result SimplerProcessor::loadSamples(const File &bank, var &bankJsonInfo)
{
	instrumentsLoaded.clear();

	if (!bankJsonInfo.getProperty("bank", var()).isArray())
		return Result::fail("Can't parse the bank array in json");

	for (int i = 0; i < bankJsonInfo.getProperty("bank", var()).getArray()->size(); i++)
	{
		bool firstInstrument = true;
		var instrument = bankJsonInfo.getProperty("bank", var()).getArray()->getReference(i);
		String instrumentName = instrument.getDynamicObject()->getProperty("name").toString();
		int midiNoteNumber = instrument.getDynamicObject()->getProperty("midiNote");
		int midiChannel = instrument.getDynamicObject()->getProperty("midiChannel");
		int audioOutputChannel = instrument.getDynamicObject()->getProperty("audioOutputChannel");

		if (instrument.getDynamicObject()->getProperty("files").isString())
		{
			DirectoryIterator it (bank, false, instrument.getDynamicObject()->getProperty("files").toString());
			SimplerInstrument *instrument = new SimplerInstrument;
			instrument->name = instrumentName;
			instrument->midiNote = midiNoteNumber;
			instrument->midiChannel = midiChannel;
			instrument->audioOutputChannel = audioOutputChannel;
			while (it.next())
			{
				instrument->fileList.add(it.getFile());
			}

			instrumentsLoaded.add(instrument);
		}
		else if (instrument.getDynamicObject()->getProperty("files").isArray())
		{
			SimplerInstrument *instrumentObject = new SimplerInstrument;
			instrumentObject->name = instrumentName;
			instrumentObject->midiNote = midiNoteNumber;
			instrumentObject->midiChannel = midiChannel;
			instrumentObject->audioOutputChannel = audioOutputChannel;

			for (int i = 0; i < instrument.getDynamicObject()->getProperty("files").size(); i++)
			{
				File f;

				if (instrument.getDynamicObject()->getProperty("files").size() == 1)
				{
					f = bank.getChildFile
					(
						instrument.getDynamicObject()->getProperty("files")[i].toString()
					);

					instrumentObject->name = f.getFileNameWithoutExtension();
				}
				else if (instrument.getDynamicObject()->getProperty("files").size() > 1)
				{
					f = bank.getChildFile
					(
						instrument.getDynamicObject()->getProperty("files")[i].toString()
					);
				}

				instrumentObject->fileList.add(f);
			}

			instrumentsLoaded.add(instrumentObject);
		}
	}
	processorState.getParameterAsValue("bank") = bankList.indexOf(bank);
	reloadInstruments();
	return Result::ok();
}

void SimplerProcessor::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == &programList)
	{
		if (!programList.isStillLoading())
		{
			if (programList.getNumFiles() > 0)
			{
				bankList.clear();
				for (int i = 0; i < programList.getNumFiles(); i++)
				{
					bankList.add(programList.getFile(i));
				}
			}
			sendChangeMessage();
			loadLastBank();
		}
	}
}

void SimplerProcessor::reloadInstruments()
{
	sampler.clearSounds();

	for (int i = 0; i < instrumentsLoaded.size(); i++)
	{
		if (i > 15)
		{
			DBG("TOO MANY instruments to load sorry, only 16 supported");
			break;
		}
		addSoundToSampler(instrumentsLoaded[i]);
	}
	sendChangeMessage();
}

void SimplerProcessor::addSoundToSampler(SimplerInstrument *instrumentToAdd)
{
	int sampleCount = instrumentToAdd->fileList.size();
	int veloStep = 127 / sampleCount;
	int velocityRangeStart = 0;
	int velocityRangeEnd = veloStep;

	for (int i = 0; i < sampleCount; i++)
	{
		File file = instrumentToAdd->fileList[i];
		std::unique_ptr<AudioFormatReader> fileReader (formatManager.createReaderFor(file));
		BigInteger midiNotes;
		midiNotes.setBit(instrumentToAdd->midiNote);

		if (i == sampleCount - 1)
			velocityRangeEnd = 127;

		SimplerSound *sound = new SimplerSound (
			instrumentToAdd->name, 
			*fileReader,
			midiNotes,
			instrumentToAdd->midiNote,
			0.0,  /* attack time */
			1.0,  /* release time */
			10.0, /* max sample length */
			sampleCount == 1 ? 0 : velocityRangeStart,
			sampleCount == 1 ? 127 : velocityRangeEnd,
			file  /* for later info */
		);

		velocityRangeStart += veloStep;
		velocityRangeEnd += veloStep;
		
		instrumentToAdd->assosiatedSound.add(sound);
		sampler.addSound(sound);
	}
}

void SimplerProcessor::parameterChanged (const String &parameterID, float newValue)
{
}

void SimplerProcessor::loadLastBank()
{
	DBG("SimplerProcessor::loadLastBank lastBank: " + processorState.getParameter("bank")->getCurrentValueAsText());

	if (processorState.getParameter("bank")->getCurrentValueAsText().isNotEmpty())
	{
		File bank(processorState.getParameter("bank")->getCurrentValueAsText());
		if (bank.isDirectory())
		{
			loadBank(bank);
		}
		else
		{
			DBG("Last saved bank is not a directory");
		}
	}
	else
	{
		DBG("No last bank saved");
	}
}
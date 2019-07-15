#include "SimpleSamplerProcessor.h"
#include "SimpleSamplerEditor.h"

#define MAX_VOICES 32
#define MAX_SOUNDS 8

SimpleSamplerProcessor::SimpleSamplerProcessor(const PluginDescription& descr) 
	: InternalPlugin (descr, true), currentProgramZip(nullptr)
{
	programDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(ProjectInfo::projectName);
	if (!programDir.isDirectory())
	{
		if (!programDir.createDirectory().wasOk())
		{
			DBG("can't create data directory " + programDir.getFullPathName());
		}
	}

	programZipFiles = programDir.findChildFiles(File::findFiles, false, "*.zip");

	setCurrentProgram(1);
}

SimpleSamplerProcessor::~SimpleSamplerProcessor()
{
	deleteAndZero (currentProgramZip);
}

void SimpleSamplerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void SimpleSamplerProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
}

int SimpleSamplerProcessor::getNumPrograms()
{
	if (programZipFiles.size() > 0)
	{
		return (programZipFiles.size());
	}
	else
	{
		DBG("no programs in data directory "+ programDir.getFullPathName());
		return 1;
	}
}

void SimpleSamplerProcessor::setCurrentProgram (int index)
{
	File programFile = programZipFiles[index];

	if (programFile.existsAsFile())
	{
		DBG("setting program to:\"" + programFile.getFullPathName() + "\"");
		if (currentProgramZip)
		{
			deleteAndZero(currentProgramZip);
		}

		currentProgramZip = new ZipFile(programFile.getFullPathName());
		for (int i = 0; i < currentProgramZip->getNumEntries(); i++)
		{
			const ZipFile::ZipEntry *sample = currentProgramZip->getEntry(i);
			DBG(sample->filename);
		}
	}
}

const String SimpleSamplerProcessor::SimpleSamplerProcessor::getProgramName (int index)
{
	return (programZipFiles[index].getFileNameWithoutExtension());
}

AudioProcessorEditor* SimpleSamplerProcessor::createEditor() { return new SimpleSamplerEditor(*this);  }
void SimpleSamplerProcessor::releaseResources() {}
void SimpleSamplerProcessor::getStateInformation (MemoryBlock& destData) {}
void SimpleSamplerProcessor::setStateInformation (const void* data, int sizeInBytes) {}
bool SimpleSamplerProcessor::hasEditor() const { return true; }
bool SimpleSamplerProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const { return true; }
const String SimpleSamplerProcessor::getName() const { return "Simple Sampler"; }
bool SimpleSamplerProcessor::acceptsMidi() const { return true; }
bool SimpleSamplerProcessor::producesMidi() const { return false; }
bool SimpleSamplerProcessor::isMidiEffect() const { return false; }
double SimpleSamplerProcessor::getTailLengthSeconds() const { return 0.0; }

int SimpleSamplerProcessor::getCurrentProgram() { return 0; }
void SimpleSamplerProcessor::changeProgramName (int index, const String& newName) {}
#include "SimpleSamplerProcessor.h"
#include "SimpleSamplerEditor.h"
#define MAX_VOICES 32
#define MAX_SOUNDS 8
TwonkSamplerSound::TwonkSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLenthSecs)
	: SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLenthSecs)
{
}

bool TwonkSamplerSound::appliesToChannel(int midiChannel)
{
	return (true);
}

void TwonkSamplerSynth::setup()
{
	// add voices to our sampler
	for (int i = 0; i < MAX_VOICES; i++) {
		addVoice(new SamplerVoice());
	}

	// set up our AudioFormatManager class as detailed in the API docs
	// we can now use WAV and AIFF files!
	audioFormatManager.registerBasicFormats();

	// now that we have our manager, lets read a simple file so we can pass it to our SamplerSound object.
	File* file = new File("c:\\devel\\file.wav");
	ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(*file);

	// allow our sound to be played on all notes
	BigInteger allNotes;
	allNotes.setRange(0, 128, true);

	// finally, add our sound
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		addSound(new TwonkSamplerSound(String(i), *reader, allNotes, 60, 0, 10, 10.0));
	}
}

SimpleSamplerProcessor::SimpleSamplerProcessor(const PluginDescription& descr) : InternalPlugin (descr, true)
{
}

void SimpleSamplerProcessor::setFileForSound(int index, File &filePath)
{
	if (index < MAX_SOUNDS)
	{
	}
}

SimpleSamplerProcessor::~SimpleSamplerProcessor()
{
}

void SimpleSamplerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	samplerSynth.setCurrentPlaybackSampleRate(sampleRate);
	samplerSynth.setup();
}

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
int SimpleSamplerProcessor::getNumPrograms() { return 1; }
int SimpleSamplerProcessor::getCurrentProgram() { return 0; }
void SimpleSamplerProcessor::setCurrentProgram (int index) { }
const String SimpleSamplerProcessor::getProgramName (int index) { return {}; }
void SimpleSamplerProcessor::changeProgramName (int index, const String& newName) {}

void SimpleSamplerProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	samplerSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

AudioProcessorEditor* SimpleSamplerProcessor::createEditor() { return new SimpleSamplerEditor(*this);  }
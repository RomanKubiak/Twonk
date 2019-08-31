#pragma once
#include "JuceHeader.h"
class SimplerSound : public SynthesiserSound
{
	public:
		SimplerSound (const String& name,
			AudioFormatReader& source,
			const BigInteger& midiNotes,
			int midiNoteForNormalPitch,
			double attackTimeSecs,
			double releaseTimeSecs,
			double maxSampleLengthSeconds,
			int velocityRangeStart,
			int velocityRangeEnd,
			const File &sampleFile);

		~SimplerSound() override;
		const String& getName() const noexcept { return name; }
		AudioBuffer<float>* getAudioData() const noexcept { return data.get(); }
		void setEnvelopeParameters (ADSR::Parameters parametersToUse);
		bool appliesToNote (int midiNoteNumber) override;
		bool appliesToChannel (int midiChannel) override;
		bool appliesToVelocity(const float velocity);
		const double getSampleRate() const { return (sourceSampleRate); }
		const double getLength() const { return (length); }
		const File getSampleFile() const { return (sampleFile); }
		const int getMidiRootNote() const { return (midiRootNote); }
		NormalisableRange<int> &getVelocityRange() { return (velocityRange); }
		const ADSR::Parameters getCurrentADSRParameters() { return (params); }

	private:
		friend class SimplerVoice;
		String name;
		std::unique_ptr<AudioBuffer<float>> data;
		double sourceSampleRate = 44100;
		BigInteger midiNotes;
		double length = 0;
		int midiRootNote = 0;
		ADSR::Parameters params;
		File sampleFile;
		NormalisableRange<int> velocityRange;
		JUCE_LEAK_DETECTOR (SimplerSound)
};
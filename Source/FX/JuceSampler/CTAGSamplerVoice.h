/**
	A Sampler Voice Object, which is able to play a sampled sound.

	

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CTAGSamplerSound.h"
#include "EnvelopeGenerator.h"
#include "OnePoleFilter.h"
#include "WaveShaper.h"
#include "PanPos.h"

class CTAGSamplerVoice : public SamplerVoice,  public AudioProcessorValueTreeState::Listener
{
	public:
		CTAGSamplerVoice(int i);
		void parameterChanged(const String &parameterID, float newValue) override;
		bool canPlaySound(SynthesiserSound* sampSound) override;
		void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sampSound, int pitchWheel) override;
		void stopNote(float velocity, bool allowTailOff) override;
		void pitchWheelMoved(int newValue) override;
		void controllerMoved(int controllerNumber, int newValue) override;
		void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
		void setMidiNote(int note);
		bool canPlayCTAGSound(int note) const;
		void setCurrentPlaybackSampleRate(double newRate);
		EnvelopeGenerator & getEnvelope() { return env; }
		VAOnePoleFilter& getFilterLeft() { return filterLeft; }
		VAOnePoleFilter& getFilterRight() { return filterRight; }
		void setPitchVal(int pitch) { pitchVal = pitch; }
		int getPitchVal() { return pitchVal; }
		void setEnvelopeAttack(double time) { env.setAttackTime_mSec(time); }
		void setEnvelopeDecay(double time) { env.setDecayTime_mSec(time); }
		void setEnvelopeSustain(double sus) { env.setSustainLevel(sus); }
		void setEnvelopeRelease(double time) { env.setReleaseTime_mSec(time); }
		bool isFilterActive() { return filterLeft.isActive() && filterRight.isActive(); }
		void setFilterActive(bool val)
		{
			filterLeft.setActive(val);
			filterRight.setActive(val);
		}
		void setCutoffFreq(double cutoffFrequency)
		{
			filterLeft.cutoffControl = cutoffFrequency;
			filterRight.cutoffControl = cutoffFrequency;
		}
		bool isWaveShaperActive() { return shaper.isActive(); }
		void setWaveShaperActive(bool val) { shaper.setActive(val); }
		void setWaveShaperSymmetrical(double amp) { shaper.setAmplificationSymmetrical(amp); }

	private:
		int pitchVal;
		BigInteger midiNote;
		EnvelopeGenerator env;
		VAOnePoleFilter filterLeft, filterRight;
		WaveShaper shaper;
		PanPos pan;
		int index;
		LinearSmoothedValue<double> shaperAmp, levelAmp, panAmp;
		double currSampRate;
		bool isVelocityFilterActive, isVelocityVolumeActive;
		//Variables from SamplerVoice Base Class
		double pitchRatio = 0;
		double sourceSamplePosition = 0;
		float lgain = 0, rgain = 0;
		double filterCutoff;
		double levelSlider;
};


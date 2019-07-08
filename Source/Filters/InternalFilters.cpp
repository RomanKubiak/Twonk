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

#include "../JuceLibraryCode/JuceHeader.h"
#include "InternalFilters.h"
#include "FilterGraph.h"
#include "../FX/TwonkFilters.h"
#include "../FX/SineWaveSynth/SineWaveSynth.h"
#include "../TwonkPlayHead.h"

//==============================================================================
InternalPluginFormat::InternalPluginFormat(TwonkPlayHead &_twonkPlayHead) : twonkPlayHead(_twonkPlayHead)
{
    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
        p.fillInPluginDescription (audioOutDesc);
    }

    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
        p.fillInPluginDescription (audioInDesc);
    }

    {
        AudioProcessorGraph::AudioGraphIOProcessor p (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);
        p.fillInPluginDescription (midiInDesc);
    }
}

AudioPluginInstance* InternalPluginFormat::createInstance (const String& name)
{
	DBG("InternalPluginFormat::createInstance " + name);
    if (name == audioOutDesc.name)
		return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
    
	if (name == audioInDesc.name)
		return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
    
	if (name == midiInDesc.name)
		return new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);

    if (name == SineWaveSynth::getIdentifier())
		return new SineWaveSynth (SineWaveSynth::getPluginDescription());
	
	return TwonkFilters::createInstance(name);
    return nullptr;
}

void InternalPluginFormat::createPluginInstance (const PluginDescription& desc,
                                                 double /*initialSampleRate*/,
                                                 int /*initialBufferSize*/,
                                                 void* userData,
                                                 PluginCreationCallback callback)
{
	AudioPluginInstance* p = createInstance (desc.name);
	DBG("InternalPluginFormat::createPluginInstance " + desc.name + " setting twonk play head");
	//p->setPlayHead(&twonkPlayHead);
    callback (userData, p, p == nullptr ? NEEDS_TRANS ("Invalid internal filter name") : String());
}

bool InternalPluginFormat::requiresUnblockedMessageThreadDuringCreation (const PluginDescription&) const noexcept
{
    return false;
}

void InternalPluginFormat::getAllTypes (OwnedArray<PluginDescription>& results)
{
    results.add (new PluginDescription (audioInDesc));
    results.add (new PluginDescription (audioOutDesc));
    results.add (new PluginDescription (midiInDesc));
    results.add (new PluginDescription (SineWaveSynth::getPluginDescription()));
	results.add (new PluginDescription (midiDesc));
	TwonkFilters::getAllTypes(results);
}
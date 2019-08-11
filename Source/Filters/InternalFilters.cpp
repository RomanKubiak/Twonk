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

std::unique_ptr<AudioPluginInstance> InternalPluginFormat::createInstance (const String& name)
{
	if (name == audioOutDesc.name) return std::make_unique<AudioProcessorGraph::AudioGraphIOProcessor> (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
	if (name == audioInDesc.name)  return std::make_unique<AudioProcessorGraph::AudioGraphIOProcessor> (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	if (name == midiInDesc.name)   return std::make_unique<AudioProcessorGraph::AudioGraphIOProcessor> (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);

	if (name == SineWaveSynth::getIdentifier()) return std::make_unique<SineWaveSynth> (SineWaveSynth::getPluginDescription());
	
 	return TwonkFilters::createInstance(name);
}

void InternalPluginFormat::createPluginInstance (const PluginDescription& desc,
                                                 double /*initialSampleRate*/,
                                                 int /*initialBufferSize*/,
                                                 PluginCreationCallback callback)
{
	if (auto p = createInstance (desc.name))
		callback (std::move (p), {});
	else
		callback (nullptr, NEEDS_TRANS ("Invalid internal plugin name"));
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
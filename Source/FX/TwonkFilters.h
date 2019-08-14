/*
  ==============================================================================

    TwonkFilters.h
    Created: 3 Jun 2019 4:29:20pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "../Filters/InternalPlugins.h"

class TwonkFilter
{
	public:
		virtual Component *getComponentForPanel() { return nullptr; }
};

class TwonkFilters
{
	public:
		static void getAllTypes(Array<PluginDescription>& results);
		static std::unique_ptr<AudioPluginInstance> createInstance (const String& name);
};
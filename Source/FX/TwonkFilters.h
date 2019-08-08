/*
  ==============================================================================

    TwonkFilters.h
    Created: 3 Jun 2019 4:29:20pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "../Filters/InternalFilters.h"

class TwonkFilter
{
	public:
		virtual Component *getComponentForPanel() { return nullptr; }
};

class TwonkFilters
{
	public:
		static void getAllTypes(OwnedArray<PluginDescription>& results);
		static AudioPluginInstance* createInstance (const String& name);
};
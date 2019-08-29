/*
  ==============================================================================

    TwonkPlatformSpecific.h
    Created: 26 Aug 2019 10:13:02pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
int getCpuUsage();
int64 getMemoryUsageMegabytes();
#if defined(WIN32)
#include "Windows/CpuUsage.h"
#endif
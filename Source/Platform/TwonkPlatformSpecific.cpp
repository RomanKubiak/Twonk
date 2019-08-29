/*
  ==============================================================================

    TwonkPlatformSpecific.cpp
    Created: 26 Aug 2019 10:13:02pm
    Author:  rkubiak

  ==============================================================================
*/

#include "TwonkPlatformSpecific.h"

#if defined(WIN32)
CpuUsage cpuUsage;
int getCpuUsage()
{
	return (cpuUsage.GetUsage());
}

int64 getMemoryUsageMegabytes()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	return ((statex.ullTotalVirtual - statex.ullAvailVirtual) / 1048576);
}
#else
int getCpuUsage()
{
	return (-1);
}

int64 getMemoryUsageMegabytes()
{
	return (-1);
}
#endif
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
float getCpuUsage()
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

#elif defined(__linux__)
#include <sys/types.h>
#include <unistd.h>
float getCpuUsage()
{
	FILE *in;
	char buff[512];
	float cpuUsage;
	
	if (!(in = popen("ps -C Twonk -o %cpu| tail -n 1", "r")))
	{
        	return 0.0;
	}
	
	if (fgets(buff, sizeof(buff), in) !=NULL)
	{		
		cpuUsage = atof(buff);
	}
	pclose(in);
	
	return cpuUsage;
}

int64 getMemoryUsageMegabytes()
{	
	FILE *in;
	char buff[512];
	char cmd[128];
	long int memoryUsed;
	int pid = getpid();
	sprintf(cmd, "pmap %d | tail -n 1 | awk '/[0-9]K/{print $2}'", pid);
	
	if (!(in = popen(cmd, "r")))
	{
		return (0);
	}
	if (fgets(buff, sizeof(buff), in) != NULL)
	{
		buff[strlen(buff)-1] = '\0';
		memoryUsed = atol(buff);
	}
	return (memoryUsed/1024); // megs
}

#else
int getCpuUsage()
{
	printf("undefined platform\n");
	fflush();
	return (-1);
}

int64 getMemoryUsageMegabytes()
{
	return (-1);
}

#endif
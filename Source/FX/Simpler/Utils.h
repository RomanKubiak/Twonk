/*
  ==============================================================================

    Utils.h
    Created: 29 Aug 2019 2:58:47pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

static String doubleToString(double val) { return String(val); }
static double stringToDouble(String s) { return std::stod(s.toStdString()); }

static String boolToString(float val) { return (val == 1.0f) ? "active" : "inactive"; }
static bool stringToBool(String s) { return (s == "active") ? true : false; }

static String intToString(int val) { return String(val); }
static int stringToInt(String s) { return std::stoi(s.toStdString()); }

static const String createJsonForDirWithSamples(const File &dir)
{
	DBG("String createJsonForInstrument dir: " + dir.getFullPathName());
	String json;

	DirectoryIterator instrumentDirIterator(dir, false, "*", File::findFiles);
	int midiNote = 35;
	while (instrumentDirIterator.next())
	{
		File sample = instrumentDirIterator.getFile();
		json << ("\t\t{\n\t\t\t\"name\":\"") << dir.getFileNameWithoutExtension() << "\",\n";
		json << ("\t\t\t\"files\":\n\t\t\t[\n");
		json << "\t\t\t\t\"" << sample.getFileName() << "\",\n";
		json = json.upToLastOccurrenceOf(",", false, false);
		json << "\n\t\t\t],\n\t\t\t\"midiNote\":\"" << String(midiNote++) << "\",\n";
		json << "\t\t\t\"audioOutputChannel\":\"0\",\n";
		json << "\t\t\t\"midiChannel\":\"1\"\n\t\t},\n";
	}

	return json.upToLastOccurrenceOf(",", false, false);
}

static const String createJsonForDirWithSubDirs(const File &dir, int &baseMidiNote)
{
	DBG("String createJsonForInstrument dir: " + dir.getFullPathName());
	String json;
	json << ("\t\t{\n\t\t\t\"name\":\"") << dir.getFileNameWithoutExtension() << "\",\n";
	json << ("\t\t\t\"files\":\n\t\t\t[\n");

	DirectoryIterator instrumentDirIterator(dir, false, "*", File::findFiles);
	while (instrumentDirIterator.next())
	{
		File sample = instrumentDirIterator.getFile();

		json << "\t\t\t\t\"" << sample.getParentDirectory().getFileName() << "/" << sample.getFileName() << "\",\n";
	}

	json = json.upToLastOccurrenceOf(",", false, false);
	json << "\n\t\t\t],\n\t\t\t\"midiNote\":\"" << String(baseMidiNote++) << "\",\n";
	json << "\t\t\t\"audioOutputChannel\":\"0\",\n";
	json << "\t\t\t\"midiChannel\":\"1\"\n\t\t},\n";

	return json;
}
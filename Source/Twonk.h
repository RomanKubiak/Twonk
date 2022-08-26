/*
  ==============================================================================

    Twonk.h
    Created: 17 Jul 2019 2:19:57pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cstdarg>
#define TWONK_DEFAULT_TYPEFACE "Liberation Sans"
#define DEFAULT_PPQN 960.0
#define TITLEBAR_HEIGHT 48
#define BUBBLE_SIZE 140
#define NODE_SIZE   40
#define TOOLBAR_BUTTON_SIZE 64
#define BUBBLE_COLOUR_INTERNAL_MIDI_IN		0xffbb3366
#define BUBBLE_COLOUR_INTERNAL_MIDI_OUT		0xffff1188

#define BUBBLE_COLOUR_INTERNAL_AUDIO_IN		0xff11bbcc
#define BUBBLE_COLOUR_INTERNAL_AUDIO_OUT	0xff1199bb

#define BUBBLE_COLOUR_INTERNAL_PLUGIN_FX		0xffffee22
#define BUBBLE_COLOUR_INTERNAL_SYNTH			0xff64ff22
#define BUBBLE_COLOUR_PLUGIN_SYNTH_WITH_INPUT	0xff64ff22
#define BUBBLE_COLOUR_PLUGIN_FX					0xffffee22
#define BUBBLE_COLOUR_PLUGIN_SYNTH				0xff64ff22

#define MIDI_KEYBOARD_HEIGHT 0
#define GET_TWONK_PROGRAM_DIR() File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk").getChildFile("Programs")
#define GET_TWONK_PLUGINS_DIR() File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk").getChildFile("Plugins")
#define GET_TWONK_SAMPLES_DIR() File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk").getChildFile("Samples")
#define GET_TWONK_SETTINGS_DIR() File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk")

#define _TXT(...) logMessage(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define IMG(n) ImageCache::getFromMemory(BinaryData::n, BinaryData::n##Size)

enum ProgramType
{
	Synth,
	Effect,
	MIDI,
	Generic,
	FuckIfIKnow
};

static void logMessage(const String &file, const String &function, const int line, char *format, ...)
{
    char buffer[512];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer,512,format, args);
    va_end (args);

    Logger::getCurrentLogger()->writeToLog("[" + File(file).getFileName() + ":" + function + ":" + String(line) + "]: " + String(buffer));
}

static const String programTypeDescriptor(const ProgramType type)
{
	switch (type)
	{
	case Synth:
		return "synth";
	case Effect:
		return "fx";
	case MIDI:
		return "midi";
	case Generic:
		return "generic";
	default:
		return "fuckifiknow";
	}
}

static const ProgramType descriptorToProgramType(const String &descriptor)
{
	if (descriptor == "synth")
		return Synth;
	else if (descriptor == "fx")
		return Effect;
	else if (descriptor == "midi")
		return MIDI;
	else if (descriptor == "generic")
		return Generic;
	else
		return FuckIfIKnow;
}

static const Image getIconForType(const ProgramType type)
{
	switch (type)
	{
	case Synth:
		return IMG(icon_synth_png);
		break;
	case Effect:
		return IMG(icon_effect_png);
		break;
	case MIDI:
		return IMG(icon_midi_64_png);
		break;
	case Generic:
		return IMG(icon_project_png);
		break;
	default:
		return IMG(icon_question_jpg);
		break;
	}
}

static const String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
{
	if (numerator == 0 || denominator == 0)
		return "1.1.000";

	auto quarterNotesPerBar = (numerator * 4 / denominator);
	auto beats = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

	auto bar = ((int)quarterNotes) / quarterNotesPerBar + 1;
	auto beat = ((int)beats) + 1;
	auto ticks = ((int)(fmod (beats, 1.0) * 960.0 + 0.5));

	return String::formatted ("%d.%d.%03d", bar, beat, ticks);
}
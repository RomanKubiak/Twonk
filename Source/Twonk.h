/*
  ==============================================================================

    Twonk.h
    Created: 17 Jul 2019 2:19:57pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "BinaryData.h"
#define TWONK_DEFAULT_TYPEFACE "Liberation Sans"
#define DEFAULT_PPQN 960.0
#define TITLEBAR_HEIGHT 48
#define BUBBLE_SIZE 100
#define NODE_SIZE   25
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
#define GET_TWONK_SETTINGS_DIR() File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Twonk")

#define IMG(n) ImageCache::getFromMemory(BinaryData::n, BinaryData::n##Size)

enum ProgramType
{
	Synth,
	Effect,
	MIDI,
	Generic,
	FuckIfIKnow
};

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
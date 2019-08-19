/*
  ==============================================================================

    Twonk.h
    Created: 17 Jul 2019 2:19:57pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#define TWONK_DEFAULT_TYPEFACE "Liberation Sans"
#define DEFAULT_PPQN 960.0
#define TITLEBAR_HEIGHT 48
#define BUBBLE_SIZE 100
#define NODE_SIZE 32
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

#define IMG(n) ImageCache::getFromMemory(BinaryData::n, BinaryData::n##Size)
#ifndef _AudioCore_Internal_h_
#define _AudioCore_Internal_h_


#if defined flagBUILTIN_PORTAUDIO || defined BUILTIN_PORTAUDIO
	#include <plugin/portaudio/portaudio.h>
	#include <plugin/portaudio/pa_types.h>
#else
	#include <portaudio.h>
#endif

#if defined flagBUILTIN_PORTMIDI || defined BUILTIN_PORTMIDI
	#include <plugin/portmidi/portmidi.h>
	#include <plugin/portmidi/pmutil.h>
	#include <plugin/portmidi/porttime.h>
#else
	#include <portmidi.h>
	#include <porttime.h>
#endif


#endif

#ifndef _AudioCore_Internal_h_
#define _AudioCore_Internal_h_


#if defined flagBUILTIN_PORTAUDIO || (defined flagWIN32 && defined flagMSC)
	#include <ports/portaudio/portaudio.h>
	#include <ports/portaudio/pa_types.h>
#else
	#include <portaudio.h>
#endif

#if defined flagBUILTIN_PORTMIDI || (defined flagWIN32 && defined flagMSC) || flagFREEBSD
	#include <ports/portmidi/portmidi.h>
	#include <ports/portmidi/pmutil.h>
	#include <ports/portmidi/porttime.h>
#else
	#include <portmidi.h>
	#include <porttime.h>
#endif

#ifdef flagPOSIX
	#define HAVE_FLUIDSYNTH 1
#endif

#endif

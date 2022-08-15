#ifndef _SoftSynth_SoftSynth_h_
#define _SoftSynth_SoftSynth_h_

#include <Local/Local.h>
#include <MidiFile/MidiFile.h>
#undef Status

#define NAMESPACE_SOFTSYNTH_BEGIN NAMESPACE_TOPSIDE_BEGIN namespace SoftSynth {
#define NAMESPACE_SOFTSYNTH_END   NAMESPACE_TOPSIDE_END }


#if CPU_ARM
	#define SYNTH_NEON_ASM 1
#endif


#include "Common.h"
#include "Fm.h"


#endif

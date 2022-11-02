#ifndef _SoftInstru_Common_h_
#define _SoftInstru_Common_h_


NAMESPACE_SOFTINSTRU_BEGIN




// Supported output modes by the render methods
enum OutputMode
{
	// Two channels with single left/right samples one after another
	STEREO_INTERLEAVED,
	// Two channels with all samples for the left channel first then right
	STEREO_UNWEAVED,
	// A single channel (stereo instruments are mixed into center)
	MONO,
};



// The lower this block size is the more accurate the effects are.
// Increasing the value significantly lowers the CPU usage of the voice rendering.
// If LFO affects the low-pass filter it can be hearable even as low as 8.
#ifndef RENDER_EFFECTSAMPLEBLOCK
#define RENDER_EFFECTSAMPLEBLOCK 64
#endif

// When using RenderShort, to do the conversion a buffer of a fixed size is
// allocated on the stack. On low memory platforms this could be made smaller.
// Increasing this above 512 should not have a significant impact on performance.
// The value should be a multiple of RENDER_EFFECTSAMPLEBLOCK.
#ifndef RENDER_SHORTBUFFERBLOCK
#define RENDER_SHORTBUFFERBLOCK 512
#endif

// Grace release time for quick voice off (avoid clicking noise)
#define FASTRELEASETIME 0.01f

#if !defined(MALLOC) || !defined(FREE) || !defined(REALLOC)
#  include <stdlib.h>
#  define MALLOC  malloc
#  define FREE    free
#  define REALLOC realloc
#endif

#if !defined(MEMCPY) || !defined(MEMSET)
#  include <string.h>
#  define MEMCPY  memcpy
#  define MEMSET  memset
#endif

#if !defined(POW) || !defined(POWF) || !defined(EXPF) || !defined(LOG_) || !defined(TAN) || !defined(LOG10) || !defined(SQRT)
#  include <math.h>
#  if !defined(__cplusplus) && !defined(NAN) && !defined(powf) && !defined(expf) && !defined(sqrtf)
#    define powf (float)pow // deal with old math.h
#    define expf (float)exp // files that come without
#    define sqrtf (float)sqrt // powf, expf and sqrtf
#  endif
#  define POW     pow
#  define POWF    powf
#  define EXPF    expf
#  define LOG_    log
#  define TAN     tan
#  define LOG10   log10
#  define SQRTF   sqrtf
#endif

#ifndef NO_STDIO
#  include <stdio.h>
#endif


#define FourCCEquals(value1, value2) (value1[0] == value2[0] && value1[1] == value2[1] && value1[2] == value2[2] && value1[3] == value2[3])


enum { LOOPMODE_NONE, LOOPMODE_CONTINUOUS, LOOPMODE_SUSTAIN };
enum { SEGMENT_NONE, SEGMENT_DELAY, SEGMENT_ATTACK, SEGMENT_HOLD, SEGMENT_DECAY, SEGMENT_SUSTAIN, SEGMENT_RELEASE, SEGMENT_DONE };


NAMESPACE_SOFTINSTRU_END



#endif

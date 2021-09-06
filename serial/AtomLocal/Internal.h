#ifndef _AtomLocal_Internal_h_
#define _AtomLocal_Internal_h_


// http://dranger.com/ffmpeg/tutorial01.html
#if defined flagPOSIX || defined HAVE_MINGW
	#define HAVE_FFMPEG 1
	
	#if defined flagFREEBSD && defined flagGCC
		// skip v4l2 because of weird VideoDevice::open
	#else
		#define HAVE_V4L2_DEVMGR	0
		#define HAVE_OPENCV			0
		
		#define HAVE_V4L2_CAP		0
		
		#ifdef UPP_VERSION
			#define V4L2_SLOW		0
		#endif
	#endif
#endif


#if HAVE_FFMPEG
extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}
#endif


#if HAVE_V4L2_DEVMGR || HAVE_V4L2_CAP
	#ifdef flagWIN32
		#error V4L2 is not supported in windows
	#else
		#include <ports/libv4l2/libv4l2.h>
	#endif
#endif


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

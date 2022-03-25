#ifndef _AtomLocal_Internal_h_
#define _AtomLocal_Internal_h_


#include <SerialLib/SerialLib.h>
#include <AtomSDL2/AtomSDL2.h>
#include <AudioCore/AudioCore.h>

#ifdef flagDEBUG_ATOM
	#define HAVE_MANUAL_DBG_CLASSES 1
#endif


#if HAVE_FFMPEG
extern "C" {
	#include <libavdevice/avdevice.h>
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



#if HAVE_V4L2_DEVMGR || HAVE_V4L2_CAP
	#ifdef flagWIN32
		#error V4L2 is not supported in windows
	#else
		#include <ports/libv4l2/libv4l2.h>
	#endif
#endif


#endif

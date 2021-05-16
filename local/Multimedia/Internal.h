#ifndef _Multimedia_Internal_h_
#define _Multimedia_Internal_h_

// http://dranger.com/ffmpeg/tutorial01.html
#ifdef flagPOSIX
	#define HAVE_FFMPEG 1
	
	#if defined flagFREEBSD && defined flagGCC
		// skip v4l2 because of weird VideoDevice::open
	#else
		#define HAVE_V4L2_DEVMGR 1
		#define HAVE_OPENCV 1
		
		#define HAVE_V4L2_CAP 0
		
		#ifdef flagUPP
			#define V4L2_SLOW 0
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

#endif

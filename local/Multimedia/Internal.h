#ifndef _Multimedia_Internal_h_
#define _Multimedia_Internal_h_

// http://dranger.com/ffmpeg/tutorial01.html
#ifdef flagPOSIX
	#define HAVE_FFMPEG 1
	
	#if defined flagFREEBSD && defined flagGCC
		// skip v4l2 because of weird VideoDevice::open
	#else
		#define flagV4L2 1
		#define flagV4L2_OPENCV 1
		
		#ifndef flagALTCORE
			//#define V4L2_SLOW 1
		#endif
	#endif
#endif


#if HAVE_FFMPEG
#define HAVE_MEDIAFILE 1
extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}
#endif

#ifdef flagV4L2_OPENCV
	#define HAVE_CAPTUREDEV 1
#endif

#ifdef flagV4L2
	#ifdef flagWIN32
		#error V4L2 is not supported in windows
	#else
		#include <plugin/libv4l2/libv4l2.h>
	#endif
#endif

#endif

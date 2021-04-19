#ifndef _Multimedia_Multimedia_h_
#define _Multimedia_Multimedia_h_

// http://dranger.com/ffmpeg/tutorial01.html

#define FFMPEG 1

#ifdef flagLINUX
	#define flagV4L2 1
	#define flagV4L2_OPENCV 1
	
	#ifndef flagALTCORE
		//#define V4L2_SLOW 1
	#endif
#endif


#if FFMPEG
extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}
#endif

#if flagV4L2
	#ifdef flagWIN32
		#error V4L2 is not supported in windows
	#else
		#include <plugin/libv4l2/libv4l2.h>
	#endif
#endif
 
#if !defined flagALTCORE && defined flagGUI
	#include <plugin/jpg/jpg.h>
#endif

#include <Oulu/Oulu.h>


#include "Audio.h"
#include "Video.h"
#include "Media.h"
#include "Capture.h"
#include "FileIn.h"
#include "DeviceManager.h"


NAMESPACE_OULU_BEGIN


void TestFfmpeg();


NAMESPACE_OULU_END

#endif

#ifndef _Multimedia_Multimedia_h_
#define _Multimedia_Multimedia_h_

 
#if !defined flagALTCORE && defined flagGUI
	#include <plugin/jpg/jpg.h>
#endif

#include <Oulu/Oulu.h>

#include "Internal.h"
#include "Audio.h"
#include "Video.h"
#include "Media.h"

#include "Capture_OpenCV.h"
#include "FileIn_Ffmpeg.h"
#include "DeviceManager_V4L2.h"
#include "DeviceManager_DShow.h"



#endif

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
#include "Capture.h"
#include "FileIn.h"
#include "DeviceManager.h"


NAMESPACE_OULU_BEGIN


void TestFfmpeg();


NAMESPACE_OULU_END

#endif

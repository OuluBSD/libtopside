#ifndef _AtomLocal_AtomLocal_h_
#define _AtomLocal_AtomLocal_h_

#include <SerialLib/SerialLib.h>
#include <AtomSDL2/AtomSDL2.h>
#include <AudioCore/AudioCore.h>

#ifdef flagDEBUG_ATOM
	#define HAVE_MANUAL_DBG_CLASSES 1
#endif

#include "Internal.h"
#include "Debug.h"
#include "Util.h"
#include "Audio.h"
#include "Video.h"
#include "Media.h"
#include "Volume.h"
#include "FfmpegFileIn.h"
#include "Ffmpeg.h"
#include "OpenCV.h"
#include "Capture_OpenCV.h"
#include "Capture_V4L2.h"
#include "Portaudio.h"
#include "Fluidsynth.h"
#include "Midi.h"



#if HAVE_MANUAL_DBG_CLASSES

#else
	#include "Generated.h"
#endif


NAMESPACE_SERIAL_BEGIN





NAMESPACE_SERIAL_END


#endif

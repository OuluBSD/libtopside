#include "IMedia.h"


#if HAVE_DIRECTSHOW

#if 0
//#ifdef flagWIN32
	// https://github.com/microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/multimedia/directshow/capture/playcap/playcap.cpp
	// https://github.com/microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/multimedia/directshow/capture/playcap/playcap.h
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0500
	#endif
	#include <windows.h>
	#include <dshow.h>
	#include <stdio.h>
	#include <strsafe.h>
#endif

#endif

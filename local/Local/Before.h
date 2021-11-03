#ifndef _Local_Before_h_
#define _Local_Before_h_

#include <random>
#include <memory>
#include <cstring>
#include <optional>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

#include <Core/Core.h>
#include <Draw/Draw.h>

#if HAVE_SHORT_NAMESPACE
	#define NAMESPACE_TOPSIDE_NAME ts
	#define NAMESPACE_TOPSIDE_BEGIN namespace NAMESPACE_TOPSIDE_NAME {
	#define NAMESPACE_TOPSIDE_END }
	#define TS ts
#else
	#define NAMESPACE_TOPSIDE_NAME Topside
	#define NAMESPACE_TOPSIDE_BEGIN namespace NAMESPACE_TOPSIDE_NAME {
	#define NAMESPACE_TOPSIDE_END }
	#define TS Topside
	namespace UPP {}
	namespace TS {using namespace UPP;}
#endif



#ifdef UPP_VERSION
	#define flagSTDRTTI
	#define flagSTDEXC
	#include <algorithm>
	#include <plugin/bz2/bz2.h>
	#define IML_HEADER <Draw/iml_header.h>
	#define IML_SOURCE <Draw/iml_source.h>
#endif
#undef Complex


#ifdef flagDEBUG_RT
	#define DEBUG_RT_PIPE 1
	#define RTLOG(x) {StringStream ____; ____ << "RTDBG: " << x << "\n"; UPP::VppLog() << ____.GetResult(); UPP::VppLog().Flush();}
#else
	#define DEBUG_RT_PIPE 0
	#define RTLOG(x)
#endif


#define MAX_VDTUPLE_SIZE		8



// http://dranger.com/ffmpeg/tutorial01.html
#if defined flagPOSIX || defined HAVE_MINGW
	#define HAVE_FFMPEG 1
	
	#if defined flagFREEBSD && defined flagGCC
		// skip v4l2 because of weird VideoDevice::open
	#else
		#define HAVE_V4L2_DEVMGR	1
		#define HAVE_OPENCV			1
		
		//#define HAVE_V4L2_CAP		1
		
		#ifdef UPP_VERSION
			//#define V4L2_SLOW		1
		#endif
	#endif
#endif



NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;
NAMESPACE_TOPSIDE_END



#endif

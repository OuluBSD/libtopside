#ifndef _AccelCore_AccelCore_h_
#define _AccelCore_AccelCore_h_

#include <stdlib.h> // free, malloc, int
#include <string.h> // memcpy, strlen
#include <limits.h> // INT_MAX, UINT_MAX
#include <stdarg.h> // va_list, va_copy, va_start, va_end
#include <stdio.h>  // vsnprintf

#include <Local/Local.h>
#include <Multimedia/Multimedia.h>
#include <EcsCore/EcsCore.h>
#include <EcsLib/EcsLib.h>
#include <Structural/Structural.h>

#if defined(flagGUI) && !defined(__gl_h_)
	#error OpenGL is not included
#endif

#define NAMESPACE_FUSION_BEGIN namespace Topside { namespace FusionCore {
#define NAMESPACE_FUSION_END   }}
#define NAMESPACE_FUSION       FusionCore
#define NS_SHADER              NAMESPACE_FUSION


#include "AccelSystem.h"


#endif

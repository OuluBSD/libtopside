#ifndef _GRAPHICS_GRAPHICS_h_
#define _GRAPHICS_GRAPHICS_h_


#include <Geometry/Geometry.h>
#include <SoftRend/SoftRend.h>

typedef float			Gxf;
typedef unsigned char	Gxb;
typedef unsigned char	Gxby;
typedef int				Gxi;
typedef unsigned int	Gxu;
typedef unsigned int	Gxbf;


#define NAMESPACE_GRAPHICS_BEGIN namespace  TS { namespace  GL {
#define NAMESPACE_GRAPHICS_END }}

#define TNG typename Gfx::



#include "Enums.h"

#if defined flagSWRENDER
	#error todo
#elif defined(flagSCREEN)
	#include "OpenGL.h"
#endif




#if defined flagSWDUMMY
	#include "GlobalApi.h"
#endif


#include "Types.h"
#include "State.h"
#include "Camera.h"

#include "GfxClasses.h"

#include "TState.h"
#include "TFramebuffer.h"
#include "TRuntime.h"
#include "TContext.h"
#include "TUtil.h"
#include "TBuffer.h"

#include "Cpu.h"
/*#include "CpuShader.h"
#include "CpuRenderer.h"
#include "CpuSDL.h"*/

#if defined(flagSCREEN)
#include "Ogl.h"
/*#include "OglShader.h"
#include "OglRenderer.h"
#include "OglCompiler.h"
#include "OglBuffer.h"*/
#endif

#include "ProgDraw.h"




#endif

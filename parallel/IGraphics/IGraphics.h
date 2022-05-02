#ifndef _IGraphics_IGraphics_h_
#define _IGraphics_IGraphics_h_


#if 0 && defined flagWIN32
	#define GLEW_STATIC 1
	#include <ports/glew/glew.h>
#else
	#include <GL/glew.h>
#endif


#if defined flagSDL2
	#if defined flagWIN32 && defined flagMSC
		#include <SDL.h>
		#include <SDL_ttf.h>
		#include <SDL_image.h>
		#include <SDL_syswm.h>
		#ifdef flagSCREEN
			#include <SDL_opengl.h>
		#endif
	#else
		#include <SDL2/SDL.h>
		#include <SDL2/SDL_ttf.h>
		#include <SDL2/SDL_image.h>
		#ifdef flagSCREEN
			#include <SDL2/SDL_opengl.h>
		#endif
	#endif
#endif

#undef main

#ifdef flagPOSIX
	#define Time XTime
	#define Font XFont
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#ifdef flagOGL
		#include <GL/glx.h>
	#endif
	#undef Time
	#undef Font
#endif



#include <Geometry/Geometry.h>
#include <ParallelLib/ParallelLib.h>



typedef float			Gxf;
typedef unsigned char	Gxb;
typedef unsigned char	Gxby;
typedef int				Gxi;
typedef unsigned int	Gxu;
typedef unsigned int	Gxbf;


#define NAMESPACE_GRAPHICS_BEGIN namespace  TS { namespace  Parallel { namespace  GL {
#define NAMESPACE_GRAPHICS_END }}}

#define TNG typename Gfx::




#if defined flagSWRENDER
	#error todo
#elif defined(flagSCREEN)
	#include "OpenGL.h"
#endif




#if defined flagSWDUMMY
	#include "GlobalApi.h"
#endif



//SoftRend
#include "Common.h"
#include "Backend.h"
#include "Data.h"
#include "Framebuffer.h"
#include "ShaderSoft.h"
#include "Program.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "Compiler.h"
#include "Library.h"



#include "Types.h"
#include "State.h"

#include "GfxClasses.h"

#include "TState.h"
#include "TFramebuffer.h"
#include "TRuntime.h"
#include "TContext.h"
#include "TUtil.h"
#include "TBuffer.h"
#include "TBufferField.h"

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
#include "GfxAccelAtom.h"

#include "Base.h"
#include "FboBase.h"

#include "ObjViewProg.h"
#include "UtilProg.h"




#endif

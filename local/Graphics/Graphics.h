#ifndef _GRAPHICS_GRAPHICS_h_
#define _GRAPHICS_GRAPHICS_h_


#include <Geometry/Geometry.h>

typedef float			Gxf;
typedef unsigned char	Gxb;
typedef unsigned char	Gxby;
typedef int				Gxi;
typedef unsigned int	Gxu;
typedef unsigned int	Gxbf;


#define NAMESPACE_GRAPHICS_BEGIN namespace  TS { namespace  GL {
#define NAMESPACE_GRAPHICS_END }}


#include "Enums.h"

#if defined flagSWRENDER
	#error todo
#elif defined(flagSCREEN)
	#include "OpenGL.h"
#endif




#if defined flagSWDUMMY
	#include "GlobalApi.h"
#endif


#include "Camera.h"
#include "Shader.h"
#include "Framebuffer.h"
#include "Renderer.h"

#include "CpuShader.h"
#include "CpuRenderer.h"

#if defined(flagSCREEN)
#include "OpenGLShader.h"
#include "OpenGLRenderer.h"
#include "OpenGLBuffer.h"
#endif



#endif

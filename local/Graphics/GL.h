#ifndef _GL_GL_h_
#define _GL_GL_h_


#include <Geometry/Geometry.h>

typedef float			Gxf;
typedef unsigned char	Gxb;
typedef unsigned char	Gxby;
typedef int				Gxi;
typedef unsigned int	Gxu;
typedef unsigned int	Gxbf;


#define NAMESPACE_GL_BEGIN namespace  Oulu { namespace  GL {
#define NAMESPACE_GL_END }}


#include "Enums.h"

#if defined flagSWRENDER
	#error todo
#elif defined(flagGUI)
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

#if defined(flagGUI)
#include "OpenGLShader.h"
#include "OpenGLRenderer.h"
#endif

#endif

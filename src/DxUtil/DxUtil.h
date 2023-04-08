#ifndef _DxUtil_DxUtil_h_
#define _DxUtil_DxUtil_h_

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "driver.h"
#include "log.h"
#include "glheader.h"

#include "common_x86_asm.h"		// For glGetString().
#include "version.h"			// For MESA_VERSION_STRING


#include "glheader.h"
#include "arrayelt.h"
#include "context.h"
#include "dll_main.h"
#include "driver.h"
#include "imports.h"
#include "macros.h"
#include "mtypes.h"
#include "context.h"
#include "driver.h"
#include "mmsystem.h"
#include "globals.h"

#define STRICT
#include <windows.h>

#include "log.h"
#include "driver.h"

#include "pf.h"
#include "driver.h"

#include "wgl.h"
#include "driver.h"

#include "glu.h"	// MUST USE MICROSOFT'S GLU32!

// Need to export wgl* functions if using GLD3,
// otherwise export GLD2 GLD_* functions.
#define _GLD_WGL_EXPORT(a) wgl##a

// Calls into Mesa 4.x are different
#include "dlist.h"
#include "drawpix.h"
#include "get.h"
#include "matrix.h"

#include <malloc.h> // For _msize()

#include "context.h"
#include "log.h"
#include "gldirect5.h"

#include "glheader.h"
#include "context.h"
#include "colormac.h"
#include "depth.h"
#include "extensions.h"
#include "macros.h"
#include "matrix.h"
#include "mtypes.h"
#include "texformat.h"
#include "texstore.h"
#include "vtxfmt.h"
#include "dlist.h"
#include "m_eval.h" // Evaluator functions

#include "context.h"

#include "log.h"
#include "gldirect5.h"

#include "glheader.h"
#include "context.h"
#include "colormac.h"
#include "depth.h"
#include "extensions.h"
#include "macros.h"
#include "matrix.h"
#include "mtypes.h"
#include "texformat.h"
#include "texstore.h"
#include "teximage.h"
#include "api_arrayelt.h"

#include <windows.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#include "glheader.h"
#include "context.h"
#include "colormac.h"
#include "depth.h"
#include "extensions.h"
#include "macros.h"
#include "matrix.h"
#include "mtypes.h"
#include "texformat.h"
#include "texstore.h"
#include "context.h"
#include "extensions.h"

#pragma warning( disable:4996) // secure versions of strcat(), etc

#include <malloc.h> // For _msize()

#include "context.h"
#include "log.h"
#include "gldirect5.h"

#include "glheader.h"
#include "context.h"
#include "colormac.h"
#include "depth.h"
#include "extensions.h"
#include "macros.h"
#include "matrix.h"
#include "mtypes.h"
#include "texformat.h"
#include "texstore.h"
#include "vtxfmt.h"
#include "dlist.h"

#include "context.h"
#include "log.h"
#include "gldirect5.h"

#include <d3dx9tex.h>

#include "texformat.h"
#include "colormac.h"
#include "texstore.h"
#include "image.h"
// #include "mem.h"

#include "context.h"
#include "log.h"
#include "gldirect5.h"

#include "glheader.h"
#include "context.h"
#include "colormac.h"
#include "depth.h"
#include "extensions.h"
#include "macros.h"
#include "matrix.h"
#include "mtypes.h"
#include "texformat.h"
#include "texstore.h"
#include "vtxfmt.h"
#include "dlist.h"
#include "state.h" // mesa_update_state()
#include "api_noop.h"
#include "api_arrayelt.h"
#include "m_eval.h" // Evaluator functions

#include "context.h"
#include "driver.h"
#include "dxerr9.h"
#include "gldirect5.h"


#endif

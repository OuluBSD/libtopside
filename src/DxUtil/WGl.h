#ifndef __GLD_WGL_H
#define __GLD_WGL_H


// Description:  OpenGL window  functions (wgl*).


// Disable compiler complaints about DLL linkage
#pragma warning (disable:4273)

// Macros to control compilation
#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <GL\gl.h>

#include "context.h"
#include "globals.h"
#include "macros.h"
#include "log.h"
#include "pf.h"

/*---------------------- Macros and type definitions ----------------------*/

typedef struct {
	PROC proc;
	char *name;
}  GLD_extension;

/*------------------------- Function Prototypes ---------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

BOOL	gldWglResizeBuffers(GLcontext *ctx, BOOL bDefaultDriver);

#ifdef  __cplusplus
}
#endif

#endif
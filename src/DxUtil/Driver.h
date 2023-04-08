#ifndef _GLD_DRIVER_H
#define _GLD_DRIVER_H


// Description:  Driver functions and interfaces


#include "context.h"

//---------------------------------------------------------------------------

// Same as DX8 D3DDISPLAYMODE
typedef struct {
	DWORD	Width;
	DWORD	Height;
	DWORD	Refresh;
	DWORD	BPP;
} GLD_displayMode;

//---------------------------------------------------------------------------

typedef struct {
	// Returns a string for a given HRESULT error code.
	BOOL	(*GetDXErrorString)(HRESULT hr, char *buf, int nBufSize);

	// Driver functions for managing drawables.
	// Functions must respect persistant buffers / persistant interface.
	// NOTE: Persistant interface is: DirectDraw, pre-DX8; Direct3D, DX8 and above.
	BOOL	(*CreateDrawable)(GLD_ctx *ctx, BOOL bPersistantInterface, BOOL bPersistantBuffers);
	BOOL	(*ResizeDrawable)(GLD_ctx *ctx, BOOL bDefaultDriver, BOOL bPersistantInterface, BOOL bPersistantBuffers);
	BOOL	(*DestroyDrawable)(GLD_ctx *ctx);

	// Create/Destroy private globals belonging to driver
	BOOL	(*CreatePrivateGlobals)(void);
	BOOL	(*DestroyPrivateGlobals)(void);

	// Build pixelformat list
	BOOL	(*BuildPixelformatList)(void);

	// Initialise Mesa's driver pointers
	BOOL	(*InitialiseMesa)(GLD_ctx *ctx);

	// Swap buffers
	BOOL	(*SwapBuffers)(GLD_ctx *ctx, HDC hDC, HWND hWnd);

	// wglGetProcAddress()
	PROC	(*wglGetProcAddress)(LPCSTR a);

	BOOL	(*GetDisplayMode)(GLD_ctx *ctx, GLD_displayMode *glddm);
} GLD_driver;

//---------------------------------------------------------------------------

#ifdef  __cplusplus
extern "C" {
#endif

extern GLD_driver _gldDriver;

BOOL gldInitDriverPointers(DWORD dwDriver);
const GLubyte* _gldGetStringGeneric(GLcontext *ctx, GLenum name);
BOOL gldValidate();

#ifdef  __cplusplus
}
#endif

//---------------------------------------------------------------------------

#endif // _GLD_DRIVER_H

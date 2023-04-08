#ifndef __GLD_PF_H
#define __GLD_PF_H


// Description:  Pixel Formats.


#ifndef STRICT
#define STRICT
#endif // STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

/*---------------------- Macros and type definitions ----------------------*/

typedef struct {
	PIXELFORMATDESCRIPTOR	pfd;		// Win32 Pixel Format Descriptor
	// Driver-specific data.
	// Example: The DX8 driver uses this to hold an index into a
	// list of depth-stencil descriptions.
	DWORD					dwDriverData;
} GLD_pixelFormat;

#include "globals.h"

/*------------------------- Function Prototypes ---------------------------*/

#ifdef  __cplusplus
extern "C" {
#endif

BOOL	IsValidPFD(int iPFD);
BOOL	gldBuildPixelFormatList();
void	gldReleasePixelFormatList();

#ifdef  __cplusplus
}
#endif

#endif
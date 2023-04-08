#ifndef __DLLMAIN_H
#define __DLLMAIN_H


// Description:  Win32 DllMain functions.


// Macros to control compilation
#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "globals.h"
#include "log.h"
#include "wgl.h"

#ifdef  __cplusplus
extern "C" {
#endif

extern BOOL bInitialized;

BOOL gldInitDriver(void);
void gldExitDriver(void);

#ifdef  __cplusplus
}
#endif

#endif
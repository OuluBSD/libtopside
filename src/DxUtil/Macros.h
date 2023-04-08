#ifndef __GLD_MACROS_H
#define __GLD_MACROS_H


// Description:  Useful generic macros.


#include <ddraw.h>

// Define the relevant RELEASE macro depending on C or C++
#if !defined(__cplusplus) || defined(CINTERFACE)
	// Standard C version
	#define RELEASE(x) if (x!=NULL) { x->lpVtbl->Release(x); x=NULL; }
#else
	// C++ version
	#define RELEASE(x) if (x!=NULL) { x->Release(); x=NULL; }
#endif

// We don't want a message *every* time we call an unsupported function
#define UNSUPPORTED(x)												\
	{																\
		static BOOL bFirstTime = TRUE;								\
		if (bFirstTime) {											\
			bFirstTime = FALSE;										\
			gldLogError(GLDLOG_WARN, (x), DDERR_CURRENTLYNOTAVAIL);	\
		}															\
	}

#define GLD_CHECK_CONTEXT		\
	if (ctx == NULL) return;

// Don't render if bCanRender is not TRUE.
#define GLD_CHECK_RENDER		\
	if (!gld->bCanRender) return;

#if 0
#define TRY(a,b) (a)
#define TRY_ERR(a,b) (a)
#else
// hResult should be defined in the function
// Return codes should be checked via SUCCEDDED and FAILED macros
#define TRY(a,b)									\
	{												\
		if (FAILED(hResult=(a)))					\
			gldLogError(GLDLOG_ERROR, (b), hResult);	\
	}

// hResult is a global
// The label exit_with_error should be defined within the calling scope
#define TRY_ERR(a,b)								\
	{												\
		if (FAILED(hResult=(a))) {					\
			gldLogError(GLDLOG_ERROR, (b), hResult);	\
			goto exit_with_error;					\
		}											\
	}
#endif // #if 1

#endif

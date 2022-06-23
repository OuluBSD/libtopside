#ifndef _LocalHMD_ANDROID_H
#define _LocalHMD_ANDROID_H


NAMESPACE_HMD_BEGIN


#ifdef flagANDROID

typedef enum {
	DROID_DUROVIS_OPEN_DIVE   = 1,
	DROID_DUROVIS_DIVE_5      = 2,
	DROID_DUROVIS_DIVE_7      = 3,
	DROID_CARL_ZEISS_VRONE    = 4,
	DROID_GOOGLE_CARDBOARD    = 5,
	
	DROID_NONE                = 0,
} AndroidHmdProfile;


struct android_app;

#endif


NAMESPACE_HMD_END


#endif

// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IWebcam_Vendors_h_
#define _IWebcam_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

#define CAM_CLS_LIST(x) \
	CAM_CLS(Webcam, x) \



#define CAM_VNDR_LIST \



#define CAM_CLS(x, v) struct v##x;
#define CAM_VNDR(x) CAM_CLS_LIST(x)
CAM_VNDR_LIST
#undef CAM_VNDR
#undef CAM_CLS



VENDORSSZZ


NAMESPACE_TOPSIDE_END


#endif


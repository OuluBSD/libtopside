// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

#ifndef _IWebcam_Vendors_h_
#define _IWebcam_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define CAM_CLS_LIST(x) \
	CAM_CLS(Webcam, x) \



#define CAM_VNDR_LIST \



#define CAM_CLS(x, v) struct v##x;
#define CAM_VNDR(x) CAM_CLS_LIST(x)
CAM_VNDR_LIST
#undef CAM_VNDR
#undef CAM_CLS





NAMESPACE_PARALLEL_END


#endif


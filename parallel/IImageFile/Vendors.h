// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 26.3.26 14:33:33

#ifndef _IImageFile_Vendors_h_
#define _IImageFile_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define IMG_CLS_LIST(x) \
	IMG_CLS(Image, x) \



#define IMG_VNDR_LIST \



#define IMG_CLS(x, v) struct v##x;
#define IMG_VNDR(x) IMG_CLS_LIST(x)
IMG_VNDR_LIST
#undef IMG_VNDR
#undef IMG_CLS





NAMESPACE_TOPSIDE_END


#endif


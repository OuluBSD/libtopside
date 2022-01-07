// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IImageFile_Vendors_h_
#define _IImageFile_Vendors_h

NAMESPACE_TOPSIDE_BEGIN

#define IMG_CLS_LIST(x) \
	IMG_CLS(Image, x) \



#define IMG_VNDR_LIST \



#define IMG_CLS(x, v) struct v##x;
#define IMG_VNDR(x) IMG_CLS_LIST(x)
IMG_VNDR_LIST
#undef IMG_VNDR
#undef IMG_CLS



VENDORSSZZ


NAMESPACE_TOPSIDE_END


#endif


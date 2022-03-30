// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

#ifndef _IImageFile_Vendors_h_
#define _IImageFile_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define IMG_CLS_LIST(x) \
	IMG_CLS(Image, x) \



#define IMG_VNDR_LIST \



#define IMG_CLS(x, v) struct v##x;
#define IMG_VNDR(x) IMG_CLS_LIST(x)
IMG_VNDR_LIST
#undef IMG_VNDR
#undef IMG_CLS





NAMESPACE_PARALLEL_END


#endif


// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 26.3.26 14:33:33

#ifndef _IAvFile_Vendors_h_
#define _IAvFile_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define AV_CLS_LIST(x) \
	AV_CLS(AVFile, x) \



#define AV_VNDR_LIST \



#define AV_CLS(x, v) struct v##x;
#define AV_VNDR(x) AV_CLS_LIST(x)
AV_VNDR_LIST
#undef AV_VNDR
#undef AV_CLS





NAMESPACE_TOPSIDE_END


#endif


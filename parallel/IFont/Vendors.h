// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

#ifndef _IFont_Vendors_h_
#define _IFont_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define FNT_CLS_LIST(x) \
	FNT_CLS(Font, x) \



#define FNT_VNDR_LIST \



#define FNT_CLS(x, v) struct v##x;
#define FNT_VNDR(x) FNT_CLS_LIST(x)
FNT_VNDR_LIST
#undef FNT_VNDR
#undef FNT_CLS





NAMESPACE_TOPSIDE_END


#endif


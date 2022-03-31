// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IAvFile_Vendors_h_
#define _IAvFile_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define AV_CLS_LIST(x) \
	AV_CLS(AVFile, x) \



#define AV_VNDR_LIST \



#define AV_CLS(x, v) struct v##x;
#define AV_VNDR(x) AV_CLS_LIST(x)
AV_VNDR_LIST
#undef AV_VNDR
#undef AV_CLS





NAMESPACE_PARALLEL_END


#endif


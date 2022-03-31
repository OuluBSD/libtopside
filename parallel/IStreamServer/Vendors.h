// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IStreamServer_Vendors_h_
#define _IStreamServer_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define SVR_CLS_LIST(x) \
	SVR_CLS(StreamServer, x) \



#define SVR_VNDR_LIST \



#define SVR_CLS(x, v) struct v##x;
#define SVR_VNDR(x) SVR_CLS_LIST(x)
SVR_VNDR_LIST
#undef SVR_VNDR
#undef SVR_CLS





NAMESPACE_PARALLEL_END


#endif


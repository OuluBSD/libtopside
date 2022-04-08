// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _IStaticServer_Vendors_h_
#define _IStaticServer_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define SVT_CLS_LIST(x) \
	SVT_CLS(ServerInstance, x) \



#define SVT_VNDR_LIST \



#define SVT_CLS(x, v) struct v##x;
#define SVT_VNDR(x) SVT_CLS_LIST(x)
SVT_VNDR_LIST
#undef SVT_VNDR
#undef SVT_CLS





NAMESPACE_PARALLEL_END


#endif


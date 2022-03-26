// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 26.3.26 14:33:33

#ifndef _IOptimizer_Vendors_h_
#define _IOptimizer_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define OPT_CLS_LIST(x) \
	OPT_CLS(Solver, x) \



#define OPT_VNDR_LIST \



#define OPT_CLS(x, v) struct v##x;
#define OPT_VNDR(x) OPT_CLS_LIST(x)
OPT_VNDR_LIST
#undef OPT_VNDR
#undef OPT_CLS





NAMESPACE_TOPSIDE_END


#endif


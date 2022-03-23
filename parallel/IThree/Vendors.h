// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

#ifndef _IThree_Vendors_h_
#define _IThree_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define THR_CLS_LIST(x) \
	THR_CLS(Model, x) \



#define THR_VNDR_LIST \



#define THR_CLS(x, v) struct v##x;
#define THR_VNDR(x) THR_CLS_LIST(x)
THR_VNDR_LIST
#undef THR_VNDR
#undef THR_CLS





NAMESPACE_TOPSIDE_END


#endif


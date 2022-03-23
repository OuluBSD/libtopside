// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

#ifndef _INeural_Vendors_h_
#define _INeural_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define NRL_CLS_LIST(x) \
	NRL_CLS(Network, x) \



#define NRL_VNDR_LIST \



#define NRL_CLS(x, v) struct v##x;
#define NRL_VNDR(x) NRL_CLS_LIST(x)
NRL_VNDR_LIST
#undef NRL_VNDR
#undef NRL_CLS





NAMESPACE_TOPSIDE_END


#endif


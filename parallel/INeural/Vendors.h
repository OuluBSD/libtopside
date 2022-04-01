// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.1 19:22:00

#ifndef _INeural_Vendors_h_
#define _INeural_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define NRL_CLS_LIST(x) \
	NRL_CLS(Network, x) \



#define NRL_VNDR_LIST \



#define NRL_CLS(x, v) struct v##x;
#define NRL_VNDR(x) NRL_CLS_LIST(x)
NRL_VNDR_LIST
#undef NRL_VNDR
#undef NRL_CLS





NAMESPACE_PARALLEL_END


#endif


// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IAircraftSimulator_Vendors_h_
#define _IAircraftSimulator_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define ASIM_CLS_LIST(x) \
	ASIM_CLS(System, x) \



#define ASIM_VNDR_LIST \



#define ASIM_CLS(x, v) struct v##x;
#define ASIM_VNDR(x) ASIM_CLS_LIST(x)
ASIM_VNDR_LIST
#undef ASIM_VNDR
#undef ASIM_CLS





NAMESPACE_PARALLEL_END


#endif


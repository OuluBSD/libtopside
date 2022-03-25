// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

#ifndef _IElectricSimulator_Vendors_h_
#define _IElectricSimulator_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define ESIM_CLS_LIST(x) \
	ESIM_CLS(System, x) \



#define ESIM_VNDR_LIST \



#define ESIM_CLS(x, v) struct v##x;
#define ESIM_VNDR(x) ESIM_CLS_LIST(x)
ESIM_VNDR_LIST
#undef ESIM_VNDR
#undef ESIM_CLS





NAMESPACE_TOPSIDE_END


#endif


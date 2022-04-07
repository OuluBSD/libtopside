// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 11:11:00

#ifndef _ICfr_Vendors_h_
#define _ICfr_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define CFR_CLS_LIST(x) \
	CFR_CLS(System, x) \



#define CFR_VNDR_LIST \



#define CFR_CLS(x, v) struct v##x;
#define CFR_VNDR(x) CFR_CLS_LIST(x)
CFR_VNDR_LIST
#undef CFR_VNDR
#undef CFR_CLS





NAMESPACE_PARALLEL_END


#endif


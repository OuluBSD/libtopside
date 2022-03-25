// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

#ifndef _ICfr_Vendors_h_
#define _ICfr_Vendors_h_

NAMESPACE_TOPSIDE_BEGIN

#define CFR_CLS_LIST(x) \
	CFR_CLS(System, x) \



#define CFR_VNDR_LIST \



#define CFR_CLS(x, v) struct v##x;
#define CFR_VNDR(x) CFR_CLS_LIST(x)
CFR_VNDR_LIST
#undef CFR_VNDR
#undef CFR_CLS





NAMESPACE_TOPSIDE_END


#endif


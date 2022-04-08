// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

#ifndef _IMath_Vendors_h_
#define _IMath_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define MATH_CLS_LIST(x) \
	MATH_CLS(System, x) \



#define MATH_VNDR_LIST \



#define MATH_CLS(x, v) struct v##x;
#define MATH_VNDR(x) MATH_CLS_LIST(x)
MATH_VNDR_LIST
#undef MATH_VNDR
#undef MATH_CLS





NAMESPACE_PARALLEL_END


#endif


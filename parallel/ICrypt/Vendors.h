// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _ICrypt_Vendors_h_
#define _ICrypt_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define CRY_CLS_LIST(x) \
	CRY_CLS(Crypt, x) \



#define CRY_VNDR_LIST \



#define CRY_CLS(x, v) struct v##x;
#define CRY_VNDR(x) CRY_CLS_LIST(x)
CRY_VNDR_LIST
#undef CRY_VNDR
#undef CRY_CLS





NAMESPACE_PARALLEL_END


#endif


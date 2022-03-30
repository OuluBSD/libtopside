// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.30 15:00:33

#ifndef _IOperatingSystem_Vendors_h_
#define _IOperatingSystem_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define OS_CLS_LIST(x) \
	OS_CLS(MessageBus, x) \
	OS_CLS(ProcessManager, x) \
	OS_CLS(DesktopManager, x) \



#define OS_VNDR_LIST \



#define OS_CLS(x, v) struct v##x;
#define OS_VNDR(x) OS_CLS_LIST(x)
OS_VNDR_LIST
#undef OS_VNDR
#undef OS_CLS





NAMESPACE_PARALLEL_END


#endif


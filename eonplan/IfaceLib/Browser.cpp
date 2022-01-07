#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(WebBrowser, Web, W) {
	IfaceLib::Add(this);
	
	COLOR(14, 37, 142)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(WebBrowser) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(WebBrowser)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateWebBrowser, bool, NativeWebBrowser&)
		FUNCTION1V(ClearWebBrowser, NativeWebBrowser&)
		
	}
	
}


NAMESPACE_PLAN_END

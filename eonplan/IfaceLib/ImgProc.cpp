#include "IfaceLib.h"
/*
- https://cimg.eu/screenshots.html
- https://libgd.github.io/pages/about.html

*/

NAMESPACE_PLAN_BEGIN



PKG(ImgProc, Imp, I) {
	IfaceLib::Add(this);
	
	COLOR(214, 57, 42)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Image) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Image)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateImage, bool, NativeImage&)
		FUNCTION1V(ClearImage, NativeImage&)
		
	}
	
}


NAMESPACE_PLAN_END

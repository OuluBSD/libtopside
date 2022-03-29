#include "IfaceLib.h"
/*
- https://cimg.eu/screenshots.html
- https://libgd.github.io/pages/about.html

*/

NAMESPACE_PLAN_BEGIN



PKG(ImgProc, Imp, I) {
	IfaceLib::Add(this);
	
	COLOR(214, 57, 42)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(Image)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		
	}
	
	NAMESPACE {
		CLASS(Image) {
			NATIVE_INHERIT(Image, dev)
			
			METHOD1R(CreateImage, bool, NativeImage& this)
			METHOD1V(ClearImage, NativeImage& this)
		}
	}
	
}


NAMESPACE_PLAN_END

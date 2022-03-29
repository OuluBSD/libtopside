#include "IfaceLib.h"

/*
 - https://github.com/movableink/cximage
*/

NAMESPACE_PLAN_BEGIN



PKG(ImageFile, Img, i) {
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
			NATIVE_INHERIT(Image, img)
			
			METHOD1R(CreateImage, bool, NativeImage& this)
			METHOD1V(ClearImage, NativeImage& this)
		}
	}
	
}


NAMESPACE_PLAN_END

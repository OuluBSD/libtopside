#include "IGraphics.h"

#ifdef flagMAIN


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
void Test1() {
	
	
}




NAMESPACE_PARALLEL_END


CONSOLE_APP_MAIN {
	using namespace UPP;
	
	LOG("Graphics tests");
	
	Test1<SdlOglGfx>();
	
}

#endif

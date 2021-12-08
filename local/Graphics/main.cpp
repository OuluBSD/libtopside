#include "Graphics.h"

#ifdef flagMAIN


NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
void Test1() {
	
	
}




NAMESPACE_TOPSIDE_END


CONSOLE_APP_MAIN {
	using namespace UPP;
	
	LOG("Graphics tests");
	
	Test1<SdlOglGfx>();
	
}

#endif

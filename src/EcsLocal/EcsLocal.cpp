#include "EcsLocal.h"

NAMESPACE_TOPSIDE_BEGIN



/*void BindEcsEventsBase(Serial::EcsEventsBase* b) {
	Ecs::GetActiveEngine().Get<Ecs::EventSystem>()->Attach(b);
}*/

/*template <class Gfx>
void BindGfxBuffer(String id, Parallel::BufferT<Gfx>* b) {
	TODO
}*/

void BindEcsToSerial() {
	using namespace Parallel;
	
	//Serial::EcsEventsBase::WhenInitialize << callback(BindEcsEventsBase);
	
	/*#ifdef flagSDL2
	BufferT<SdlSwGfx>::WhenLinkInit << callback(BindGfxBuffer<SdlSwGfx>);
	#ifdef flagOGL
	BufferT<SdlOglGfx>::WhenLinkInit << callback(BindGfxBuffer<SdlOglGfx>);
	#endif
	#endif*/
}



NAMESPACE_TOPSIDE_END

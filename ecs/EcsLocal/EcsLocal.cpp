#include "EcsLocal.h"

NAMESPACE_TOPSIDE_BEGIN



void BindEcsEventsBase(Serial::EcsEventsBase* b) {
	Ecs::GetActiveEngine().Get<Ecs::EventSystem>()->Attach(b);
}

template <class Gfx>
void BindGfxBuffer(String id, Parallel::BufferT<Gfx>* b) {
	Ecs::GetActiveEngine().Get<Ecs::RenderingSystem>()->Attach(id, b);
}

void BindEcsToSerial() {
	using namespace Parallel;
	Serial::EcsEventsBase::WhenInitialize << callback(BindEcsEventsBase);
	#ifdef flagSDL2
	//BufferT<SdlCpuGfx>::WhenLinkInit.Add(callback(BindGfxBuffer<SdlCpuGfx>));
	BufferT<SdlSwGfx>::WhenLinkInit.Add(callback(BindGfxBuffer<SdlSwGfx>));
	#ifdef flagOGL
	BufferT<SdlOglGfx>::WhenLinkInit.Add(callback(BindGfxBuffer<SdlOglGfx>));
	#endif
	#endif
}



NAMESPACE_TOPSIDE_END

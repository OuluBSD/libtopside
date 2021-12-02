#include "EcsLocal.h"

NAMESPACE_TOPSIDE_BEGIN



void BindEcsEventsBase(Serial::EcsEventsBase* b) {
	Ecs::GetActiveEngine().Get<Ecs::EventSystem>()->Attach(b);
}

void BindOglBuffer(String id, OglBuffer* b) {
	Ecs::GetActiveEngine().Get<Ecs::RenderingSystem>()->Attach(id, b);
}

void BindEcsToSerial() {
	Serial::EcsEventsBase::WhenInitialize << callback(BindEcsEventsBase);
	OglBuffer::WhenLinkInit << callback(BindOglBuffer);
}



NAMESPACE_TOPSIDE_END

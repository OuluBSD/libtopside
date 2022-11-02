#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


bool EventSystem::Initialize() {
	return true;
}

void EventSystem::Attach(Serial::EcsEventsBase* b) {
	ASSERT(b);
	b->AddBinder(this);
	serial = b;
}

void EventSystem::Start() {
	
}

void EventSystem::Update(double dt) {
	
}

void EventSystem::Stop() {
	
}

void EventSystem::Uninitialize() {
	if (serial) {
		serial->RemoveBinder(this);
		serial = 0;
	}
}


NAMESPACE_ECS_END

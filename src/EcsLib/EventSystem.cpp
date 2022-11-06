#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


bool EventSystem::Initialize() {
	return true;
}

void EventSystem::Attach(Serial::EcsEventsBase* b) {
	ASSERT(b);
	EventStateBase::AddBinder(this);
	serial = b;
}

void EventSystem::Start() {
	
}

void EventSystem::Update(double dt) {
	
}

void EventSystem::Stop() {
	
}

void EventSystem::Uninitialize() {
	EventStateBase::RemoveBinder(this);
}


NAMESPACE_ECS_END

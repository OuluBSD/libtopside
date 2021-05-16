#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN


bool ActionSystem::Initialize() {
	return true;
}

void ActionSystem::Start() {
	
}

void ActionSystem::Update(double dt) {
	
	for (ActionSourceRef& src : srcs)
		src->EmitActionSource(dt);
	
}

void ActionSystem::Stop() {
	
}

void ActionSystem::Uninitialize() {
	
}

void ActionSystem::Add(ActionSourceRef src) {
	srcs.FindAdd(src);
}

void ActionSystem::Remove(ActionSourceRef src) {
	srcs.RemoveKey(src);
}



NAMESPACE_TOPSIDE_END

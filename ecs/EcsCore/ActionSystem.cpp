#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


bool ActionSystem::Initialize() {
	return true;
}

void ActionSystem::Start() {
	
}

void ActionSystem::Update(double dt) {
	
	for (ActionSource* src : srcs)
		src->EmitActionSource(dt);
	
}

void ActionSystem::Stop() {
	
}

void ActionSystem::Uninitialize() {
	
}

void ActionSystem::Add(ActionSource* src) {
	VectorFindAdd(srcs, src);
}

void ActionSystem::Remove(ActionSource* src) {
	VectorRemoveKey(srcs, src);
}



NAMESPACE_OULU_END

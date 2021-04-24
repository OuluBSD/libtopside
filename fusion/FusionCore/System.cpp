#include "FusionCore.h"

NAMESPACE_OULU_BEGIN



FusionSystem::FusionSystem(Machine& m) : System<FusionSystem>(m) {
	
}

bool FusionSystem::Initialize() {
	return true;
}

void FusionSystem::Start() {
	
}

void FusionSystem::Update(double dt) {
	DLOG("FusionSystem::Update: begin");
	
	for (FusionComponent* comp : comps)
		comp->Update0(dt);
	
	for (FusionContextComponent* ctx : ctxs)
		ctx->Update(dt);
	
	DLOG("FusionSystem::Update: end\n");
}

void FusionSystem::Stop() {
	
}

void FusionSystem::Uninitialize() {
	
}

void FusionSystem::AddContext(FusionContextComponent& ctx) {
	VectorFindAdd(ctxs, &ctx);
}

void FusionSystem::RemoveContext(FusionContextComponent& ctx) {
	VectorRemoveKey(ctxs, &ctx);
}

void FusionSystem::AddComponent(FusionComponent& comp) {
	VectorFindAdd(comps, &comp);
}

void FusionSystem::RemoveComponent(FusionComponent& comp) {
	VectorRemoveKey(comps, &comp);
}


NAMESPACE_OULU_END

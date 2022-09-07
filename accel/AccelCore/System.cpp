#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN



bool AccelSystem::Initialize() {
	return true;
}

void AccelSystem::Start() {
	
}

void AccelSystem::Update(double dt) {
	DLOG("AccelSystem::Update: begin");
	
	for (AccelComponentRef& comp : comps)
		comp->Update0(dt);
	
	for (AccelContextConnectorRef& ctx : ctxs)
		ctx->Update(dt);
	
	for (AccelContextConnectorRef& ctx : ctxs)
		ctx->ForwardPackets(dt);
	
	DLOG("AccelSystem::Update: end\n");
}

void AccelSystem::Stop() {
	
}

void AccelSystem::Uninitialize() {
	
}

void AccelSystem::Add(AccelContextConnectorRef ctx) {
	ctxs.FindAdd(ctx);
}

void AccelSystem::Remove(AccelContextConnectorRef ctx) {
	ctxs.RemoveKey(ctx);
}




NAMESPACE_TOPSIDE_END

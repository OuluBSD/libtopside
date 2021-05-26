#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN



bool AccelSystem::Initialize() {
	return true;
}

void AccelSystem::Start() {
	
}

void AccelSystem::Update(double dt) {
	DLOG("AccelSystem::Update: begin");
	
	/*#define IFACE(x) \
	for (Accel##x##ComponentRef& comp : comps_##x) \
		comp->Update0(dt);
	IFACE_LIST
	#undef IFACE*/
	TODO
	
	for (AccelContextComponentRef& ctx : ctxs)
		ctx->Update(dt);
	
	DLOG("AccelSystem::Update: end\n");
}

void AccelSystem::Stop() {
	
}

void AccelSystem::Uninitialize() {
	
}

void AccelSystem::Add(AccelContextComponentRef ctx) {
	ctxs.FindAdd(ctx);
}

void AccelSystem::Remove(AccelContextComponentRef ctx) {
	ctxs.RemoveKey(ctx);
}




NAMESPACE_TOPSIDE_END

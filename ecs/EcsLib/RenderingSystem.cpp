#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


bool RenderingSystem::Initialize() {
	return true;
}

void RenderingSystem::Attach(String key, OglBuffer* b) {
	if (key != "ecs") {
		RTLOG("RenderingSystem::Attach: warning: skipping unrelated key '" << key << "'");
		return;
	}
	
	ASSERT(!buf);
	if (buf) buf->RemoveBinder(this);
	
	ASSERT(b);
	b->AddBinder(this);
	buf = b;
}

void RenderingSystem::AddRenderable(ComponentBaseRef b) {
	ASSERT(b);
	ArrayFindAdd(rends, b);
}

void RenderingSystem::RemoveRenderable(ComponentBaseRef b) {
	ASSERT(b);
	ArrayRemoveKey(rends, b);
}

void RenderingSystem::Start() {
	
}

void RenderingSystem::Update(double dt) {
	
}

void RenderingSystem::Stop() {
	
}

void RenderingSystem::Uninitialize() {
	ASSERT_(rends.IsEmpty(), "RenderingSystem must be added to Engine before EntityStore");
	
	if (buf) {
		buf->RemoveBinder(this);
		buf = 0;
	}
}


NAMESPACE_ECS_END

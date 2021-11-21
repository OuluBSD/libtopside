#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


void Renderable::Initialize() {
	Engine& e = GetEngine();
	RenderingSystemRef rend = e.TryGet<RenderingSystem>();
	if (rend)
		rend->AddRenderable(AsRef<ComponentBase>());
}

void Renderable::Uninitialize() {
	Engine& e = GetEngine();
	RenderingSystemRef rend = e.TryGet<RenderingSystem>();
	if (rend)
		rend->RemoveRenderable(AsRef<ComponentBase>());
}



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

void RenderingSystem::AddRenderable(RenderableRef b) {
	ASSERT(b);
	ArrayFindAdd(rends, b);
	//ASSERT(rends.GetCount() < 10);
}

void RenderingSystem::RemoveRenderable(RenderableRef b) {
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

void RenderingSystem::Render(const OglBuffer& buf, OglShader& shader) {
	DUMPC(rends);
	
	for (RenderableRef& rend : rends) {
		rend->cb(shader);
	}
	
}


NAMESPACE_ECS_END

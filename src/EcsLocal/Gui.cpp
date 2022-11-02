#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


#ifdef flagGUI

DefaultGuiAppComponent::DefaultGuiAppComponent() {
	
}

void DefaultGuiAppComponent::Initialize() {
	AddToUpdateList();
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void DefaultGuiAppComponent::Uninitialize() {
	RemoveFromUpdateList();
	Serial::EcsVideoBase::Latest().RemoveBinder(this);
}

void DefaultGuiAppComponent::Update(double dt) {
	
}

void DefaultGuiAppComponent::StateStartup(GfxDataState& state) {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	
	TODO
}

bool DefaultGuiAppComponent::Render(Draw& d) {
	
	ProgDraw* pd = CastPtr<ProgDraw>(&d);
	ASSERT(pd);
	if (!pd) {
		return false;
	}
	
	return true;
}

void DefaultGuiAppComponent::DrawObj(GfxStateDraw& fb, bool use_texture) {
	
	TODO
}

bool DefaultGuiAppComponent::Arg(const String& key, const String& value) {
	
	return true;
}

#endif


NAMESPACE_ECS_END

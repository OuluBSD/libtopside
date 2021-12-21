#include "EcsLib.h"

NAMESPACE_ECS_BEGIN

void Viewable::Initialize() {
	
}

void Viewable::Uninitialize()  {
	// try remove this from rendering system, in case it was added manually
	RenderingSystemRef rend = GetEngine().Get<RenderingSystem>();
	if (rend)
		rend->RemoveViewable(AsRefT());
}

/*Ref<Transform> Viewable::GetTransform() {
	EntityRef ent = GetEntity();
	return ent->Find<Transform>();
}*/

void ChaseCam::Initialize() {
	view = GetEntity()->Get<Viewable>();
	vport = GetEntity()->Get<Viewport>();
	if (view)
		view->cb << THISBACK(Refresh);
}

void ChaseCam::Refresh(GfxShader& s) {
	if (vport) {
		
	}
}


NAMESPACE_ECS_END

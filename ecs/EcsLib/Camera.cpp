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
	trans = GetEntity()->Get<Transform>();
	view = GetEntity()->Get<Viewable>();
	vport = GetEntity()->Get<Viewport>();
	//if (view)
	//	view->cb << THISBACK(Refresh);
}

void ChaseCam::Refresh(GfxDataState& s) {
	int width = 1280;
	int height = 720;
	
	mat4 projection = perspective(DEG2RAD(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    //simple_shader.SetMat4("projection", projection);
    
    // camera/view transformation
    vec3 pos = trans->position;
    vec3 target = this->target->position;
    
	//mat4 view = LookAt(t.position, c.target, vec3(0.0f, 1.0f, 0.0f));
	mat4 look = LookAt(pos, target, vec3(0.0f, 1.0f, 0.0f));
	mat4 view = projection * look;
	
	s.view = view;
}


NAMESPACE_ECS_END

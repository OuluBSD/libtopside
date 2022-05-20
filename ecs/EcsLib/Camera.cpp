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
	trans		= GetEntity()->Get<Transform>();
	viewable	= GetEntity()->Get<Viewable>();
	vport		= GetEntity()->Get<Viewport>();
	
	SetViewportSize(Size(1280, 720));
	
	//if (view)
	//	view->cb << THISBACK(Refresh);
	
	AddToUpdateList();
}

void ChaseCam::Uninitialize() {
	
	RemoveFromUpdateList();
}

void ChaseCam::Update(double dt) {
	
	if (trans && target) {
	    // camera/view transformation
	    vec3 pos = trans->position;
	    vec3 tgt = target->position;
	    
	    if (pos == tgt) {
	        RTLOG("ChaseCam::Update: warning: camera position is same as target position");
	    }
	    else {
			//LOG(pos.ToString());
			//LOG(tgt.ToString());
		    look = LookAt(pos, tgt, vec3(0.0f, 1.0f, 0.0f));
		    view = projection * look;
		    
			if (test_log) {
				vec3 ori(0,0,0);
				vec3 diff = ori - pos;
				vec3 mod = (diff.Extend(0.0) * view).Splice();
				double angle_x = asin(mod[0] / mod[2]) * 360.0 / (2.0*M_PI);
				double len_xz = sqrt(mod[0] * mod[0] + mod[2] * mod[2]);
				double angle_y = asin(mod[1] / len_xz) * 360.0 / (2.0*M_PI);
				LOG("ChaseCam::Update: horz " << angle_x << ", vert " << angle_y);
			}
	    }
	}
	
}

bool ChaseCam::Arg(String key, Object value) {
	
	if (key == "target") {
		String path = value;
		
		EntityStoreRef ents = GetEngine().Get<EntityStore>();
		ASSERT(ents);
		
		EntityRef tgt_ent = ents->FindEntity(path);
		if (!tgt_ent) {
			LOG("ChaseCam::Arg: error: could not find entity with path '" + path + "'");
			return false;
		}
		
		target = tgt_ent->Get<Transform>();
		if (!tgt_ent) {
			LOG("ChaseCam::Arg: error: target entity doesn't have Transform component");
			return false;
		}
		
	}
	else if (key == "log") {
		test_log = (String)value == "test";
	}
	else return false;
	
	return true;
}

void ChaseCam::SetViewportSize(Size sz) {
	viewport_sz[0] = sz.cx;
	viewport_sz[1] = sz.cy;
	
	double fov = 120;
	if (vport) {
		fov = vport->fov;
	}
	
	projection = perspective(DEG2RAD(fov), viewport_sz[0] / viewport_sz[1], 0.1f, 100.0f);
}

void ChaseCam::Refresh(GfxDataState& s) {
	int width = 1280;
	int height = 720;
	
    //simple_shader.SetMat4("projection", projection);
    
	//mat4 view = LookAt(t.position, c.target, vec3(0.0f, 1.0f, 0.0f));
	
	s.view = view;
}


NAMESPACE_ECS_END

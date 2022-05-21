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
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->AddCamera(*this);
	
	//if (view)
	//	view->cb << THISBACK(Refresh);
	
	AddToUpdateList();
}

void ChaseCam::Uninitialize() {
	
	RenderingSystemRef rend = this->GetEngine().Get<RenderingSystem>();
	rend->RemoveCamera(*this);
	
	RemoveFromUpdateList();
}

void ChaseCam::Update(double dt) {
	time += dt;
	
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

bool ChaseCam::Load(GfxDataState& s) {
	int width = 1280;
	int height = 720;
	
    //simple_shader.SetMat4("projection", projection);
    
	//mat4 view = LookAt(t.position, c.target, vec3(0.0f, 1.0f, 0.0f));
	
	
	{
		double phase_time = 1.5;
		float ratio = (float)height / (float)width;
		float aspect = (float)width / (float)height;
		float f = time / phase_time;
		float f2 = 1 - fabs(2 * f - 1);
		float angle = f * (2.0 * M_PI);
		float x = cos(angle);
		float y = sin(angle);
		bool use_texture = false;
		
		float eye_angle = (use_texture ? -1 : +1) * f /** 0.25*/ * M_2PI;
		float eye_x = cos(eye_angle);
		float eye_y = sin(eye_angle);
		float x_mod = 0.2 * eye_x;
		float y_mod = 0.2 * eye_y;
		/*mat4 proj {
			vec4{1,		0,	    0,		0},
			vec4{0,		1,	    0,		0},
			vec4{0,		0,	    1,		0},
			vec4{0,		0, -1./5.,		1}
		};*/
		mat4 proj = perspective(90, 1, 0.01, 10);
		
		#if 1
		vec3 eye {0.3f * eye_x, 0+0.3f * eye_y, -6};
		vec3 center {0, 0, -2};
		//vec3 center {0, 0, -2};
		#else
		vec3 eye {0, 0, 2};
		vec3 center {0, 1, 4};
		#endif
		vec3 up {0, 1, 0};
		mat4 lookat = LookAt(eye, center, up);
		mat4 port;
		
		/*if (phase == 0)
			port = GetViewport((-1 + x_mod) * ratio, -1 + y_mod, (2 - x_mod) * ratio, 2 + y_mod, 1);
		else*/
			port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, -1);
	
		s.view = port * proj * lookat;
	}
	s.user_view = true;
	//s.view = view;
	
	return true;
}


NAMESPACE_ECS_END

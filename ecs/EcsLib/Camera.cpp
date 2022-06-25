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






bool Viewport::Arg(String key, Object value) {
	if (key == "fov") {
		fov = value.ToDouble();
		return true;
	}
	return false;
}









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
	
	UpdateView();
}

bool ChaseCam::Arg(String key, Object value) {
	
	if (key == "fov") {
		fov = max(0.10f, min(180.f, (float)StrDbl(value)));
		return true;
	}
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
	/*else if (key == "mode") {
		String m = value;
		if (m == "static")			mode = STATIC;
		else if (m == "circle.cw")	mode = CIRCLE_CW;
		else if (m == "circle.ccw")	mode = CIRCLE_CCW;
		else return false;
	}*/
	else return false;
	
	return true;
}

void ChaseCam::SetViewportSize(Size sz) {
	viewport_sz[0] = sz.cx;
	viewport_sz[1] = sz.cy;
	float ratio = viewport_sz[1] / viewport_sz[0];
	port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
	
	if (vport)
		fov = vport->fov;
	projection = perspective(DEG2RAD(fov), 1.0f, 0.1f, 100.0f);
}

void ChaseCam::UpdateView() {
	int width = TS::default_width;
	int height = TS::default_height;
	
	if (this->target) {
		vec3 target = this->target->position;
		vec3 eye {0.0f, 2.0f, -6.0f};
		vec3 up {0, 1, 0};
		
		if (this->trans) {
			
		    // camera/view transformation
		    eye = this->trans->position;
		    
		    if (eye == target) {
		        RTLOG("ChaseCam::Update: warning: camera position is same as target position");
		        target[0] += 0.01f;
		    }
		    else {
				if (test_log) {
					vec3 diff = target - eye;
					vec3 mod = (diff.Extend(0.0) * view).Splice();
					double angle_x = asin(mod[0] / mod[2]) * 360.0 / (2.0*M_PI);
					double len_xz = sqrt(mod[0] * mod[0] + mod[2] * mod[2]);
					double angle_y = asin(mod[1] / len_xz) * 360.0 / (2.0*M_PI);
					LOG("ChaseCam::Update: horz " << angle_x << ", vert " << angle_y);
				}
		    }
		    #if 0
			if (mode == CIRCLE_CW || mode == CIRCLE_CCW) {
				float f = time / phase_time;
				float f2 = 1 - fabs(2 * f - 1);
				float angle = f * (2.0 * M_PI);
				float eye_angle =  f /** 0.25*/ * M_2PI;
				float eye_x = cos(eye_angle);
				float eye_y = sin(eye_angle);
				float x_mod = 0.2 * eye_x;
				float y_mod = 0.2 * eye_y;
				
				eye = eye + vec3{0.3f * eye_x, 0.3f * eye_y, 0.0f};
				rot = rotate(identity<mat4>(), angle, up);
			}
			#endif
		}
	    
		mat4 lookat = LookAt(eye, target, up);
		
		this->view = port * projection * lookat;
	}
	else if (this->trans) {
		
		if (this->trans->use_lookat) {
			vec3 position = this->trans->position;
			vec3 direction = this->trans->direction;
			vec3 target = position + direction;
			vec3 up = this->trans->up;
			if (direction == up)
				direction += vec3(0.01, 0.01, 0.01);
			mat4 lookat = LookAt(position, target, up);
			this->view = port * projection * lookat;
		}
		else {
			quat orientation = this->trans->orientation;
			mat4 rotate = ToMat4(orientation);
			mat4 tran = translate(-this->trans->position);
			this->view = port * projection * rotate * tran;
		}
	}
	/*mat4 model = translate(target);
	this->view = port * projection * lookat * model * rot;*/
}

bool ChaseCam::Load(GfxDataState& s) {
	s.view = view;
	s.user_view = true;
	
	return true;
}


NAMESPACE_ECS_END

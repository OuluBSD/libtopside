#include "EcsLib.h"

NAMESPACE_ECS_BEGIN




void CalculateCameraView(mat4& view, mat4* stereo_view, float eye_dist, const vec3& eye, const vec3& target, const vec3& up, const mat4& port, const mat4& eye_port, const mat4& proj) {
	vec3 look_vec = target - eye;
	vec3 side_vec = cross(look_vec, up);
	side_vec.Normalize();
	float eye_dist_2 = eye_dist / 2;
	vec3 eye_off = side_vec * eye_dist_2;
	
	mat4 lookat = LookAt(eye, target, up);
	view = port * proj * lookat;
	
	if (stereo_view) {
		vec3 l_eye = eye - eye_off;
		vec3 r_eye = eye + eye_off;
		vec3 l_target = target - eye_off;
		vec3 r_target = target + eye_off;
		mat4 base = eye_port * proj;
		//vec3 l_eye(-eye_dist, 0, +1);
		//vec3 r_eye(+eye_dist, 0, +1);
		//vec3 l_center { -eye_dist, 0, 0};
		//vec3 r_center { +eye_dist, 0, 0};
		mat4 l_lookat = LookAt(l_eye, l_target, up);
		mat4 r_lookat = LookAt(r_eye, r_target, up);
		stereo_view[0] = base * l_lookat;
		stereo_view[1] = base * r_lookat;
	}
}








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

void ChaseCam::UpdateCalibration() {
	UpdateProjection();
	UpdateView();
}
	

void ChaseCam::SetViewportSize(Size sz) {
	viewport_sz[0] = sz.cx;
	viewport_sz[1] = sz.cy;
	UpdateProjection();
}

void ChaseCam::UpdateProjection() {
	float ratio = viewport_sz[1] / viewport_sz[0];
	float eye_ratio = viewport_sz[1] / (viewport_sz[0] * 0.5);
	port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
	port_stereo = GetViewport(-1 * eye_ratio, -1, 2 * eye_ratio, 2, 1);
	
	if (vport)
		fov = vport->fov;
	
	float used_fov = calib.is_enabled ? DEG2RAD(fov) + calib.fov : DEG2RAD(fov);
	
	projection = perspective(used_fov, 1.0f, 0.1f, 100.0f);
}

void ChaseCam::UpdateView() {
	int width = TS::default_width;
	int height = TS::default_height;
	
	float eye_dist = 0.064;
	
	if (this->target) {
		vec3 target = this->target->data.position;
		vec3 eye {0.0f, 2.0f, -6.0f};
		vec3 up {0, 1, 0};
		
		if (this->trans) {
			
		    // camera/view transformation
		    eye = this->trans->data.position;
		    
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
		//mat4 lookat = LookAt(eye, target, up);
		//this->view = port * projection * lookat;
		
		CalculateCameraView(this->view, this->mvp_stereo, eye_dist, eye, target, up, port, port_stereo, projection);
	    
	}
	else if (this->trans) {
		TransformMatrix& tm = this->trans->data;
		if (tm.is_stereo) {
			if (tm.mode == TransformMatrix::MODE_POSITION) {
				TODO
			}
			else if (tm.mode == TransformMatrix::MODE_LOOKAT) {
				vec3 position = tm.position;
				vec3 direction = tm.direction;
				vec3 target = position + direction;
				vec3 up = tm.up;
				if (direction == up)
					direction += vec3(0.01, 0.01, 0.01);
				CalculateCameraView(this->view, this->mvp_stereo, eye_dist, position, target, up, port, port_stereo, projection);
			}
			else if (tm.mode == TransformMatrix::MODE_AXES) {
				//DUMP(tm.axes);
				//mat4 rotate = make_mat4_from_yaw_pitch_roll(tm.axes[0], tm.axes[1], tm.axes[2]);
				
				// TODO solve and clean this horrible separate-yaw mess!
				mat4 rotate = make_mat4_from_yaw_pitch_roll(M_PI, tm.axes[1], tm.axes[2]);
				mat4 yaw = YRotation(tm.axes[0]);
				mat4 tran = translate(-tm.position);
				this->view = port * projection * rotate * tran;
				DUMP(tm.position);
				
				if (calib.is_enabled) {
					eye_dist += calib.eye_dist;
				}
				
				float mul = -0.5;
				mat4 l_trans = translate(vec3(-eye_dist * mul, 0, 0));
				mat4 r_trans = translate(vec3(+eye_dist * mul, 0, 0));
				//mat4 stereo_base = port_stereo * projection * rotate * yaw * tran;
				//this->mvp_stereo[0] = stereo_base;
				//this->mvp_stereo[1] = stereo_base;
				
				if (calib.is_enabled) {
					mat4 scale_mat = scale(vec3(1.0 + calib.scale));
					this->mvp_stereo[0] = port_stereo * scale_mat * l_trans * projection * rotate * yaw * tran;
					this->mvp_stereo[1] = port_stereo * scale_mat * r_trans * projection * rotate * yaw * tran;
				}
				else {
					this->mvp_stereo[0] = port_stereo * l_trans * projection * rotate * yaw * tran;
					this->mvp_stereo[1] = port_stereo * r_trans * projection * rotate * yaw * tran;
				}
			}
			else if (tm.mode == TransformMatrix::MODE_QUATERNION) {
				quat orientation = tm.orientation;
				mat4 rotate = ToMat4(orientation);
				mat4 tran = translate(-tm.position);
				this->view = port * projection * rotate * tran;
				
				float mul = -0.5;
				mat4 l_trans = translate(vec3(-eye_dist * mul, 0, 0));
				mat4 r_trans = translate(vec3(+eye_dist * mul, 0, 0));
				this->mvp_stereo[0] = port_stereo * l_trans * projection * rotate * tran;
				this->mvp_stereo[1] = port_stereo * r_trans * projection * rotate * tran;
			}
			else TODO
		}
		#if 0
		if (this->use_stereo) {
			mat4 tran = translate(-this->trans->data.position);
			#if 0
			this->mvp_stereo[0] = this->proj_stereo[0] * this->view_stereo[0] * tran;
			this->mvp_stereo[1] = this->proj_stereo[1] * this->view_stereo[1] * tran;
			#else
			this->mvp_stereo[0] = this->view_stereo[0] * this->proj_stereo[0] * tran;
			this->mvp_stereo[1] = this->view_stereo[1] * this->proj_stereo[1] * tran;
			#endif
		}
		#endif
	}
	
	/*if (calib.is_enabled) {
		mat4 scale_mat = scale(vec3(1.0 + calib.scale));
		this->mvp_stereo[0] = this->mvp_stereo[0] * scale_mat;
		this->mvp_stereo[1] = this->mvp_stereo[1] * scale_mat;
	}*/
	
	/*mat4 model = translate(target);
	this->view = port * projection * lookat * model * rot;*/
}

bool ChaseCam::Load(GfxDataState& s) {
	s.view = view;
	s.user_view = true;
	
	if (s.is_stereo) {
	//if (use_stereo) {
		s.is_stereo = true;
		s.view_stereo[0] = mvp_stereo[0];
		s.view_stereo[1] = mvp_stereo[1];
	}
	
	return true;
}


NAMESPACE_ECS_END

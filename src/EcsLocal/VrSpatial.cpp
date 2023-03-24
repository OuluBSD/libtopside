#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


void VrControllerSource::GetVelocity(float* v3) const {
	COPY3(v3, mgr->hand_velocity);
}

void VrControllerSource::GetAngularVelocity(float* v3) const {
	COPY3(v3, mgr->hand_angular_velocity);
}






VrSpatialInteractionManager::VrSpatialInteractionManager() {
	ctrl.mgr = this;
	ctrl_state.source = &ctrl;

	for(int i = 0; i < 3; i++) av[i].Resize(30);
	
}

bool VrSpatialInteractionManager::Initialize(InteractionSystem& sys) {
	this->sys = &sys;
	
	hand_velocity = vec3(0, 0.1, 0.1);
	hand_angular_velocity = vec3(0.1, 0.1, 0);
	
	prev.SetAll(false);
	
	return true;
}

void VrSpatialInteractionManager::Update(double dt) {
	time += dt;
	last_dt = dt;
	
	String env_name = sys->env_name;
	
	if (!env_name.IsEmpty()) {
		Serial::Machine& m = Serial::GetActiveMachine();
		Ref<LoopStore> ls = m.Find<LoopStore>();
		LoopRef l = ls->GetRoot();
		state = l->GetSpace()->FindStateDeep(env_name);
		if (!state) {
			LOG("InteractionSystem::Update: error: environment state with name '" << env_name << "' not found");
		}
		env_name.Clear();
		
		DetectController();
	}
	
	if (state)
		UpdateState();

}

void VrSpatialInteractionManager::DetectController() {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_CONTROLLER_DETECTED;
	
	WhenSourceDetected(*this, ev);
}

void VrSpatialInteractionManager::UpdateState() {
	ASSERT(state);
	
	if (sys->use_state_hmd) {
		UpdateStateHmd();
	}
	
	if (sys->is_calibration) {
		if (!rend)
			rend = sys->GetEngine().TryGet<Ecs::RenderingSystem>();
		UpdateCalibrationStateKeyboard();
	}
	
}

void VrSpatialInteractionManager::UpdateStateHmd() {
	TransformMatrix& tm = state->Set<TransformMatrix>(HMD_CAMERA);
	Look(tm);
	
	ControllerMatrix& ctrl = state->Set<ControllerMatrix>(HMD_CONTROLLER);
	Control(ctrl);
	
}

void VrSpatialInteractionManager::UpdateCalibrationStateKeyboard() {
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	
	if      (data['1']) calib_mode = CALIB_FOV_SCALE_EYEDIST;
	else if (data['2']) calib_mode = CALIB_CTRL_LEFT;
	else if (data['3']) calib_mode = CALIB_CTRL_RIGHT;
	
	
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_CALIB;
	ev.n = -1;
	
	
	WhenSourcePressed(*this, ev);
	float step = last_dt * 0.3;
	
	if (calib_mode == CALIB_FOV_SCALE_EYEDIST) {
		
		if (data['q']) {
			// decrease fov
			ev.n = HOLO_CALIB_FOV;
			ev.fvalue = -step;
		}
		else if (data['w']) {
			// increase fov
			ev.n = HOLO_CALIB_FOV;
			ev.fvalue = +step;
		}
		else if (data['z']) {
			// decrease eye distance
			ev.n = HOLO_CALIB_EYE_DIST;
			ev.fvalue = -step;
		}
		else if (data['x']) {
			// increase eye distance
			ev.n = HOLO_CALIB_EYE_DIST;
			ev.fvalue = +step;
		}
	}
	else if (calib_mode == CALIB_CTRL_LEFT || calib_mode == CALIB_CTRL_RIGHT) {
		
		if (data['s']) {
			// bwd
			ev.n = HOLO_CALIB_Z;
			ev.fvalue = -step;
		}
		else if (data['w']) {
			// fwd
			ev.n = HOLO_CALIB_Z;
			ev.fvalue = +step;
		}
		else if (data['a']) {
			// left
			ev.n = HOLO_CALIB_X;
			ev.fvalue = -step;
		}
		else if (data['d']) {
			// right
			ev.n = HOLO_CALIB_X;
			ev.fvalue = +step;
		}
		else if (data['q']) {
			// down
			ev.n = HOLO_CALIB_Y;
			ev.fvalue = -step;
		}
		else if (data['e']) {
			// up
			ev.n = HOLO_CALIB_Y;
			ev.fvalue = +step;
		}
		else if (data['h']) {
			// yaw right
			ev.n = HOLO_CALIB_YAW;
			ev.fvalue = -step;
		}
		else if (data['f']) {
			// yaw left
			ev.n = HOLO_CALIB_YAW;
			ev.fvalue = +step;
		}
		else if (data['t']) {
			// pitch down
			ev.n = HOLO_CALIB_PITCH;
			ev.fvalue = -step;
		}
		else if (data['g']) {
			// pitch up
			ev.n = HOLO_CALIB_PITCH;
			ev.fvalue = +step;
		}
		
	}
	
	if (data['h']) {
		// yaw right
		ev.n = HOLO_CALIB_YAW;
		ev.fvalue = -step;
	}
	else if (data['f']) {
		// yaw left
		ev.n = HOLO_CALIB_YAW;
		ev.fvalue = +step;
	}
	else if (data['t']) {
		// pitch down
		ev.n = HOLO_CALIB_PITCH;
		ev.fvalue = -step;
	}
	else if (data['g']) {
		// pitch up
		ev.n = HOLO_CALIB_PITCH;
		ev.fvalue = +step;
	}
	else if (data['y']) {
		// roll right
		ev.n = HOLO_CALIB_ROLL;
		ev.fvalue = -step;
	}
	else if (data['r']) {
		// roll left
		ev.n = HOLO_CALIB_ROLL;
		ev.fvalue = +step;
	}
	
	if (ev.n >= 0) {
		TODO //rend->CalibrationEvent(ev);
	}
	
}

void VrSpatialInteractionManager::Pressed(ControllerMatrix::Value b, float f) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_PRESSED;
	ev.value = (int)b;
	
	WhenSourcePressed(*this, ev);
}

void VrSpatialInteractionManager::Released(ControllerMatrix::Value b, float f) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_RELEASED;
	ev.value = (int)b;
	
	WhenSourceReleased(*this, ev);
}

void VrSpatialInteractionManager::Updated(ControllerMatrix::Value b, float f) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_UPDATED;
	ev.value = (int)b;
	
	WhenSourceUpdated(*this, ev);
}








void VrSpatialInteractionManager::Look(const TransformMatrix& tm) {
	this->trans = tm;
	
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = Point(0,0);
	ev.trans = &trans;
	
	if (sys->debug_log) {
		mat4 m = QuatMat(trans.orientation);
		vec4 dir = vec4(0,0,1,1) * m;
		DirAxes(dir.Splice(), yaw, pitch);
		
		LOG("VrSpatialInteractionManager::Look: orientation: " << trans.orientation.ToString() <<
			", angle: " << yaw << ", angle1: " << pitch);
	}
	
	WhenSourceUpdated(*this, ev);
}

void VrSpatialInteractionManager::Control(const ControllerMatrix& ctrl) {
	
	if (0) {
		CtrlEvent ev;
		ev.ctrl = &ctrl_state.props;
		ev.state = &ctrl_state;
		ev.type = EVENT_HOLO_LOOK;
		ev.pt = Point(0,0);
		
		if (sys->debug_log) {
			mat4 m = QuatMat(trans.orientation);
			vec4 dir = vec4(0,0,1,1) * m;
			DirAxes(dir.Splice(), yaw, pitch);
			
			LOG("VrSpatialInteractionManager::Look: orientation: " << trans.orientation.ToString() <<
				", angle: " << yaw << ", angle1: " << pitch);
		}
		
		WhenSourceUpdated(*this, ev);
	}
	
	if (1) {
		for(int i = 0; i < 2; i++) {
			const ControllerMatrix::Ctrl& prev = ctrl_state.props.ctrl[i];
			const ControllerMatrix::Ctrl& curr = ctrl.ctrl[i];
			
			if (!curr.is_enabled || !prev.is_enabled)
				continue;
			
			for(int j = 0; j < ControllerMatrix::VALUE_COUNT; j++) {
				bool changed = prev.value[j] != curr.value[j];
				if (!changed)
					continue;
				
				bool pushed   = curr.value[j] != 0 && prev.value[j] == 0;
				bool released = curr.value[j] == 0 && prev.value[j] != 0;
				
				if (pushed)
					Pressed((ControllerMatrix::Value)j, curr.value[j]);
				
				else if (released)
					Released((ControllerMatrix::Value)j, curr.value[j]);
				
				else
					Updated((ControllerMatrix::Value)j, curr.value[j]);
			}
			
		}
	}
	
	this->ctrl_state.props = ctrl;
	
	
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_MOVE_CONTROLLER;
	WhenSourceUpdated(*this, ev);
}


void VrSpatialInteractionManager::Move(vec3 rel_dir, float step) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_MOVE_FAR_RELATIVE;
	TODO
	#if 0
	ev.spatial = &ev3d;
	vec3 dir = head_direction;
	
	// remove y component
	dir[1] = 0;
	
	float straight = rel_dir[2];
	float sideways = rel_dir[0];
	
	if (straight) {
		vec3 pos_diff = dir * step * straight;
		COPY3(ev3d.position, pos_diff);
	}
	if (sideways) {
		vec3 s = dir * step * sideways;
		vec3 pos_diff(-s[2], 0, +s[0]);
		COPY3(ev3d.position, pos_diff);
	}
	
	WhenSourceUpdated(*this, ev);
	#endif
}


NAMESPACE_ECS_END

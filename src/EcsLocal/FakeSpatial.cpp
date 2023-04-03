#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


void FakeControllerSource::GetVelocity(float* v3) const {
	COPY3(v3, mgr->hand_velocity);
}

void FakeControllerSource::GetAngularVelocity(float* v3) const {
	COPY3(v3, mgr->hand_angular_velocity);
}







FakeSpatialInteractionManager::FakeSpatialInteractionManager() {
	ctrl.mgr = this;
	ctrl_state.source = &ctrl;

	for(int i = 0; i < 3; i++) av[i].Resize(30);
	
}

bool FakeSpatialInteractionManager::Initialize(InteractionSystem& sys) {
	this->sys = &sys;
	
	hand_velocity = vec3(0, 0.1f, 0.1f);
	hand_angular_velocity = vec3(0.1f, 0.1f, 0);
	
	prev.SetAll(false);
	
	return true;
}

void FakeSpatialInteractionManager::Update(double dt) {
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
		Look(Point(0,0)); // camera might be messed up, so update it immediately
	}
	
	if (state)
		UpdateState();

}

void FakeSpatialInteractionManager::DetectController() {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_CONTROLLER_DETECTED;
	
	WhenSourceDetected(*this, ev);
}

void FakeSpatialInteractionManager::UpdateState() {
	
	UpdateStateKeyboard();
	
}

void FakeSpatialInteractionManager::UpdateStateKeyboard() {
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	
	if (state->GetBool(MOUSE_LEFTDOWN)) {
		Point& drag = state->Set<Point>(MOUSE_TOYCOMPAT_DRAG);
		
		Point diff = drag - prev_mouse;
		
		if (prev_mouse.x != 0 && prev_mouse.y != 0 && (diff.x || diff.y))
			Look(diff);
		
		prev_mouse = drag;
	}
	else {
		prev_mouse = Point(0,0);
	}
	
	
	bool fwd   = data['w'];
	bool left  = data['a'];
	bool bwd  = data['s'];
	bool right = data['d'];
	
	float step = (float)last_dt * 1.5f;
	
	if (fwd) {
		Move(VEC_FWD, step);
	}
	if (left) {
		Move(VEC_LEFT, step);
	}
	if (bwd) {
		Move(VEC_BWD, step);
	}
	if (right) {
		Move(VEC_RIGHT, step);
	}
	
	static const int assign[ControllerMatrix::VALUE_COUNT] = {
		'1',
		0,
		0,
		'2',
		'3',
		
		0,
		'2',
		0,
		0,
		0,
		
		0,
		0,
		0,
		0,
		0,
		
		0,
		0,
		0,
		0,
		0,
		
		0,
		0,
		0,
		0,
		0,
		
	};
	
	for(int i = 0; i < ControllerMatrix::VALUE_COUNT; i++) {
		int key = assign[i];
		if (!key)
			continue;
		
		bool pushed = data[key] && !prev[key];
		bool released = !data[key] && prev[key];
		
		if (pushed)
			Pressed((ControllerMatrix::Value)i);
		
		if (released)
			Released((ControllerMatrix::Value)i);
		
	}
	
	prev = data;
	
}

void FakeSpatialInteractionManager::Pressed(ControllerMatrix::Value b) {
	ctrl_state.props.ctrl[1].value[(int)b] = 1.0f;
	ctrl_state.props.ctrl[1].is_value[(int)b] = true;
	
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_PRESSED;
	ev.value = (int)b;
	
	WhenSourcePressed(*this, ev);
}

void FakeSpatialInteractionManager::Released(ControllerMatrix::Value b) {
	ctrl_state.props.ctrl[1].value[(int)b] = 0.0f;
	ctrl_state.props.ctrl[1].is_value[(int)b] = true;
	
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_RELEASED;
	ev.value = (int)b;
	
	WhenSourceReleased(*this, ev);
}








void FakeSpatialInteractionManager::Look(Point mouse_diff) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = mouse_diff; // extra
	ev.trans = &trans;
	
	float prev_yaw = yaw;
	float prev_pitch = pitch;
	
	float rot_speed = 0.05f / (2*M_PIf);
	float yaw_change = -mouse_diff.x * rot_speed;
	float pitch_change = mouse_diff.y * rot_speed;
	yaw += yaw_change;
	pitch += pitch_change;
	
	vec3 prev_head_direction;
	for(int i = 0; i < 3; i++)
		prev_head_direction[i] = (float)av[i].GetMean();
	
	head_direction = AxesDir(yaw, pitch);
	
	for(int i = 0; i < 3; i++)
		av[i].Add(head_direction[i]);
	
	trans.mode = TransformMatrix::MODE_LOOKAT;
	trans.direction = head_direction;
	trans.position = vec3(0,0,0);
	trans.up = VEC_UP;
	trans.FillFromLookAt();
	
	vec3 head_direction_diff = head_direction - prev_head_direction;
	float multiplier = 5;
	hand_velocity = head_direction_diff * multiplier;
	hand_angular_velocity = vec3(yaw, pitch, 0);
	
	if (sys->debug_log) {
		LOG("FakeSpatialInteractionManager::Look: dx: " << mouse_diff.x << ", dy: " << mouse_diff.y <<
			", rot: " << head_direction[0] << ", " << head_direction[1] << ", " << head_direction[2] <<
			", angle: " << yaw << ", angle1: " << pitch);
	}
	
	WhenSourceUpdated(*this, ev);
}

void FakeSpatialInteractionManager::Move(vec3 rel_dir, float step) {
	CtrlEvent ev;
	ev.ctrl = &ctrl_state.props;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_MOVE_FAR_RELATIVE;
	ev.trans = &trans;
	vec3 dir = head_direction;
	
	// remove y component
	dir[1] = 0;
	
	float straight = rel_dir[2] * VEC_FWD[2];
	float sideways = rel_dir[0];
	
	if (straight) {
		trans.position = dir * step * straight;
	}
	if (sideways) {
		vec3 s = dir * step * sideways;
		trans.position = vec3(-s[2], 0, +s[0]);
	}
	
	WhenSourceUpdated(*this, ev);
}


NAMESPACE_ECS_END

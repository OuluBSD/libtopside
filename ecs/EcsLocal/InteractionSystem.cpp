#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool InteractionListener::Initialize(Engine& e, Ref<InteractionListener, RefParent1<Engine>> l) {
	Ref<InteractionSystem> iasys = e.TryGet<InteractionSystem>();
	if (!iasys) {
		LOG("InteractionListener::Initialize: error: InteractionSystem is required in engine");
		return false;
	}
	
	iasys->AddListener(l);
	
	return true;
}

void InteractionListener::Uninitialize(Engine& e, Ref<InteractionListener, RefParent1<Engine>> l) {
	Ref<InteractionSystem> iasys = e.TryGet<InteractionSystem>();
	if (!iasys) {
		LOG("InteractionListener::Uninitialize: error: InteractionSystem is required in engine");
		return;
	}
	
	iasys->RemoveListener(l);
}

bool InteractionListener::IsEnabled() const {
	ComponentBase* cb = CastPtr<ComponentBase>(this);
	if(cb)
		return cb->GetEntity()->IsEnabled();
	
	return true;
}





bool InteractionSystem::Initialize() {
	
	if (1) {
		fake_spatial_interaction_manager.Create();
		spatial_interaction_manager = &*fake_spatial_interaction_manager;
		BindEventHandlers();
		
		if (!fake_spatial_interaction_manager->Initialize(*this))
			return false;
	}
	
    return true;
}


void InteractionSystem::Uninitialize() {
	
	if (spatial_interaction_manager) {
	    ReleaseEventHandlers();
	    spatial_interaction_manager = 0;
	    
	    fake_spatial_interaction_manager.Clear();
	}
}

bool InteractionSystem::Arg(String key, Object value) {
	
	if (key == "log") {
		debug_log = (String)value == "debug";
	}
	
	if (key == "env") {
		env_name = value;
	}
	
	if (key == "hmd") {
		if ((String)value == "state")
			use_state_hmd = true;
	}
	
	return true;
}

void InteractionSystem::Update(double dt) {
	
	if (fake_spatial_interaction_manager)
		fake_spatial_interaction_manager->Update(dt);
	
	if (!spatial_interaction_manager) {
		TODO
	    /*spatial_interaction_manager = PlayerInteractionManager::GetForCurrentView();
	    if (spatial_interaction_manager)
			BindEventHandlers();*/
	}
}

void InteractionSystem::BindEventHandlers() {
	ASSERT(spatial_interaction_manager);
	InteractionManager* s = spatial_interaction_manager;
	
    s->WhenSourceDetected.Add(THISBACK(HandleSourceDetected));
    s->WhenSourcePressed.Add(THISBACK(HandleSourcePressed));
    s->WhenSourceUpdated.Add(THISBACK(HandleSourceUpdated));
    s->WhenSourceReleased.Add(THISBACK(HandleSourceReleased));
    s->WhenSourceLost.Add(THISBACK(HandleSourceLost));
    
}

void InteractionSystem::ReleaseEventHandlers() {
    ASSERT(spatial_interaction_manager);
	InteractionManager* s = spatial_interaction_manager;

    s->WhenSourceLost.RemoveThis(this);
    s->WhenSourceReleased.RemoveThis(this);
    s->WhenSourceUpdated.RemoveThis(this);
    s->WhenSourcePressed.RemoveThis(this);
    s->WhenSourceDetected.RemoveThis(this);
}

void InteractionSystem::HandleSourceDetected(const InteractionManager&, const CtrlEvent& e) {
    for (auto& listener : interaction_listeners) {
        if (listener->IsEnabled())
			listener->OnControllerDetected(e);
    }
}


void InteractionSystem::HandleSourceLost(const InteractionManager&, const CtrlEvent& e) {
    for (auto& listener : interaction_listeners) {
        if (listener->IsEnabled())
			listener->OnControllerLost(e);
    }
}


void InteractionSystem::HandleSourcePressed(const InteractionManager&, const CtrlEvent& e) {
    for (auto& listener : interaction_listeners) {
        if (listener->IsEnabled())
			listener->OnControllerPressed(e);
    }
}


void InteractionSystem::HandleSourceUpdated(const InteractionManager&, const CtrlEvent& e)
{
    for (auto& listener : interaction_listeners) {
        if (listener->IsEnabled())
			listener->OnControllerUpdated(e);
    }
}


void InteractionSystem::HandleSourceReleased(const InteractionManager&, const CtrlEvent& e)
{
    for (auto& listener : interaction_listeners) {
        if (listener->IsEnabled())
			listener->OnControllerReleased(e);
    }
}










/*bool FakeControllerSource::GetLocation(float* matrix4x4) const {
	
}*/

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
	
	hand_velocity = vec3(0, 0.1, 0.1);
	hand_angular_velocity = vec3(0.1, 0.1, 0);
	
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
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_CONTROLLER_DETECTED;
	
	WhenSourceDetected(*this, ev);
}

void FakeSpatialInteractionManager::UpdateState() {
	ASSERT(state);
	
	if (sys->use_state_hmd) {
		UpdateStateHmd();
	}
	else {
		UpdateStateKeyboard();
	}
}

void FakeSpatialInteractionManager::UpdateStateHmd() {
	#if 1
	TransformMatrix& cm = state->Set<TransformMatrix>(HMD_CAMERA);
	Look(cm);
	#elif 0
	StereoMatrix& st = state->Set<StereoMatrix>(HMD_VIEW_STEREO);
	Look(st);
	#else
	Quaternion& orient = state->Set<Quaternion>(HMD_ORIENTATION);
	Look(orient.data);
	#endif
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
	
	
	bool fwd   = data['W'];
	bool left  = data['A'];
	bool down  = data['S'];
	bool right = data['D'];
	
	float step = last_dt * 1.5;
	
	if (fwd) {
		Move(vec3(0,0,1), step);
	}
	if (left) {
		Move(vec3(-1,0,0), step);
	}
	if (down) {
		Move(vec3(0,0,-1), step);
	}
	if (right) {
		Move(vec3(+1,0,0), step);
	}
	
	static const int assign[ControllerProperties::BUTTON_COUNT] = {
		'F',
		'T',
		'H',
		'G',
		
		'K',
		'J',
		'L',
		'I',
		
		'U',
		'7',
		'O',
		'9',
		
		'1',
		'2',
		'3',
	};
	
	for(int i = 0; i < ControllerProperties::BUTTON_COUNT; i++) {
		int key = assign[i];
		bool pushed = data[key] && !prev[key];
		bool released = !data[key] && prev[key];
		
		if (pushed)
			Pressed((ControllerProperties::Button)i);
		
		if (released)
			Released((ControllerProperties::Button)i);
		
	}
	
	prev = data;
	
}

void FakeSpatialInteractionManager::Pressed(ControllerProperties::Button b) {
	ctrl_state.props.pressed[(int)b] = true;
	
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_PRESSED;
	ev.value = (int)b;
	
	WhenSourcePressed(*this, ev);
}

void FakeSpatialInteractionManager::Released(ControllerProperties::Button b) {
	ctrl_state.props.pressed[(int)b] = false;
	
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_RELEASED;
	ev.value = (int)b;
	
	WhenSourceReleased(*this, ev);
}









void FakeSpatialInteractionManager::Look(const TransformMatrix& tm) {
	this->trans = tm;
	
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = Point(0,0);
	ev.trans = &trans;
	
	if (sys->debug_log) {
		mat4 m = ToMat4(trans.orientation);
		vec4 dir = vec4(0,0,1,1) * m;
		direction_to_yaw_pitch(dir.Splice(), yaw, pitch);
		
		LOG("FakeSpatialInteractionManager::Look: orientation: " << trans.orientation.ToString() <<
			", angle: " << yaw << ", angle1: " << pitch);
	}
	
	WhenSourceUpdated(*this, ev);
}

/*void FakeSpatialInteractionManager::Look(quat orient) {
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = Point(0,0);
	ev.spatial = &ev3d;
	
	ev3d.use_lookat = false;
	COPY4(ev3d.orient, orient.data);
	
	mat4 m = ToMat4(orient);
	vec4 dir = vec4(0,0,1,1) * m;
	direction_to_yaw_pitch(dir.Splice(), yaw, pitch);
	
	if (sys->debug_log) {
		LOG("FakeSpatialInteractionManager::Look: orientation: " << orient.ToString() <<
			", angle: " << yaw << ", angle1: " << pitch);
	}
	
	WhenSourceUpdated(*this, ev);
}

void FakeSpatialInteractionManager::Look(const StereoMatrix& st) {
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = Point(0,0);
	ev.spatial = &ev3d;
	
	ev3d.use_view = true;
	COPY4x4(ev3d.l_proj, st.proj[0]);
	COPY4x4(ev3d.r_proj, st.proj[1]);
	COPY4x4(ev3d.l_view, st.view[0]);
	COPY4x4(ev3d.r_view, st.view[1]);
}*/

void FakeSpatialInteractionManager::Look(Point mouse_diff) {
	CtrlEvent ev;
	ev.state = &ctrl_state;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = mouse_diff; // extra
	ev.trans = &trans;
	
	double prev_yaw = yaw;
	double prev_pitch = pitch;
	
	double rot_speed = 0.05 / (2*M_PI);
	double yaw_change = mouse_diff.x * rot_speed;
	double pitch_change = mouse_diff.y * rot_speed;
	yaw += yaw_change;
	pitch += pitch_change;
	
	vec3 prev_head_direction;
	for(int i = 0; i < 3; i++) prev_head_direction[i] = av[i].GetMean();
	
	head_direction = vec3(
		 sin(pitch) * sin(yaw),
		 cos(pitch),
		-sin(pitch) * cos(yaw));
	
	for(int i = 0; i < 3; i++) av[i].Add(head_direction[i]);
	
	trans.mode = TransformMatrix::MODE_LOOKAT;
	trans.direction = head_direction;
	trans.position = vec3(0,0,0);
	trans.up = vec3(0,1,0);
	
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

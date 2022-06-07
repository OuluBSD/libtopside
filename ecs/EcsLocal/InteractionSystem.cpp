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
        listener->OnControllerDetected(e);
    }
}


void InteractionSystem::HandleSourceLost(const InteractionManager&, const CtrlEvent& e) {
    for (auto& listener : interaction_listeners) {
        listener->OnControllerLost(e);
    }
}


void InteractionSystem::HandleSourcePressed(const InteractionManager&, const CtrlEvent& e) {
    for (auto& listener : interaction_listeners) {
        listener->OnControllerPressed(e);
    }
}


void InteractionSystem::HandleSourceUpdated(const InteractionManager&, const CtrlEvent& e)
{
    for (auto& listener : interaction_listeners) {
        listener->OnControllerUpdated(e);
    }
}


void InteractionSystem::HandleSourceReleased(const InteractionManager&, const CtrlEvent& e)
{
    for (auto& listener : interaction_listeners) {
        listener->OnControllerReleased(e);
    }
}












bool FakeSpatialInteractionManager::Initialize(InteractionSystem& sys) {
	this->sys = &sys;
	
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
	ev.type = EVENT_HOLO_CONTROLLER_DETECTED;
	
	WhenSourceDetected(*this, ev);
}

void FakeSpatialInteractionManager::UpdateState() {
	ASSERT(state);
	
	FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
	FboKbd::KeyVec& prev = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED_PREVIOUS);
	
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
}

void FakeSpatialInteractionManager::Look(Point mouse_diff) {
	CtrlEvent ev;
	ev.type = EVENT_HOLO_LOOK;
	ev.pt = mouse_diff; // extra
	
	double rot_speed = 0.05 / (2*M_PI);
	yaw += mouse_diff.x * rot_speed;
	pitch += mouse_diff.y * rot_speed;
	
	head_direction = vec3(
		 sin(pitch) * sin(yaw),
		 cos(pitch),
		-sin(pitch) * cos(yaw));
	
	COPY3(ev.direction, head_direction);
	
	if (sys->debug_log) {
		LOG("FakeSpatialInteractionManager::Look: dx: " << mouse_diff.x << ", dy: " << mouse_diff.y <<
			", rot: " << head_direction[0] << ", " << head_direction[1] << ", " << head_direction[2] <<
			", angle: " << yaw << ", angle1: " << pitch);
	}
	
	WhenSourceUpdated(*this, ev);
}

void FakeSpatialInteractionManager::Move(vec3 rel_dir, float step) {
	CtrlEvent ev;
	ev.type = EVENT_HOLO_MOVE_FAR_RELATIVE;
	vec3 dir = head_direction;
	
	// remove y component
	dir[1] = 0;
	
	float straight = rel_dir[2];
	float sideways = rel_dir[0];
	
	if (straight) {
		vec3 pos_diff = dir * step * straight;
		COPY3(ev.position, pos_diff);
	}
	if (sideways) {
		vec3 s = dir * step * sideways;
		vec3 pos_diff(-s[2], 0, +s[0]);
		COPY3(ev.position, pos_diff);
	}
	
	WhenSourceUpdated(*this, ev);
}

NAMESPACE_ECS_END

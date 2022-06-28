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
	
	if (use_state_hmd) {
		vr_spatial_interaction_manager.Create();
		spatial_interaction_manager = &*vr_spatial_interaction_manager;
		BindEventHandlers();
		
		if (!vr_spatial_interaction_manager->Initialize(*this))
			return false;
	}
	else {
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
	    
	    vr_spatial_interaction_manager.Clear();
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
	
	if (key == "calibration") {
		is_calibration = (String)value == "true";
	}
	
	return true;
}

void InteractionSystem::Update(double dt) {
	
	if (fake_spatial_interaction_manager)
		fake_spatial_interaction_manager->Update(dt);
	
	if (vr_spatial_interaction_manager)
		vr_spatial_interaction_manager->Update(dt);
	
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










NAMESPACE_ECS_END

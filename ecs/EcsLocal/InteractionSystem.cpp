#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool PlayerInteractionSystem::Initialize() {
	//if (!HolographicScopeBinder::Initialize())
	//	return false;
	
    return true;
}


void PlayerInteractionSystem::Uninitialize() {
    ReleaseEventHandlers();
    //spatial_interaction_manager = nullptr;
}

void PlayerInteractionSystem::Update(double dt) {
	
	TODO
	/*if (!spatial_interaction_manager) {
	    spatial_interaction_manager = PlayerInteractionManager::GetForCurrentView();
	    if (spatial_interaction_manager)
			BindEventHandlers();
	}*/
	
}

void PlayerInteractionSystem::BindEventHandlers() {
	//ASSERT(spatial_interaction_manager);

	TODO
    /*s->spatial_interaction_manager.WhenSourceDetected.Add(THISBACK(HandleSourceDetected));
    s->spatial_interaction_manager.WhenSourcePressed.Add(THISBACK(HandleSourcePressed));
    s->spatial_interaction_manager.WhenSourceUpdated.Add(THISBACK(HandleSourceUpdated));
    s->spatial_interaction_manager.WhenSourceReleased.Add(THISBACK(HandleSourceReleased));
    s->spatial_interaction_manager.WhenSourceLost.Add(THISBACK(HandleSourceLost));*/
    
}

void PlayerInteractionSystem::ReleaseEventHandlers() {
    //ASSERT(spatial_interaction_manager);

	TODO
    /*s->spatial_interaction_manager.WhenSourceLost.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceReleased.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceUpdated.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourcePressed.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceDetected.RemoveThis(this);*/
}

void PlayerInteractionSystem::HandleSourceDetected(const ControllerEventArgs& args) {
    for (auto& listener : player_interaction_listeners) {
        listener->OnControllerDetected(args);
    }
}


void PlayerInteractionSystem::HandleSourceLost(const ControllerEventArgs& args) {
    for (auto& listener : player_interaction_listeners) {
        listener->OnControllerLost(args);
    }
}


void PlayerInteractionSystem::HandleSourcePressed(const ControllerEventArgs& args) {
    for (auto& listener : player_interaction_listeners) {
        listener->OnControllerPressed(args);
    }
}


void PlayerInteractionSystem::HandleSourceUpdated(const ControllerEventArgs& args)
{
    for (auto& listener : player_interaction_listeners) {
        listener->OnControllerUpdated(args);
    }
}


void PlayerInteractionSystem::HandleSourceReleased(const ControllerEventArgs& args)
{
    for (auto& listener : player_interaction_listeners) {
        listener->OnControllerReleased(args);
    }
}


NAMESPACE_ECS_END

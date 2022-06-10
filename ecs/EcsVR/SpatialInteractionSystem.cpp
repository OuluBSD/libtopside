#include "EcsVR.h"


NAMESPACE_ECS_BEGIN



bool SpatialInteractionSystem::Initialize()
{
	if (!HolographicScopeBinder::Initialize())
		return false;
	
    return true;
}


void SpatialInteractionSystem::Uninitialize()
{
    ReleaseEventHandlers();
    //spatial_interaction_manager = nullptr;
}

void SpatialInteractionSystem::Update(double dt) {
	
	/*if (!spatial_interaction_manager) {
	    spatial_interaction_manager = SpatialInteractionManager::GetForCurrentView();
	    if (spatial_interaction_manager)
			BindEventHandlers();
	}*/
	
}

void SpatialInteractionSystem::BindEventHandlers()
{
	//ASSERT(spatial_interaction_manager);

    s->spatial_interaction_manager.WhenSourceDetected.Add(THISBACK(HandleSourceDetected));
    s->spatial_interaction_manager.WhenSourcePressed.Add(THISBACK(HandleSourcePressed));
    s->spatial_interaction_manager.WhenSourceUpdated.Add(THISBACK(HandleSourceUpdated));
    s->spatial_interaction_manager.WhenSourceReleased.Add(THISBACK(HandleSourceReleased));
    s->spatial_interaction_manager.WhenSourceLost.Add(THISBACK(HandleSourceLost));
    
}

void SpatialInteractionSystem::ReleaseEventHandlers()
{
    //ASSERT(spatial_interaction_manager);

    s->spatial_interaction_manager.WhenSourceLost.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceReleased.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceUpdated.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourcePressed.RemoveThis(this);
    s->spatial_interaction_manager.WhenSourceDetected.RemoveThis(this);
}

void SpatialInteractionSystem::HandleSourceDetected(
    const SpatialInteractionManager& sender,
    const SpatialSourceEventArgs& args)
{
    for (auto& listener : spatial_interaction_listeners)
    {
        listener->OnControllerDetected(args);
    }
}


void SpatialInteractionSystem::HandleSourceLost(
    const SpatialInteractionManager& /*sender*/,
    const SpatialSourceEventArgs& args)
{
    for (auto& listener : spatial_interaction_listeners)
    {
        listener->OnControllerLost(args);
    }
}


void SpatialInteractionSystem::HandleSourcePressed(
    const SpatialInteractionManager& /*sender*/,
    const SpatialSourceEventArgs& args)
{
    for (auto& listener : spatial_interaction_listeners)
    {
        listener->OnControllerPressed(args);
    }
}


void SpatialInteractionSystem::HandleSourceUpdated(
    const SpatialInteractionManager& /*sender*/,
    const SpatialSourceEventArgs& args)
{
    for (auto& listener : spatial_interaction_listeners)
    {
        listener->OnControllerUpdated(args);
    }
}


void SpatialInteractionSystem::HandleSourceReleased(
    const SpatialInteractionManager& /*sender*/,
    const SpatialSourceEventArgs& args)
{
    for (auto& listener : spatial_interaction_listeners)
    {
        listener->OnControllerReleased(args);
    }
}


NAMESPACE_ECS_END

#include "EcsVR.h"


NAMESPACE_ECS_BEGIN



bool SpatialInteractionSystem::Initialize()
{
    TODO
    /*spatial_interaction_manager = SpatialInteractionManager::GetForCurrentView();
    BindEventHandlers();*/
    return true;
}


void SpatialInteractionSystem::Uninitialize()
{
    TODO
    /*ReleaseEventHandlers();
    spatial_interaction_manager = nullptr;*/
}

#if 0

void SpatialInteractionSystem::BindEventHandlers()
{
	fail_fast_if(spatial_interaction_manager == nullptr);

    source_tokens[Detected] = spatial_interaction_manager.SourceDetected(
        std::bind(&SpatialInteractionSystem::HandleSourceDetected, this, _1, _2));

    source_tokens[Pressed] = spatial_interaction_manager.SourcePressed(
        std::bind(&SpatialInteractionSystem::HandleSourcePressed, this, _1, _2));

    source_tokens[Updated] = spatial_interaction_manager.SourceUpdated(
        std::bind(&SpatialInteractionSystem::HandleSourceUpdated, this, _1, _2));

    source_tokens[Released] = spatial_interaction_manager.SourceReleased(
        std::bind(&SpatialInteractionSystem::HandleSourceReleased, this, _1, _2));

    source_tokens[Lost] = spatial_interaction_manager.SourceLost(
        std::bind(&SpatialInteractionSystem::HandleSourceLost, this, _1, _2));
}


void SpatialInteractionSystem::ReleaseEventHandlers()
{
    fail_fast_if(spatial_interaction_manager == nullptr);

    spatial_interaction_manager.SourceLost(source_tokens[Lost]);
    spatial_interaction_manager.SourceReleased(source_tokens[Released]);
    spatial_interaction_manager.SourceUpdated(source_tokens[Updated]);
    spatial_interaction_manager.SourcePressed(source_tokens[Pressed]);
    spatial_interaction_manager.SourceDetected(source_tokens[Detected]);
}

void SpatialInteractionSystem::HandleSourceDetected(
    const SpatialInteractionManager& sender,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceDetected(args);
    }
}


void SpatialInteractionSystem::HandleSourceLost(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceLost(args);
    }
}


void SpatialInteractionSystem::HandleSourcePressed(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourcePressed(args);
    }
}


void SpatialInteractionSystem::HandleSourceUpdated(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceUpdated(args);
    }
}


void SpatialInteractionSystem::HandleSourceReleased(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceReleased(args);
    }
}

#endif


NAMESPACE_ECS_END

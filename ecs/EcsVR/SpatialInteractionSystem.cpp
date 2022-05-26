#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


template <class Holo>
void SpatialInteractionSystemT<Holo>::Initialize()
{
    spatial_interaction_manager = SpatialInteractionManager::GetForCurrentView();
    BindEventHandlers();
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::Uninitialize()
{
    ReleaseEventHandlers();
    spatial_interaction_manager = nullptr;
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::BindEventHandlers()
{
	TODO
	
    /*fail_fast_if(spatial_interaction_manager == nullptr);

    source_tokens[Detected] = spatial_interaction_manager.SourceDetected(
        std::bind(&SpatialInteractionSystemT<Holo>::HandleSourceDetected, this, _1, _2));

    source_tokens[Pressed] = spatial_interaction_manager.SourcePressed(
        std::bind(&SpatialInteractionSystemT<Holo>::HandleSourcePressed, this, _1, _2));

    source_tokens[Updated] = spatial_interaction_manager.SourceUpdated(
        std::bind(&SpatialInteractionSystemT<Holo>::HandleSourceUpdated, this, _1, _2));

    source_tokens[Released] = spatial_interaction_manager.SourceReleased(
        std::bind(&SpatialInteractionSystemT<Holo>::HandleSourceReleased, this, _1, _2));

    source_tokens[Lost] = spatial_interaction_manager.SourceLost(
        std::bind(&SpatialInteractionSystemT<Holo>::HandleSourceLost, this, _1, _2));*/
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::ReleaseEventHandlers()
{
    fail_fast_if(spatial_interaction_manager == nullptr);

    spatial_interaction_manager.SourceLost(source_tokens[Lost]);
    spatial_interaction_manager.SourceReleased(source_tokens[Released]);
    spatial_interaction_manager.SourceUpdated(source_tokens[Updated]);
    spatial_interaction_manager.SourcePressed(source_tokens[Pressed]);
    spatial_interaction_manager.SourceDetected(source_tokens[Detected]);
}

#if 0

template <class Holo>
void SpatialInteractionSystemT<Holo>::HandleSourceDetected(
    const SpatialInteractionManager& sender,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceDetected(args);
    }
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::HandleSourceLost(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceLost(args);
    }
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::HandleSourcePressed(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourcePressed(args);
    }
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::HandleSourceUpdated(
    const SpatialInteractionManager& /*sender*/,
    const SpatialInteractionSourceEventArgs& args)
{
    for (const auto& listener : spatial_interaction_listeners.PurgeAndGetListeners())
    {
        listener->OnSourceUpdated(args);
    }
}

template <class Holo>
void SpatialInteractionSystemT<Holo>::HandleSourceReleased(
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

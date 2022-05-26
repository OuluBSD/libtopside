#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


template <class Holo>
HolographicSceneT<Holo>::HolographicSceneT(
    Engine& core,
    HoloSpace holospace) :
    Ecs::System<HolographicSceneT<Holo>>(core),
    holospace(std::move(holospace))
{}

template <class Holo>
void HolographicSceneT<Holo>::Initialize()
{
	TODO // also override funcs
    /*stage_frame_of_reference = SpatialStageFrameOfReference::Current();

    // Create a fallback frame of reference 1.5 meters under the HMD when we start-up
    stationary_frame_of_reference = SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(
        vec3{0.0f, -1.5f, 0.0f});

    spatial_stage_current_changed = SpatialStageFrameOfReference::CurrentChanged(
        std::bind(&HolographicSceneT<Holo>::OnCurrentStageChanged, this));*/
}

template <class Holo>
void HolographicSceneT<Holo>::Update(double)
{
    current_frame = holospace.CreateNextFrame();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicSpaceCreateNextFrame);
}

template <class Holo>
void HolographicSceneT<Holo>::Uninitialize()
{
    SpatialStageFrameOfReference::CurrentChanged(spatial_stage_current_changed);

    current_frame = nullptr;
    stationary_frame_of_reference = nullptr;
    stage_frame_of_reference = nullptr;
}

template <class Holo>
void HolographicSceneT<Holo>::UpdateCurrentPrediction()
{
    current_frame.UpdateCurrentPrediction();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicFrameUpdatePrediction);
}

#if 0
template <class Holo>
void HolographicSceneT<Holo>::OnCurrentStageChanged()
{
    Mutex::Lock lock(this->lock);
    stage_frame_of_reference = SpatialStageFrameOfReference::Current();
}

template <class Holo>
void HolographicSceneT<Holo>::OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason)
{
    const HolographicFramePrediction prediction = current_frame.CurrentPrediction();
    const SpatialCoordinateSystem coord_system = WorldCoordinateSystem();

    for (const auto& listener : prediction_update_listeners.PurgeAndGetListeners())
    {
        listener->OnPredictionUpdated(reason, coord_system, prediction);
    }
}
#endif

template <class Holo>
void HolographicSceneT<Holo>::AddPredictionUpdateListener(Shared<IPredictionUpdateListener> listener)
{
    prediction_update_listeners.Add(std::move(listener));
}

template <class Holo>
void HolographicSceneT<Holo>::RemovePredictionUpdateListener(Shared<IPredictionUpdateListener> listener)
{
    prediction_update_listeners.Remove(std::move(listener));
}

template <class Holo>
typename Holo::SpatialCoordinateSystem
HolographicSceneT<Holo>::WorldCoordinateSystem() const
{
    Mutex::Lock lock(this->lock);
    if (stage_frame_of_reference)
    {
        return stage_frame_of_reference.CoordinateSystem();
    }
    else
    {
        return stationary_frame_of_reference.CoordinateSystem();
    }
}

template <class Holo>
PerceptionTimestamp HolographicSceneT<Holo>::CurrentTimestamp() const
{
    return CurrentFrame().CurrentPrediction().Timestamp();
}

template <class Holo>
typename Holo::HoloFrame
HolographicSceneT<Holo>::CurrentFrame() const
{
    fail_fast_if(current_frame == nullptr);
    return current_frame;
}

template <class Holo>
typename Holo::HoloSpace HolographicSceneT<Holo>::HolographicSpace() const
{
    fail_fast_if(holospace == nullptr);
    return holospace;
}


NAMESPACE_ECS_END

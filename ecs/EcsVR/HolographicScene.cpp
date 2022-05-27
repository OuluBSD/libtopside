#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


/*HolographicScene::HolographicScene(
    Engine& core,
    HoloSpace holospace) :
    Ecs::System<HolographicScene>(core),
    holospace(std::move(holospace))
{}*/

bool HolographicScene::Initialize()
{
	TODO // also override funcs
    /*stage_frame_of_reference = SpatialStageFrameOfReference::Current();

    // Create a fallback frame of reference 1.5 meters under the HMD when we start-up
    stationary_frame_of_reference = SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(
        vec3{0.0f, -1.5f, 0.0f});

    spatial_stage_current_changed = SpatialStageFrameOfReference::CurrentChanged(
        std::bind(&HolographicScene::OnCurrentStageChanged, this));*/
}

void HolographicScene::Update(double)
{
	TODO
    /*current_frame = holospace.CreateNextFrame();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicSpaceCreateNextFrame);*/
}

void HolographicScene::Uninitialize()
{
	TODO
    /*SpatialStageFrameOfReference::CurrentChanged(spatial_stage_current_changed);

    current_frame = nullptr;
    stationary_frame_of_reference = nullptr;
    stage_frame_of_reference = nullptr;*/
}

void HolographicScene::UpdateCurrentPrediction()
{
	TODO
    /*current_frame.UpdateCurrentPrediction();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicFrameUpdatePrediction);*/
}

#if 0
void HolographicScene::OnCurrentStageChanged()
{
    Mutex::Lock lock(this->lock);
    stage_frame_of_reference = SpatialStageFrameOfReference::Current();
}

void HolographicScene::OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason)
{
    const HolographicFramePrediction prediction = current_frame.CurrentPrediction();
    const SpatialCoordinateSystem coord_system = WorldCoordinateSystem();

    for (const auto& listener : prediction_update_listeners.PurgeAndGetListeners())
    {
        listener->OnPredictionUpdated(reason, coord_system, prediction);
    }
}

void HolographicScene::AddPredictionUpdateListener(Shared<IPredictionUpdateListener> listener)
{
    prediction_update_listeners.Add(std::move(listener));
}

void HolographicScene::RemovePredictionUpdateListener(Shared<IPredictionUpdateListener> listener)
{
    prediction_update_listeners.Remove(std::move(listener));
}

typename Holo::SpatialCoordinateSystem
HolographicScene::WorldCoordinateSystem() const
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

PerceptionTimestamp HolographicScene::CurrentTimestamp() const
{
    return CurrentFrame().CurrentPrediction().Timestamp();
}

typename Holo::HoloFrame
HolographicScene::CurrentFrame() const
{
    fail_fast_if(current_frame == nullptr);
    return current_frame;
}

typename Holo::HoloSpace HolographicScene::HolographicSpace() const
{
    fail_fast_if(holospace == nullptr);
    return holospace;
}

#endif

NAMESPACE_ECS_END

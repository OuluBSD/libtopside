#include "WinLib.h"


NAMESPACE_PARALLEL_BEGIN


HolographicScene::HolographicScene(
    Engine& core,
    HoloSpace holospace) :
    System(core),
    holospace(std::move(holospace))
{}

void HolographicScene::Initialize()
{
    stage_frame_of_reference = SpatialStageFrameOfReference::Current();

    // Create a fallback frame of reference 1.5 meters under the HMD when we start-up
    stationary_frame_of_reference = SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(
        vec3{0.0f, -1.5f, 0.0f});

    spatial_stage_current_changed = SpatialStageFrameOfReference::CurrentChanged(
        std::bind(&HolographicScene::OnCurrentStageChanged, this));
}

void HolographicScene::Update(double)
{
    current_frame = holospace.CreateNextFrame();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicSpaceCreateNextFrame);
}

void HolographicScene::Uninitialize()
{
    SpatialStageFrameOfReference::CurrentChanged(spatial_stage_current_changed);

    current_frame = nullptr;
    stationary_frame_of_reference = nullptr;
    stage_frame_of_reference = nullptr;
}

void HolographicScene::UpdateCurrentPrediction()
{
    current_frame.UpdateCurrentPrediction();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicFrameUpdatePrediction);
}

void HolographicScene::OnCurrentStageChanged()
{
    std::unique_lock<std::shared_mutex> lock(lock);
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

SpatialCoordinateSystem HolographicScene::WorldCoordinateSystem() const
{
    std::shared_lock<std::shared_mutex> lock(lock);
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

HolographicFrame HolographicScene::CurrentFrame() const
{
    fail_fast_if(current_frame == nullptr);
    return current_frame;
}

HolographicSpace HolographicScene::HolographicSpace() const
{
    fail_fast_if(holospace == nullptr);
    return holospace;
}


NAMESPACE_PARALLEL_END

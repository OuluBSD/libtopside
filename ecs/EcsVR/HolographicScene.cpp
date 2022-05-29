#include "EcsVR.h"


NAMESPACE_ECS_BEGIN


/*HolographicScene::HolographicScene(
    Engine& core,
    HolographicSpace holospace) :
    Ecs::System<HolographicScene>(core),
    holospace(std::move(holospace))
{}*/

bool HolographicScene::Initialize()
{
	vr_room_anchor = GetActiveVirtualRoomAnchor();
	
    // Create a fallback frame of reference 1.5 meters under the HMD when we start-up
    stationary_frame_of_reference =
		GetActiveSpatialLocator()
			.GetRelative(vec3{0.0f, -1.5f, 0.0f});
	
	VirtualRoomAnchor::WhenActiveChanged << THISBACK(OnCurrentStageChanged);
	
	return true;
}

void HolographicScene::Update(double dt)
{
    current_frame = holospace.CreateNextFrame();

    OnPredictionChanged(PredictionUpdateReason::HolographicSpaceCreateNextFrame);
}

void HolographicScene::Uninitialize()
{
	TODO
    /*VirtualRoomAnchor::WhenActiveChanged.RemoveThis(this); //SpatialStageFrameOfReference::CurrentChanged(spatial_stage_current_changed);

    current_frame = nullptr;
    stationary_frame_of_reference = nullptr;
    vr_room_anchor = nullptr;*/
}

void HolographicScene::UpdateCurrentPrediction()
{
	current_frame.UpdateCurrentPrediction();

    OnPredictionChanged(PredictionUpdateReason::HolographicFrameUpdatePrediction);
}

void HolographicScene::OnCurrentStageChanged()
{
    Mutex::Lock lock(this->lock);
    vr_room_anchor = GetActiveVirtualRoomAnchor();
}

void HolographicScene::OnPredictionChanged(PredictionUpdateReason reason)
{
    const HolographicFramePrediction& prediction = current_frame.GetCurrentPrediction();
    const SpatialCoordinateSystem& coord_system = GetWorldCoordinateSystem();

    for (PredictionUpdateListenerRef& listener : prediction_update_listeners) {
        listener->OnPredictionUpdated(reason, coord_system, prediction);
    }
}

void HolographicScene::AddPredictionUpdateListener(PredictionUpdateListenerRef listener)
{
    prediction_update_listeners.Add(listener);
}

void HolographicScene::RemovePredictionUpdateListener(PredictionUpdateListenerRef listener)
{
    prediction_update_listeners.Remove(listener);
}

SpatialCoordinateSystem& HolographicScene::GetWorldCoordinateSystem() const
{
    Mutex::Lock lock(this->lock);
    if (vr_room_anchor)
    {
        return vr_room_anchor->GetCoordinateSystem();
    }
    else
    {
        return stationary_frame_of_reference.GetCoordinateSystem();
    }
}

#if 0

PerceptionTimestamp HolographicScene::CurrentTimestamp() const
{
    return CurrentFrame().CurrentPrediction().Timestamp();
}

typename Holo::HolographicFrame
HolographicScene::CurrentFrame() const
{
    fail_fast_if(current_frame == nullptr);
    return current_frame;
}

#endif

NAMESPACE_ECS_END

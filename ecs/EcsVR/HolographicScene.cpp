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
	vr_room_anchor = GetActiveVirtualRoomAnchor();
	
    // Create a fallback frame of reference 1.5 meters under the HMD when we start-up
    stationary_frame_of_reference =
		GetActiveSpatialDynamicAnchor()
			.GetRelative(vec3{0.0f, -1.5f, 0.0f});
	
	VirtualRoomAnchor::WhenActiveChanged << THISBACK(OnCurrentStageChanged);
	
	return true;
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
    /*VirtualRoomAnchor::WhenActiveChanged.RemoveThis(this); //SpatialStageFrameOfReference::CurrentChanged(spatial_stage_current_changed);

    current_frame = nullptr;
    stationary_frame_of_reference = nullptr;
    vr_room_anchor = nullptr;*/
}

void HolographicScene::UpdateCurrentPrediction()
{
	TODO
    /*current_frame.UpdateCurrentPrediction();

    OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicFrameUpdatePrediction);*/
}

void HolographicScene::OnCurrentStageChanged()
{
    Mutex::Lock lock(this->lock);
    vr_room_anchor = GetActiveVirtualRoomAnchor();
}

#if 0

void HolographicScene::OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason)
{
    const HolographicFramePrediction prediction = current_frame.CurrentPrediction();
    const SpatialCoordinateSystem coord_system = WorldCoordinateSystem();

    for (const auto& listener : prediction_update_listeners.PurgeAndGetListeners())
    {
        listener->OnPredictionUpdated(reason, coord_system, prediction);
    }
}

#endif

void HolographicScene::AddPredictionUpdateListener(PredictionUpdateListenerRef listener)
{
    prediction_update_listeners.Add(listener);
}

void HolographicScene::RemovePredictionUpdateListener(PredictionUpdateListenerRef listener)
{
    prediction_update_listeners.Remove(listener);
}

#if 0

typename Holo::SpatialCoordinateSystem
HolographicScene::WorldCoordinateSystem() const
{
    Mutex::Lock lock(this->lock);
    if (vr_room_anchor)
    {
        return vr_room_anchor.CoordinateSystem();
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

#endif

NAMESPACE_ECS_END

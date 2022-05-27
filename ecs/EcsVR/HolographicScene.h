#pragma once


NAMESPACE_ECS_BEGIN


// PredictionUpdated event listener
template <class Holo>
struct IPredictionUpdateListenerT
{
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using HoloFramePred = typename Holo::HoloFramePred;
	
public:
    enum PredictionUpdateReason
    {
        HolographicSpaceCreateNextFrame,
        HolographicFrameUpdatePrediction,
    };

    virtual void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HoloFramePred& prediction) = 0;
    
};


// HolographicScene
// Maintains a list of our current state of Windows::Perception objects, ensuring the rest of the systems
// use the same coordinate system, timestamp, etc.
class HolographicScene : public Ecs::System<HolographicScene>
{
public:
	/*using HoloSpace = typename Holo::HoloSpace;
	using HoloFrame = typename Holo::HoloFrame;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using SpatialStageFrameOfReference = typename Holo::SpatialStageFrameOfReference;
	using SpatialStationaryFrameOfReference = typename Holo::SpatialStationaryFrameOfReference;
	using NativeEventToken = typename Holo::NativeEventToken;
	using IPredictionUpdateListener = IPredictionUpdateListenerT<Holo>;
	using PredictionUpdateReason = typename IPredictionUpdateListenerT<Holo>::PredictionUpdateReason;*/
	
	ECS_SYS_CTOR(HolographicScene)
	
    //HolographicScene(Ecs::Engine& core, HoloSpace holospace);

    /*HoloFrame CurrentFrame() const;
    HoloSpace HolographicSpace() const;

    SpatialCoordinateSystem WorldCoordinateSystem() const;
    PerceptionTimestamp CurrentTimestamp() const;*/

    void UpdateCurrentPrediction();

    /*void AddPredictionUpdateListener(Shared<IPredictionUpdateListener> listener);
    void RemovePredictionUpdateListener(Shared<IPredictionUpdateListener> listener);*/

protected:
    bool Initialize() override;
    void Update(double dt) override;
    void Uninitialize() override;

    /*void OnCurrentStageChanged();

    void OnPredictionChanged(PredictionUpdateReason reason);*/

private:
    mutable Mutex						lock;
    
    /*SpatialStageFrameOfReference		stage_frame_of_reference = 0;
    SpatialStationaryFrameOfReference	stationary_frame_of_reference = 0;
    NativeEventToken					spatial_stage_current_changed;

    HoloSpace							holospace;
    HoloFrame							current_frame;

    Array<Shared<IPredictionUpdateListener>>		prediction_update_listeners;*/
    
};


NAMESPACE_ECS_END

#pragma once


NAMESPACE_ECS_BEGIN


// PredictionUpdated event listener
struct PredictionUpdateListener : WeakRefScopeEnabler<PredictionUpdateListener, Engine>, RTTIBase
{
	RTTI_DECL0(PredictionUpdateListener)
	
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

using PredictionUpdateListenerRef = Ref<PredictionUpdateListener, RefParent1<Ecs::Engine>>;


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

    //HoloFrame CurrentFrame() const;
    
    const HoloSpace& GetHolographicSpace() const {return holospace;}
    HoloSpace& GetHolographicSpace() {return holospace;}

    /*SpatialCoordinateSystem WorldCoordinateSystem() const;
    PerceptionTimestamp CurrentTimestamp() const;*/

    void UpdateCurrentPrediction();

    void AddPredictionUpdateListener(PredictionUpdateListenerRef listener);
    void RemovePredictionUpdateListener(PredictionUpdateListenerRef listener);

protected:
    bool Initialize() override;
    void Update(double dt) override;
    void Uninitialize() override;

    void OnCurrentStageChanged();
	
    //void OnPredictionChanged(PredictionUpdateReason reason);

private:
    mutable Mutex						lock;
    
    VirtualRoomAnchor*					vr_room_anchor = 0;
    SpatialDynamicAnchor				stationary_frame_of_reference;
    
    //NativeEventToken					spatial_stage_current_changed;

    HoloSpace							holospace;
    //HoloFrame							current_frame;
	
	
    Array<PredictionUpdateListenerRef>	prediction_update_listeners;
    
};


NAMESPACE_ECS_END

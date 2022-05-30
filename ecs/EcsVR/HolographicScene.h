#pragma once


NAMESPACE_ECS_BEGIN


// PredictionUpdated event listener
struct PredictionUpdateListener : WeakRefScopeEnabler<PredictionUpdateListener, Engine>, RTTIBase
{
	RTTI_DECL0(PredictionUpdateListener)
	
public:

    virtual void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HolographicFramePrediction& prediction) = 0;
    
};

using PredictionUpdateListenerRef = Ref<PredictionUpdateListener, RefParent1<Ecs::Engine>>;


// HolographicScene
// Maintains a list of our current state of Windows::Perception objects, ensuring the rest of the systems
// use the same coordinate system, timestamp, etc.
class HolographicScene : public Ecs::System<HolographicScene>, public HolographicScopeBinder
{
public:
	/*using HolographicSpace = typename Holo::HolographicSpace;
	using HolographicFrame = typename Holo::HolographicFrame;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using SpatialStageFrameOfReference = typename Holo::SpatialStageFrameOfReference;
	using SpatialStationaryFrameOfReference = typename Holo::SpatialStationaryFrameOfReference;
	using NativeEventToken = typename Holo::NativeEventToken;
	using IPredictionUpdateListener = IPredictionUpdateListenerT<Holo>;
	using PredictionUpdateReason = typename IPredictionUpdateListenerT<Holo>::PredictionUpdateReason;*/
	
	ECS_SYS_CTOR(HolographicScene)
	
    //HolographicScene(Ecs::Engine& core, HolographicSpace holospace);

    /*const HolographicFrame& GetCurrentFrame() const {ASSERT(s); return s->current_frame;}
    HolographicFrame& GetCurrentFrame() {ASSERT(s); return s->current_frame;}
    
    const HolographicSpace& GetHolographicSpace() const {ASSERT(s); return s->holospace;}
    HolographicSpace& GetHolographicSpace() {ASSERT(s); return s->holospace;}*/

    SpatialCoordinateSystem& GetWorldCoordinateSystem() const;
    /*PerceptionTimestamp CurrentTimestamp() const;*/

    void UpdateCurrentPrediction();

    void AddPredictionUpdateListener(PredictionUpdateListenerRef listener);
    void RemovePredictionUpdateListener(PredictionUpdateListenerRef listener);

protected:
    bool Initialize() override;
    void Update(double dt) override;
    void Uninitialize() override;

    void OnCurrentStageChanged();
	
    void OnPredictionChanged(PredictionUpdateReason reason);

private:
    mutable Mutex						lock;
    
    SpatialStageFrameOfReference*		vr_room_anchor = 0;
    SpatialLocator						stationary_frame_of_reference;
    
    //NativeEventToken					spatial_stage_current_changed;
	
    /*HolographicSpace*					holospace = 0;
    HolographicFrame*					current_frame = 0;*/
	
	
    Array<PredictionUpdateListenerRef>	prediction_update_listeners;
    
};


NAMESPACE_ECS_END

#pragma once


NAMESPACE_ECS_BEGIN


struct MotionControllerComponent : Ecs::Component<MotionControllerComponent>
{
	/*using SpatialSourceHandedness = typename Holo::SpatialSourceHandedness;
	using SpatialSource = typename Holo::SpatialSource;
	using SpatialSourceLocation = typename Holo::SpatialSourceLocation;*/
	
	COPY_PANIC(MotionControllerComponent)
	
    bool IsSource(const SpatialSource& rhs) const;

    bool						attach_ctrl_model = false;
    SpatialSourceHandedness		req_hand { SpatialSourceHandedness::Unspecified };
    SpatialSource				source;
    SpatialSourceLocation		location;
    
};



// MotionControllerSystem
// This system manages events and behaviors specific to Motion Controllers
//
// You can use the MotionControllerComponent::req_hand to automatically update an Entity's Transform based on handedness
// i.e. Attach this entity to the Left or Right controller, and the MotionControllerSystem will automatically update the Transform
//
// You can also use the MotionControllerComponent::attach_ctrl_model to automatically attach the correct 3D model to the object
// so that the virtual controller will be rendered in the same position as the physical controller
class MotionControllerSystem :
    public System<MotionControllerSystem>,
    public PredictionUpdateListener,
    public SpatialInteractionListener
{
	/*using IPredictionUpdateListener = IPredictionUpdateListenerT<Holo>;
	using PredictionUpdateReason = typename IPredictionUpdateListenerT<Holo>::PredictionUpdateReason;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using HoloFramePred = typename Holo::HoloFramePred;
	using SpatialSourceEventArgs = typename Holo::SpatialSourceEventArgs;
	using SpatialSource = typename Holo::SpatialSource;*/
	
public:
	RTTI_DECL3(MotionControllerSystem, System<MotionControllerSystem>, PredictionUpdateListener, SpatialInteractionListener)
	ECS_SYS_CTOR(MotionControllerSystem)
	
protected:
    // System
    void Start() override;
    void Stop() override;

    // PredictionUpdateListener
    void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HoloFramePred& prediction) override;

    // ISpatialInteractionListener
    /*void OnSourceDetected(const SpatialSourceEventArgs& args) override;
    void OnSourceUpdated(const SpatialSourceEventArgs& args) override;
    void OnSourceLost(const SpatialSourceEventArgs& args) override;*/
    
private:
    //void RefreshComponentsForSource(const SpatialSource& source);
    
};


NAMESPACE_ECS_END


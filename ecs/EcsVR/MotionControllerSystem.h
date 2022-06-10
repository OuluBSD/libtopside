#pragma once


NAMESPACE_ECS_BEGIN


struct MotionControllerComponent : Ecs::Component<MotionControllerComponent>
{
	/*using SpatialSourceHandedness = typename Holo::SpatialSourceHandedness;
	using SpatialSource = typename Holo::SpatialSource;
	using SpatialSourceLocation = typename Holo::SpatialSourceLocation;*/
	
	COPY_PANIC(MotionControllerComponent)
	
	void Initialize() override;
	void Uninitialize() override;
	
    bool IsSource(const SpatialInteractionSource& rhs) const;

    bool								attach_ctrl_model = false;
    PlayerHandedness					req_hand = Unspecified;
    const SpatialSource*				source = 0;
    SpatialInteractionSourceLocation*	location = 0;
    
};

using MotionControllerComponentRef = Ref<MotionControllerComponent>;


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
    public SpatialInteractionListener,
	public HolographicScopeBinder
{
	/*using IPredictionUpdateListener = IPredictionUpdateListenerT<Holo>;
	using PredictionUpdateReason = typename IPredictionUpdateListenerT<Holo>::PredictionUpdateReason;
	using SpatialCoordinateSystem = typename Holo::SpatialCoordinateSystem;
	using HolographicFramePrediction = typename Holo::HolographicFramePrediction;
	using SpatialSourceEventArgs = typename Holo::SpatialSourceEventArgs;
	using SpatialSource = typename Holo::SpatialSource;*/
	
public:
	RTTI_DECL3(MotionControllerSystem, System<MotionControllerSystem>, PredictionUpdateListener, SpatialInteractionListener)
	ECS_SYS_CTOR(MotionControllerSystem)
	
	void Attach(MotionControllerComponent* comp);
	void Detach(MotionControllerComponent* comp);
	
	const Vector<MotionControllerComponent*>& GetComponents() const {return comps;}
	
protected:
    // System
    bool Initialize() override;
    void Uninitialize() override;
    void Start() override;
    void Stop() override;

    // PredictionUpdateListener
    void OnPredictionUpdated(
        PredictionUpdateReason reason,
        const SpatialCoordinateSystem& coord_system,
        const HolographicFramePrediction& prediction) override;

    // ISpatialInteractionListener
    /*void OnControllerDetected(const SpatialSourceEventArgs& args) override;
    void OnControllerUpdated(const SpatialSourceEventArgs& args) override;
    void OnControllerLost(const SpatialSourceEventArgs& args) override;*/
    
private:
    void RefreshComponentsForSource(const SpatialInteractionSource& source);
    
    Vector<MotionControllerComponent*> comps;
    
};


NAMESPACE_ECS_END


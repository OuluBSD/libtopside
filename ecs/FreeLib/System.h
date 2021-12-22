#ifndef _FreeLib_System_h_
#define _FreeLib_System_h_

NAMESPACE_ECS_BEGIN



class SpatialInteractionSystem : public System<SpatialInteractionSystem>
{
	LinkedList<ISpatialInteractionListenerRef> listeners;
	
public:
	ECS_SYS_CTOR(SpatialInteractionSystem);
	SYS_DEF_VISIT
	
	using Parent = Engine;
	
	
    void AddListener(ISpatialInteractionListenerRef listener) {listeners.Add(listener);}
	void RemoveListener(ISpatialInteractionListenerRef listener) {listeners.RemoveKey(listener);}
    
};


class MotionControllerComponent :
	public Component<MotionControllerComponent>
{
	
public:
	RTTI_COMM0(MotionControllerComponent);
	COPY_PANIC(MotionControllerComponent)
	COMP_DEF_VISIT
	
	
	SpatialInteractionSourceHandedness	req_hand;
	SpatialInteractionSourceLocation	location;
	bool								attach_ctrl_model = false;
	
	
	bool IsSource(const SpatialInteractionSource& src) const;
	
};


class MotionControllerSystem :
    public System<MotionControllerSystem>
{
	
public:
	SYS_RTTI(MotionControllerSystem)
	ECS_SYS_CTOR(MotionControllerSystem);
	SYS_DEF_VISIT
	
};


class HolographicScene :
	public System<HolographicScene>
{
	
public:
	SYS_RTTI(HolographicScene)
	ECS_SYS_CTOR(HolographicScene);
	SYS_DEF_VISIT
    
    
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
    const SpatialCoordinateSystem&		WorldCoordinateSystem() const;
    PerceptionTimestamp					CurrentTimestamp() const;
    
};


class HolographicRenderer :
	public System<HolographicRenderer>
{
	
public:
	SYS_RTTI(HolographicRenderer)
	ECS_SYS_CTOR(HolographicRenderer);
	SYS_DEF_VISIT
	
};


class PbrRenderable :
	public Component<PbrRenderable>
{
	
	
public:
	RTTI_COMP0(PbrRenderable)
	COPY_PANIC(PbrRenderable)
	COMP_DEF_VISIT
	
    void ResetModel(String name, Optional<mat4> offset = null_opt) {
        model_name = name;
        offset = offset;
    }

    String				model_name;
    One<Pbr::Model>		model;
    Optional<vec4>		color;
    Optional<mat4>		offset;
    Optional<double>	alpha_multiplier;
    
};

NAMESPACE_ECS_END

#endif

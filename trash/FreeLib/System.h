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
	RTTI_COMP0(MotionControllerComponent);
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


class HolographicRenderingSystem :
	public System<HolographicRenderingSystem>
{
	
public:
	SYS_RTTI(HolographicRenderingSystem)
	ECS_SYS_CTOR(HolographicRenderingSystem);
	SYS_DEF_VISIT
	
};


NAMESPACE_ECS_END

#endif

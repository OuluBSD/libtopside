#ifndef _OpenLib_Spatial_h_
#define _OpenLib_Spatial_h_

NAMESPACE_OULU_BEGIN


typedef enum {
	Thumbstick,
	Menu,
	Grasp
}
SpatialInteractionPressKind;


typedef enum {
	Controller
}
SpatialInteractionSourceKind;


struct SpatialCoordinateSystem {

};

struct HeadPose {
	
	
	vec3								Position() const;
	vec3								ForwardDirection() const;
	vec3								UpDirection() const;
	
	
};

struct SpatialPointerPose {
	
	
	const HeadPose&						Head() const;
	
	static SpatialPointerPose TryGetAtTimestamp(SpatialCoordinateSystem coord, PerceptionTimestamp ts);
	
	operator bool() const;
	
};

struct SpatialInteractionSource {
	
	
	SpatialInteractionSourceKind		Kind() const;
	
};

struct SpatialInteractionSourcePositionAccuracy {
	
	
	
};

struct SpatialPointerInteractionSourcePose {
	
	
	
};

struct SpatialInteractionSourceLocation {
	SpatialInteractionSourcePositionAccuracy	pos_acc;
	SpatialPointerInteractionSourcePose			src_ptr_pose;
	vec3	angular_vel;
	quat	orient;
	vec3	pos;
	vec3	velocity;
	
	
	operator bool() const;
	
};

struct SpatialInteractionSourceState {
	
	
	const SpatialInteractionSource&			Source() const;
	
};

struct SpatialInteractionSourceEventArgs {
	
	
	const SpatialInteractionPressKind&		PressKind() const;
	const SpatialInteractionSourceState&	State() const;
	
};

class ISpatialInteractionListener : public RefScopeEnabler<ISpatialInteractionListener, Machine> {
	
public:
	using Parent = Machine;
	
    virtual void OnSourceDetected(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceLost(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) {};
    
};


class SpatialInteractionSystem : public System<SpatialInteractionSystem>
{
	LinkedList<ISpatialInteractionListenerRef> listeners;
	
public:
	using Parent = Machine;
	
	
    void AddListener(ISpatialInteractionListenerRef listener) {
        listeners.Add(listener);
    }

    void RemoveListener(ISpatialInteractionListenerRef listener) {
        listeners.RemoveKey(listener);
    }
    
};


NAMESPACE_OULU_END

#endif

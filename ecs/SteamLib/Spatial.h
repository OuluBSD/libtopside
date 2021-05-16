#ifndef _SteamLib_Spatial_h_
#define _SteamLib_Spatial_h_

NAMESPACE_TOPSIDE_BEGIN

typedef enum {
	Thumbstick
	
}
SpatialInteractionPressKind;


struct SpatialInteractionSource {
	
	
	
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
	
	
};

struct SpatialInteractionSourceEventArgs {
	
	
	SpatialInteractionPressKind PressKind();
	
};

class ISpatialInteractionListener {
	
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


NAMESPACE_TOPSIDE_END

#endif

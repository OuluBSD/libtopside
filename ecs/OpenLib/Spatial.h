#ifndef _OpenLib_Spatial_h_
#define _OpenLib_Spatial_h_

NAMESPACE_TOPSIDE_BEGIN


typedef enum {
	Thumbstick,
	Menu,
	Grasp,
	Select
}
SpatialInteractionPressKind;


typedef enum {
	Controller
}
SpatialInteractionSourceKind;



struct SpatialInteractionControllerProperties {
	
	
	double								TouchpadX() const;
	double								TouchpadY() const;
	double								ThumbstickX() const;
	double								ThumbstickY() const;
	bool								IsTouchpadTouched() const;
	bool								IsTouchpadPressed() const;
	
};

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
	
	
	
	vec3											Position() const;
	vec3											ForwardDirection() const;
	quat											Orientation() const;
	
	bool IsNull() const;
	
	operator bool() const {return !IsNull();}
	
};

struct SpatialInteractionSourceLocation {
	SpatialInteractionSourcePositionAccuracy	pos_acc;
	SpatialPointerInteractionSourcePose			src_ptr_pose;
	vec3	angular_vel;
	quat	orient;
	vec3	pos;
	vec3	velocity;
	
	
	vec3		AngularVelocity() const {return angular_vel;}
	
	const SpatialPointerInteractionSourcePose&		SourcePointerPose() const;
	
	void SetNull();
	bool IsNull() const;
	
	operator bool() const {return !IsNull();}
	void operator=(void* o) {ASSERT(!o); SetNull();}
	
};


struct SpatialInteractionSourceProperties {
	
	
	const SpatialInteractionSourceLocation&			TryGetLocation(const SpatialCoordinateSystem& coord) const;
	
	
};


struct SpatialInteractionSourceState {
	
	bool											IsSelectPressed() const;
	bool											IsGrasped() const;
	
	const SpatialInteractionSource&					Source() const;
	const SpatialInteractionControllerProperties&	ControllerProperties() const;
	const SpatialInteractionSourceProperties&		Properties() const;
	
};

struct SpatialInteractionSourceEventArgs {
	
	
	const SpatialInteractionPressKind&		PressKind() const;
	const SpatialInteractionSourceState&	State() const;
	
};

class ISpatialInteractionListener :
	public RefScopeEnabler<ISpatialInteractionListener, Machine>
{
	
public:
	
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
	void Visit(RuntimeVisitor& vis) override {TODO}
	SYS_CTOR(SpatialInteractionSystem);
	
	using Parent = Machine;
	
	
    void AddListener(ISpatialInteractionListenerRef listener) {
        listeners.Add(listener);
    }

    void RemoveListener(ISpatialInteractionListenerRef listener) {
        listeners.RemoveKey(listener);
    }
    
};


class SpatialInputUtilities {
	public:
	
	class Physics {
		public:
			
		static vec3 GetVelocityNearSourceLocation(const SpatialInteractionSourceLocation& loc, const vec3 pos);
		
	};
	
	class Haptics {
		public:
		
		static void SendContinuousBuzzForDuration(const SpatialInteractionSource& src, MilliSeconds ts);
		
	};
	
};

NAMESPACE_TOPSIDE_END

#endif

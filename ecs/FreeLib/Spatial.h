#ifndef _FreeLib_Spatial_h_
#define _FreeLib_Spatial_h_

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
	double touch_x = 0;
	double touch_y = 0;
	double thumb_x = 0;
	double thumb_y = 0;
	bool is_touch_touch = 0;
	bool is_touch_press = 0;
	
	
	double			TouchpadX() const {return touch_x;}
	double			TouchpadY() const {return touch_y;}
	double			ThumbstickX() const {return thumb_x;}
	double			ThumbstickY() const {return thumb_y;}
	bool			IsTouchpadTouched() const {return is_touch_touch;}
	bool			IsTouchpadPressed() const {return is_touch_press;}
	
};

struct SpatialCoordinateSystem {

};

struct Pose {
	vec3 pos, fwd_dir, up_dir;
	
	
	vec3			Position() const			{return pos;}
	vec3			ForwardDirection() const	{return fwd_dir;}
	vec3			UpDirection() const			{return up_dir;}
	quat			Orientation() const			{TODO}
	
	bool IsNull() const {TODO}
	operator bool() const {return !IsNull();}
	
};

struct HeadPose : public Pose {
	
	
};

struct SpatialPointerPose {
	HeadPose head;
	
	const HeadPose&						Head() const {return head;}
	
	static SpatialPointerPose TryGetAtTimestamp(SpatialCoordinateSystem coord, PerceptionTimestamp ts);
	
	operator bool() const;
	
};

struct SpatialInteractionSource {
	SpatialInteractionSourceKind kind;
	
	const SpatialInteractionSourceKind&		Kind() const {return kind;}
	
};

struct SpatialInteractionSourcePositionAccuracy {
	
	
};

struct SpatialPointerInteractionSourcePose : public Pose {
	
	
};

struct SpatialInteractionSourceLocation {
	SpatialInteractionSourcePositionAccuracy	pos_acc;
	SpatialPointerInteractionSourcePose			src_ptr_pose;
	vec3	angular_vel;
	quat	orient;
	vec3	pos;
	vec3	velocity;
	
	vec3		AngularVelocity() const {return angular_vel;}
	
	const SpatialPointerInteractionSourcePose&		SourcePointerPose() const {return src_ptr_pose;}
	
	void SetNull() {pos.SetNull();}
	bool IsNull() const {return pos.IsNull();}
	
	operator bool() const {return !IsNull();}
	void operator=(void* o) {ASSERT(!o); SetNull();}
	
};


struct SpatialInteractionSourceProperties {
	SpatialInteractionSourceLocation loc;
	
	const SpatialInteractionSourceLocation&			TryGetLocation(const SpatialCoordinateSystem& coord) const {return loc;}
	
	
};


struct SpatialInteractionSourceState {
	SpatialInteractionSource src;
	SpatialInteractionControllerProperties ctrl_prop;
	SpatialInteractionSourceProperties src_prop;
	bool is_select_press = false;
	bool is_grasped = false;
	bool is_valid = false;
	
	bool IsSelectPressed() const {return is_select_press;}
	bool IsGrasped() const {return is_grasped;}
	
	const SpatialInteractionSource&					Source() const {return src;}
	const SpatialInteractionControllerProperties&	ControllerProperties() const {return ctrl_prop;}
	const SpatialInteractionSourceProperties&		Properties() const {return src_prop;}
	
};

struct SpatialInteractionSourceEventArgs {
	SpatialInteractionPressKind kind;
	SpatialInteractionSourceState state;
	
	const SpatialInteractionPressKind&		PressKind() const {return kind;}
	const SpatialInteractionSourceState&	State() const {return state;}
	
};

class ISpatialInteractionListener
{
	
public:
	
    virtual void OnSourceDetected(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceLost(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) {};
    virtual void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) {};
    
};

typedef ISpatialInteractionListener* ISpatialInteractionListenerRef;



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

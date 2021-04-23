#ifndef _EcsCore_Controller_h_
#define _EcsCore_Controller_h_

#if 0

NAMESPACE_OULU_BEGIN


typedef enum {
	Controller,
	HMD,
	Invalid,
	TrackingReference,
} ControllerSourceKind;

typedef enum {
	Unspecified,
	Left,
	Right
} ControllerSourceHandedness;

typedef enum {
	Menu,
	Grasp,
	Thumbstick,
	Select,
	Trigger,
	Touchpad,
} ControllerPressKind;



struct ControllerSourceHead {
	mat4 pose;
	vec3 Position() const {return pose[3].Splice();}
	vec3 ForwardDirection() const {return { -pose[2][0], -pose[2][1], -pose[2][2] };}
	vec3 UpDirection() const {return { +pose[1][0], +pose[1][1], +pose[1][2] };}
};

struct ControllerPointerPose {
	mat4 pose;
	bool is_valid = false;
	
	vec3 GetPosition() const {return pose[3].Splice();}
	vec3 GetForwardDirection() const {return { -pose[2][0], -pose[2][1], -pose[2][2] };}
	quat GetOrientation() const {return orientation(pose);}
	
	void SetValid(bool b) {is_valid = b;}
	
	operator bool () const {return is_valid;}
};

struct ControllerSourceLocation {
	ControllerSourceHead head;
	ControllerPointerPose pointer;
	mat4 pose;
	vec3 velocity, angular_veolcity;
	bool is_valid = false;
	
public:
	
	
	vec3 GetVelocity() const {return velocity;}
	vec3 GetPosition() const {return pose[3].Splice();}
	vec3 GetAngularVelocity() const {return angular_veolcity;}
	quat GetOrientation() const {return orientation(pose);}
	mat4 GetPose() const {return pose;}
	ControllerPointerPose GetSourcePointerPose() const {return pointer;}
	
	const ControllerSourceHead& Head() const {return head;}
	
	void SetValid(bool b) {is_valid = b;}
	
	operator bool () const {return is_valid;}
};

struct ControllerSourceDevice {
	ControllerSourceKind kind;
	ControllerSourceHandedness handedness;
	int id = 0;
	bool is_valid = false;
	
	
	int Id() const {return id;}
	ControllerSourceKind Kind() const {return kind;}
	ControllerSourceHandedness Handedness() const {return handedness;}
	
	void SetValid(bool b) {is_valid = b;}
	
	operator bool () const {return is_valid;}
};

struct ControllerProperties {
	float touch_x = 0, touch_y = 0, thumb_x = 0, thumb_y = 0;
	bool is_touch_touch = 0, is_touch_press = 0;
	
	float TouchpadX() const {return touch_x;}
	float TouchpadY() const {return touch_y;}
	float ThumbstickX() const {return thumb_x;}
	float ThumbstickY() const {return thumb_y;}
	bool IsTouchpadTouched() const {return is_touch_touch;}
	bool IsTouchpadPressed() const {return is_touch_press;}
};

struct ControllerState : Moveable<ControllerState> {
	ControllerSourceDevice src;
	ControllerSourceLocation loc;
	ControllerProperties prop;
	bool is_select_press = false;
	bool is_grasped = false;
	bool is_valid = false;
	
	
	const ControllerSourceDevice& Source() const {return src;}
	const ControllerSourceLocation& GetLocation() const {return loc;}
	const ControllerProperties& GetProperties() const {return prop;}
	
	bool IsSelectPressed() const {return is_select_press;}
	bool IsGrasped() const {return is_grasped;}
	
	void SetValid(bool b) {is_valid = b; src.SetValid(b); loc.SetValid(b);}
	
	operator bool () const {return is_valid;}
};

struct ControllerEventArgs {
	ControllerState state;
	ControllerPressKind kind;
	
	
	const ControllerState& State() const {return state;}
	
	ControllerPressKind PressKind() const {return kind;}
	
};

/*struct ControllerManager {
	
	void SourceDetected(Callback2<const ControllerManager&, const ControllerEventArgs&> cb) {}
	void SourcePressed(Callback2<const ControllerManager&, const ControllerEventArgs&> cb) {}
	void SourceUpdated(Callback2<const ControllerManager&, const ControllerEventArgs&> cb) {}
	void SourceReleased(Callback2<const ControllerManager&, const ControllerEventArgs&> cb) {}
	void SourceLost(Callback2<const ControllerManager&, const ControllerEventArgs&> cb) {}
};*/

class ControllerListenerInterface
{
public:
    virtual void OnSourceDetected(const ControllerEventArgs& args) {};
    virtual void OnSourceLost(const ControllerEventArgs& args) {};
    virtual void OnSourcePressed(const ControllerEventArgs& args) {};
    virtual void OnSourceUpdated(const ControllerEventArgs& args) {};
    virtual void OnSourceReleased(const ControllerEventArgs& args) {};
};

class OpenVR;

class ControllerSystem final : public System<ControllerSystem>
{
public:
	typedef ControllerSystem CLASSNAME;
    using System::System;

    void AddListener(Ref<ControllerListenerInterface> listener) {
        m_ctrl_Listeners.Add(pick(listener));
    }

    void RemoveListener(Ref<ControllerListenerInterface> listener) {
        m_ctrl_Listeners.Remove(pick(listener));
    }
	
	#ifdef flagOPENVR
	
	void UpdateHMDMatrixPose();
	void ProcessEvent(const vr::VREvent_t& event);
	void ProcessController(vr::TrackedDeviceIndex_t device, vr::VRControllerState_t* state, mat4& M);
	
	Ref<OpenVR> vr;

	#endif
	
	Vector<ControllerState> GetDetectedSourcesAtTimestamp(PerceptionTimestamp ts);
	
protected:
    bool Initialize() override;
    void Start() override;
    void Uninitialize() override;

private:
    //ControllerManager m_ctrl_Manager;

    enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    //event_token m_sourceTokens[SourceEvent::Count];
	Vector<ControllerState> ctrl_states;
	int left_id = -1, right_id = -1;
	
    ListenerCollection<ControllerListenerInterface> m_ctrl_Listeners;
	
    // Events Handlers
    void HandleSourceDetected(const ControllerEventArgs&  args);
    void HandleSourceLost(const ControllerEventArgs& args);
    void HandleSourcePressed(const ControllerEventArgs& args);
    void HandleSourceUpdated(const ControllerEventArgs& args);
    void HandleSourceReleased(const ControllerEventArgs& args);

};


NAMESPACE_OULU_END


#endif
#endif

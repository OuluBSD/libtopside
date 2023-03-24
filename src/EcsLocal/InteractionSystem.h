#ifndef _EcsLocal_InteractionSystem_h_
#define _EcsLocal_InteractionSystem_h_

NAMESPACE_ECS_BEGIN


//TODO common base with these and IHolograph classes
// - SpatialSourceEventArgs
// - SpatialInteractionManager
// - SpatialSourceEventArgs


class InteractionSystem;
struct FakeSpatialInteractionManager;
struct VrSpatialInteractionManager;


struct InteractionManager {
	
	
	using Cb = Callback2<const InteractionManager&, const CtrlEvent&>;
	Cb WhenSourceDetected;
	Cb WhenSourcePressed;
	Cb WhenSourceUpdated;
	Cb WhenSourceReleased;
	Cb WhenSourceLost;
	
	
	virtual void Update(double dt) {}
	
};

struct FakeControllerSource : ControllerSource {
	FakeSpatialInteractionManager* mgr = 0;
	
	void GetVelocity(float* v3) const override;
	void GetAngularVelocity(float* v3) const override;
	
};

struct FakeSpatialInteractionManager : InteractionManager {
	EnvStateRef state;
	FakeControllerSource ctrl;
	ControllerState ctrl_state;
	InteractionSystem* sys = 0;
	Point prev_mouse = Point(0,0);
	double time = 0;
	double last_dt = 0;
	FboKbd::KeyVec prev;
	//ControllerMatrix ev3d;
	TransformMatrix trans;
	
	// player camera
	float pitch = 0;
	float yaw = 0;
	vec3 head_direction = VEC_FWD;
	vec3 hand_velocity = vec3(0,0,0);
	vec3 hand_angular_velocity = vec3(0,0,0);
	
	OnlineAverage av[3];
	
	
	FakeSpatialInteractionManager();
	
	bool Initialize(InteractionSystem& sys);
	void Update(double dt) override;
	
    void DetectController();
    void UpdateState();
    void UpdateStateKeyboard();
	void Look(Point mouse_diff);
	void Move(vec3 rel_dir, float step);
    void Pressed(ControllerMatrix::Value b);
    void Released(ControllerMatrix::Value b);
    
};










struct VrControllerSource : ControllerSource {
	VrSpatialInteractionManager* mgr = 0;
	
	void GetVelocity(float* v3) const override;
	void GetAngularVelocity(float* v3) const override;
	
};

struct VrSpatialInteractionManager : InteractionManager {
	EnvStateRef state;
	Ecs::RenderingSystemRef rend;
	VrControllerSource ctrl;
	InteractionSystem* sys = 0;
	Point prev_mouse = Point(0,0);
	double time = 0;
	double last_dt = 0;
	FboKbd::KeyVec prev;
	TransformMatrix trans;
	ControllerState ctrl_state;
	
	// player camera
	float pitch = 0;
	float yaw = 0;
	vec3 head_direction = VEC_FWD;
	vec3 hand_velocity = vec3(0,0,0);
	vec3 hand_angular_velocity = vec3(0,0,0);
	
	OnlineAverage av[3];
	
	// Calibration
	enum {
		CALIB_FOV_SCALE_EYEDIST,
		CALIB_CTRL_LEFT,
		CALIB_CTRL_RIGHT,
	};
	int calib_mode = 0;
	
	VrSpatialInteractionManager();
	
	bool Initialize(InteractionSystem& sys);
	void Update(double dt) override;
	
    void DetectController();
    void UpdateState();
    void UpdateStateHmd();
    void UpdateCalibrationStateKeyboard();
	void Look(const TransformMatrix& tm);
	void Control(const ControllerMatrix& cm);
	void Move(vec3 rel_dir, float step);
    void Pressed(ControllerMatrix::Value b, float f);
    void Released(ControllerMatrix::Value b, float f);
    void Updated(ControllerMatrix::Value b, float f);
    
};









struct InteractionListener :
	WeakRefScopeEnabler<InteractionListener, Engine>,
	RTTIBase
{
	RTTI_DECL0(InteractionListener)
	
    virtual void OnControllerDetected(const CtrlEvent& e) {};
    virtual void OnControllerLost(const CtrlEvent& e) {};
    virtual void OnControllerPressed(const CtrlEvent& e) {};
    virtual void OnControllerUpdated(const CtrlEvent& e) {};
    virtual void OnControllerReleased(const CtrlEvent& e) {};
    
    virtual bool IsEnabled() const;
    
    static bool Initialize(Engine& e, Ref<InteractionListener, RefParent1<Engine>> l);
    static void Uninitialize(Engine& e, Ref<InteractionListener, RefParent1<Engine>> l);
};

using InteractionListenerRef = Ref<InteractionListener, RefParent1<Ecs::Engine>>;



class InteractionSystem :
	public Ecs::System<InteractionSystem>
{
public:
	ECS_SYS_CTOR(InteractionSystem)
	
    void AddListener(InteractionListenerRef listener) {
        ArrayFindAdd(interaction_listeners, listener);
    }

    void RemoveListener(InteractionListenerRef listener) {
        ArrayRemoveKey(interaction_listeners, listener);
    }

    
protected:
    bool Initialize() override;
    void Uninitialize() override;
    void Update(double dt) override;
	bool Arg(String key, Object value) override;

protected:
	friend struct FakeSpatialInteractionManager;
	friend struct VrSpatialInteractionManager;
	String env_name;
	bool debug_log = false;
	bool use_state_hmd = false;
	bool is_calibration = false;
	
private:
    Array<InteractionListenerRef> interaction_listeners;
    One<FakeSpatialInteractionManager> fake_spatial_interaction_manager;
    One<VrSpatialInteractionManager> vr_spatial_interaction_manager;
    InteractionManager* spatial_interaction_manager = 0;
    
    
    void BindEventHandlers();
    void ReleaseEventHandlers();
    
    
	
    // Events Handlers
    void HandleSourceDetected(const InteractionManager&, const CtrlEvent& e);
    void HandleSourceLost(const InteractionManager&, const CtrlEvent& e);
    void HandleSourcePressed(const InteractionManager&, const CtrlEvent& e);
    void HandleSourceUpdated(const InteractionManager&, const CtrlEvent& e);
    void HandleSourceReleased(const InteractionManager&, const CtrlEvent& e);
    
};


NAMESPACE_ECS_END

#endif

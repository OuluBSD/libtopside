#ifndef _EcsLocal_Player_h_
#define _EcsLocal_Player_h_

NAMESPACE_ECS_BEGIN


class PlayerBodyComponent;
using PlayerBodyComponentRef = RefT_Entity<PlayerBodyComponent>;


typedef enum {
	Unspecified,
	Left,
	Right
} PlayerHandedness;

typedef enum {
	High,
	Approximate,
} HandPositionAccuracy;

struct HandActionSourcePose {
	vec3 forward_direction;
	quat orientation;
	vec3 position;
	HandPositionAccuracy position_accuracy;
	vec3 up_direction;
	
	vec3 GetPosition() const {return position;}
	vec3 GetForwardDirection() const {return forward_direction;}
	quat GetOrientation() const {return orientation;}
};

// "SpatialSource"
struct HandLocationSource : ControllerSource {
	RTTI_DECL1(HandLocationSource, ControllerSource)
	
};

struct HandSourceLocation {
	vec3 position;
	quat orientation;
	HandActionSourcePose* pose = 0;
	
	const vec3& GetPosition() const {return position;}
	const quat& GetOrientation() const {return orientation;}
	virtual HandActionSourcePose* GetHandPose() const {return pose;}
	
};

struct HandActionSourceLocation : HandSourceLocation {
	
	
};


class PlayerHandComponent : public Component<PlayerHandComponent> {
	
public:
	RTTI_COMP0(PlayerHandComponent)
	COMP_DEF_VISIT_(vis & body)
	
	COPY_PANIC(PlayerHandComponent)
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
    bool IsSource(const ControllerSource& rhs) const;
	
	
	PlayerBodyComponentRef				body;
	bool								is_simulated = false;
    bool								attach_ctrl_model = false;
    PlayerHandedness					req_hand = Unspecified;
    const HandLocationSource*			source = 0;
    HandActionSourceLocation*			location = 0;
    
};

using PlayerHandComponentRef = Ref<PlayerHandComponent>;



class PlayerHeadComponent : public Component<PlayerHeadComponent> {
	
public:
	RTTI_COMP0(PlayerHeadComponent)
	COMP_DEF_VISIT_(vis & body)
	
	COPY_PANIC(PlayerHeadComponent)
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
	
	PlayerBodyComponentRef				body;
	
};

using PlayerHeadComponentRef = Ref<PlayerHeadComponent>;



class PlayerBodyComponent : public Component<PlayerBodyComponent> {
	
protected:
	friend class PlayerBodySystem;
	PlayerHandComponentRef hands[2];
	PlayerHeadComponentRef head;
	float height = 1.8f;
	
public:
	RTTI_COMP0(PlayerBodyComponent)
	COMP_DEF_VISIT_(vis & hands[0] & hands[1] & head)
	COPY_PANIC(PlayerBodyComponent)
	
	void Initialize() override;
	void Uninitialize() override;
	bool Arg(String key, Object value) override;
	
	bool SetHand(PlayerHandedness hand, PlayerHandComponentRef comp);
	bool SetHead(PlayerHeadComponentRef head);
	
	float GetHeight() const {return height;}
	const PlayerHeadComponentRef& GetHead() const {return head;}
	
};




class PlayerBodySystem :
    public System<PlayerBodySystem>,
    public InteractionListener
{
	
public:
	RTTI_DECL2(PlayerBodySystem, System<PlayerBodySystem>, InteractionListener)
	ECS_SYS_CTOR(PlayerBodySystem)
	ECS_SYS_DEF_VISIT_(vis && bodies)
	
	const Array<PlayerBodyComponentRef>& GetComponents() const {return bodies;}
	
	void Attach(PlayerBodyComponentRef h);
	void Detach(PlayerBodyComponentRef h);
protected:
    // System
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
	
	void OnControllerDetected(const CtrlEvent& e) override;
	void OnControllerLost(const CtrlEvent& e) override;
	void OnControllerPressed(const CtrlEvent& e) override;
	void OnControllerUpdated(const CtrlEvent& e) override;
	void OnControllerReleased(const CtrlEvent& e) override;
    
private:
    void RefreshComponentsForSource(const HandLocationSource& source);
    
    Ref<InteractionSystem> iasys;
    Array<PlayerBodyComponentRef> bodies;
    
};



NAMESPACE_ECS_END

#endif

#ifndef _EcsLocal_Player_h_
#define _EcsLocal_Player_h_

NAMESPACE_ECS_BEGIN



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
	//bool is_set = false;
	vec3 forward_direction;
	quat orientation;
	vec3 position;
	HandPositionAccuracy position_accuracy;
	vec3 up_direction;
	
	vec3 GetPosition() const {return position;}
	vec3 GetForwardDirection() const {return forward_direction;}
	quat GetOrientation() const {return orientation;}
	//operator bool() const {return is_set;}
};

// "SpatialSource"
struct HandLocationSource {
	
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
	COMP_DEF_VISIT
	
	COPY_PANIC(PlayerHandComponent)
	
	void Initialize() override;
	void Uninitialize() override;
	
    bool IsSource(const HandLocationSource& rhs) const;

    bool								attach_ctrl_model = false;
    PlayerHandedness					req_hand = Unspecified;
    const HandLocationSource*			source = 0;
    HandActionSourceLocation*			location = 0;
    
};

using PlayerHandComponentRef = Ref<PlayerHandComponent>;


class PlayerHandSystem :
    public System<PlayerHandSystem>
{
	
public:
	RTTI_DECL1(PlayerHandSystem, System<PlayerHandSystem>)
	ECS_SYS_CTOR(PlayerHandSystem)
	
	const Vector<PlayerHandComponent*>& GetComponents() const {return comps;}
	
protected:
    // System
    bool Initialize() override;
    void Start() override;
    void Stop() override;
    void Uninitialize() override;

private:
    void RefreshComponentsForSource(const HandLocationSource& source);
    
    Vector<PlayerHandComponent*> comps;
    
};



NAMESPACE_ECS_END

#endif

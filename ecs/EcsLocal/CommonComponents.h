#ifndef _System_CommonComponents_h_
#define _System_CommonComponents_h_


NAMESPACE_ECS_BEGIN


class RigidBody : public Component<RigidBody> {
	
public:
	RTTI_COMP0(RigidBody)
	COMP_DEF_VISIT
	
	
	vec3 velocity;
	vec3 acceleration;
	vec3 angular_velocity;
	vec3 angular_acceleration;
	
	float damping_factor;
	
	
	void Initialize() override;
	
    void operator=(const RigidBody& r) {
        velocity = r.velocity;
        acceleration = r.acceleration;
        angular_velocity = r.angular_velocity;
        angular_acceleration = r.angular_acceleration;
        damping_factor = r.damping_factor;
    }
    
	
};

using RigidBodyRef = Ref<RigidBody>;



#if 0

class StaticVolumeComponent :
	public Component<StaticVolumeComponent>,
	public StaticSource
{
	
protected:
	friend class VolumeStream;
	
	Vector<byte> values;
	String errstr;
	Size sz;
	int depth;
	int stride;
	
	struct VolumeStream : public SimpleStaticStream {
		StaticVolumeComponent& comp;
		
		VolumeStream(StaticVolumeComponent* c) : comp(*c) {}
		bool LoadFileAny(String path) override {return comp.LoadFileAny(path);}
		Size GetResolution() const;
		int GetDepth() const;
	};
	
	VolumeStream stream;
	
public:
	RTTI_COMP1(StaticVolumeComponent, StaticSource)
	COPY_PANIC(StaticVolumeComponent);
	COMP_DEF_VISIT
	
	
	StaticVolumeComponent() : stream(this) {}
	
	void Initialize() override;
	void Uninitialize() override;
	
	StaticStream& GetStream(StcCtx) override {return stream;}
	void BeginStream(StcCtx) override {}
	void EndStream(StcCtx) override {}
	
	String GetLastError() const {return errstr;}
	bool LoadFileAny(String path);
	
	
};

#endif















class TextRenderable :
	public Component<TextRenderable>
{
	
public:
	RTTI_COMP0(TextRenderable)
	COPY_PANIC(TextRenderable);
	COMP_DEF_VISIT
	
	
    String				text = "";
    double				font_size = 60.0;
    
    
};




NAMESPACE_ECS_END

#endif

#ifndef _System_CommonComponents_h_
#define _System_CommonComponents_h_

NAMESPACE_OULU_BEGIN


class Transform : public Component<Transform> {
public:
	vec3 position = zero<vec3>();
	vec3 size = one<vec3>();
	quat orientation = identity<quat>();
	
	/*void SetFromMatrix(const mat4& matrix) {
		vec3 skew;
		vec4 persp;
		decompose(matrix, size, orientation, position, skew, persp);
	}*/
	
	void operator=(const Transform& t) {
		position		= t.position;
		size			= t.size;
		orientation		= t.orientation;
	}
	mat4 GetMatrix() const {
		return scale(size) * ToMat4(orientation) * translate(position);
	}
	
	String ToString() const {
		String s;
		s << "pos" << position.ToString() << ", size" << size.ToString() << ", orient" << orientation.ToString();
		return s;
	}
	//void MoveTo(const OverlapSink& conn);
	
};

void CopyTransformPos(EntityRef from, EntityRef to);

class Transform2D : public Component<Transform2D> {
public:
	vec2 position = zero<vec2>();
	vec2 size = one<vec2>();
	
    void operator=(const Transform2D& t) {
        position = t.position;
        size = t.size;
    }
    
};

class RigidBody : public Component<RigidBody> {
public:
	vec3 velocity = zero<vec3>();
	vec3 acceleration = zero<vec3>();
	vec3 angular_velocity = zero<vec3>();
	vec3 angular_acceleration = zero<vec3>();
	
	float damping_factor = 0.999f;
	
    void operator=(const RigidBody& r) {
        velocity = r.velocity;
        acceleration = r.acceleration;
        angular_velocity = r.angular_velocity;
        angular_acceleration = r.angular_acceleration;
        damping_factor = r.damping_factor;
    }
    
};


class Renderable : public Component<Renderable> {
public:
	void ResetModel(mat4 offset = zero<mat4>()) {
		color = RGBAZero();
		this->offset = offset;
		alpha_multiplier = 0;
		//model_name = name;
		//model.Clear();
	}
	
	RGBA color;
	mat4 offset;
	float alpha_multiplier;
	//String model_name;
	//Ref<ModelComponent> model;
	
    void operator=(const Renderable& e) {
        color = e.color;
        offset = e.offset;
        alpha_multiplier = e.alpha_multiplier;
    }
#ifdef flagGUI
	Callback1<Shader&> cb;
#endif
	//Model* GetModel() {return model ? model->GetModel() : 0;}
	
};



class StaticVolumeComponent :
	public Component<StaticVolumeComponent>,
	public StaticSource
{
	Vector<byte> values;
	String errstr;
	Size sz;
	int depth;
	int stride;
	
public:
	COPY_PANIC(StaticVolumeComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	StaticVolumeComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	bool LoadFileAny(String path) override;
	Size GetResolution() const override;
	int GetDepth() const override;
	void EmitStatic() override;
	
	String GetLastError() const {return errstr;}
	
};

NAMESPACE_OULU_END

#endif

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
};

class RigidBody : public Component<RigidBody> {
public:
	vec3 velocity = zero<vec3>();
	vec3 acceleration = zero<vec3>();
	vec3 angular_velocity = zero<vec3>();
	vec3 angularAcceleration = zero<vec3>();
	
	float dampingFactor = 0.999f;
};


class Renderable : public Component<Renderable> {
public:
	void ResetModel(String name, mat4 offset = zero<mat4>()) {
		model_name = name;
		color = RGBAZero();
		this->offset = offset;
		alpha_multiplier = 0;
		//model.Clear();
	}
	
	String model_name;
	RGBA color;
	mat4 offset;
	float alpha_multiplier;
	//Ref<ModelComponent> model;
	
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

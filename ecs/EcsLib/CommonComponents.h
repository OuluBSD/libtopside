#ifndef _System_CommonComponents_h_
#define _System_CommonComponents_h_

NAMESPACE_TOPSIDE_BEGIN


class Transform : public Component<Transform> {
	
public:
	VIS_COMP_0_0
	RTTI_COMP0(Transform)
	COMP_DEF_VISIT
	
	vec3 position = zero<vec3>();
	vec3 size = one<vec3>();
	quat orientation = identity<quat>();
	
	void SetFromMatrix(const mat4& matrix) {
		vec3 skew;
		vec4 persp;
		bool succ = Decompose(matrix, size, orientation, position, skew, persp);
		ASSERT(succ);
	}
	
	void operator=(const Transform& t) {
		position		= t.position;
		size			= t.size;
		orientation		= t.orientation;
	}
	mat4 GetMatrix() const {
		return scale(size) * ToMat4(orientation) * translate(position);
	}
	
	String ToString() const override {
		String s;
		s << "pos" << position.ToString() << ", size" << size.ToString() << ", orient" << orientation.ToString();
		return s;
	}
	//void MoveTo(const OverlapSink& conn);
	
	
};

void CopyTransformPos(EntityRef from, EntityRef to);

class Transform2D : public Component<Transform2D> {
	
public:
	VIS_COMP_0_0
	RTTI_COMP0(Transform2D)
	COMP_DEF_VISIT
	
	vec2 position = zero<vec2>();
	vec2 size = one<vec2>();
	
    void operator=(const Transform2D& t) {
        position = t.position;
        size = t.size;
    }
    
	
};

class RigidBody : public Component<RigidBody> {
	
public:
	VIS_COMP_0_0
	RTTI_COMP0(RigidBody)
	COMP_DEF_VISIT
	
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
	VIS_COMP_0_0
	RTTI_COMP0(Renderable)
	COMP_DEF_VISIT
	
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
	public StaticSource,
	public GeneratorComponentBase
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
	VIS_COMP_1_0(Static)
	RTTI_COMP1(StaticVolumeComponent, StaticSource)
	COPY_PANIC(StaticVolumeComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
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











namespace Pbr {
    struct Model;
}





/*class PbrRenderable :
	public Component<PbrRenderable>
{
	VIS_COMP_0_0
	
public:
	RTTI_COMP0(PbrRenderable)
	COPY_PANIC(PbrRenderable)
	COMP_DEF_VISIT
	
    void ResetModel(String name, Optional<mat4> offset = null_opt) {
        model_name = name;
        offset = offset;
    }

    String				model_name;
    One<Pbr::Model>		model;
    Optional<vec4>		color;
    Optional<mat4>		offset;
    Optional<double>	alpha_multiplier;
    
};*/


class TextRenderable :
	public Component<TextRenderable>
{
	
public:
	VIS_COMP_0_0
	RTTI_COMP0(TextRenderable)
	COPY_PANIC(TextRenderable);
	COMP_DEF_VISIT
	
    String				text = "";
    double				font_size = 60.0;
    
    
};


/*class CustomerComponent :
	public Component<CustomerComponent>,
	public OrderSource,
	public ReceiptSink
{
	RTTI_DECL_3(CustomerComponent, Component<CustomerComponent>, \
				OrderSource, ReceiptSink, \
				"CustomerComponent")
	VIS_COMP_1_1(Order, Receipt)
	COPY_PANIC(CustomerComponent)
	IFACE_GENERIC
	COMP_DEF_VISIT
	
public:
	CustomerComponent() {}
	
	// ComponentBase
	void				Initialize() override;
	void				Uninitialize() override;
	TypeCls				GetValSpec() const override {return AsTypeCls<OrderSpec>();}
	bool				IsValSpec(TypeCls t) const override {return AsTypeCls<OrderSpec>() == t;}
	
	// ReceiptSink
	Format				GetFormat(ReceiptSpec*) override;
	Value&				GetValue(ReceiptSpec*) override;
	
	// OrderSource
	CtxStream&			GetStream(OrderSpec*) override;
	void				BeginStream(OrderSpec*) override;
	void				EndStream(OrderSpec*) override;
	
};*/

NAMESPACE_TOPSIDE_END

#endif

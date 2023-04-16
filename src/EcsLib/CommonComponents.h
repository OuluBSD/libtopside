#ifndef _EcsLib_CommonComponents_h_
#define _EcsLib_CommonComponents_h_

NAMESPACE_ECS_BEGIN


extern const vec3 EarthGravity;


class Transform : public Component<Transform> {
	
public:
	RTTI_COMP0(Transform)
	COMP_DEF_VISIT
	
	TransformMatrix data;
	vec3 size;
	vec3 relative_position;
	vec3 anchor_position;
	quat anchor_orientation;
	bool verbose = false;
	
	void operator=(const Transform& t);
	mat4 GetMatrix() const;
	vec3 GetForwardDirection() const;
	
	bool Arg(String key, Object value) override;
	String ToString() const override;
	void Initialize() override;
	void Uninitialize() override;
	
};

typedef Ref<Transform> TransformRef;


void CopyTransformPos(EntityRef from, EntityRef to);

class Transform2D : public Component<Transform2D> {
	
public:
	RTTI_COMP0(Transform2D)
	COMP_DEF_VISIT
	
	
	vec2 position = zero<vec2>();
	vec2 size = one<vec2>();
	
	void operator=(const Transform2D& t);
	
	
};


NAMESPACE_ECS_END

#endif

#ifndef _EcsLib_CommonComponents_h_
#define _EcsLib_CommonComponents_h_

NAMESPACE_ECS_BEGIN


class Transform : public Component<Transform> {
	
public:
	RTTI_COMP0(Transform)
	COMP_DEF_VISIT
	
	
	vec3 position = zero<vec3>();
	vec3 size = one<vec3>();
	quat orientation = identity<quat>();
	vec3 direction = vec3(0,0,1);
	vec3 up = vec3(0,1,0); // "look at" alternative to quaternion
	bool use_lookat = false; // use direction & up instead of orientation
	
	
	void SetFromMatrix(const mat4& matrix);
	void operator=(const Transform& t);
	mat4 GetMatrix() const;
	
	bool Arg(String key, Object value) override;
	String ToString() const override;
	void Initialize() override;
	void Uninitialize() override;
	
};

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

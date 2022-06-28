#ifndef _EcsLib_CommonComponents_h_
#define _EcsLib_CommonComponents_h_

NAMESPACE_ECS_BEGIN


class Transform : public Component<Transform> {
	
public:
	RTTI_COMP0(Transform)
	COMP_DEF_VISIT
	
	TransformMatrix data;
	vec3 size;
	vec3 anchor_position;
	quat anchor_orientation;
	bool verbose = false;
	/*
	vec3 position;
	quat orientation;
	vec3 direction; // "look at" alternative to quaternion
	vec3 up; // "look at" alternative to quaternion
	bool use_lookat; // use direction & up instead of orientation
	//bool use_stereo = false;v
	*/
	
	void SetFromMatrix(const mat4& matrix);
	void operator=(const Transform& t);
	mat4 GetMatrix() const;
	vec3 GetForwardDirection() const;
	
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

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
	
	
};

void CopyTransformPos(EntityRef from, EntityRef to);

class Transform2D : public Component<Transform2D> {
	
public:
	RTTI_COMP0(Transform2D)
	COMP_DEF_VISIT
	
	
	vec2 position = zero<vec2>();
	vec2 size = one<vec2>();
	
    void operator=(const Transform2D& t) {
        position = t.position;
        size = t.size;
    }
    
	
};


NAMESPACE_ECS_END

#endif

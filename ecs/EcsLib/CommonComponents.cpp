#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


void Transform::Initialize() {
	Ref<WorldLogicSystem> sys = GetEngine().TryGet<WorldLogicSystem>();
	if (sys)
		sys->Attach(this);
}

void Transform::Uninitialize() {
	Ref<WorldLogicSystem> sys = GetEngine().TryGet<WorldLogicSystem>();
	if (sys)
		sys->Detach(this);
}

void Transform::SetFromMatrix(const mat4& matrix) {
	vec3 skew;
	vec4 persp;
	bool succ = Decompose(matrix, size, orientation, position, skew, persp);
	ASSERT(succ);
}

void Transform::operator=(const Transform& t) {
	position		= t.position;
	size			= t.size;
	orientation		= t.orientation;
}

mat4 Transform::GetMatrix() const {
	return translate(position) * ToMat4(orientation) * scale(size);
}

bool Transform::Arg(String key, Object value) {
	if (key == "x")
		position[0] = value.ToDouble();
	else if (key == "y")
		position[1] = value.ToDouble();
	else if (key == "z")
		position[2] = value.ToDouble();
	else if (key == "cx")
		size[0] = value.ToDouble();
	else if (key == "cy")
		size[1] = value.ToDouble();
	else if (key == "cz")
		size[2] = value.ToDouble();
	else
		return false;
	
	return true;
}

String Transform::ToString() const {
	String s;
	s << "pos" << position.ToString() << ", size" << size.ToString() << ", orient" << orientation.ToString();
	return s;
}







void Transform2D::operator=(const Transform2D& t) {
    position = t.position;
    size = t.size;
}



NAMESPACE_ECS_END

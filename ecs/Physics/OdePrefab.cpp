#include "Physics.h"

#ifdef flagODE

NAMESPACE_ECS_BEGIN

void StaticBox::OnAttach() {
	OdeObject::OnAttach();
	
	geom = dCreateBox(GetSpace()->GetSpaceId(), width, height, length);
	
	ModelBuilder mb;
	mb	.AddBox(vec3(-width/2, -height/2, -length/2), vec3(width, height, length))
		.SetMaterial(DefaultMaterial());
	loader = mb;
}

NAMESPACE_ECS_END

#endif

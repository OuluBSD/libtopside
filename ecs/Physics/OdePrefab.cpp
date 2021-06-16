#include "Physics.h"

#ifdef flagODE

NAMESPACE_TOPSIDE_BEGIN

void StaticBox::OnAttach() {
	OdeObject::OnAttach();
	
	geom = dCreateBox(GetSpace()->GetSpaceId(), width, height, length);
	
	ModelBuilder mb;
	mb	.AddBox(vec3(-width/2, -height/2, -length/2), vec3(width, height, length))
		.SetMaterial(DefaultMaterial());
	model = mb;
}

NAMESPACE_TOPSIDE_END

#endif

#ifndef _TemplatesCore_Classes_h_
#define _TemplatesCore_Classes_h_

NAMESPACE_ECS_BEGIN




struct PhysicsGlobalVariables {
	vec3 gravity;
};

class PhysicsSystemBase :
	RTTIBase
{
public:
	RTTI_DECL0(PhysicsSystemBase)
	
	PhysicsGlobalVariables var;
	
};

class DisplaySystemBase :
	RTTIBase
{
	Size screen_sz;
public:
	RTTI_DECL0(DisplaySystemBase)
	
	Size GetVirtualScreenSize() const{return screen_sz;}
	void SetVirtualScreenSize(Size sz) {screen_sz = sz;}
	
};







NAMESPACE_ECS_END

#endif

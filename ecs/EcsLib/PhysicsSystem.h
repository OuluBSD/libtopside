#pragma once


#if 0


NAMESPACE_TOPSIDE_BEGIN


class PhysicsSystem :
	public System<PhysicsSystem>
{
	
public:
	COMP_DEF_VISIT
	SYS_CTOR(PhysicsSystem);
	
	static const vec3 EarthGravity;
	
protected:
	void Update(double dt) override;
	
	
};


NAMESPACE_TOPSIDE_END

#endif

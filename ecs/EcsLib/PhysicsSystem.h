#pragma once


NAMESPACE_OULU_BEGIN


class PhysicsSystem :
	public System<PhysicsSystem>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {}
	SYS_CTOR(PhysicsSystem);
	
	static const vec3 EarthGravity;
	
protected:
	void Update(double dt) override;
	
	
};


NAMESPACE_OULU_END

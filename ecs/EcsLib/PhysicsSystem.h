#pragma once


NAMESPACE_OULU_BEGIN


class PhysicsSystem :
	public System<PhysicsSystem>
{
	
public:
	
	using System::System;
	
	static const vec3 EarthGravity;
	
protected:
	void Update(double dt) override;
	
	
};


NAMESPACE_OULU_END

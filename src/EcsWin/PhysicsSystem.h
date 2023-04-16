#if 0
#pragma once


NAMESPACE_ECS_BEGIN


////////////////////////////////////////////////////////////////////////////////
// PhysicsSystem
// Simple physics system to move objects around with basic integration (acceleration, velocity)
class PhysicsSystem : public ::TS::Ecs::System<PhysicsSystem>
{
public:
    using System::System;

    static const winrt::Windows::Foundation::Numerics::float3 EarthGravity;

protected:
    void Update(double dt) override;
    
};


NAMESPACE_ECS_END
#endif

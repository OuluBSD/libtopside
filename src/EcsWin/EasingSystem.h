#if 0
#pragma once


namespace Neso
{

struct Easing : Component<Easing>
{
    winrt::Windows::Foundation::Numerics::float3 TargetPosition{ 0,0,0 };
    winrt::Windows::Foundation::Numerics::quaternion TargetOrientation = winrt::Windows::Foundation::Numerics::quaternion::identity();
    float PositionEasingFactor = 0;
    float OrientationEasingFactor = 0;
};

////////////////////////////////////////////////////////////////////////////////
// EasingSystem
// Manages the Easing component, which allows objects with a Transform component to be
// interpolated to new position/orientations.
class EasingSystem : public System<EasingSystem>
{
public:
    using System::System;

protected:
    void Update(double) override;
};

}
#endif

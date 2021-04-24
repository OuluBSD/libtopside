#ifndef _System_EasingSystem_h_
#define _System_EasingSystem_h_

NAMESPACE_OULU_BEGIN

	
struct Easing : Component<Easing>
{
    vec3 TargetPosition = { 0,0,0 };
    quat TargetOrientation = identity<quat>();
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


NAMESPACE_OULU_END

#endif

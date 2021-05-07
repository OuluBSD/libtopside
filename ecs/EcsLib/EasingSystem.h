#ifndef _System_EasingSystem_h_
#define _System_EasingSystem_h_

NAMESPACE_OULU_BEGIN

	
struct Easing : Component<Easing>
{
    vec3 target_position = { 0,0,0 };
    quat target_orientation = identity<quat>();
    float position_easing_factor = 0;
    float orientation_easing_factor = 0;
    
    void operator=(const Easing& e) {
        target_position = e.target_position;
        target_orientation = e.target_orientation;
        position_easing_factor = e.position_easing_factor;
        orientation_easing_factor = e.orientation_easing_factor;
    }
};


////////////////////////////////////////////////////////////////////////////////
// EasingSystem
// Manages the Easing component, which allows objects with a Transform component to be
// interpolated to new position/orientations.
class EasingSystem : public System<EasingSystem>
{
public:
    SYS_CTOR(EasingSystem)

protected:
    void Update(double) override;
};


NAMESPACE_OULU_END

#endif

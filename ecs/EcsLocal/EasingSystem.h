#ifndef _System_EasingSystem_h_
#define _System_EasingSystem_h_

NAMESPACE_ECS_BEGIN

	
class Easing :
	public Component<Easing>
{
	
public:
	RTTI_COMP0(Easing)
	COMP_DEF_VISIT
	
	
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

using EasingRef = Ref<Easing>;



class EasingSystem : public System<EasingSystem>
{
	
public:
	SYS_RTTI(EasingSystem)
    ECS_SYS_CTOR(EasingSystem)
	SYS_DEF_VISIT
	
protected:
    void Update(double) override;
};


NAMESPACE_ECS_END

#endif

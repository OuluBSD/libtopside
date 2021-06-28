#ifndef _OpenLib_MotionController_h_
#define _OpenLib_MotionController_h_

NAMESPACE_TOPSIDE_BEGIN


typedef enum {
	Unspecified,
	Left,
	Right
} SpatialInteractionSourceHandedness;


class MotionControllerComponent :
	public Component<MotionControllerComponent>
{
	
public:
	COPY_PANIC(MotionControllerComponent)
	COMP_DEF_VISIT
	
	
	SpatialInteractionSourceHandedness	req_hand;
	SpatialInteractionSourceLocation	location;
	bool								attach_ctrl_model = false;
	
	
	bool IsSource(const SpatialInteractionSource& src) const;
	
};


class MotionControllerSystem :
    public System<MotionControllerSystem>
{
	
public:
	SYS_RTTI(MotionControllerSystem)
	SYS_CTOR(MotionControllerSystem);
	SYS_DEF_VISIT
	
};


NAMESPACE_TOPSIDE_END

#endif

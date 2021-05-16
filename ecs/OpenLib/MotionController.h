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
	VIS_COMP_0_0
	
public:
	COPY_PANIC(MotionControllerComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
	
	SpatialInteractionSourceHandedness	req_hand;
	SpatialInteractionSourceLocation	location;
	bool								attach_ctrl_model = false;
	
	
	bool IsSource(const SpatialInteractionSource& src) const;
	
};


class MotionControllerSystem :
    public System<MotionControllerSystem>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	SYS_CTOR(MotionControllerSystem);
	
	
};


NAMESPACE_TOPSIDE_END

#endif

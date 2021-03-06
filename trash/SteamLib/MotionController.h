#ifndef _SteamLib_MotionController_h_
#define _SteamLib_MotionController_h_

NAMESPACE_TOPSIDE_BEGIN


typedef enum {
	Unspecified
	
} SpatialInteractionSourceHandedness;


class MotionControllerComponent :
	public Component<MotionControllerComponent>
{
	
	
public:
	RTTI_COMM0(MotionControllerComponent);
	
	
	SpatialInteractionSourceHandedness req_hand;
	bool attach_ctrl_model = false;
	
};


NAMESPACE_TOPSIDE_END

#endif

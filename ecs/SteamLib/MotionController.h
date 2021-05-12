#ifndef _SteamLib_MotionController_h_
#define _SteamLib_MotionController_h_

NAMESPACE_OULU_BEGIN


typedef enum {
	Unspecified
	
} SpatialInteractionSourceHandedness;


class MotionControllerComponent :
	public Component<MotionControllerComponent>
{
	VIS_COMP_0_0
	
public:
	
	
	SpatialInteractionSourceHandedness req_hand;
	bool attach_ctrl_model = false;
	
};


NAMESPACE_OULU_END

#endif

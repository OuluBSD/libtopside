#ifndef _HighAnim_Common_h_
#define _HighAnim_Common_h_

NAMESPACE_TOPSIDE_BEGIN


struct AnimKeypointPlayer;
class AnimObject;


struct AnimFrameHeader {
	int kpi;
	double time;
	int keypoints_per_second;
	
};


struct AnimAction : Moveable<AnimAction> {
	
	typedef enum {
		ACB_NULL,
		ACB_REMOVE_OBJECT,
	} Type;
	
	Type type = ACB_NULL;
	double time = 0;
	double duration = 0;
	
	AnimObject* o0 = 0;
	Callback WhenStop;
	
};


NAMESPACE_TOPSIDE_END

#endif

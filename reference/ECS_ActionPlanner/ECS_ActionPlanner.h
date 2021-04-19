#ifndef _ECS_ActionPlanner_ECS_ActionPlanner_h_
#define _ECS_ActionPlanner_ECS_ActionPlanner_h_

#include <Complete/Complete.h>
using namespace Upp;
using namespace Oulu;


struct DemoEntity :
	public Component<DemoEntity>/*,
	public ActionSource*/
{
	enum {
		CAT,
		MOUSE
	};
	
	int type;
public:
	COPY_PANIC(DemoEntity)
	/*IFACE_GENERIC
	IFACE_CB(ActionSource);*/
	
	void InitCat();
	void InitMouse();
	
	
};

PREFAB_BEGIN(Cat)
	DemoEntity,
	ActionAgent
PREFAB_END

PREFAB_BEGIN(Mouse)
	DemoEntity,
	ActionAgent
PREFAB_END


#endif

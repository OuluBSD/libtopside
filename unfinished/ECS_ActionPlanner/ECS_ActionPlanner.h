#ifndef _ECS_ActionPlanner_ECS_ActionPlanner_h_
#define _ECS_ActionPlanner_ECS_ActionPlanner_h_

#include <Complete/Complete.h>
using namespace UPP;
using namespace TS;


struct DemoCat :
	public Component<DemoCat>,
	public ActionSink
{
	ActionGroup ag;
	
	
	COPY_PANIC(DemoCat)
	IFACE_GENERIC
	IFACE_CB(ActionSink);
	
	void InitCat();
	void InitMouse();
	
	void OnLink(Ref provider, Cookie cookie) override;
	
};

struct DemoMouse :
	public Component<DemoCat>
{
	
};

PREFAB_BEGIN(Cat)
	DemoCat,
	ActionAgent,
	Connector
PREFAB_END

PREFAB_BEGIN(Mouse)
	DemoMouse,
	ActionAgent,
	Connector
PREFAB_END


#endif

#ifndef _ECS_RouteSearch_ECS_RouteSearch_h_
#define _ECS_RouteSearch_ECS_RouteSearch_h_


#include <Complete/Complete.h>
using namespace Upp;
using namespace Oulu;


void TraverseMap(EntityPool& externals, String map, ArrayMap<int, SE>& classes);





/*struct DemoMouse :
	public Component<DemoCat>
{
	
};*/

struct SimpleRouteNode :
	public Component<SimpleRouteNode>,
	public RouteSink,
	public RouteSource
{
	double idle_cost = 0;
	
	COPY_PANIC(SimpleRouteNode);
	IFACE_GENERIC;
	IFACE_CB(RouteSink);
	IFACE_CB(RouteSource);
	
	void SetIdleCost(double d) override {idle_cost = d;}
	
	
};


PREFAB_BEGIN(RouteRoad)
	Connector
PREFAB_END

PREFAB_BEGIN(RouteGround)
	Connector
PREFAB_END

PREFAB_BEGIN(RouteWall)
	Connector
PREFAB_END

PREFAB_BEGIN(RouteWater)
	Connector
PREFAB_END

PREFAB_BEGIN(RouteNode)
	Transform,
	SimpleRouteNode,
	Connector
PREFAB_END


#endif

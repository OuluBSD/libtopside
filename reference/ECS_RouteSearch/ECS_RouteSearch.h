#ifndef _ECS_RouteSearch_ECS_RouteSearch_h_
#define _ECS_RouteSearch_ECS_RouteSearch_h_


#include <Complete/Complete.h>
using namespace Upp;
using namespace Oulu;


void TraverseMap(EntityPool& externals, String map, ArrayMap<int, SE>& classes);





struct GameEntity :
	public Component<GameEntity>
{
	
};

struct RouteFollower :
	public Component<RouteFollower>
{
	
	
	void MakeRouteTo(SE end) {TODO}
	
};

struct SimpleRouteNode :
	public Component<SimpleRouteNode>,
	public RouteSink,
	public RouteSource
{
	double idle_cost = 0;
	
	void operator=(const SimpleRouteNode& n) {
		idle_cost = n.idle_cost;
	}
	
	IFACE_GENERIC;
	IFACE_CB(RouteSink);
	IFACE_CB(RouteSource);
	
	void SetIdleCost(double d) override {idle_cost = d;}
	double GetStepValue(RouteSink& sink) override;
	double GetHeuristicValue(RouteSink& sink) override;
	
};

struct SimpleWaypointNode :
	public Component<SimpleWaypointNode>,
	public RouteSink,
	public RouteSource
{
	double idle_cost = 0;
	
	
	void operator=(const SimpleWaypointNode& n) {
		idle_cost = n.idle_cost;
	}
	
	IFACE_GENERIC;
	IFACE_CB(RouteSink);
	IFACE_CB(RouteSource);
	
	void SetIdleCost(double d) override {idle_cost = d;}
	double GetStepValue(RouteSink& sink) override;
	double GetHeuristicValue(RouteSink& sink) override;
	
	
};


void FindRoute(SE begin, SE end, EntityPool& route);
void MergeRoute(EntityPool& route, EntityPool& waypoints);

PREFAB_BEGIN(DemoActor)
	GameEntity,
	RouteFollower,
	Connector
PREFAB_END

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

PREFAB_BEGIN(WaypointNode)
	Transform,
	SimpleWaypointNode,
	Connector
PREFAB_END



#endif

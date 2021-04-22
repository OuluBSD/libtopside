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
	struct SinkData {
		double value_mul = 0.0;
	};
	
	Array<SinkData> data;
	double idle_cost = 0;
	
	void operator=(const SimpleRouteNode& n) {
		idle_cost = n.idle_cost;
	}
	
	IFACE_GENERIC;
	IFACE_CB(RouteSink);
	IFACE_CB(RouteSource);
	
	void SetIdleCost(double d) override {idle_cost = d;}
	double GetStepValue(const RouteSource::Connection& sink_conn) override;
	double GetHeuristicValue(RouteSink& sink) override;
	void* OnLink(InterfaceBase* iface) override;
	
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




#endif

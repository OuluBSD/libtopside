#ifndef _ECS_RouteSearch_ECS_RouteSearch_h_
#define _ECS_RouteSearch_ECS_RouteSearch_h_


#include <Complete/Complete.h>


NAMESPACE_TOPSIDE_BEGIN


struct Tile : Moveable<Tile> {
	double act_value_mul[9];
	bool invalid[9];
	int value, cls;
	int x, y;
	bool is_begin = false, is_end = false;
	VAR e;
	
	Tile() {
		memset(&act_value_mul, 0, sizeof(act_value_mul));
		memset(&invalid, 0, sizeof(invalid));
	}
	void SetValueMul(int x, int y, double d) {x += 1; y += 1; act_value_mul[y * 3 + x] = d;}
	void Check(Tile* t, int x, int y) {
		if (!t) {
			x += 1; y += 1; invalid[y * 3 + x] = true;
			return;
		}
		if (value == '.' && t->value == '.' && (x == 0 || y == 0))
			SetValueMul(x, y, 0.2);
		else if (value == 'x' || t->value == 'x')
			SetValueMul(x, y, 1000000000.0);
		else if (value == '-' && t->value == '-')
			SetValueMul(x, y, 2.0);
		else if (value == '-' || t->value == '-')
			SetValueMul(x, y, 1.4);
		else
			SetValueMul(x, y, 1.0);
	}
};



void TraverseMap(PoolRef externals, String map);




class DummyActor :
	public Component<DummyActor>,
	public ActionSource
{
	typedef enum {
		INVALID
	} ExType;
	class Ex : public ActionEx {
		
	};
	ExType type = INVALID;
	Ex ex;
	
	typedef Tuple<String, Callback> NameCallback;
	typedef Tuple<ActionGroup, ActionId> ActGroupId;
	struct Group : Moveable<Group> {
		Vector<NameCallback> actions;
		ActionSink* sink = 0;
	};
	Vector<Group> groups;
	String cur_action;
	ActionSink* updated_sink = 0;
	bool has_route = false;
	
public:
	typedef DummyActor CLASSNAME;
	COPY_PANIC(DummyActor);
	IFACE_GENERIC;
	IFACE_CB(ActionSource);
	
	void Act(String cmd);
	void FindRoute();
	void DoSinkAction(ActGroupId a);
	
	void Initialize() override;
	void Uninitialize() override;
	
	void EmitActionSource(double dt) override;
	bool RequestExchange(ActionSink& sink) override;
	bool OnActionSource(ActionEx& e) override;
	
	/*ActionGroup AddActionGroup(ActionSink& sink, int act_count, int atom_count) override;
	void OnActionDone(ActionGroup ag, ActionId act_i, int ret_code) override;
	void SetActionName(ActionGroup ag, ActionId act_i, String name) override;
	void SetCurrentAtom(ActionGroup ag, AtomId atom_i, bool value) override;
	void SetGoalAtom(ActionGroup ag, AtomId atom_i, bool value) override;
	void RefreshActionPlan() override;*/
	
};


class Observer :
	public Component<Observer>,
	public ActionSink
{
	typedef enum {
		INVALID,
		SET_ACTIONS
	} ExType;
	class Ex : public ActionEx {
		
	};
	ExType type = INVALID;
	Ex ex;
	
	Vector<EntityRef> route;
	String last_error;
	ActionGroup ag;
	int route_i = 0;
	bool follow_route = false;
	
public:
	static const char* act_names[];
	
	
	enum {
		TURN_LEFT,
		TURN_LEFT_FAST,
		TURN_RIGHT,
		TURN_RIGHT_RIGHT,
		TURN_UP,
		TURN_DOWN,
		GO_FORWARD,
		GO_FORWARD_FAST,
		GO_BACKWARD,
		GO_BACKWARD_FAST,
		FOLLOW_ROUTE,
		ACT_COUNT
	};
	enum {
		ATOM_COUNT
	};
	
	COPY_PANIC(Observer);
	IFACE_GENERIC;
	IFACE_CB(ActionSink);
	
	bool MakeRouteTo();
	void TeleportToRouteBegin();
	String GetLastError() const {return last_error;}
	
	State* OnLinkActionSource(ActionSource& src) override;
	bool RequestExchange(ActionSource& ssrc) override;
	bool OnActionSink(ActionEx& e) override;
	/*bool Act(ActionGroup ag, ActionId act) override;
	bool UpdateAct() override;*/
	
};

struct SimpleRouteNode :
	public Component<SimpleRouteNode>,
	public RouteSink,
	public RouteSource
{
	struct SinkData : public State {
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
	double GetStepValue(const ExchangePoint& sink_conn) override;
	double GetHeuristicValue(RouteSink& sink) override;
	void OnLink(Ref provider, Cookie cookie) override;
	
};



void FindRoute(VAR begin, VAR end, Pool& route);
void MergeRoute(Pool& route, Pool& waypoints);

PREFAB_BEGIN(DemoActor)
	DummyActor,
	Observer,
	Connector
PREFAB_END

PREFAB_BEGIN(RouteNode)
	Transform,
	SimpleRouteNode,
	Connector
PREFAB_END



NAMESPACE_TOPSIDE_END


#endif

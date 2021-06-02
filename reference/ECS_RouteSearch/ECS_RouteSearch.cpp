#include "ECS_RouteSearch.h"

NAMESPACE_TOPSIDE_BEGIN

void DumpTransforms(String s, PoolRef pool) {
	LOG(s);
	int i = 0;
	for (EntityRef& e : pool->GetEntities()) {
		Ref<Transform> t = e->Find<Transform>();
		if (t) {
			LOG("\t" << i << ": " << e->ToString() << ": " << t->ToString());
		}
		else {
			LOG("\t" << i << ": " << e->ToString() << ": NO TRANSFORM");
		}
		++i;
	}
}

void RunTest() {
	SetCoutLog();
	
	Machine& mach = GetMachine();
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
	EntityStoreRef es = mach.Add<EntityStore>();
	PoolRef root = es->GetRoot();
	PoolRef actors = root->AddPool("actors");
	PoolRef externals = root->AddPool("externals");
	
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    
    
    VAR actor			= actors->CreateConnectedInternal<DemoActor>();
    
    const char* map1 =
		"|A|x| \n"
		"|.|x| \n"
		"|-| |B";
	
    const char* map2 =
		"|A| | | | | | | | | | | | | | | \n"
		"|.|.| | |.|.|.|.|.|.|.|.| | | | \n"
		"| |.| | |.| |x|x|x| | |.| | | | \n"
		"| |.|.|.|.|x|x| |x|x| |.|.| | | \n"
		"| | | | |x|x| | | |x|x| |.| | | \n"
		"| | | |x|x| | | | | | | |.| | | \n"
		"| | | |x| | |.|.|.| |x|x|.|x|x|x\n"
		"| | |x|x| | |.| |.|.| | |.| | |.\n"
		"|-|-|x| | | |.| | |.|.|.|.|.|.|.\n"
		"|-|-|x| |x| |.|.| | |x|x|x| | |.\n"
		"|-|-|x| |x|x|x|.|x|x|x| | | | | \n"
		"|-|-|x| | | |x|x|x| |x|x|x| | | \n"
		"|-|-|x| | |x|x|.| | | |.|x|x|x|x\n"
		"|-|-|-|-|-|x| |.| | |x|.|.|.|.|.\n"
		"|-|-|-|-|.|.|.|.| | |x| | | | |.\n"
		"|-|-|-|-|-|x| | | | | | | | | |B";
	
    const char* map = map2;
    
    try {
	    TraverseMap(externals, map);
	    DumpTransforms("All map points", externals);
	    
	    mach.Start();
	    
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	    }
    }
    catch (Exc e) {
        LOG("error: " << e);
        Exit(1);
    }
    
    mach.Stop();
    
}


void TraverseMap(PoolRef externals, String map) {
	Vector<String> lines = Split(map, "\n");
	if (lines.IsEmpty())
		throw Exc("No lines");
	int width = lines[0].GetCount();
	int height = lines.GetCount();
	if (width < 2 || height < 2)
		throw Exc("Too small resolution. At least 2x2 is expected");
	if (width % 2 != 0)
		throw Exc("width must be even number");
	for(String& line : lines)
		if (line.GetCount() != width)
			throw Exc("Unexpected length in line");
	width /= 2;
	
	Vector<Tile> tiles;
	tiles.SetCount(width * height);
	{
		Tile* t = tiles.Begin();
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				t->x = x;
				t->y = y;
				t++;
			}
		}
	}
	
	enum {
		BIT_NUM = 0x1,
		BIT_LETTER = 0x2,
	};
	
	for(int y = 0; y < lines.GetCount(); y++) {
		const String& line = lines[y];
		for(int x2 = 0; x2 < line.GetCount(); x2++) {
			int value = line[x2];
			int x = x2 / 2;
			dword coord = y * width + x;
			
			if (value == '|') continue;
			
			Tile& t = tiles[x + y * width];
			t.x = x;
			t.y = y;
			if (value == 'A') {
				t.value = '.';
				t.is_begin = true;
			}
			else if (value == 'B') {
				t.value = '.';
				t.is_end = true;
			}
			else
				t.value = value;
		}
	}
	
	for(int i = 0; i < tiles.GetCount(); i++) {
		Tile& ct = tiles[i];
		Tile* tl = ct.x > 0			&& ct.y > 0			? &tiles[ct.x - 1	+ (ct.y - 1) * width] : 0;
		Tile* t  =					   ct.y > 0			? &tiles[ct.x		+ (ct.y - 1) * width] : 0;
		Tile* tr = ct.x < width-1	&& ct.y > 0			? &tiles[ct.x + 1	+ (ct.y - 1) * width] : 0;
		Tile* r  = ct.x < width-1						? &tiles[ct.x + 1	+       ct.y * width] : 0;
		Tile* br = ct.x < width-1	&& ct.y < height-1	? &tiles[ct.x + 1	+ (ct.y + 1) * width] : 0;
		Tile* b  =					   ct.y < height-1	? &tiles[ct.x		+ (ct.y + 1) * width] : 0;
		Tile* bl = ct.x > 0			&& ct.y < height-1	? &tiles[ct.x - 1	+ (ct.y + 1) * width] : 0;
		Tile* l  = ct.x > 0								? &tiles[ct.x - 1	+       ct.y * width] : 0;
		
		ct.Check(tl, -1, -1);
		ct.Check(t,   0, -1);
		ct.Check(tr, +1, -1);
		ct.Check(r,  +1,  0);
		ct.Check(br, +1, +1);
		ct.Check(b,   0, +1);
		ct.Check(bl, -1, +1);
		ct.Check(l,  -1,  0);
		if (ct.value == '-')
			ct.SetValueMul(0, 0, 1);
	}
	
	for (Tile& t : tiles) {
		vec3 pos(t.x, 0, -t.y);
		{
			t.e = externals->Create<RouteNode>();
			Transform& tf = *t.e->Get<Transform>();
			tf.position = pos;
		}
		if (t.is_begin) {
			VAR begin = externals->Create<RouteNode>();
			begin->SetName("begin");
			Transform& tf = *begin->Get<Transform>();
			tf.position = pos;
			tf.position[1] = 1; // but above normal waypoints
			if (0) {
				t.e->GetComponents().Dump();
				begin->GetComponents().Dump();
				Ref<RouteSource> r;
				int i = 0;
				for(Ref<ComponentBase>& base : begin->GetComponents().GetValues()) {\
					LOG(i++ << ": " << base->GetType().CleanDemangledName());
					r = base->AsRouteSource();
					if (r) {
						LOG("");
					}
				}
			}
			Ref<RouteSink> rsink = t.e->FindRouteSink();
			Ref<RouteSource> rsrc = begin->FindRouteSource();
			rsrc->LinkManually(*rsink);
		}
		if (t.is_end) {
			VAR end = externals->Create<RouteNode>();
			end->SetName("end");
			Transform& tf = *end->Get<Transform>();
			tf.position = pos;
			tf.position[1] = 1; // but above normal waypoints
			Ref<RouteSource> rsrc = t.e->FindRouteSource();
			Ref<RouteSink> rsink = end->FindRouteSink();
			rsrc->LinkManually(*rsink);
		}
	}
	
	for (Tile& t : tiles) {
		RouteSource& src = *t.e->FindRouteSource();
		for(int i = 0; i < 9; i++) {
			if (i == 4) {
				src.SetIdleCost(t.act_value_mul[4]);
			}
			else if (i == 0 || i == 2 || i == 2*3+0 || i == 2*3+2) {
				// pass
			}
			else if (t.invalid[i])
				continue;
			else {
				int x_diff = (i % 3) - 1;
				int y_diff = (i / 3) - 1;
				int x = t.x + x_diff;
				int y = t.y + y_diff;
				
				Tile& dst = tiles[x + y * width];
				RouteSink& sink = *dst.e->FindRouteSink();
				
				// Use SinkData what is provided in SimpleRouteNode::OnLink
				State* src_user_arg;
				src.LinkManually(sink, &src_user_arg);
				ASSERT(src_user_arg);
				SimpleRouteNode::SinkData& sink_data = *CastPtr<SimpleRouteNode::SinkData>(src_user_arg);
				sink_data.value_mul = t.act_value_mul[i];
			}
		}
	}
	
}



// A* search

void FindRouteInPool(VAR begin, VAR end, PoolRef route) {
	route->Clear();
	if (begin.IsEmpty() || end.IsEmpty())
		throw Exc("empty begin or end shared-entity");
	
	Ref<RouteSink> end_sink = end->FindRouteSink();
	if (!end_sink)
		throw Exc("No RouteSink in end node");
	
	struct SearchData {
		Entity* e;
		SearchData* came_from;
		double current_value;
	};
	Array<SearchData> data;
	
	struct LinkValue : Moveable<LinkValue> {
		double value;
		SearchData* arg;
		LinkValue() {}
		LinkValue(double v, SearchData* a) {value = v; arg = a;}
		bool operator()(const LinkValue& a, const LinkValue& b) const {return a.value > b.value;}
	};
	typedef Tuple<Entity*,LinkValue> UsedLink;
	Vector<UsedLink> visited;
	visited.Reserve(1024);
	
	typedef TopValueSorterLinkedList<Entity*, LinkValue, LinkValue > Frontier;
	Frontier frontier;
	frontier.Reserve(1024);
	frontier.SetMaxCount(1024);
	
	SearchData& begin_data = data.Add();
	begin_data.e = &*begin;
	begin_data.came_from = 0;
	begin_data.current_value = 0;
	LinkValue begin_value(-DBL_MAX, &begin_data);
	frontier.Add(begin_data.e, begin_value);
	
	SearchData* end_data = 0;
	
	int max_iters = 100000;
	int iter = 0;
	while (!frontier.IsEmpty() && iter++ < max_iters) {
		Frontier::Item current = frontier.PickFirst();
		UsedLink& ul = visited.Add();
		ul.a = current.key;
		ul.b = current.value;
		
		// Break when end is found
		if (current.key == &*end) {
			end_data = current.value.arg;
			break;
		}
		
		// Get clean references
		Entity& e = *current.key;
		const SearchData& current_data = *current.value.arg;
		
		// Find the beginning of the step (RouteSource)
		Ref<RouteSource> src = e.FindRouteSource();
		if (!src)
			continue;
		
		// Loop neighbours (end of steps, RouteSink interfaces)
		int dbg_i = 0;
		for (const auto& c : src->GetSinks()) {
			RouteSink& sink = *c.sink;
			
			// Get the neighbour entity from the interface object
			Entity& dst = sink.AsComponentBase()->GetEntity();
			
			// Calculate heuristic value to the end
			// The RouteSource interface of the neighbour entity calculates heuristics.
			Ref<RouteSource> dst_src = dst.FindRouteSource();
			if (!dst_src)
				continue; // dead-end
			double heuristic_value = dst_src->GetHeuristicValue(*end_sink);
			
			// Normal A* stuff
			double step_value = src->GetStepValue(c);
			double current_value = current_data.current_value + step_value;
			double new_value = current_value + heuristic_value;
			
			// Debug printing
			if (0) {
				Transform& dst_t = *dst.Find<Transform>();
				LOG(dbg_i << ": " << dst_t.ToString() << ": " << new_value);
			}
			
			// This is rather complicated method to avoid useless searching.
			
			// Existing iterator is usually kept inside TopValueSorterLinkedList,
			// but we bring it here to get reference to SearchData, which speeds up the process.
			SearchData* sink_data = 0;
			Frontier::Item* existing_iter = frontier.Find(&dst);
			if (existing_iter) {
				if (new_value > existing_iter->value.value) {
					sink_data = existing_iter->value.arg;
					
					// As in TopValueSorterLinkedList::SetAdd
					LinkValue new_link_value(new_value, sink_data);
					if (!frontier.UpdateValue(existing_iter, new_link_value)) {
						frontier.RemoveItem(existing_iter);
						frontier.Add(&dst, new_link_value);
					}
				}
			}
			// In normal case, the reference to SearchData is searched here, but after the
			// previous speed-up, we can loop only the used links. If it's not there, it's new.
			else {
				bool skip = false;
				int i = 0;
				for (UsedLink& ul : visited) {
					LinkValue& lv = ul.b;
					if (ul.a == &dst) {
						sink_data = lv.arg;
						if (sink_data->current_value < current_value) {
							ASSERT(lv.value < new_value);
							// Add back to frontier
							visited.Remove(i);
							LinkValue new_link_value(new_value, sink_data);
							frontier.Add(&dst, new_link_value);
						}
						else {
							skip = true;
							sink_data = 0;
						}
						break;
					}
					i++;
				}
				
				// Create new data if this is completely unvisited entity
				if (!skip && !sink_data) {
					sink_data = &data.Add();
					sink_data->e = &dst;
					LinkValue new_link_value(new_value, sink_data);
					frontier.Add(&dst, new_link_value);
				}
			}
			
			// Update data
			if (sink_data) {
				sink_data->came_from = current.value.arg;
				sink_data->current_value = current_value;
			}
			
			dbg_i++;
		}
	}
	
	// Make the result route vector, if endpoint was found.
	if (end_data) {
		SearchData* iter = end_data;
		while (iter) {
			//route.Add(iter->e->GetSharedFromThis());
			route->Clone(*iter->e);
			iter = iter->came_from;
		}
		route->ReverseEntities();
	}
}

void ConnectRoute(RouteSource& src, RouteSink& sink) {
	src.LinkManually(sink);
}

void MergeRoute(PoolRef route, PoolRef waypoints) {
	struct Item : Moveable<Item> {
		EntityRef e;
		Ref<RouteSource> src;
		Ref<RouteSink> sink;
		void Set(EntityRef e, Ref<RouteSource> src, Ref<RouteSink> sink) {
			this->e = e;
			this->src = src;
			this->sink = sink;
		}
	};
	ArrayMap<vec3, Item> ents;
	
	for (EntityRef& e : waypoints->GetEntities())
		ents.Add(e->Get<Transform>()->position).Set(&*e, e->FindRouteSource(), e->FindRouteSink());
	
	int dbg_i = 0;
	Item* prev = 0;
	for (EntityRef& e : route->GetEntities()) {
		vec3 position = e->Get<Transform>()->position;
		int i = ents.Find(position);
		Item* it;
		if (i < 0) {
			EntityRef new_e = waypoints->Clone(*e);
			it = &ents.Add(position);
			it->e		= &*new_e;
			it->src		= new_e->FindRouteSource();
			it->sink	= new_e->FindRouteSink();
		}
		else {
			it = &ents[i];
		}
		
		if (prev)
			ConnectRoute(*prev->src, *it->sink);
		
		prev = it;
		dbg_i++;
	}
	
}



double SimpleTransformValue(Entity& a, Entity& b) {
	Ref<Transform> src = a.Find<Transform>();
	Ref<Transform> dst = b.Find<Transform>();
	ASSERT(src && dst);
	double dist = (dst->position - src->position).GetLength();
	
	// the value is negative distance, because we want shortest distance
	return -dist;
}

double SimpleRouteNode::GetStepValue(const ExchangePoint& c) {
	TODO
	/*SinkData& sink_data = *CastPtr<SinkData>(c.src_state);
	double value = SimpleTransformValue(GetEntity(), c.sink->AsComponentBase()->GetEntity());
	//ASSERT(sink_data.value_mul > 0.0);
	double result = value * sink_data.value_mul;
	return result;*/
}

double SimpleRouteNode::GetHeuristicValue(RouteSink& sink) {
	return SimpleTransformValue(GetEntity(), sink.AsComponentBase()->GetEntity());
}

void SimpleRouteNode::OnLink(Ref provider, Cookie cookie) {
	// this fails if component has both sink and source: RouteSink* sink = CastPtr<RouteSink>(iface);
	
	TODO
	/*if (iface->GetValDevSpec() == AsTypeId(RouteSink))
		return &data.Add();
	
	return 0;*/
}



const char* Observer::act_names[] = {
	"turn_left",
	"turn_left_fast",
	"turn_right",
	"turn_right_fast",
	"turn_up",
	"turn_down",
	"go_forward",
	"go_forward_fast",
	"go_backward",
	"go_backward_fast",
	"follow_route",
	0
};

bool Observer::MakeRouteTo() {
	PoolRef waypoints = GetEntity().GetPool().GetAddPool("waypoints");
    VAR begin	= waypoints->FindEntityByName("begin");
    VAR end		= waypoints->FindEntityByName("end");
    if (begin.IsEmpty() || end.IsEmpty()) {
        last_error = "route has no begin and end nodes";
        return false;
    }
	
	route.Clear();
	
	VAR current = begin;
	while (1) {
		route.Add(current);
		
		if (current == end)
			break;
		
		Ref<RouteSource> from_src = current->FindRouteSource();
		if (!from_src) {
			last_error = "entity has no RouteSource";
			return false;
		}
		
		const auto& sinks = from_src->GetSinks();
		if (sinks.IsEmpty()) {
			last_error = "RouteSource has no sinks";
			return false;
		}
		
		const auto& conn = sinks[0];
		ComponentBase* b = conn.sink->AsComponentBase();
		Entity& next = b->GetEntity();
		
		current = next;
	}
	
	route_i = 0;
    
	return true;
}

void Observer::TeleportToRouteBegin() {
	if (route.GetCount())
		CopyTransformPos(route[0], GetEntity());
}

State* Observer::OnLinkActionSource(ActionSource& src) {
	type = SET_ACTIONS;
	src.RequestExchange(*this);
	return 0;
}

bool Observer::RequestExchange(ActionSource& src) {
	return src.OnActionSource(ex);
}

bool Observer::OnActionSink(ActionEx& e) {
	if (type == SET_ACTIONS) {
		TODO
		/*ag = e.AddActionGroup(*this, ACT_COUNT, ATOM_COUNT);
		for(int i = 0; i < ACT_COUNT; i++)
			e.SetActionName(ag, i, act_names[i]);*/
		return true;
	}
	return false;
}

/*bool Observer::Act(ActionGroup ag, ActionId act) {
	ASSERT(ag == this->ag);
	if (act == FOLLOW_ROUTE) {
		follow_route = true;
		return true; // Keep updating act
	}
	else {
		TODO
	}
	return false;
}

bool Observer::UpdateAct() {
	if (follow_route) {
		Pool& waypoints = GetEntity().GetPool().GetAddPool("waypoints");
		ASSERT(waypoints.GetCount());
		if (route_i < waypoints.GetCount()) {
			TODO;
			return true;
		}
		return false;
	}
	return false;
}*/








void DummyActor::Initialize() {
	Ref<ActionSystem> as = GetMachine().Get<ActionSystem>();
	if (as)
		as->Add(this);
	
	auto& g = groups.Add();
	g.actions.Add(NameCallback("find_route", THISBACK(FindRoute)));
}

void DummyActor::Uninitialize() {
	Ref<ActionSystem> as = GetMachine().Get<ActionSystem>();
	if (as)
		as->Remove(this);
}

void DummyActor::EmitActionSource(double dt) {
	if (cur_action.IsEmpty()) {
		if (!has_route) {
			Act("find_route");
		}
		else {
			Act("follow_route");
			ASSERT(cur_action.GetCount());
		}
	}
	TODO
	//if (updated_sink && !updated_sink->UpdateAct())
	//	updated_sink = 0;
	
}

bool DummyActor::RequestExchange(ActionSink& sink) {
	return sink.OnActionSink(ex);
}

bool DummyActor::OnActionSource(ActionEx& e) {
	TODO
}

void DummyActor::Act(String cmd) {
	for(auto& ag : groups) {
		for(auto& act : ag.actions) {
			if (act.a == cmd) {
				LOG("DummyActor: starting action '" << cmd << "'");
				cur_action = act.a;
				act.b();
				return;
			}
		}
	}
}

/*
void DummyActor::OnActionDone(ActionGroup ag, ActionId act_i, int ret_code) {
	cur_action.Clear();
}

ActionGroup DummyActor::AddActionGroup(ActionSink& sink, int act_count, int atom_count) {
	int i = groups.GetCount();
	auto& g = groups.Add();
	g.sink = &sink;
	g.actions.SetCount(act_count);
	return i;
}

void DummyActor::SetActionName(ActionGroup ag, ActionId act_i, String name) {
	groups[ag].actions[act_i] = NameCallback(name, THISBACK1(DoSinkAction, ActGroupId(ag, act_i)));
}

void DummyActor::SetCurrentAtom(ActionGroup ag, AtomId atom_i, bool value) {
	Panic("not implemented");
}

void DummyActor::SetGoalAtom(ActionGroup ag, AtomId atom_i, bool value) {
	Panic("not implemented");
}

void DummyActor::RefreshActionPlan() {
	Panic("not implemented");
}
*/


void DummyActor::FindRoute() {
	PoolRef root = GetMachine().Get<EntityStore>()->GetRoot();
	PoolRef externals = root->GetAddPool("externals");
	PoolRef found_route = root->GetAddPool("found_route");
	PoolRef waypoints = GetEntity().GetPool().GetAddPool("waypoints");
	
    VAR begin	= externals->FindEntityByName("begin");
    VAR end		= externals->FindEntityByName("end");
    if (begin.IsEmpty() || end.IsEmpty())
        throw Exc("Map did not have start and end points. Add 'A' and 'B' tiles.");
    
    FindRouteInPool(begin, end, found_route);
    DumpTransforms("Found route", found_route);
    
    MergeRoute(found_route, waypoints);
    DumpTransforms("All valid routes", waypoints);
    
    
    Ref<Observer> rflw = GetEntity().Find<Observer>();
    if (!rflw->MakeRouteTo())
        throw Exc(rflw->GetLastError());
    
    rflw->TeleportToRouteBegin();
    
    cur_action.Clear();
    has_route = true;
}

void DummyActor::DoSinkAction(ActGroupId a) {
	Group& g = groups[a.a];
	ASSERT(g.sink);
	if (g.sink) {
		TODO
		//if (g.sink->Act(a.a, a.b))
		//	updated_sink = g.sink;
	}
}

NAMESPACE_TOPSIDE_END

CONSOLE_APP_MAIN {
	TS::RunTest();
}

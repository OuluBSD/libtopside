#include "ECS_RouteSearch.h"

void DumpTransforms(String s, EntityPool& pool) {
	LOG(s);
	for(int i = 0; i < pool.GetCount(); i++) {
		SharedEntity& e = pool.Get(i);
		Transform* t = e->Find<Transform>();
		if (t) {
			LOG("\t" << i << ": " << e.ToString() << ": " << t->ToString());
		}
		else {
			LOG("\t" << i << ": " << e.ToString() << ": NO TRANSFORM");
		}
	}
}

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	Machine& mach = GetMachine();
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& es = *mach.Add<EntityStore>();
	EntityPool& root = es.GetRoot();
	EntityPool& actors = root.AddPool("actors");
	EntityPool& externals = root.AddPool("externals");
	EntityPool& external_cls = root.AddPool("external_classes");
	EntityPool& waypoints = root.AddPool("waypoints");
	EntityPool& found_route = root.AddPool("found_route");
	
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    //mach.Add<RouteSystem>();
    
    
    SE actor			= actors.Create<DemoActor>();
    SE road_cls			= external_cls.Create<RouteRoad>();
    SE ground_cls		= external_cls.Create<RouteGround>();
    SE wall_cls			= external_cls.Create<RouteWall>();
    SE water_cls		= external_cls.Create<RouteWater>();
    
    ArrayMap<int, SE> classes;
    classes.Add('.', road_cls);
    classes.Add('x', wall_cls);
    classes.Add(' ', ground_cls);
    classes.Add('-', water_cls);
    
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
	    TraverseMap(externals, map, classes);
	    
	    DumpTransforms("All waypoints", externals);
	    {
		    SE begin	= externals.FindEntityByName("begin");
		    SE end		= externals.FindEntityByName("end");
		    if (begin.IsEmpty() || end.IsEmpty())
		        throw Exc("Map did not have start and end points. Add 'A' and 'B' tiles.");
		    
		    FindRoute(begin, end, waypoints);
		    DumpTransforms("Found route", waypoints);
		    //DUMPC(route);
		    
		    MergeRoute(waypoints, found_route);
		    //LOG("Merged pool:"); DUMPC(found_route.GetEntities());
		    DumpTransforms("All valid routes", found_route);
	    }
	    
	    {
		    SE begin	= found_route.FindEntityByName("begin");
		    SE end		= found_route.FindEntityByName("end");
		    if (begin.IsEmpty() || end.IsEmpty())
		        throw Exc("internal error");
		    
		    CopyTransformPos(begin, actor);
		    RouteFollower* rflw = actor->Find<RouteFollower>();
		    rflw->MakeRouteTo(end);
	    }
	    
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


void TraverseMap(EntityPool& externals, String map, ArrayMap<int, SE>& classes) {
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
	
	struct Tile : Moveable<Tile> {
		double act_value_mul[9];
		bool invalid[9];
		int value, cls;
		int x, y;
		bool is_begin = false, is_end = false;
		SE e;
		
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
			t.cls = classes.Find(t.value);
			if (t.cls < 0)
				throw Exc("Map value is not defined in classes: " + IntStr(value));
			
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
			t.e = externals.Create<RouteNode>();
			Transform& tf = *t.e->Get<Transform>();
			tf.position = pos;
		}
		if (t.is_begin) {
			SE begin = externals.Create<RouteNode>();
			begin->SetName("begin");
			Transform& tf = *begin->Get<Transform>();
			tf.position = pos;
			tf.position[1] = 1; // but above normal waypoints
			RouteSink& rsink = *t.e->FindRouteSink();
			RouteSource& rsrc = *begin->FindRouteSource();
			rsrc.LinkManually(rsink);
		}
		if (t.is_end) {
			SE end = externals.Create<RouteNode>();
			end->SetName("end");
			Transform& tf = *end->Get<Transform>();
			tf.position = pos;
			tf.position[1] = 1; // but above normal waypoints
			RouteSource& rsrc = *t.e->FindRouteSource();
			RouteSink& rsink = *end->FindRouteSink();
			rsrc.LinkManually(rsink);
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
				void* src_user_arg;
				src.LinkManually(sink, &src_user_arg);
				ASSERT(src_user_arg);
				SimpleRouteNode::SinkData& sink_data = *(SimpleRouteNode::SinkData*)src_user_arg;
				sink_data.value_mul = t.act_value_mul[i];
			}
		}
	}
	
}



// A* search

void FindRoute(SE begin, SE end, EntityPool& route) {
	route.Clear();
	if (begin.IsEmpty() || end.IsEmpty())
		throw Exc("empty begin or end shared-entity");
	
	RouteSink* end_sink = end->FindRouteSink();
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
		RouteSource* src = e.FindRouteSource();
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
			RouteSource* dst_src = dst.FindRouteSource();
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
			route.Clone(*iter->e);
			iter = iter->came_from;
		}
		route.ReverseEntities();
	}
}

void ConnectRoute(RouteSource& src, RouteSink& sink) {
	src.LinkManually(sink);
}

void MergeRoute(EntityPool& route, EntityPool& waypoints) {
	struct Item : Moveable<Item> {
		Entity* e = 0;
		RouteSource* src = 0;
		RouteSink* sink = 0;
		void Set(Entity* e, RouteSource* src, RouteSink* sink) {
			this->e = e;
			this->src = src;
			this->sink = sink;
		}
	};
	VectorMap<vec3, Item> ents;
	
	for (SharedEntity& e : waypoints.GetEntities())
		ents.Add(e->Get<Transform>()->position).Set(&*e, e->FindRouteSource(), e->FindRouteSink());
	
	int dbg_i = 0;
	Item* prev = 0;
	for (SharedEntity& e : route.GetEntities()) {
		vec3 position = e->Get<Transform>()->position;
		int i = ents.Find(position);
		Item* it;
		if (i < 0) {
			SharedEntity new_e = waypoints.Clone(*e);
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
	Transform* src = a.Find<Transform>();
	Transform* dst = b.Find<Transform>();
	ASSERT(src && dst);
	double dist = (dst->position - src->position).GetLength();
	
	// the value is negative distance, because we want shortest distance
	return -dist;
}

double SimpleRouteNode::GetStepValue(const RouteSource::Connection& c) {
	SinkData& sink_data = *(SinkData*)c.src_arg;
	double value = SimpleTransformValue(GetEntity(), c.sink->AsComponentBase()->GetEntity());
	//ASSERT(sink_data.value_mul > 0.0);
	double result = value * sink_data.value_mul;
	return result;
}

double SimpleRouteNode::GetHeuristicValue(RouteSink& sink) {
	return SimpleTransformValue(GetEntity(), sink.AsComponentBase()->GetEntity());
}

void* SimpleRouteNode::OnLink(InterfaceBase* iface) {
	// this fails if component has both sink and source: RouteSink* sink = dynamic_cast<RouteSink*>(iface);
	
	if (iface->GetInterfaceType() == typeid(RouteSink))
		return &data.Add();
	
	return 0;
}





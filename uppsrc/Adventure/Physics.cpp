#include "Adventure.h"

namespace Adventure {



// collision detection
void Program::CheckCollisions() {
	auto& global = ctx.global;
	
	// check for (current room
	if (room_curr.IsVoid())
		return;
		
	// reset hover collisions
	hover_curr_verb			= HiValue();
	hover_curr_default_verb	= HiValue();
	hover_curr_object		= HiValue();
	//hover_curr_sentence	= HiValue();
	hover_curr_arrow		= HiValue();
	
	// are we in dialog mode?
	if (dialog_curr && dialog_curr.visible) {
		for (Sentence& s : dialog_curr.sentences) {
			if (IsCursorColliding(s))
				hover_curr_sentence = &s;
		}
		// skip remaining collisions
		return;
	}
	
	// reset zplane info
	ResetZPlanes();
	
	// check room/object collisions
	HiValue objects = room_curr["objects"];
	Vector<HiValue>& room_arr = const_cast<Vector<HiValue>&>(objects.GetArray());
	for (HiValue& obj : room_arr) {
		// capture bounds (even for ("invisible", but not untouchable/dependent, objects)
		HiValue c = Classes(obj);
		HiValue dep_on = global.Get(obj.MapGet("dependent_on").ToString(), HiValue());
		if ((c.IsVoid() || (!c.IsVoid() && !HasFlag(c, "class_untouchable")))
			&& (dep_on.IsVoid() // object has a valid dependent state?
			 || dep_on.MapGet("state") == obj.MapGet("dependent_on_state"))) {
			int w = obj.MapGet("w").GetInt();
			int h = obj.MapGet("h").GetInt();
			RecalculateBounds(obj, w*8, h*8, cam.x, cam.y);
		}
		else {
			// reset bounds
			obj.Set("bounds", HiValue());
		}
		
		if (IsCursorColliding(obj)) {
			// if (highest (or first) object in hover "stack"
			int obj_z = obj.MapGet("z").GetInt();
			int hover_curr_object_z = hover_curr_object.IsMap() ? hover_curr_object.MapGet("z").GetInt() : 0;
			int max_z = max(obj_z, hover_curr_object_z);
			if (hover_curr_object.IsVoid() || max_z == obj_z) {
				hover_curr_object = obj;
			}
		}
		// recalc z-plane
		RecalcZPlane(obj);
	}
	
	SObj selected_actor = GetSelectedActor();
	
	// check actor collisions
	SObj actors = global.Get("actors", HiValue());
	if (actors.IsArray()) {
		int actor_count = actors.GetArray().GetCount();
		for(int k = 0; k < actor_count; k++) {
			SObj actor = actors.ArrayGet(k);
			if (actor["in_room"] == room_curr) {
				RecalculateBounds(actor, (int)actor["w"]*8, (int)actor["h"]*8, cam.x, cam.y);
				
				// recalc z-plane
				RecalcZPlane(actor);
				
				// are we colliding (ignore self!)
				if (IsCursorColliding(actor) && actor != selected_actor)
					hover_curr_object = actor;
			}
		}
	}
	
	if (selected_actor) {
		// check ui/inventory collisions
		for (const HiValue& v : verbs.GetArray()) {
			if (IsCursorColliding(v))
				hover_curr_verb = v;
		}
		for (const HiValue& a : ui_arrows.GetArray()) {
			if (IsCursorColliding(a))
				hover_curr_arrow = a;
		}
		    
		// check room/object collisions
		for (const HiValue& obj : selected_actor["inventory"].GetArray()) {
			if (IsCursorColliding(obj)) {
				hover_curr_object = obj;
				// pickup override for (inventory objects
				if (verb_curr == V_PICKUP && !hover_curr_object.MapGet("owner").IsVoid())
					verb_curr = HiValue();
			}
			// check for (disowned objects!
			if (obj.MapGet("owner") != selected_actor)
				selected_actor["inventory"].ArrayRemoveValue(obj);
		}
		
		// default to walkto (if (nothing set)
		if (!verb_curr)
			verb_curr = GetVerb(verb_default);
		
		// update "default" verb for (hovered object (if (any)
		hover_curr_default_verb =
			hover_curr_object ? FindDefaultVerb(hover_curr_object) : hover_curr_default_verb;
	}
}



void Program::ResetZPlanes() {
	draw_zplanes.Clear();
	draw_zplanes.SetCount(64*2+1); // -64 to +64
}

void Program::RecalcZPlane(SObj& obj) {
	// calculate the correct z-plane
	// based on obj || x,y pos + elevation
	HiValue y = obj.MapGet("y");
	HiValue h = obj.MapGet("h");
	HiValue z = obj.MapGet("z");
	HiValue offset_y = obj.MapGet("offset_y");
	int idx;
	if (z.IsInt())
		idx = z.GetInt();
	else {
		int hi = h.IsInt() ? h.GetInt() : 0;
		int yi = y.IsInt() ? y.GetInt() : 0;
		int offset_yi = offset_y.IsInt() ? offset_y.GetInt() : 0;
		idx = (int)(yi + (offset_yi ? 0 : hi * 8));
	}
	draw_zplanes[idx].objs.Add(obj);
}

bool Program::IsCellWalkable(int celx, int cely) {
	const uint16* m = map.Begin();
	int img_w = map_sz.cx;
	int img_h = map_sz.cy;
	ASSERT(celx >= 0 && celx < img_w);
	ASSERT(cely >= 0 && cely < img_h);
	int i = (cely * img_w) + celx;
	uint16 tile = *(m + i);
	
	ASSERT(tile >= 0 && tile < gff.GetCount());
	uint16 flag = *(gff + tile);
	
	bool r = flag & 1;
	return r;
}


void Program::RecalculateBounds(SObj o, int w, int h, int cam_off_x, int cam_off_y) {
	int x = o("x");
	int y = o("y");
	
	// offset for (actors?
	if (HasFlag(Classes(o), "class_actor")) {
		int w = o("w");
		int h = o("h");
		int offset_x = x - (w * 8) / 2;
		int offset_y = y - (h * 8) + 1;
		x = offset_x;
		y = offset_y;
		o.Set("offset_x", offset_x);
		o.Set("offset_y", offset_y);
	}
	
	HiValue bounds;
	bounds.SetEmptyMap();
	bounds.Set("x", x);
	bounds.Set("y", y + stage_top);
	bounds.Set("x1", x + w - 1);
	bounds.Set("y1", y + h + stage_top - 1);
	bounds.Set("cam_off_x", cam_off_x);
	bounds.Set("cam_off_y", cam_off_y);
	o.Set("bounds", bounds);
}



//
// a* pathfinding functions
//

double Program::GetHeuristic(Point chk, Point goal) {
	double h = max(abs(goal.x - chk.x), abs(goal.y - chk.y)) + min(abs(goal.x - chk.x), abs(goal.y - chk.y)) * .414;
	return h;
}

void Program::FindPath(Point start, Point goal, Vector<Point>& path) {
	path.SetCount(0);
	
	struct Node {
		Point pt;
		Node* came_from;
		double cost;
		double heuristic;
		
		void Set(Point p, Node* came, double c, double h) {pt = p; came = came_from; cost = c; heuristic = h;}
	};
	ArrayMap<Point, Node> frontier, visited;
	frontier.Add(start).Set(start, 0, 0, GetDistance(start, goal));
	
	const int frontier_limit = 1000;
	
	SObj map = room_curr("map");
	int rc_map_x = map[0];
	int rc_map_y = map[1];
	int rc_map_w = map[2];
	int rc_map_h = map[3];
	Node* lowest_dist_node = 0;
	while (!frontier.IsEmpty() && frontier.GetCount() < frontier_limit) {
		double lowest_dist = DBL_MAX;
		lowest_dist_node = 0;
		int lowest_dist_i = -1, i = 0;
		for (Node& n : frontier.GetValues()) {
			bool fast_exit = n.pt == goal;
			if (fast_exit || n.heuristic < lowest_dist) {
				lowest_dist = n.heuristic;
				lowest_dist_node = &n;
				lowest_dist_i = i;
				if (fast_exit)
					break;
			}
			i++;
		}
		
		// pop the last element off a table
		Node& current = *lowest_dist_node;
		visited.Add(current.pt, frontier.Detach(lowest_dist_i));
		
		if (current.pt == goal)
			break;
		
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (x == 0 && y == 0) continue;
				
				Point next_pt(current.pt.x + x, current.pt.y + y);
				
				if (    next_pt.x >= rc_map_x && next_pt.x <= rc_map_x + rc_map_w
					and next_pt.y >= rc_map_y && next_pt.y <= rc_map_y + rc_map_h
					and IsCellWalkable(next_pt.x, next_pt.y)
					
					// squeeze check for (corners
					and((abs(x) != abs(y))
						or IsCellWalkable(next_pt.x, current.pt.y)
						or IsCellWalkable(next_pt.x - x, next_pt.y)
						or enable_diag_squeeze)) {
					// process a valid neighbor
					double new_cost = current.cost + (x * y == 0 ? 1.0 : 1.414); // diagonals cost more
					
					int next_i = visited.Find(next_pt);
					Node* next = next_i >= 0 ? &visited[next_i] : 0;
					if (!next || new_cost < next->cost) {
						if (next)
							frontier.Add(next_pt, visited.Detach(next_i));
						else
							next = &frontier.Add(next_pt);
						next->pt = next_pt;
						next->cost = new_cost;
						next->came_from = &current;
						next->heuristic = new_cost + GetHeuristic(next_pt, goal);
					}
				}
			}
		}
	}
	if (!lowest_dist_node)
		return;
	
	int i = 0;
	Node* n = lowest_dist_node;
	while (n) {
		path.Add(n->pt);
		n = n->came_from;
		if (++i >= 10000) {
			ASSERT(0);
			path.SetCount(0);
			return;
		}
	}
	int c = path.GetCount();
	int c_2 = c / 2;
	for(int i = 0; i < c_2; i++)
		Swap(path[i], path[c-1-i]);
	
}


// collision check
bool Program::IsCursorColliding(const Sentence& obj) {
	// check params / not in cutscene
	if (cutscene_curr) return false;
	const Bounds& b = obj.bounds;
	return !((cursor_x + b.cam_off_x > b.x1 || cursor_x + b.cam_off_x < b.x) || (cursor_y > b.y1 || cursor_y < b.y));
}

bool Program::IsCursorColliding(const SObj& obj) {
	// check params / not in cutscene
	HiValue bounds = obj("bounds");
	if (!bounds || cutscene_curr) return false;

	int cam_off_x = bounds["cam_off_x"];
	int x1 = bounds["x1"];
	int y1 = bounds["y1"];
	int x = bounds["x"];
	int y = bounds["y"];
	
	return !((cursor_x + cam_off_x > x1 || cursor_x + cam_off_x < x) || (cursor_y > y1 || cursor_y < y));
}


}

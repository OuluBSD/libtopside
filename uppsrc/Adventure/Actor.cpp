#include "Adventure.h"

namespace Adventure {
	

SObj Program::GetSelectedActor() {
	auto& global = ctx.global;
	//DUMPC(global.GetKeys());
	//ASSERT(global.Find("selected_actor") >= 0);
	return global.Get("selected_actor", HiValue());
}


// actions to perform when object doesn't have an entry for (verb
void Program::UnsupportedAction(HiValue verb, SObj& obj1, SObj& obj2) {
	bool is_actor = HasFlag(Classes(obj1), "class_actor");

	if (verb == V_WALKTO)
		return;

	else if (verb == V_PICKUP)
		SayLine(is_actor ? "i don't need them" : "i don't need that");

	else if (verb == V_USE)
		SayLine(is_actor ? obj1 : obj2,
			is_actor ? "i can't just *use* someone" :
				(HasFlag(Classes(obj2), "class_actor") ?
					"i can't use that on someone!" : "that doesn't work"));

	else if (verb == V_GIVE)
		SayLine(is_actor ? "i don't think i should be giving this away" : "i can't do that");

	else if (verb == V_LOOKAT)
		SayLine(is_actor ? "i think it's alive" : "looks pretty ordinary");

	else if (verb == V_OPEN || verb == V_CLOSE)
		SayLine(String(is_actor ? "they don't" : "it doesn't")  + " seem to " + GetVerbString(verb));

	else if (verb == V_PUSH || verb == V_PULL)
		SayLine(is_actor ? "moving them would accomplish nothing" : "it won't budge!");

	else if (verb == V_TALKTO)
		SayLine(is_actor ? "erm ...  i don't think they want to talk" : "i am not talking to that!");

	else
		SayLine("hmm. no.");
	
}

void Program::PickupObj(SObj& obj, SObj& actor) {
	// use actor spectified, || default to selected
	if (actor.IsVoid())
		actor = GetSelectedActor();
	
	TODO
	/*add(actor.inventory, obj);
	obj.owner = actor;
	// remove it from room
	
	del(obj.in_room.objects, obj);*/
}

// uses actor's position and color
void Program::SayLine(SObj& actor, String msg, bool use_caps, float duration) {
	TODO
	/*
	// check for (missing actor
	if (type(actor) == "string") {
		// assume actor ommitted and default to current
		msg, actor = actor, selected_actor;
	}

	// trigger actor's talk anim
	talking_actor = actor;
	
	// offset to display speech above actors (dist in px from their feet)
	// call the base PrintLine to show actor line
	PrintLine(msg, actor.x, actor.y - actor.h * 8 + 4, actor.col, 1, use_caps, duration);
	*/
}

void Program::SayLine(String msg) {
	TODO
}

// stop everyone talking & remove displayed text
void Program::StopTalking() {
	talking_curr.enabled = false;
	talking_actor = HiValue();
}

void Program::StopActor(SObj& actor) {
	// 0=stopped, 1=walking, 2=arrived
	actor.Set("moving", 0);
	actor.Set("curr_anim", 0);
	
	// no need to) {DoAnim(idle) here, as actor_draw code handles this
	ClearCurrCmd();
}

// walk actor to position
void Program::WalkTo(SObj a, int x, int y) {
	Point actor_cell_pos = GetCellPos(a);
	HiValue map = room_curr("map");
	int map_x = map(0,0);
	int map_y = map(1,0);
	int celx = x / 8 + map_x;
	int cely = y / 8 + map_y;
	Point target_cell_pos(celx, cely);
	
	// use pathfinding!
	FindPath(actor_cell_pos, target_cell_pos, path);
	
	a.Set("moving", 1);
	
	for (int c = 0; c < path.GetCount(); c++) {
		Point p = path[c];
		
		// auto-adjust walk-speed for (depth
		double walk_speed = a("walk_speed");
		SObj scale = a("scale");
		SObj auto_scale = a("auto_scale", 1.0);
		double s = scale ? scale : auto_scale;
		double scaled_speed = walk_speed * s;
		
		//local y_speed = actor.walk_speed/2 // removed, messes up the a* pathfinding
		SObj rc_map = room_curr("map");
		int rc_map_x = rc_map[0];
		int rc_map_y = rc_map[1];
		int px = (p.x - rc_map_x) * 8 + 4;
		int py = (p.y - rc_map_y) * 8 + 4;
		
		// last cell (walk to precise location, if (clicked in it)
		if (c == path.GetCount() && x >= px-4 && x <= px+4 && y >= py-4 && y <= py+4) {
			px = x;
			py = y;
		}
		
		int actor_x = a("x");
		int actor_y = a("y");
		double distance = sqrt(pow(px - actor_x, 2) + pow(py - actor_y, 2));
		double step_x = scaled_speed * (px - actor_x) / distance;
		double step_y = scaled_speed * (py - actor_y) / distance;
		
		// only walk if (we're not already there!
		if (distance > 0) {
		
			//walking
			
			int lim = distance / scaled_speed - 1;
			for (int i = 0; i < lim; i++) {
			
				// todo: need to somehow recalc here, else walk too fast/slow in depth planes
				
				// abort if (actor stopped
				int m = a("moving", 0);
				if (m == 0) {
					return;
				}
			    
				a.Set("flip", step_x < 0);
				    
				// choose walk anim based on dir
				//if (abs(step_x) < abs(step_y) {
				if (abs(step_x) < scaled_speed / 2) {
					// vertical walk
					a.Set("curr_anim", step_y > 0 ? a("walk_anim_front") : a("walk_anim_back"));
					a.Set("face_dir", step_y > 0 ? "face_front" : "face_back");
				}
				else {
					// horizontal walk
					a.Set("curr_anim", a("walk_anim_side"));
					
					// face dir (at end of walk)
					a.Set("face_dir", a("flip") ? "face_left" : "face_right");
				}
				
				// actually move actor
				actor_x = a("x");
				actor_y = a("y");
				a.Set("x", actor_x + step_x);
				a.Set("y", actor_y + step_y);
				
				// yield();
			}
			
		}
	}
	
	a.Set("moving", 2);
}

void Program::WaitForActor(SObj& actor) {
	if (actor.IsVoid())
		actor = GetSelectedActor();
	
	ASSERT(actor.IsMap());
	
	// wait for (actor to stop moving/turning
	while (actor.MapGet("moving").GetInt() != 2) {
		TODO // yield();
	}
}

bool Program::WalkScript() {
	auto& global = ctx.global;
	
	HiValue selected_actor = global.Get("selected_actor");
	WalkTo(selected_actor, cursor_x + cam.x, cursor_y - stage_top);
	
	// clear current command
	ClearCurrCmd();
	return false;
}

bool Program::VerbScript(HiValue vc2) {
	auto& global = ctx.global;
	
	// if (obj not in inventory (or about to give/use it)...
	if ((!noun1_curr("owner")
			 ? !HasFlag(Classes(noun1_curr), "class_actor")
			 : vc2 != V_USE)
		|| noun2_curr) {
		SObj selected_actor = global.Get("selected_actor");
		
		// walk to use pos and face dir
		// determine which item we're walking to
		SObj walk_obj = noun2_curr || noun1_curr;
		
		//todo: find nearest usepos if (none set?
		Point dest_pos = GetUsePoint(walk_obj);
		WalkTo(selected_actor, dest_pos.x, dest_pos.y);
		
		// abort if (walk was interrupted
		int m = selected_actor("moving");
		if (m != 2) {
			return (false);
		}
		
		// face object/actor by default
		int use_dir = walk_obj;
		
		// unless a diff dir specified
		int walk_dir = walk_obj("use_dir");
		if (walk_dir) {
			use_dir = walk_dir;
		}
		
		// turn to use dir
		DoAnim(selected_actor, "face_towards", use_dir);
	}
	// does current object support active verb?
	if (IsValidVerb(verb_curr, noun1_curr)) {
		// finally, execute verb script
		SObj nc_verbs = noun1_curr("verbs");
		String verb_name = verb_curr("name");
		SObj verb_lambda = nc_verbs(verb_name);
		ASSERT(verb_lambda.IsLambda());
		StartScriptHi(0, verb_lambda, false, noun1_curr, noun2_curr);
	}
	else {
		// check for door
		if (HasFlag(Classes(noun1_curr), "class_door")) {
			// perform default door action
			String s = vc2;
			ASSERT(s.GetCount());
			Gate0 func;
			if      (s == "open")	OpenDoor(noun1_curr, noun1_curr("target_door"));
			else if (s == "close")	CloseDoor(noun1_curr, noun1_curr("target_door"));
			else if (s == "walkto")	ComeOutDoor(noun1_curr, noun1_curr("target_door"), 0);
		}
		else {
			// e.g. "i don't think that will work"
			UnsupportedAction(vc2, noun1_curr, noun2_curr);
		}
	}
	
	// clear current command
	ClearCurrCmd();
	return false;
}

	
	
}

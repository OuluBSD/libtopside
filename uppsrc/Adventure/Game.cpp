#include "Adventure.h"

namespace Adventure {




void Program::RealizeGame() {
	auto& global = ctx.global;
	
	if (game.IsVoid())
		game = global.Get("game", HiValue());
}

bool Program::ReadGame() {
	auto& global = ctx.global;
	
	//DUMPM(global);
	RealizeGame();
	
	/*room_names.Clear();
	FindRooms("", game, room_names);
	if (room_names.IsEmpty()) {
		LOG("Could not find any rooms");
		return false;
	}*/
	//DUMPC(room_names);
	
	if (!room_curr) {
		TODO
		/*const SObj* found = FindDeep(room_names[0]);
		if (!found || !found->IsMap()) {
			LOG("Could not find room " << room_names[0]);
			return false;
		}
		room_curr = *found;*/
	}
	
	//rooms = game.MapGet("rooms");
	rooms = global.Get("rooms", HiValue());
	
	if (!rooms.IsArray() || rooms.GetArray().IsEmpty()) {
		LOG("Program::ParseGame: error: could not find rooms");
		return false;
	}
	
	verbs = global.Get("verbs", SObj());
	if (!verbs.IsArray()) {
		LOG("No verbs in game");
		return false;
	}
	
	const Vector<HiValue>& verb_arr = verbs.GetArray();
	for(int i = 0; i < verb_arr.GetCount(); i++) {
		const HiValue& verb = verb_arr[i];
		if (!verb.IsMap() || verb.GetMap().Find("name") < 0 || verb.GetMap().Find("text") < 0) {
			LOG("Invalid verb");
			return false;
		}
		String name = verb.MapGet("name");
		if (name == "use")		V_USE = verb;
		if (name == "use")		V_USE = verb;
		if (name == "give")		V_GIVE = verb;
		if (name == "push")		V_PUSH = verb;
		if (name == "pull")		V_PULL = verb;
		if (name == "walkto")	V_WALKTO = verb;
		if (name == "pickup")	V_PICKUP = verb;
		if (name == "lookat")	V_LOOKAT = verb;
		if (name == "open")		V_OPEN = verb;
		if (name == "close")	V_CLOSE = verb;
		if (name == "talkto")	V_TALKTO = verb;
		
		if (verb_idx.Find(name) >= 0) {
			LOG("Verb already defined");
			return false;
		}
		verb_idx.Add(name);
	}
	V_COUNT = verb_arr.GetCount();
	if (V_COUNT == 0)  {
		LOG("No verbs");
		return false;
	}
	
	/*EscValue def_verb = global.Get("verb_default", EscValue());
	if (!def_verb.IsMap() || def_verb.GetMap().Find("name") < 0) {
		LOG("No default verb defined");
		return false;
	}
	String def_verb_name = def_verb.MapGet("name");
	int def_verb_idx = verb_idx.Find(def_verb_name);
	if (def_verb_idx < 0) {
		LOG("Could not find default verb from list");
		return false;
	}*/
	
	int verb_default = global.Get("verb_default", -1);
	if (verb_default < 0 || verb_default >= verb_idx.GetCount()) {
		LOG("Invalid default inventory index");
		return false;
	}
	verb_curr = verbs[verb_default];
	
	
	//LOG(game.ToString());
	return true;
}

// initialise all the rooms (e.g. add in parent links)
bool Program::InitGame() {
	auto& global = ctx.global;
	
	game = HiValue();
	
	try {
		HiValue empty_lambda;
		empty_lambda.CreateLambda();
		Vector<HiValue> arg;
		Execute(global, 0, global.Get("main", empty_lambda), arg, INT_MAX);
		RealizeGame();
		Execute(global, 0, global.Get("startup_script", empty_lambda), arg, INT_MAX);
	}
	catch(CParser::Error e) {
		LOG("Program::ParseGame: error: " << e << "\n");
		return false;
	}
	
	
	/*for (room in all(rooms)) {
		ExplodeData(room);
		
		room.map_w = #room.map > 2 ? room.map[3] - room.map[1] + 1 : 16;
		room.map_h = #room.map > 2 ? room.map[4] - room.map[2] + 1 : 8;
		// auto-depth (or defaults)
		room.autodepth_pos = room.autodepth_pos || {9, 50};
		room.autodepth_scale = room.autodepth_scale || {0.25, 1};
		
		// init objects (in room)
		for (obj in all(room.objects)) {
			ExplodeData(obj);
			obj.in_room, obj.h = room, obj.h || 0;
			if (obj.init)
				obj.init(obj);
		}
	}
	// init actors with defaults
	for (ka, actor in pairs(actors)) {
		ExplodeData(actor);
		actor.moving = 2 ;	// 0=stopped, 1=walking, 2=arrived
		actor.tmr = 1;      // internal timer for (managing animation
		actor.talk_tmr = 1;
		actor.anim_pos = 1; // used to track anim pos
		actor.inventory = {
			// obj_switch_player,
			// obj_switch_tent
		};
		actor.inv_pos = 0;  // pointer to the row to start displaying from
	}*/
	
	
	return true;
}


}

#include "Adventure.h"

namespace Adventure {


bool ReadFlag(const SObj& o, String key) {
	TODO
}





extern const char* builtin_map;
extern const char* builtin_gff;

Program::Program() {
	draw_zplanes.SetCount(128+1);
	
	LoadBuiltinGfxStr(builtin_map, map, map_sz);
	LoadBuiltinGfxStr(builtin_gff, gff, gff_sz);
	
	ResetUI();
}

bool Program::Init() {
	
	ResetUI();
	
	ClearCurrCmd();
	
	// talking_curr = NULL  // currently displayed speech {x,y,col,lines ... }
	// dialog_curr = NULL   // currently displayed dialog options to pick
	// cutscene_curr = NULL // currently active cutscene
	// talking_actor = NULL // currently talking actor
	
	ctx.Clear();
	
	fade_iris = 0;
	cutscene_cooloff = 0;
	
	ctx.InitializeEmptyScene();
	
	if (!ctx.AddCodePath(GetDataFile("Game.esc")))
		return false;
	
	if (!ctx.Init(false))
		return false;
	
	if (!AddHighFunctions())
		return false;
	
	// init all the rooms/objects/actors
	if (!InitGame())
		return false;
	
	if (!ReadGame())
		return false;
	
	ctx.KeepRunning();
	
	return true;
}

/*void Program::ProcessHi() {
	//LOG("Program::ProcessHi: start");
	
	int i = 0;
	for (Script& s : global_scripts) {
		if (s.is_esc && s.IsRunning()) {
			s.ProcessHi();
			i++;
		}
	}
	
	for (Script& s : local_scripts) {
		if (s.is_esc && s.IsRunning()) {
			s.ProcessHi();
			i++;
		}
	}
	
	for (Script& s : cutscenes) {
		if (s.is_esc && s.IsRunning()) {
			s.ProcessHi();
			i++;
		}
	}
	
	//LOG("Program::ProcessHi: end " << i);
}*/

const SObj* Program::FindDeep(const String& name) const {
	DUMP(name);
	TODO
	//return FindDeep(name, &game);
}

const SObj* Program::FindDeep(const String& name, const SObj* o) const {
	if (!o || !o->IsMap())
		return 0;
	const auto& m = o->GetMap();
	int i = m.Find(name);
	if (i >= 0)
		return &m[i];
	const auto& v = m.GetValues();
	for (const auto& val : v) {
		const SObj* r = FindDeep(name, &val);
		if (r)
			return r;
	}
	return 0;
}

HiValue Program::Classes(SObj s) {
	if (!s.IsMap()) {DUMP(s);}
	ASSERT(s.IsMap());
	//DUMP(s);
	return s("classes");
}

String Program::State(SObj& s) {
	TODO
}

/*String Program::GetInRoomString(SObj& o) {
	if (o.IsMap()) {
		SObj in_room = o.MapGet("in_room");
		if (in_room.IsArray()) {
			String name = in_room.ToString();
			return name;
		}
	}
	DUMP(o);
	ASSERT(0);
	return String();
}*/







HiValue Program::FindDefaultVerb(SObj& obj) {
	HiValue default_verb = V_LOOKAT;

	if (HasFlag(Classes(obj), "class_talkable"))
		default_verb = V_TALKTO;
	else if (HasFlag(Classes(obj), "class_openable")) {
		if (State(obj) == "state_closed")
			default_verb = V_OPEN;
		else
			default_verb = V_CLOSE;
	}

	// now find the full verb definition
	/*for (auto v : all(verbs)) {
		vi = GetVerb(v);
		if (vi[2] == default_verb) { default_verb = v; break; }
	}*/
	
	return default_verb;
}





bool Program::IsValidVerb(SObj verb, SObj object) {
	TODO
	/*
 // check params
	if ((!object || !object.verbs)
		return false;
	// look for (verb
	if (IsTable(verb)) {
		if (object.verbs[verb[1]]) return true;
	}
	else {
		if (object.verbs[verb]) return true;
	}
	// must not be valid if (reached here
	return false;
	*/
}


void Program::BreakTime(int jiffies) {
	// wait for (cycles specified (min 1 cycle)
	jiffies = max(1, jiffies);
	for (int x = 0; x < jiffies; x++) {
		TODO // yield();
	}
}

/*void Program::WaitForMessage() {
	while (talking_curr) {
		yield();
	}
}*/


#if 0
void Program::GetReference(SObj& obj, bool everywhere) {
	if (!obj.IsMap()) {
		String name = obj;
		//LOG(name);
		int i = global.Find(name);
		if (i >= 0) {
			obj = global[i];
			return;
		}
		
		/*const SObj* f = FindDeep(name, &room_curr);
		if (f) {
			obj = *f;
			return;
		}
		if (everywhere) {
			f = FindDeep(name, &game);
			if (f) {
				obj = *f;
				return;
			}
		}*/
		ASSERT(0);
	}
}
#endif


double Program::Proximity(SObj& obj1, SObj& obj2) {
	// calc dist between objects, || big value for (different room
	Point pt1 = GetXY(obj1);
	Point pt2 = GetXY(obj2);
	return
		GetInRoom(obj1) == GetInRoom(obj2)
			? sqrt((pt1.x - pt2.x) ^ 2 + (pt1.y - pt2.y) ^ 2)
			: 1000;
}




/*const StrMap& Program::get_keys(SObj& obj) {
	local keys = {};
	for (k,v in pairs(obj)) {
		add(keys,k);
	}
	return keys;
}*/

HiValue Program::GetVerb(int idx) {
	HiValue ret = verbs(idx);
	//DUMP(ret);
	return ret;
}

String Program::GetVerbString(int i) {
	if (i >= 0 && i < V_COUNT)
		return verbs.ArrayGet(i);
	return "<error>";
}

String Program::GetVerbString(SObj v) {
	ASSERT(v.IsMap());
	String name = v.MapGet("name");
	ASSERT(name.GetCount() > 0);
	return name;
}

void Program::ClearCurrCmd() {
	// reset all command values
	verb_curr = V_DEFAULT;
	executing_cmd = 0;
	cmd_curr.Clear();
	noun1_curr = HiValue();
	noun2_curr = HiValue();
	//me.Clear();
}



void Program::Update() {
	SObj selected_actor = GetSelectedActor();
	
	// See HiAnimContext::Iterate
	// It is implemented here
	ASSERT(ctx.IsRunning());
	
	// global scripts (always updated - regardless of cutscene)
	ctx.ProcessAndRemoveGroup(SCRIPT_GLOBAL);

	// update active cutscene (if (any)
	if (cutscene_curr) {
		Script& cut = *cutscene_curr;
		
		if (!cut.IsRunning() || !cut.Process()) {
			// cutscene ended, restore prev state

			// restore follow-cam if (flag allows (and had a value!)
			dword& flags = cut.user_flags;
			HiValue& paused_cam_following = cut.user;
			if (flags != 3 && paused_cam_following) {
				CameraFollow(paused_cam_following);
				
				// assume to re-select prev actor
				SetSelectedActor(paused_cam_following);
			}
			
			// now delete cutscene
			ctx.RemoveStoppedGroup(SCRIPT_CUTSCENE);

			// any more cutscenes?
			Vector<HiAnimProgram*> cutscenes = ctx.FindGroupPrograms(SCRIPT_CUTSCENE);
			if (!cutscenes.IsEmpty()) {
				cutscene_curr = cutscenes.Top();
				ASSERT(cutscene_curr);
			}
			else {
				// start countdown (delay to ensure cutscenes/dialogs all over!)
				if (flags != 2)
					cutscene_cooloff = 3;
				
				cutscene_curr = NULL;
			}
		}
	}
	else {
		// no cutscene...
		// update all the active scripts
		// (will auto-remove those that have ended)

		// local/room-level scripts
		ctx.ProcessAndRemoveGroup(SCRIPT_LOCAL);
	}
	
	ctx.p.Data();
	if (!ctx.IsRunning())
		ctx.WhenStop();
	
	// player/ui control
	PlayerControl();

	// check for (collisions
	CheckCollisions();

	// update camera shake (if (active)
	cam_shake_x = 1.5 - Randomf() * 3;
	cam_shake_y = 1.5 - Randomf() * 3;
	cam_shake_x = (int)(cam_shake_x * cam_shake_amount);
	cam_shake_y = (int)(cam_shake_y * cam_shake_amount);
	
	if (!cam_shake)
		cam_shake_amount = cam_shake_amount > 0.05 ? cam_shake_amount * 0.90 : 0;
	
}







// function show_collision_box(obj)
// 	local obj_bounds = obj.bounds
// 	if (show_collision
// 	 && obj_bounds
// 	then
// 		rect(obj_bounds.x, obj_bounds.y, obj_bounds.x1, obj_bounds.y1, 8)
// 	}
// }

bool Program::IsTable(SObj& t) {
	TODO
	///return type(t) == "table";
}



Point Program::GetCellPos(SObj& obj) {
	Point p;
	int map_x = room_curr("map")(0,0);
	int map_y = room_curr("map")(1,0);
	int obj_x = obj("x");
	int obj_y = obj("y");
	p.x = obj_x/8 + map_x;
	p.y = obj_y/8 + map_y;
	return p;
}


bool Program::HasFlag(const SObj& obj, String key) {
	ASSERT(obj.IsVoid() || obj.IsArray());
	/*if (obj.IsMap()) {
		const auto& map = obj.GetMap();
		return map.Find(key) >= 0;
	}
	else */
	//DUMP(obj);
	if (obj.IsArray()) {
		const auto& arr = obj.GetArray();
		for (const auto& v : arr)
			if ((String)v == key)
				return true;
	}
	return false;
}




//
// helper functions
//



void Program::ShowError(String msg) {
	TODO
	//PrintLine("-error-;"..msg,5+cam_x,5,8,0);
}

void Program::ExplodeData(SObj& obj) {
	TODO
	/*for (l in all(split(obj.data, "\n"))) {
		local pairs=split(l, "=");
		if (#pairs==2) {
			obj[pairs[1]] = Autotype(pairs[2]);
		}
		else {
			printh(" > invalid data: ["..pairs[1].."]");
		}
	}*/
}

// split s on delimiter, ignoring leading and trailing space and tab

/*function split(s, delimiter) {
	local retval, start_pos, last_char_pos = {}, 0, 0;

	for (i=1,#s) {
		local curr_letter = sub(s,i,i);
		if (curr_letter == delimiter) {
			add(retval, sub(s,start_pos,last_char_pos));
			start_pos, last_char_pos = 0, 0;
		}
		else if (curr_letter != " "
		 && curr_letter != "\t") {
			// curr letter is useful
			last_char_pos, start_pos = i, start_pos == 0 ? i : start_pos;
		}
	}
	// add remaining content?
	if (start_pos + last_char_pos > 0) {
		add(retval, sub(s,start_pos,last_char_pos));
	}
	return retval
}*/

String Program::Autotype(const String& str_value) {
	TODO
	/*local first_letter = sub(str_value, 1, 1);
	
	if (str_value == "true") {
		return true;
	}
	else if (str_value == "false") {
		return false;
	}
	else if (tonum(str_value)) {
		// must be number
		return tonum(str_value);
	}
	else if (first_letter == "{") {
		// array - so split it
		local temp = sub(str_value, 2, #str_value-1);
		retarray = {};
		for (val in all(split(temp, ","))) {
			add(retarray, Autotype(val))
			;
		}
		return retarray;
	}
	else {//if (first_letter == "\"" {
		// string - so) { nothing
		return str_value;
	}*/
}



String Program::SmallCaps(const String& s) {
	TODO
	/*
	local t = "";
	for (i = 1, #s) {
		local c = ord(s, i);
		t.. = chr(c > 96 && c < 123 ? c - 32 : c);
	}
	return t;
	*/
}


bool HasArrayValue(SObj arr, SObj value) {
	ASSERT(arr.IsArray());
	if (!arr.IsArray()) return false;
	const auto& a = arr.GetArray();
	for (const SObj& o : a)
		if (o == value)
			return true;
	return false;
}




}

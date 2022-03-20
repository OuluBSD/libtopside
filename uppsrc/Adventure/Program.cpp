#include "Adventure.h"

namespace Adventure {


Color GetPicoPalette(PaletteColor idx) {
	switch (idx) {
		case 0:  return Color(0x00, 0x00, 0x00);
		case 1:  return Color(0x1D, 0x2B, 0x53);
		case 2:  return Color(0x7E, 0x25, 0x53);
		case 3:  return Color(0x00, 0x87, 0x51);
		
		case 4:  return Color(0xAB, 0x52, 0x36);
		case 5:  return Color(0x5F, 0x57, 0x4F);
		case 6:  return Color(0xC2, 0xC3, 0xC7);
		case 7:  return Color(0xFF, 0xF1, 0xE8);
		
		case 8:  return Color(0xFF, 0x00, 0x4D);
		case 9:  return Color(0xFF, 0xA3, 0x00);
		case 10: return Color(0xFF, 0xEC, 0x27);
		case 11: return Color(0x00, 0xE4, 0x36);
		
		case 12: return Color(0x29, 0xAD, 0xFF);
		case 13: return Color(0x83, 0x76, 0x9C);
		case 14: return Color(0xFF, 0x77, 0xA8);
		case 15: return Color(0xFF, 0xCC, 0xAA);
		
		default: break;
	}
	ASSERT(0);
	return Color(0,0,0);
}




Color ReadColor(const SObj& o, HiValue key, Color def) {
	if (o.IsMap()) {
		const auto& m = o.GetMap();
		int i = m.Find(key);
		if (i >= 0) {
			LOG(o.ToString());
			TODO
		}
	}
	return def;
}

bool TryReadColor(const SObj& o, HiValue key, Color& c) {
	if (o.IsMap()) {
		const auto& m = o.GetMap();
		int i = m.Find(key);
		if (i >= 0) {
			LOG(o.ToString());
			TODO
		}
	}
	return false;
}

bool ReadFlag(const SObj& o, String key) {
	TODO
}








void Script::Clear() {
	Stop();
	fn.Clear();
	a0 = HiValue();
	a1 = HiValue();
	flags = 0;
	paused_cam_following = 0;
	type = SCENE_NULL;
	is_esc = false;
	
}

Script& Script::Set(Gate0 cb, HiValue a0, HiValue a1) {
	Clear();
	this->a0 = a0;
	this->a1 = a1;
	is_esc = false;
	fn = cb;
	global = 0;
	running = true;
	return *this;
}

Script& Script::Set(HiGlobal& g, HiValue *self, HiValue fn, HiValue a0, HiValue a1) {
	Clear();
	is_esc = false;
	
	// Find & check lambda before setting fields
	HiValue lambda;
	String fn_name;
	if (fn.IsLambda()) {
		lambda = fn;
		fn_name = "<lambda>";
	}
	else {
		fn_name = fn.ToString();
		fn_name.Replace("\"", "");
		if (self && self->IsMap())
			lambda = self->MapGet(fn_name);
		if (!lambda.IsLambda()) {
			lambda = g.Get(fn_name, HiValue());
			if (!lambda.IsLambda()) {
				LOG("Key '" << fn_name << "' is not lambda");
				return *this;
			}
		}
	}
	
	Vector<HiValue> arg;
	if (!a0.IsVoid()) arg << a0;
	if (!a0.IsVoid() && !a1.IsVoid()) arg << a1;
	
	const HiLambda& l = lambda.GetLambda();
	if (arg.GetCount() != l.arg.GetCount()) {
		String argnames;
		for(int i = 0; i < l.arg.GetCount(); i++)
			argnames << (i ? ", " : "") << l.arg[i];
		LOG(Format("invalid number of arguments (%d passed, expected: %s)", arg.GetCount(), argnames));
		return *this;
	}
	
	// Set fields
	this->a0 = a0;
	this->a1 = a1;
	is_esc = true;
	global = &g;
	this->fn_name = fn_name;
	
	// Initialize esc runner
	op_limit = 1000000;
	esc = new Hi(g, l.code, op_limit, l.filename, l.line);
	auto& e = *esc;
	if (self)
		e.Self() = *self;
	for(int i = 0; i < l.arg.GetCount(); i++)
		e.Var().GetPut(l.arg[i]) = arg[i];
	
	//e.no_return = e.no_break = e.no_continue = true;
	//e.loop = 0;
	//e.skipexp = 0;
	
	running = true;
	LOG("Script::Set: started " << fn_name);
	
	return *this;
}

Script& Script::Start() {
	tc.KillSet(10, THISBACK(Execute));
	return *this;
}

Script& Script::Stop() {
	tc.Kill();
	running = false;
	return *this;
}

void Script::Execute() {
	if (!is_esc) {
		if (!fn || !fn()) {
			tc.Kill();
			running = false;
			LOG("Script::Set: stopped " << fn_name);
			WhenStop(this);
		}
	}
	else {
		tc.Kill();
		ASSERT_(0, "Do not execute esc outside main thread");
	}
}

bool Script::ProcessHi() {
	LOG("Script::ProcessHi");
	if (!esc || !RunHiSteps()) {
		tc.Kill();
		running = false;
		LOG("Script::ProcessHi: stopped " << fn_name);
		WhenStop(this);
	}
	return running;
}

bool Script::RunHiSteps() {
	LOG("Script::RunHiSteps");
	auto& e = *esc;
	/*int op = 0;
	try {
		while(!e.IsEof() && e.no_return && e.no_break && e.no_continue && op < op_limit_at_once) {
			e.DoStatement();
			op++;
		}
	}
	catch (CParser::Error e) {
		LOG("Script::RunHiSteps: error: " << e);
		return false;
	}
	
	return !e.IsEof();*/
	
	e.Run();
	
	return false;
}







Sentence& Dialog::Add() {
	Sentence& s = sentences.Add();
	s.num = sentences.GetCount() - 1;
	return s;
}

void Dialog::Clear() {
	sentences.Clear();
	col = 0;
	hlcol = 0;
	visible = 0;
}







extern const char* builtin_map;
extern const char* builtin_gff;

Program::Program() {
	draw_zplanes.SetCount(128+1);
	
	LoadBuiltinGfxStr(builtin_map, map, map_sz);
	LoadBuiltinGfxStr(builtin_gff, gff, gff_sz);
	
	ResetUI();
}

/*void Program::ProcessHi() {
	//LOG("Program::ProcessHi: start");
	
	int i = 0;
	for (Script& s : global_scripts) {
		if (s.is_esc && s.running) {
			s.ProcessHi();
			i++;
		}
	}
	
	for (Script& s : local_scripts) {
		if (s.is_esc && s.running) {
			s.ProcessHi();
			i++;
		}
	}
	
	for (Script& s : cutscenes) {
		if (s.is_esc && s.running) {
			s.ProcessHi();
			i++;
		}
	}
	
	//LOG("Program::ProcessHi: end " << i);
}*/

void Program::ResetPalette() {
	ui_cursor_cols[0] = GetPicoPalette(7);
	ui_cursor_cols[1] = GetPicoPalette(12);
	ui_cursor_cols[2] = GetPicoPalette(13);
	ui_cursor_cols[3] = GetPicoPalette(13);
	ui_cursor_cols[4] = GetPicoPalette(12);
	ui_cursor_cols[5] = GetPicoPalette(7);
	
}

void Program::ResetUI() {
	verb_maincol = 12;   // main color (lt blue)
	verb_hovcol = 7;     // hover color (white)
	verb_shadcol = 1;    // shadow (dk blue)
	verb_defcol = 10;    // default action (yellow)
	ui_cursorspr = 224;  // default cursor sprite
	ui_uparrowspr = 208; // default up arrow sprite
	ui_dnarrowspr = 240; // default up arrow sprite
	
	// default cols to use when animating cursor
	ui_cursor_cols[0] = 7;
	ui_cursor_cols[1] = 12;
	ui_cursor_cols[2] = 13;
	ui_cursor_cols[3] = 13;
	ui_cursor_cols[4] = 12;
	ui_cursor_cols[5] = 7;
	
	for(int i = 0; i < BTN_COUNT; i++)
		pressed[i] = false;
	mouse_pressed = 0;
	
	
	ui_arrows.SetEmptyArray();
	
	HiValue up = ui_arrows.ArrayAdd(HiValue());
	up.SetEmptyMap();
	up.MapSet("spr", ui_uparrowspr);
	up.MapSet("x", 75);
	up.MapSet("y", stage_top + 60);
	
	HiValue& down = ui_arrows.ArrayAdd(HiValue());
	down.SetEmptyMap();
	down.MapSet("spr", ui_dnarrowspr);
	down.MapSet("x", 75);
	down.MapSet("y", stage_top + 72);
	
	
}

const SObj* Program::FindRoom(const String& name) const {
	const auto& arr = rooms.GetArray();
	for (const auto& val : arr) {
		String room_str = val;
		//LOG(room_str);
		if (room_str == name)
			return FindDeep(name);
	}
	return 0;
}

const SObj* Program::FindDeep(const String& name) const {
	return FindDeep(name, &game);
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

SObj Program::GetInRoom(SObj o) {
	//LOG(o.ToString());
	if (o.IsMap()) {
		SObj in_room = o.MapGet("in_room");
		if (in_room.IsMap())
			return in_room;
		
		//LOG(in_room.ToString());
		/*String name = in_room;
		if (name.GetCount()) {
			const SObj* ptr = FindDeep(name);
			if (ptr) {
				ASSERT(ptr->IsMap());
				return *ptr;
			}
		}*/
	}
	return SObj();
}






void Program::Shake(bool enabled) {
	cam_shake = enabled;
	cam_shake_amount = enabled ? 1 : cam_shake_amount;
}


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



void Program::CameraAt(const Point& val) {
	// point center of camera at val, clear other cam values
	Point c = CenterCamera(val);
	cam = c;
	cam_pan_to = c;
	cam_following_actor = 0;
}

void Program::CameraFollow(SObj actor) {
	//GetReference(actor, true);
	ASSERT(actor.IsMap());
	
	StopScript(cam_script); // bg script
	
	// set target, clear other cam values
	cam_following_actor = actor;
	cam_pan_to = GetXY(actor);
	
	StartScript(THISBACK(CamScript0), true); // bg script
	
	// auto-switch to room actor resides in
	SObj r = GetInRoom(cam_following_actor);
	ASSERT(r);
	if (r != room_curr)
		ChangeRoom(r, 1);
}

bool Program::CamScript0() {
	// keep the camera following actor
	// (until further notice)
	if (cam_following_actor.IsMap()) {
		// keep camera within "room" bounds
		if (GetInRoom(cam_following_actor) == room_curr)
			cam = CenterCamera(cam_following_actor);
		return true;
	}
	else
		return false;
}

void Program::CameraPanTo(SObj& val) {
	// set target, but keep camera within "room" bounds, clear other cam values
	Point c = CenterCamera(val);
	cam_pan_to = c;
	cam_following_actor = 0;

	cam_script.Clear();
	
	StartScript(THISBACK(CamScript1), true); // bg script
}

bool Program::CamScript1() {
	
	// update the camera pan until reaches dest
	TODO
	/*
	while (cam_x ~= cam_pan_to) {
		cam_x += sgn(cam_pan_to-cam_x)/2
		// don't hog cpu
		TODO // yield()
	}*/
	
	// pan complete
	cam_pan_to.Clear();
}

void Program::WaitForCamera() {
	while (ScriptRunning(cam_script)) {
		TODO // yield();
	}
}

void Program::Cutscene(SceneType type, HiValue* self, HiValue func_cutscene, HiValue func_override) {
	/*cut = {
		flags = type,
		thrd = cocreate(func_cutscene),
		override_ = func_override,
		paused_cam_following = cam_following_actor
	};*/
	
	if (cutscene_override.IsVoid()) {
		cutscene_override = func_override;
		
		Script& cut = cutscenes.Add();
		cut.type = type;
		cut.WhenStop = THISBACK(ClearCutsceneOverride);
		cut.Set(global, 0, func_cutscene, room_curr);
		
		// set as active cutscene
		cutscene_curr = &cut;
	}
	else {
		StartScriptHi(self, cutscene_override, 0);
	}
}

void Program::DialogSet(StrVec& msg_table) {
	for (const String& msg : msg_table) {
		DialogAdd(msg);
	}
}

void Program::DialogAdd(const String& msg) {
	Sentence& s = dialog_curr.Add();
	s.msg = msg;
	
	// break msg into lines (if (necc.)
	CreateTextLines(msg, 32, s.lines);
	
	// find longest line
	s.char_width = GetLongestLineSize(s.lines);
	
}

void Program::DialogStart(int col, int hlcol) {
	dialog_curr.col = col;
	dialog_curr.hlcol = hlcol;
	dialog_curr.visible = true;
	selected_sentence = NULL;
}

void Program::DialogHide() {
	dialog_curr.visible = false;
}

void Program::DialogClear() {
	dialog_curr.sentences = {};
	selected_sentence = NULL;
}

void Program::DialogEnd() {
	dialog_curr.Clear();
}

Point Program::GetUsePoint(SObj& obj) {
	UsePos obj_use_pos = GetUsePos(obj);
	
	Point pt = GetXY(obj);
	Size sz = GetSize(obj);
	Point off = GetOffset(obj);
	
	int y = pt.y;
	int x = pt.x;
	int w = sz.cx;
	int h = sz.cy;
	int offset_x = off.x;
	int offset_y = off.y;
	
	// first check for (specific pos
	TODO
	/*if (IsTable(obj_use_pos)) {
		x = obj_use_pos[1];
		y = obj_use_pos[2]; // -cam_x, -stage-top
	}
	// determine use pos
	else*/ {
		if (obj_use_pos == POS_LEFT && offset_x) {
			// diff calc for (actors
			x -= (w * 8 + 4);
			y += 1;
		}
		else {
			int xd = 0, yd = 0;
			switch (obj_use_pos) {
				case POS_LEFT:
					xd = -2;
					yd = h * 8 - 2;
					break;
				case POS_RIGHT:
					xd = w * 8;
					yd = h * 8 - 2;
					break;
				case POS_ABOVE:
					xd = w * 4 - 4;
					yd = -2;
					break;
				case POS_CENTER:
					xd = w * 4;
					yd = h * 4 - 4;
					break;
				case POS_INFRONT:
					xd = w * 4 - 4;
					yd = h * 8 + 2;
					break;
				default:
					break;
			}
			
			x += xd;
			y += yd;
		}
	}

	return Point(x,y);
}

void Program::DoAnim(SObj thing, const String& param1, int& param2) {
	//
	// scumm examples:
	// do-animation selected-actor stand
	// do-animation selected-actor get-up
	
	// do-animation bernard ring-bell
	//  break-here 4
	// do-animation bernard reach-low
	
	// do-animation hermit face-towards guybrush
	// do-animation max face-towards sam
	
	// face-towards?
	//   animate turn to face (object/actor || explicit direction)
	if (param1 == "face_towards") {
		TODO
		/*
		// check if param2 is an actor/object, rather than explicit face_dir
		if (IsTable(param2)) {
			// need to calculate face_dir from positions
			double angle_rad = atan2(thing.x  - param2.x , param2.y - thing.y);
			
			// calc player's angle offset in this
			double plr_angle = 93 * (3.1415 / 180);
			
			// adjust for (player's angle
			angle_rad = plr_angle - angle_rad;
			
			// convert radians to degrees
			// (note: everyone says should be: rad * (180/pi), but
			//        that only seems to give me degrees 0..57? so...)
			double degrees = (angle_rad * 360) % 360; //(1130.938/3.1415)
			
			// set final target face direction to obj/actor
			param2 = 4 - flr(degrees / 90);
			
			// convert final value
			param2 = face_dirs[param2];
		}
		
		int face_dir = face_dirs[thing.face_dir];
		//!!! param2 = face_dirs[param2];
		
		while (face_dir != param2) {
			// turn to target face_dir
			if (face_dir < param2) {
				face_dir += 1;
			}
			else {
				face_dir -= 1;
			}
			
			// set face dir
			thing.face_dir = face_dirs[face_dir];
			
			// is target dir left? flip?
			thing.flip = (thing.face_dir == "face_left");
			BreakTime(10);
		}*/
	}
	else {
		// must be an explicit animation (e.g. "idle")
		// so start it now
		thing.Set("curr_anim", param1);
		thing.Set("anim_pos", 1);
		thing.Set("tmr", 1);
	}
	
}

// open one (or more) doors
void Program::OpenDoor(SObj door_obj1, SObj door_obj2) {
	StateType state1 = GetState(door_obj1);
	
	if (state1 == STATE_OPEN) {
		SayLine("it's already open");
	}
	else {
		SetState(door_obj1, STATE_OPEN);
		if (door_obj2)
			SetState(door_obj2, STATE_OPEN);
	}
}

// close one (or more) doors
void Program::CloseDoor(SObj door_obj1, SObj door_obj2) {
	StateType state1 = GetState(door_obj1);
	if (state1 == STATE_CLOSED) {
		SayLine("it's already closed");
	}
	else {
		SetState(door_obj1, STATE_CLOSED);
		if (door_obj2)
			SetState(door_obj2, STATE_CLOSED);
	}
}

void Program::ComeOutDoor(SObj from_door, SObj to_door, bool fade_effect) {
	// check param
	/*if (to_door == NULL) {
		ShowError("target door does not exist");
		return;
	}*/
	HiValue selected_actor = GetSelectedActor();
	
	StateType from_state = GetState(from_door);
	if (from_state != STATE_OPEN) {
		SayLine("the door is closed");
		return;
	}
	
	// go to new room!
	SObj new_room = GetInRoom(to_door);
	
	if (new_room != room_curr) {
		ChangeRoom(new_room, fade_effect); // switch to new room and ...
	    
		// ...auto-position actor at to_door in new room...
		Point pos = GetUsePoint(to_door);
		PutAt(selected_actor, pos.x, pos.y, new_room);
	}
	
	FaceDir to_dir = GetFaceDir(to_door);
	FaceDir opp_dir;
	
	if (to_dir) {
		//  ... in opposite use direction!
		opp_dir = (FaceDir)(((int)to_dir + 1) % 4 + 1);
		
		// opp_dir = to_dir + 2
		// if (opp_dir > 4 {
		// opp_dir -= 4
		// }
	}
	else {
		opp_dir = FACE_FRONT;
	}
	
	selected_actor.Set("face_dir", GetFaceString(opp_dir));
	
	// is target dir left? flip?
	selected_actor.Set("flip", GetFaceDir(selected_actor) == FACE_LEFT);
	
}



bool Program::Fades(int fade, int dir) {
	// dir: 1=down, -1=up
	int fade_amount = 25 - 25 * dir;

	fade_amount += dir*2;

	if (fade_amount >= 0 && fade_amount <= 50) {
		// iris) {wn/up
		if (fade == 1)
			fade_iris = min(fade_amount, 32);
		
		fade_iter++;
		if (fade_iter < 1000)
			return true;
	}
	
	fade_iter = 0;
	return false;
}

void Program::ChangeRoom(SObj new_room, SObj fade_) {
	if (!new_room.IsMap()) {
		DUMP(new_room);
		TODO
		/*
		String name = new_room;
		const SObj* ptr = FindDeep(name);
		if (!ptr) {
			LOG("Could not find room '" << name << "'");
			return;
		}
		new_room = *ptr;
		*/
	}
	ASSERT(new_room.IsMap());
	int fade = fade_.GetInt();
	
	// check param
	if (new_room.IsVoid()) {
		ShowError("room does not exist");
		return;
	}

	// stop any existing fade (shouldn't be any, but just in case!)
	if (fade_script) {
		StopScript(*fade_script);
		fade_script = 0;
	}

	// fade) {wn existing room (or skip if (first room)
	if (fade && room_curr) {
		Fades(fade, 1);
	}
	
	// switch to new room
	// execute the exit() script of old room
	if (room_curr) {
		StartScriptHi(&room_curr, "exit", 0, room_curr); // run script directly, so wait to finish
	}
	
	// stop all active (local) scripts
	local_scripts.Clear();
	
	// clear current command
	ClearCurrCmd();
	
	// actually change rooms now
	room_curr = new_room;
	
	// reset camera pos in new room (unless camera following)
	if (cam_following_actor.IsVoid() || GetInRoom(cam_following_actor) != room_curr)
		cam = Point(0,0);
	
	// stop everyone talking & remove displayed text
	StopTalking();
	
	// fade up again?
	// (use "thread" so that room.enter code is able to
	//  reposition camera before fade-up, if (needed)
	if (fade) {
		// setup new fade up
		StartScript(THISBACK2(Fades, fade, -1), true);
	}
	else {
		// no fade - reset any existing fade
		fade_iris = 0;
	}

	// execute the enter() script of new room
	if (room_curr) {
		StartScriptHi(&room_curr, "enter", 0, room_curr);
	}
	else {
		LOG("Program::ChangeRoom. error: room is not string");
	}
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


void Program::StartScript(Gate0 func, bool bg, HiValue noun1, HiValue noun2) {
	RemoveStoppedScripts();
	
	// background || local?
	if (bg)
		global_scripts.Add().Set(func, noun1, noun2).Start();
	
	else
		local_scripts.Add().Set(func, noun1, noun2).Start();
}

void Program::StartScriptHi(HiValue* self, HiValue script_name, bool bg, HiValue noun1, HiValue noun2) {
	//LOG("Program::StartScriptHi: " << script_name);
	RemoveStoppedScripts();
	
	// background || local?
	if (bg)
		global_scripts.Add().Set(global, self, script_name, noun1, noun2);
	
	else
		local_scripts.Add().Set(global, self, script_name, noun1, noun2);
}

bool Program::ScriptRunning(Script& func)  {
	// loop through both sets of scripts...
	TODO // ptr or content?
	/*for (Script& s : local_scripts) {
		
	}
	for (Script& s : global_scripts) {
		
	}
	
	for (s : all( { local_scripts, global_scripts } )) {
		for (k,scr_obj in pairs(s)) {
			if (scr_obj[1] == &func) {
				return scr_obj;
			}
		}
	}*/
	
	// must not be running
	return false;
}

void Program::StopScript(Script& func) {
	for(int i = 0; i < local_scripts.GetCount(); i++)
		if (&local_scripts[i] == &func)
			{local_scripts.Remove(i); break;}
			
	for(int i = 0; i < global_scripts.GetCount(); i++)
		if (&global_scripts[i] == &func)
			{global_scripts.Remove(i); break;}
	
}

void Program::RemoveStoppedScripts() {
	RemoveStoppedScripts(local_scripts);
	RemoveStoppedScripts(global_scripts);
	RemoveStoppedScripts(cutscenes);
}

void Program::RemoveStoppedScripts(Array<Script>& scripts) {
	for(int i = 0; i < scripts.GetCount(); i++)
		if (!scripts[i].running)
			scripts.Remove(i);
}

void Program::BreakTime(int jiffies) {
	// wait for (cycles specified (min 1 cycle)
	jiffies = max(1, jiffies);
	for (int x = 0; x < jiffies; x++) {
		TODO // yield();
	}
}

void Program::WaitForMessage() {
	TODO
	/*while (talking_curr) {
		yield();
	}*/
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


void Program::PrintLine(String msg, int x, int y, int col, int align, bool use_caps, float duration, bool big_font) {
  // punctuation...
	//  > ":" new line, shown after text prior expires
	//  > ";" new line, shown immediately
	// note: an actor's talk animation is not activated as it is with say-line.
	
	col = col ? col : 7;   // default to white
	align = align ? align : 0; // default to no align
	
	// calc max line width based on x-pos/available space
	int screen_space = 127 - (x - cam.x);
	if (align == 1)
		screen_space = min(x -cam.x, screen_space);
	int max_line_length = max(screen_space / 2, 16);
	
	// search for (";"'s
	String msg_left = "";
	for(int i = 0; i < msg.GetCount(); i++) {
		int curchar = msg[i];
		if (curchar == ':') {
			// show msg up to this point
			// and process the rest as new message

			// next message?
			msg_left = msg.Mid(i+1);
			
			// redefine curr msg
			msg = msg.Left(i);
			break;
		}
	}
	
	Vector<String> lines;
	CreateTextLines(msg, max_line_length, lines);
	
	// find longest line
	int longest_line = GetLongestLineSize(lines);
	
	// center-align text block
	int xpos = x - cam.x;
	if (align == 1)
		xpos -= longest_line * (big_font ? 4 : 2);
	
	// screen bound check
	xpos = max(2, xpos);
	int ypos = max(18, y); // left, top
	xpos = min(xpos, 127 - (longest_line * 4) - 1); // right
	
	TODO
	/*
	talking_curr = {
		msg_lines = lines,
		x = xpos,
		y = ypos,
		col = col,
		align = align,
		time_left = duration || #msg * 8,
		char_width = longest_line,
		use_caps = use_caps,
		big_font = big_font
	};
	// ref point for (skip #####################??????
	//talking_curr.time_orig=talking_curr.time_left


	// if (message was split...
	if (#msg_left > 0) {
	  talking = talking_actor
		WaitForMessage()
		talking_actor = talking
		PrintLine(msg_left, x, y, col, align, use_caps, NULL, big_font)
	}

	// and wait for (message?
	//if (!dont_wait_msg) {
		WaitForMessage();
	//}
	*/
}

bool Program::ParseGame(String content, String path) {
	//HighCall(global, "Print(x)", SIC_Print);
	//HighCall(global, "Input()", SIC_Input);
	//HighCall(global, "InputNumber()", SIC_InputNumber);
	HighCall(global, "print_line(txt, x, y, col, align, use_caps, duration, big_font)", THISBACK(HiPrintLine));
	HighCall(global, "break_time(t)", THISBACK(HiBreakTime));
	HighCall(global, "put_at(obj, x, y, room)", THISBACK(HiPutAt));
	HighCall(global, "camera_follow(actor)", THISBACK(HiCameraFollow));
	HighCall(global, "change_room(new_room, fade)", THISBACK(HiChangeRoom));
	HighCall(global, "set_global_game(game)", THISBACK(HiSetGlobalGame));
	HighCall(global, "cutscene(type, func_cutscene, func_override)", THISBACK(HiCutscene));
	HighCall(global, "sub(type, func_cutscene, func_override)", THISBACK(HiCutscene));
	HighCall(global, "select_actor(name)", THISBACK(HiSelectActor));
	HighCall(global, "pickup_obj(me)", THISBACK(HiTodo));
	HighCall(global, "set_trans_col(name, b)", THISBACK(HiTodo));
	HighCall(global, "fades(a, b)", THISBACK(HiTodo));
	HighCall(global, "map(a, b, c, d, e, f)", THISBACK(HiTodo));
	HighCall(global, "say_line(a)", THISBACK(HiTodo));
	HighCall(global, "camera_at(a)", THISBACK(HiTodo));
	HighCall(global, "camera_pan_to(a)", THISBACK(HiTodo));
	HighCall(global, "wait_for_camera()", THISBACK(HiTodo));
	HighCall(global, "rectfill(a, b, c, d, e)", THISBACK(HiTodo));
	HighCall(global, "line(a, b, c, d, e)", THISBACK(HiTodo));
	HighCall(global, "circfill(a, b, c)", THISBACK(HiTodo));
	HighCall(global, "come_out_door(a, b)", THISBACK(HiTodo));
	HighCall(global, "start_script(a, b)", THISBACK(HiTodo));
	HighCall(global, "stop_script(a, b)", THISBACK(HiTodo));
	HighCall(global, "sfx0()", THISBACK(HiTodo));
	HighCall(global, "sfx1()", THISBACK(HiTodo));
	HighCall(global, "do_anim(a, b, c)", THISBACK(HiTodo));
	HighCall(global, "shake(a)", THISBACK(HiTodo));
	HighCall(global, "script_running(a)", THISBACK(HiTodo));
	HighCall(global, "walk_to(a, b, c)", THISBACK(HiTodo));
	HighCall(global, "open_door(a, b)", THISBACK(HiTodo));
	HighCall(global, "close_door(a)", THISBACK(HiTodo));
	HighCall(global, "dialog_set(a)", THISBACK(HiTodo));
	HighCall(global, "dialog_start(a, b)", THISBACK(HiTodo));
	HighCall(global, "dialog_hide()", THISBACK(HiTodo));
	HighCall(global, "dialog_clear()", THISBACK(HiTodo));
	StdLib(global);
	
	try {
		Scan(global, content, path);
	}
	catch(CParser::Error e) {
		LOG("Program::ParseGame: error: " << e << "\n");
		return false;
	}
	
	return true;
}

void Program::HiCameraFollow(HiEscape& e) {
	CameraFollow(e[0]);
}

void Program::HiChangeRoom(HiEscape& e) {
	ChangeRoom(e[0], e[1]);
}

void Program::HiSetGlobalGame(HiEscape& e) {
	game = e[0];
}

void Program::HiCutscene(HiEscape& e) {
	Cutscene((SceneType)e[0].GetInt(), &e.self, e[1], e[2]);
}

void Program::HiPutAt(HiEscape& e) {
	if (e.arg.GetCount() == 4) {
		PutAt(
			e[0],
			e[1].GetInt(),
			e[2].GetInt(),
			e[3]);
	}
	else {
		ASSERT_(0, "invalid put_at args");
	}
}

void Program::HiPrintLine(HiEscape& e) {
	String txt = e[0].ToString();
	int x = e[1].GetInt();
	int y = e[2].GetInt();
	int col = e[3].GetInt();
	int align = e[4].GetInt();
	bool use_caps = e[5].GetInt();
	int duration = e[6].GetInt();
	bool big_font = e[7].GetInt();
	
	LOG("Program::HiPrintLine: " << txt);
	
	if (use_caps)
		txt = ToUpper(txt);
	
	int fnt_h = big_font ? 20 : 10;
	
	TODO
	/*AObj& o = scene.GetRoot().AddObject();
	
	asdfads*/
}

void Program::HiBreakTime(HiEscape& e) {
	int t = e[0].GetInt();
	
	LOG("Program::HiPrintLine: " << t);
	
	TODO
}

void Program::HiSelectActor(HiEscape& e) {
	
	TODO
	
}

void Program::HiTodo(HiEscape& e) {
	
	TODO
	
}

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

void Program::PutAt(SObj obj, int x, int y, SObj room) {
	//GetReference(obj, true);
	//GetReference(room, true);
	//LOG(obj.ToString());
	//LOG(room.ToString());
	ASSERT(obj.IsMap());
	ASSERT(room.IsMap());
	
	if (room.IsMap()) {
		if (!HasFlag(Classes(obj), "class_actor")) {
			SObj in_room = obj.MapGet("in_room");
			//if (in_room.IsArray())
			//	GetReference(in_room, true);
			ASSERT(in_room.IsMap() || in_room.IsVoid());
			if (in_room.IsMap()) {
				SObj objects = in_room.MapGet("objects");
				Vector<HiValue>& arr = (Vector<HiValue>&)objects.GetArray();
				VectorRemoveKey(arr, obj);
			}
			obj.Set("owner", HiValue());
			SObj objects = room.MapGet("objects");
			ASSERT(objects.IsArray());
			objects.ArrayAdd(obj);
		}
	}
	obj.Set("in_room", room);
	
	//LOG(obj.ToString());
	ASSERT(obj.IsMap());
	obj.Set("x", x);
	obj.Set("y", y);
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
	
	// global scripts (always updated - regardless of cutscene)
	UpdateScripts(global_scripts);

	// update active cutscene (if (any)
	if (cutscene_curr) {
		Script& cut = *cutscene_curr;
		
		if (!cut.running || !cut.ProcessHi()) {
			// cutscene ended, restore prev state

			// restore follow-cam if (flag allows (and had a value!)
			if (cut.flags != 3 && cut.paused_cam_following) {
				CameraFollow(*cut.paused_cam_following);
				
				// assume to re-select prev actor
				SetSelectedActor(*cut.paused_cam_following);
			}
			
			// now delete cutscene
			RemoveStoppedScripts(cutscenes);

			// any more cutscenes?
			if (!cutscenes.IsEmpty()) {
				cutscene_curr = &cutscenes.Top();
			}
			else {
				// start countdown (delay to ensure cutscenes/dialogs all over!)
				if (cut.flags != 2)
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
		UpdateScripts(local_scripts);
	}

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

void Program::UpdateMouseClickState() {
	is_mouse_clicked = mouse_pressed != 0;
}

// handle button inputs
void Program::PlayerControl() {
	
	// check for (skip/override's
	if (talking_curr && !is_mouse_clicked && (IsPressed(BTN_O) || IsMouseLeftPressed())) {
		// skip current talking message
		talking_curr.time_left = 0;
		is_mouse_clicked = true;
		return;
	}
	
	// cutscene? (or skip?)
	if (cutscene_curr) {
		if ((IsPressed(BTN_X) || IsMouseRightPressed()) && cutscene_curr->running) {
			cutscene_curr->Stop();
			return;
		}
		
		// either way - don't allow other user actions!
		UpdateMouseClickState();
		return;
	}
	
	
	if (IsPressed(BTN_LEFT)) {
		cursor_x -= 1;
	}
	if (IsPressed(BTN_RIGHT)) {
		cursor_x += 1;
	}
	if (IsPressed(BTN_UP)) {
		cursor_y -= 1;
	}
	if (IsPressed(BTN_DOWN)) {
		cursor_y += 1;
	}
	if (IsPressed(BTN_O)) {
		InputButtonPressed(MBMASK_LEFT);
	}
	if (IsPressed(BTN_X)) {
		InputButtonPressed(MBMASK_RIGHT);
	}
	
	// don't repeat action if (same press/click
	if (IsAnyMousePressed() && !is_mouse_clicked) {
		InputButtonPressed(GetMouseButtonMask());
	}
	// store for (comparison next cycle
	last_cursor_x = cursor_x;
	last_cursor_y = cursor_y;
	
	UpdateMouseClickState();
}




// 1 = z/lmb, 2 = x/rmb, (4=middle)
void Program::InputButtonPressed(dword button_index) {
	SObj selected_actor = global.Get("selected_actor");
	
	// abort if (no actor selected at this point
	if (!selected_actor)
		return;
		
	// check for (sentence selection
	if (dialog_curr && dialog_curr.visible) {
		if (hover_curr_sentence)
			selected_sentence = hover_curr_sentence;
		// skip remaining
		return;
	}
	
	// if (already executing, clear current command
	// (allow abort of commands by) {ing other actions, like walking)
	if (executing_cmd)
		ClearCurrCmd();
	
	HiValue noun1_curr, noun2_curr;
	if (hover_curr_verb) {
		// change verb and now reset any active objects
		verb_curr = GetVerb(hover_curr_verb);
	}
	else if (hover_curr_object) {
		// if (valid obj, complete command
		// else, abort command (clear verb, etc.)
		if (button_index == 1) {
		}
		// if (already have obj #1
		if (noun1_curr && !executing_cmd) {
			// complete with obj #2
			noun2_curr = hover_curr_object;
		}
		else {
			noun1_curr = hover_curr_object;
		}
		
		if (verb_curr[2] == GetVerb(verb_default)[2] && hover_curr_object("owner")) {
			// inventory item, perform look-at
			verb_curr = GetVerb(verbs[verb_default]);
		}
		
		else if (hover_curr_default_verb) {
			// perform default verb action (if (present)
			verb_curr = GetVerb(hover_curr_default_verb);
			
			// force repaint of command (to reflect default verb)
			//PaintCommand();
		}
		
		// ui arrow clicked
		else if (hover_curr_arrow) {
			int inv_pos = selected_actor("inv_pos");
			
			// up arrow
			if (hover_curr_arrow == ui_arrows[1]) {
				if (inv_pos > 0)
					inv_pos -= 1;
			}
			else { // down arrow
				int inv_len = selected_actor("inventory").GetArray().GetCount();
				if (inv_pos + 2 < inv_len/4) {
					inv_pos += 1;
				}
			}
			return;
		}
		//else
		// what else could there be? actors!?
	}
	
	SObj vc2 = verb_curr;
	
	// attempt to use verb on object (if is not already executing verb)
	if (noun1_curr) {
		// are we starting a 'use' command?
		if (vc2 == V_USE || vc2 == V_GIVE) {
			if (noun2_curr) {
				// 'use' part 2
			}
			else if (noun1_curr("use_with") && noun1_curr("owner") == selected_actor) {
				// 'use' part 1 (e.g. "use hammer")
				// wait for (noun2 to be set
				return;
			}
		}
		
		// execute verb script
		executing_cmd = true;
		StartScript(THISBACK1(VerbScript, vc2), 0);
	}
	else if (cursor_y > stage_top && cursor_y < stage_top + 64) {
		// in map area
		executing_cmd = true;
		
		// attempt to walk to target
		StartScript(THISBACK(WalkScript), 0);
	}
	
}


bool Program::WalkScript() {
	HiValue selected_actor = global.Get("selected_actor");
	WalkTo(selected_actor, cursor_x + cam.x, cursor_y - stage_top);
	
	// clear current command
	ClearCurrCmd();
	return false;
}

bool Program::VerbScript(HiValue vc2) {
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


// collision detection
void Program::CheckCollisions() {
	
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

void Program::ClearCutsceneOverride(Script* s) {
	cutscene_override = HiValue();
	
	if (s == cutscene_curr)
		cutscene_curr = 0;
}

void Program::RealizeGame() {
	if (game.IsVoid())
		game = global.Get("game", HiValue());
}

bool Program::ReadGame() {
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

HiValue Program::RunLambda1(HiValue* self, const HiValue& l, const HiValue& arg0) {
	ASSERT(l.IsLambda());
	
	try {
		Vector<HiValue> args;
		args.Add(arg0);
		return Execute(global, self, l, args, 10000);
	}
	catch(CParser::Error e) {
		LOG("Program::RunLambda1: error: " << e << "\n");
		ASSERT(0);
	}
	
	return HiValue();
}

// initialise all the rooms (e.g. add in parent links)
bool Program::InitGame() {
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


// function show_collision_box(obj)
// 	local obj_bounds = obj.bounds
// 	if (show_collision
// 	 && obj_bounds
// 	then
// 		rect(obj_bounds.x, obj_bounds.y, obj_bounds.x1, obj_bounds.y1, 8)
// 	}
// }

void Program::UpdateScripts(Array<Script>& scripts) {
	int i = 0;
	Vector<int> rm_list;
	for (Script& s : scripts) {
		if (s.is_esc && s.running)
			s.ProcessHi();
		
		if (!s.running)
			rm_list << i;
		
		i++;
	}
	
	if (rm_list.GetCount())
		scripts.Remove(rm_list);
}

bool Program::IsTable(SObj& t) {
	TODO
	///return type(t) == "table";
}

Point Program::CenterCamera(const Point& val) {
	TODO
}

Point Program::CenterCamera(SObj& val) {
	//LOG(val.ToString());
	
	// check params for (obj/actor
	// keep camera within "room" bounds
	int x = 0;
	
	DUMP(val);
	TODO;
	
	if (val.IsMap())
		x = val.MapGet("x").GetInt();
	
	else if (val.IsInt())
		x = val.GetInt();
	
	//int map_w = room_curr.MapGet("map_w").GetInt();
	int map_w = room_curr("map")(2);
	
	Point pt(0,0);
	pt.x = Mid(0, x-64, (map_w*8) -128 );
	return pt;
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


// auto-break message into lines
void Program::CreateTextLines(String msg, int max_line_length, Vector<String>& lines) { //, comma_is_newline)
	TODO
	/*
	//  > ";" new line, shown immediately
	local lines, currline, curword, curchar = {}, "", "", "";

	local function upt(max_length) {
		if (#curword + #currline > max_length) {
			add(lines,currline);
			currline="";
		}
		currline=currline..curword;
		curword="";
	}

	for (i = 1, #msg) {
		curchar=sub(msg,i,i);
		curword=curword..curchar;

		if (curchar == " " || #curword > max_line_length-1) {
			upt(max_line_length);
		}
		else if (#curword>max_line_length-1) {
			curword=curword.."-";
			upt(max_line_length);
		}
		else if (curchar == ";") {
			// line break
			currline=currline..sub(curword,1,#curword-1);
			curword="";
			upt(0);
		}
	}

	upt(max_line_length);
	if (currline != "") add(lines,currline);

	return lines
	*/
}

// find longest line
int Program::GetLongestLineSize(const Vector<String>& lines) {
	int longest_line = 0;
	for (const String& l : lines)
		longest_line = max(longest_line, l.GetCount());
	return longest_line;
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


bool Program::Init() {
	
	ResetUI();
	
	ClearCurrCmd();
	
	// talking_curr = NULL  // currently displayed speech {x,y,col,lines ... }
	// dialog_curr = NULL   // currently displayed dialog options to pick
	// cutscene_curr = NULL // currently active cutscene
	// talking_actor = NULL // currently talking actor
	
	global_scripts.Clear();
	local_scripts.Clear();
	cutscenes.Clear();
	
	fade_iris = 0;
	cutscene_cooloff = 0;
	
	String path = GetDataFile("Game.esc");
	String content = LoadFile(path);
	if (content.IsEmpty()) {
		LOG("error: empty script");
		return false;
	}
	if (!ParseGame(content, path))
		return false;
	
	// init all the rooms/objects/actors
	if (!InitGame())
		return false;
	
	if (!ReadGame())
		return false;
	
	return true;
}

Point Program::GetXY(SObj o) {
	return Point(
		o("x").GetInt(),
		o("y").GetInt());
}

Point Program::GetOffset(SObj o) {
	return Point(
		o("offset_x").GetInt(),
		o("offset_y").GetInt());
}

Size Program::GetSize(SObj o) {
	return Size(
		o("w").GetInt(),
		o("h").GetInt());
}

Program::UsePos Program::GetUsePos(SObj o) {
	TODO
	/*
	UsePos obj_use_pos =
		obj.use_pos != POS_NULL
			? obj.use_pos
			: POS_INFRONT;
	*/
}

StateType Program::GetState(SObj o) {
	String s = o("state");
	if (s == "state_open")   return STATE_OPEN;
	if (s == "state_closed") return STATE_CLOSED;
	ASSERT(0);
	return STATE_CLOSED;
}

void Program::SetState(SObj o, StateType s) {
	if      (s == STATE_OPEN)	o.Set("state", "state_open");
	else if (s == STATE_CLOSED)	o.Set("state", "state_closed");
	else ASSERT(0);
}

FaceDir Program::GetFaceDir(SObj o) {
	String s = o("face_dir");
	ASSERT(s.GetCount());
	//String s = o.MapGet("state");
	if (s == "face_front")	return FACE_FRONT;
	if (s == "face_left")	return FACE_LEFT;
	if (s == "face_back")	return FACE_BACK;
	if (s == "face_right")	return FACE_RIGHT;
	return FACE_NULL;
}

String Program::GetFaceString(FaceDir d) {
	switch (d) {
		case FACE_FRONT:	return "face_front";
		case FACE_LEFT:		return "face_left";
		case FACE_BACK:		return "face_back";
		case FACE_RIGHT:	return "face_right";
		default: break;
	}
	return String();
}

void Program::SetSelectedActor(SObj o) {
	global.GetAdd("selected_actor") = o;
}

SObj Program::GetSelectedActor() {
	//DUMPC(global.GetKeys());
	//ASSERT(global.Find("selected_actor") >= 0);
	return global.Get("selected_actor", HiValue());
}

bool Program::IsPressed(GamepadButton b) const {
	ASSERT(b >= (GamepadButton)0 && b < BTN_COUNT);
	
	if (b >= (GamepadButton)0 && b < BTN_COUNT)
		return pressed[b];
	
	return false;
}

bool Program::IsMousePressed(MouseButtonMask m) const {
	return mouse_pressed & m;
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



const char* builtin_gfx = R"MULTILINE(
0000000000000000000000000000000044444444440000004444444477777777f9e9f9f9ddd5ddd5bbbbbbbb5500000010101010000000000000000000000000
00000000000000000000000000000000444444404400000044444444777777779eee9f9fdd5ddd5dbbbbbbbb5555000001010101000000000000000000000000
00800800000000000000000000000000aaaaaa00aaaa000005aaaaaa77777777feeef9f9d5ddd5ddbbbbbbbb5555550010101010000000000000000000000000
0008800055555555ddddddddeeeeeeee999990009999000005999999777777779fef9fef5ddd5dddbbbbbbbb5555555501010101000000000000000000000000
0008800055555555ddddddddeeeeeeee44440000444444000005444477777777f9f9feeeddd5ddd5bbbbbbbb5555555510101010000000000000000000000000
0080080055555555ddddddddeeeeeeee444000004444440000054444777777779f9f9eeedd5ddd5dbbbbbbbb5555555501010101000000000000000000000000
0000000055555555ddddddddeeeeeeeeaa000000aaaaaaaa000005aa77777777f9f9feeed5ddd5ddbbbbbbbb5555555510101010000000000000000000000000
0000000055555555ddddddddeeeeeeee900000009999999900000599777777779f9f9fef5ddd5dddbbbbbbbb5555555501010101000000000000000000000000
0000000077777755666666ddbbbbbbee888888553333333313131344666666665888858866666666cbcbcbcb0000005510101044999999990000000088845888
00000000777755556666ddddbbbbeeee88888855333333333131314466666666588885881c1c1c1cbcbcbcbc0000555501010144444444440000000088845888
000010007755555566ddddddbbeeeeee88887777333333331313aaaa6666666655555555c1c1c1c1cbcbcbcb005555551010aaaa000450000000000088845888
0000c00055555555ddddddddeeeeeeee88886666333333333131999966666666888588881c1c1c1cbcbcbcbc5555555501019999000450000000000088845888
001c7c1055555555ddddddddeeeeeeee8855555533333333134444446666666688858888c1c1c1c1cbcbcbcb5555555510444444000450000000000088845888
0000c00055555555ddddddddeeeeeeee88555555333333333144444466666666555555551c1c1c1cbcbcbcbc5555555501444444000450000000000088845888
0000100055555555ddddddddeeeeeeee7777777733333333aaaaaaaa6666666658888588c1c1c1c1cbcbcbcb55555555aaaaaaaa000450000000000088845888
0000000055555555ddddddddeeeeeeee66666666333333339999999966666666588885887c7c7c7cbcbcbcbc5555555599999999000450000000000088845888
0000000055777777dd666666eebbbbbb558888885555555544444444777777777777777755555555444444454444444444444445000450008888888999999999
0000000055557777dddd6666eeeebbbb5588888855553333444444447777777777777777555555554444445c4444444444444458000450008888889444444444
0000000055555577dddddd66eeeeeebb7777888855333333aaaaaaaa777777777777777755555555444445cbaaaaaa4444444588000450008888894888845888
000c000055555555ddddddddeeeeeeee66668888533333339999999977777777777777775555555544445cbc9999994444445888000450008888948888845888
0000000055555555ddddddddeeeeeeee5555558853333333444444447777775555777777555555554445cbcb4444444444458888000450008889488888845888
0000000055555555ddddddddeeeeeeee555555885533333344444444777755555555777755555555445cbcbc4444444444588888000450008894588888845888
0000000055555555ddddddddeeeeeeee7777777755553333aaaaaaaa77555555555555770000000045cbcbcbaa44444445888888999999998944588888845888
0000000055555555ddddddddeeeeeeee6666666655555555999999995555555555555555000000005cbcbcbc9944444458888888555555559484588888845888
0000000055555555ddddddddbbbbbbbb555555555555555544444444cccccccc5555555677777777c77777776555555533333336633333338884588988845888
0000000055555555ddddddddbbbbbbbb555555553333555544444444cccccccc555555677777777ccc7777777655555533333367763333338884589488845888
0000000055555555ddddddddbbbbbbbb7777777733333355aaaaaa50cccccccc55555677777777ccccc777777765555533333677776333338884594488845888
0000000055555555ddddddddbbbbbbbb666666663333333599999950cccccccc5555677777777ccccccc77777776555533336777777633338884944488845888
0000000055555555ddddddddbbbbbbbb555555553333333544445000cccccccc555677777777ccccccccc7777777655533367777777763338889444488845888
0000000055555555ddddddddbbbbbbbb555555553333335544445000cccccccc55677777777ccccccccccc777777765533677777777776338894444488845888
0b03000055555555ddddddddbbbbbbbb7777777733335555aa500000cccccccc5677777777ccccccccccccc77777776536777777777777638944444499999999
b00030b055555555ddddddddbbbbbbbb666666665555555599500000cccccccc677777777ccccccccccccccc7777777667777777777777769444444455555555
00000000000000000000000000000000777777777777777777555555555555770000000000000000000000000000000000000000d00000004444444444444444
9f00d70000c0006500c0096500000000700000077000000770700000000007070000000000000000000000000000000000000000d50000004ffffff44ffffff4
9f2ed728b3c55565b3c5596500000000700000077000000770070000000070070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c50565b3c5946500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c50565b3c5946500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c55565b3c9456500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
9f2ed728b3c55565b3c9456500000000700000077000000770006000000600070000000000000000000000000000000000000000d51000004f4444944f444494
44444444444444444444444400000000777777777777777777776000000677770000000000000000000000000000000000000000d51000004f4444944f444494
00000000000000000000000000000000700000677600000770066000000660070000000000000000000000000000000000000000d51000004f4444944f444494
00cd006500000000000a000000000000700006077060000770606000000606070000000000000000000000000000000000000000d51000004f9999944f444494
b3cd8265000000000000000000000000700005077050000770506000000605070000000000000000000000000000000000000000d5100000444444444f449994
b3cd826500a0a000000aa000000a0a00700000077000000770006000000600070000000000000000000000000000000000000000d5100000444444444f994444
b3cd826500aaaa0000aaaa0000aaa000700000077000000770050000000050070000000000000000000000000000000000000000d510000049a4444444444444
b3cd826500a9aa0000a99a0000aa9a00700000077000000770500000000005070000000000000000000000000000000000000000d51000004994444444444444
b3cd826500a99a0000a99a0000a99a00777777777777777775000000000000770000000000000000000000000000000000000000d51000004444444449a44444
44444444004444000044440000444400555555555555555555555555555555550000000000000000000000000000000000000000d51000004ffffff449944444
99999999777777777777777777777777700000077776000077777777777777770000000000000000000000000000000000000000d51000004f44449444444444
55555555555555555555555555555555700000077776000055555555555555550000000000000000000000000000000000000000d51000004f4444944444fff4
444444441dd6dd6dd6dd6dd6d6dd6d51700000077776000044444444444444440000000000000000000000000000000000000000d51000004f4444944fff4494
ffff4fff1dd6dd6dd6dd6dd6d6dd6d517000000766665555444ffffffffff4440000000000000000000000000000000000000000d51000004f4444944f444494
44494944166666666666666666666651700000070000777644494444444494440000000000000000000000000000000000000000d51000004f4444944f444494
444949441d6dd6dd6dd6dd6ddd6dd65170000007000077764449444aa44494440000000000000000000000000000000000000000d51111114f4444944f444494
444949441d6dd6dd6dd6dd6ddd6dd651777777770000777644494444444494440000000000000000000000000000000000000000d55555554ffffff44f444494
44494944166666666666666666666651555555555555666644499999999994440000000000000000000000000000000000000000dddddddd444444444f444494
444949441dd6dd600000000056dd6d516dd6dd6d0000000044494444444494440000000000000000000000000000000000000000000000004f4444944f444494
444949441dd6dd650000000056dd6d51666666660000000044494444444494440000000000000000000000000000000000000000000000004f4444944f444994
44494944166666650000000056666651d6dd6dd60000000044494444444494440000000000000000000000000000000000000000000000004f4444944f499444
444949441d6dd6d5000000005d6dd651d6dd6dd60000000044494444444494440000000000000000000000000000000000000000000000004f4444944f944444
444949441d6dd6d5000000005d6dd651666666660000000044494444444494440000000000000000000000000000000000000000000000004f44449444444400
444949441666666500000000566666516dd6dd6d0000000044494444444494440000000000000000000000000000000000000000000000004f44449444440000
999949991dd6dd650000000056dd6d516dd6dd6d0000000044499999999994440000000000000000000000000000000000000000000000004f44449444000000
444444441dd6dd650000000056dd6d51666666660000000044444444444444440000000000000000000000000000000000000000000000004f44449400000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccffffffff
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccf666677f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000cccccccc7cccccc7
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaccccd776666d
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000caaaccccf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaaaacf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccaaaaacf676650f
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ccccccccff7665ff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fff76fffffffffff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fff76ffff666677f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fbbbbccf75555557
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000bbbcccc8d776666d
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fccccc8ff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff000000000000000000000000fccc888ff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000fff22fff000000000000000000000000fff00ffff676650f
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff0020ff000000000000000000000000fff00fffff7665ff
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2302ffff2302ff0000000000007aa0fff76fff00000094
00000000000000000000000000000000000000000000000000000000000000000000000000000000ffb33bffffb33bff00000000000070a0fff76fff00000944
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2bb2ffff2bb2ff000000000000aaa0f8888bbf00009440
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2222ffff2222ff00000000000a4440888bbbbc00094400
00000000000000000000000000000000000000000000000000000000000000000000000000000000ff2bb2ffff2bb2ff0000000000a40000fbbbbbcf00044000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f2b33b2ff2b33b2f000000000a400000fbbbcccf00400000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f22bb22ff2b33b2f0000000074a90000fff00fff94000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f222222ff22bb22f00000000007a0000fff00fff44000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000f222222f00000000000000000066060bfff76fffcccccccc
00000000000000000000000000000000000000000000000000000000000000000000000000000000f22bb22f000000000000000000660600fff76fffc000000c
00000000000000000000000000000000000000000000000000000000000000000000000000000000f2b33b2f000000000000000000666600fcccc88fc0c00c0c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022b33b22000000000000000000000000ccc8888bc00cc00c
00000000000000000000000000000000000000000000000000000000000000000000000000000000222bb222000000000000000007777770f88888bfc00cc00c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022222222000000000000000007777770f888bbbfc0c00c0c
0000000000000000000000000000000000000000000000000000000000000000000000000000000022222222000000000000000007777770fff00fffc000000c
00000000000000000000000000000000000000000000000000000000000000000000000000000000bbbbbbbb000000000000000008888880fff00fffcccccccc
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000000000000000000000000000
00000000b444449bb444449bb444449bb494449bb494449bb494449bb999449bb999449bb999449b000000000000000000000000000000000000000000000000
00000000444044494440444944404449494444494944444949444449944444499444444994444449000000000000000000000000000000000000000000000000
00000000404000044040000440400004494400044944000449440004944444449444444494444444000000000000000000000000000000000000000000000000
0000000004ffff0004ffff0004ffff000440fffb0440fffb0440fffb444444444444444444444444000000000000000000000000000000000000000000000000
000000000fdffdf00fdffdf00fdffdf004f0fdfb04f0fdfb04f0fdfb444444444444444444444444000000000000000000000000000000000000000000000000
000770000f5ff5f00f5ff5f00f5ff5f000fff5fb00fff5fb00fff5fb444444404444444044444440bbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000
007557004ffffff44ffffff44ffffff440ffffff40ffffff40ffffff044444440444444404444444bffffffbbbbbbbbbbbbbbbbb000000000000000000000000
07500570bff44ffbbff44ffbbff44ffbb0fffff4b0fffff4b0fffff4b044444bb044444bb044444bbff44ffbbbfffffbbbbbbbbb000000000000000000000000
77700777b6ffff6bb6ffff6bb6ffff6bb6fffffbb6fffffbb6fffffbb044444bb044444bb044444bb6ffff6bbbfffffbbbbbbbbb000000000000000000000000
00700700bbfddfbbbbfddfbbbbfddfbbbb6fffdbbb6fffdbbb6fffdbbb0000bbbb0000bbbb0000bbbbf00fbbbb6ff00bbbbbbbbb000000000000000000000000
00700700bbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbbffbbbbbf00fbbbbbff00bbbbbbbbb000000000000000000000000
00777700bdc55cdbbdc55cdbbdc55cdbbbddcbbbbbbddbbbbbddcbbbbddddddbbddddddbbddddddbbbbffbbbbbbbfffbbbbbbbbb000000000000000000000000
00555500dcc55ccddcc55ccddcc55ccdb1ccdcbbbb1ccdbbb1ccdcbbdccccccddccccccddccccccdbbbbbbbbbbbbbbbbbbbbbbbb000000000000000000000000
00070000c1c66c1cc1c66c1dd1c66c1cb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1cc1cccc1dd1cccc1c000000000000000000000000000000000000000000000000
00070000c1c55c1cc1c55c1dd1c55c1cb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1cc1cccc1dd1cccc1c000000000000000000000000000000000000000000000000
00070000c1c55c1ccc155c1dd1c551ccb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1ccc1ccc1dd1ccc1cc000000000000000000000000000000000000000000000000
77707770c1c55c1ccc155c1dd1c551ccb1ccdcbbbb1ccdbbb1ccdcbbc1cccc1ccc1ccc1dd1ccc1cc000000000000000000000000000000000000000000000000
00070000d1cddc1dbc1ddcdbbdcdd1cbb1dddcbbbb1dddbbb1dddcbbd1cccc1dbc1cccdbbdccc1cb000000000000000000000000000000000000000000000000
00070000fe1111efbfe1112bb2111efbbbff11bbbb2ff1bbbbff11bbfe1111efbfe1112bb2111efb000000000000000000000000000000000000000000000000
00070000bf1111fbbff111ebbe111ffbbbfe11bbbb2fe1bbbbfe11bbbf1111fbbff111ebbe111ffb000000000000000000000000000000000000000000000000
00000000bb1121bbbb1121bbbb1121bbbb2111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00777700bb1121bbbb1121bbbb1121bbbb1111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00755700bb1121bbbb1121bbbb1121bbbb1111bbbb2111bbbb2111bbbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
00700700bb1121bbbb1121bbbb1121bbbb1112bbbb2111bbbb21111bbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
77700777bb1121bbbb1121bbbb1121bbbb1112bbbb2111bbbb22111bbb1211bbbb1211bbbb1211bb000000000000000000000000000000000000000000000000
57500575bb1121bbbb1121bbbb1121bbb111122bbb2111bbb222111bbb1211bbbb121cbbbbc211bb000000000000000000000000000000000000000000000000
05700750bb1121bbbb1121bbbb1121bbc111222bbb2111bbb22211ccbb1211bbbb12cc7bb7cc11bb000000000000000000000000000000000000000000000000
00577500bbccccbbbb77c77bb77c77bb7ccc222bbbccccbbb222cc77bbccccbbbbcc677bb776ccbb000000000000000000000000000000000000000000000000
00055000b776677bbbbb677bb776bbbbb7776666bb6777bbb66677bbb776677bbb77bbbbbbbb77bb000000000000000000000000000000000000000000000000
)MULTILINE";

const char* builtin_lbl = R"MULTILINE(
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
fffffffffffffffffffffffff9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffffffffffffffffffff
fffffffffffffffffffffffffeeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9e9f9f97755555555555577f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9eee9f9f70700000000007079eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffffffffffffffffffff
fffffffffffffffffffffffffeeef9f97007000000007007feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffffffffffffffffffff
ffffffffffffffffffffffff9fef9fef70006000000600079fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feee7000600000060007f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9eee70006000000600079f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffffffffffffffffffffffff
fffffffffffffffffffffffff9f9feee7000600000060007f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffffffffffffffffffffffff
ffffffffffffffffffffffff9f9f9fef77776000494449779f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffffffffffffffffffffffff
ffffffff00000000fffffffff9e9f9f97006600494444497f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9f9e9f9f9ffffffff00000000ffffffff
ffffffff00000000ffffffff9eee9f9f70606004944000479eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9fffffffff00000000ffffffff
ffffffff00000000fffffffffeeef9f970506000440fff07feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9ffffffff00000000ffffffff
ffffffff00000000ffffffff9fef9fef700060004f0f9f079fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fef9fefffff7fff00000000ffffffff
ffffffff00000000fffffffff9f9feee700500000fff5f07f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeeffff7fff00000000ffffffff
ffffffff00000000ffffffff9f9f9eee705000040ffffff79f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eee9f9f9eeeffff7fff00000000ffffffff
ffffffff00000000fffffffff9f9feee750000000fffff47f9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef9f9feeef777f77700000000ffffffff
ffffffff00000000ffffffff9f9f9fef555555556fffff559f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fef9f9f9fefffff7fff00000000ffffffff
ffffffff00000000ffffffff999999999999999996fffd9999999999ffffffffffffffffffffffff999999999999999999999999ffff7fff00000000ffffffff
ffffffff00000000ffffffff555555555555555555ff555555555555555555555555555555555555555555555555555555555555ffff7fff00000000ffffffff
ffffffff00000000ffffffff444444444444444444dd4444444444440dd6dd6dd6dd6dd6d6dd6d50444444444444444444444444ffffffff00000000ffffffff
ffffffff00000000ffffffffffff4fffffff4ffff1ccdfffffff4fff0dd6dd6dd6dd6dd6d6dd6d50ffff4fffffff4fffffff4fff22ffffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd94444494944066666666666666666666650444949444449494444494940020fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd944444949440d6dd6dd6dd6dd6ddd6dd650444949444449494444494942302fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd944444949440d6dd6dd6dd6dd6ddd6dd65044494944444949444449494b33bfffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ccd94444494944066666666666666666666650444949444449494444494942bb2fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494441ddd944444949440dd6dd600000000056dd6d50444949444449494444494942222fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442ff1944444949440dd6dd650000000056dd6d50444949444449494444494942bb2fffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442fe19444449494406666665000000005666665044494944444949444449492b33b2ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440d6dd6d500a0a0005d6dd650444949444449494444494922bb22ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440d6dd6d500aaaa005d6dd6504449494444494944444949222222ffff00000000ffffffff
ffffffff00000000ffffffff444949444449494442111944444949440666666500a9aa00566666504449494444494944444949222222ffff00000000ffffffff
ffffffff00000000ffffffff999949999999499992111999999949990dd6dd6500a99a0056dd6d50999949999999499999994922bb22ffff00000000ffffffff
ffffffff00000000ffffffff444444444444444442111444444444440dd6dd650044440056dd6d5044444444444444444444442b33b2ffff00000000ffffffff
ffffffff00000000ffffff555555555555555555521115555555555555555555555555555555555555555555555555555555522b33b22fff00000000ffffffff
ffffffff00000000ffff555555555555555555555211155555555555555555555555555555555555555555555555555555555222bb222fff00000000ffffffff
ffffffff00000000ff55555555555555555555555cccc55555555555555555555555555555555555555555555555555555555222222225ff00000000ffffffff
ffffffff5555555555555555555555555555555556777555555555555555555555555555555555555555555555555555555552222222255555555555ffffffff
ffffffff555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555bbbbbbbb55555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffffff5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555ffffffff
ffffff55555555555557655555555555555555553333333333333333333333333333333333333333333333335555555555555555555555555555555555ffffff
ffff555555555555555765555555555555553333333333333333333333333333333333333333333333333333333355555555555556666775555555555555ffff
ff555555555555555bbbb775555555555533333333333333333333333333333333333333333333333333333333333355555555557555555755555555555555ff
5555555555555555bbb7777855555555533333333333333333333333333333333333333333333333333333333333333555555555d776666d5555555555555555
55555555555555555777778555555555533333333333333333333333333333333333333333333333333333333333333555555555567665055555555555555555
55555555555555555777888555555555553333333333333333333333333333333333333333333333333333333333335555555555567665055555555555555555
55555555555555555550055555555555555533333333333333333333333333333333333333333333333333333333555555555555567665055555555555555555
55555555555555555550055555555555555555553333333333333333333333333333333333333333333333335555555555555555557665555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000c0c0ccc0c000c0c00000ccc00cc00000ccc0c0c0ccc0ccc0c000ccc00000ccc0ccc0cc00ccc0ccc0ccc0c000ccc00000000000000000000
00000000000000000c0c0c0c0c000cc0000000c00c0c00000c0c0c0c0c0c0c0c0c000cc0000000c00cc00c0c00c00c0c0c000c000cc000000000000000000000
00000000000000000ccc0ccc0c000c0c000000c00c0c00000ccc0c0c0cc00ccc0c000c00000000c00c000c0c00c00ccc0c000c000c0000000000000000000000
00000000000000000ccc0c0c0ccc0c0c000000c00cc000000c0000cc0c0c0c000ccc0ccc000000c00ccc0c0c00c00c0c0ccc0ccc0ccc00000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0cc0ccc0ccc0cc0000000000ccc0ccc00cc0c0c00000c0c0ccc00000ccc0c0c00cc0c0c000000000000001111111111011111111110111111111101111111111
c1c0c1c0c110c1c000000000c1c01c10c110c0c00000c0c0c1c00000c1c0c0c0c110c0c0000000cc000001111111111011111111110111111111101111111111
c0c0ccc0cc00c0c000000000ccc00c00c000cc10ccc0c0c0ccc00000ccc0c0c0ccc0ccc000000c11c00001111111111011111111110111111111101111111111
c0c0c110c100c0c000000000c1100c00c000c1c01110c0c0c1100000c110c0c011c0c1c00000c1001c0001111111111011111111110111111111101111111111
cc10c000ccc0c0c000000000c000ccc01cc0c0c000001cc0c0000000c0001cc0cc10c0c0000ccc00ccc001111111111011111111110111111111101111111111
11001000111010100000000010001110011010100000011010000000100001101100101000000c00c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c00c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000cccc00001111111111011111111110111111111101111111111
0cc0c0000cc00cc0ccc00000c0000cc00cc0c0c00000ccc0ccc00000ccc0c0c0c000c00000000111100001111111111011111111110111111111101111111111
c110c000c1c0c110c1100000c000c1c0c1c0c0c00000c1c01c100000c1c0c0c0c000c00000000000000001111111111011111111110111111111101111111111
c000c000c0c0ccc0cc000000c000c0c0c0c0cc10ccc0ccc00c000000ccc0c0c0c000c00000000000000000000000000000000000000000000000000000000000
c000c000c0c011c0c1000000c000c0c0c0c0c1c01110c1c00c000000c110c0c0c000c00000000000000000000000000000000000000000000000000000000000
1cc0ccc0cc10cc10ccc00000ccc0cc10cc10c0c00000c0c00c000000c0001cc0ccc0ccc000000000000001111111111011111111110111111111101111111111
01101110110011001110000011101100110010100000101001000000100001101110111000000cccc00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c11c00001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000c00c00001111111111011111111110111111111101111111111
0cc0ccc0c0c0ccc000000000aaa0aaa0a000a0a00000aaa00aa00000c0c00cc0ccc00000000ccc00ccc001111111111011111111110111111111101111111111
c1101c10c0c0c110000000001a10a1a0a000a0a000001a10a1a00000c0c0c110c11000000001c1001c1001111111111011111111110111111111101111111111
c0000c00c0c0cc00000000000a00aaa0a000aa10aaa00a00a0a00000c0c0ccc0cc00000000001c00c10001111111111011111111110111111111101111111111
c0c00c00ccc0c100000000000a00a1a0a000a1a011100a00a0a00000c0c011c0c1000000000001cc100001111111111011111111110111111111101111111111
ccc0ccc01c10ccc0000000000a00a0a0aaa0a0a000000a00aa1000001cc0cc10ccc0000000000011000001111111111011111111110111111111101111111111
11101110010011100000000001001010111010100000010011000000011011001110000000000000000001111111111011111111110111111111101111111111
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
)MULTILINE";

const char* builtin_gff = R"MULTILINE(
0001010100010100000000010000000000010101010101000000000100000000000101010101010101000000000000000001010101010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
)MULTILINE";

const char* builtin_map = R"MULTILINE(
0707070808080808080808080807070707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0707070800000808080808080807070707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0707070800000808080808080807000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0707076060606061626360606007000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0707077070707071727370707007000707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0727113131313131313131313121010707011131313131313131313131210107170212323232323232323232322202170701113131313131313131313121010717021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107
1131313125151515151515353131312111313131313131313131313131313121123232323232323232323232323232221131313131313131313131313131312112323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121
3131313131313131313131313131313131313131313131313131313131313131323232323232323232323232323232323131313131313131313131313131313132323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131
0707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717
0707071717171717171717171707070717171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707171717080808080808080808081717170707071717171717171717171707070717171708080808080808080808171717
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0700071717171717171717171707000717001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007170017080808080808080808081700170700071717171717171717171707000717001708080808080808080808170017
0701113131313131313131313121010717021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107170212323232323232323232322202170701113131313131313131313121010717021232323232323232323232220217
1131313131313131313131313131312112323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121123232323232323232323232323232221131313131313131313131313131312112323232323232323232323232323222
3131313131313131313131313131313132323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131323232323232323232323232323232323131313131313131313131313131313132323232323232323232323232323232
0000000000000000002000000000002007070717171717171717171717070707070707080808080808614858485863080808080808070707000000000000000017171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0020000000000000000000000010000007070717171717171717171717070707070707080808080808715848584873080808080808070707000000000000000017171708080808080808080808171717070707171717171717171717170707071717170808080808080808080817171707070717171717171717171717070707
0000002000000000000000000000000007000717171717171717171717070007070007080808000808714858485873080800080808070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000000007000717171717171717171717070007070007626262006262716667666773626200626262070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000000007000717171717171717171717070007070007747474007474717677767773747400747474070007000000000000000017001708080808080808080808170017070007171717171717171717170700071700170808080808080808080817001707000717171717171717171717070007
0000000000000000000000000000200007011131313131313131313131210107070111313131313131313131313131313131313131210107000000000000000017021232323232323232323232220217070111313131313131313131312101071702123232323232323232323222021707011131313131313131313131210107
0000000000100000002000000000000011313131313131313131313131313121113131313131312515151515151515353131313131313121000000000000000012323232323232323232323232323222113131313131313131313131313131211232323232323232323232323232322211313131313131313131313131313121
2000000000000000000020000000000031313131313131313131313131313131312f2f2f2f2f2f2f2f2f3131312f2f2f2f2f2f2f2f2f2f2f000000000000000032323232323232323232323232323232313131313131313131313131313131313232323232323232323232323232323231313131313131313131313131313131
000000100000200000001f0061626262626262626262626262626263001f0010070707080808080808080808080808080808080808070707070707405040504050405040504050405040504050070707171717090909090909090909090909090909090909171717000000100000616262626262626262626262626200000010
002000000000001000001f2071447144714473004e71447344734473001f200007070708080808080808080808080808080808080807070707070750405040504050405040504050405040504007070717171709090909090909444444450909090909090917171700200000002071447474744473b271447474447400002000
200000000020000000201f0071647164716473005e71647364736473201f000007000708080808004e080808080808080808080808070007070707405040504050405040504050404e00504050070707170017656565656565655464645565656565656565170017182f2f2f2f2f71647474746473b27164747464742f2f2f2f
000020000000000020001f0062626262626273006e71626262626263001f002007000760606060005e606060606060606060606060070007070707606060606060606162636060607e00606060070707170017666766676667666766676667666766676667170017183f3f3f3f3f61747474747473b27174747474743f3f3f3f
303030303030303030301b3131313131313131253531313131313131310b303007000770707070006e707070707070707070707070070007070707707070707070707172737070706e00707070070707170017767776777677767776777677767776777677170017151515151515151515151515151515151515151515151515
151515151515151515151818181818181818343434341818181818181818151507011131313131313131313131313131313131313121010707271131313131313131313131313131313131313121280717021232323232323232323232323232323232323222021715153c191919191919191919343434191919193d15151515
1515151515151515151515151515151515143434343424151515151515151515113131313131312515151515151515353131313131313121113131313131312515151515151515353131313131313121123232323232323232323232323232323232323232323222153c3937373737378e373737373737373737373a3d151515
15151515151515151515151515151515151515151515151515151515151515153131313131313131313131313131313131313131313131313131313131313131313131313131313131313131313131313232323232323232323232323232323232323232323232323c393737373737373737373737373737373737373a3d1515
)MULTILINE";


void ProgramDraw::LoadBuiltinGfx() {
	Program::LoadBuiltinGfxStr(builtin_gfx, gfx_data, gfx_sz);
	Program::LoadBuiltinGfxStr(builtin_lbl, lbl_data, lbl_sz);
	GetPaletteImage(gfx_data, gfx_sz, gfx);
	GetPaletteImage(lbl_data, lbl_sz, lbl);
}
/*
void ProgramDraw::LoadBuiltinGfxStr(const char* s, Image& out) {
	if (*s == '\n') s++;
	
	int line = 0;
	int max_col = 0;
	int col = 0;
	while (1) {
		int chr = *s++;
		
		if (chr == '\n') {
			line++;
			ASSERT(max_col == 0 || col == max_col);
			ASSERT(col > 0);
			max_col = max(max_col, col);
			col = -1;
		}
		else if (chr >= 'a' && chr <= 'f') {
			int n = chr - 'a' + 10;
			Color c = GetPaletteColor(n);
			RGBA r = c;
			data.Add(r);
		}
		else if (chr >= '0' && chr <= '9') {
			int n = chr - '0';
			RGBA r;
			if (n > 0)
				r = GetPaletteColor(n);
			else {
				r.r = 0;
				r.g = 0;
				r.b = 0;
				r.a = 0;
			}
			data.Add(r);
		}
		else if (!chr)
			break;
		else Panic("Invalid data");
		
		col++;
	}
	
}
*/
void Program::LoadBuiltinGfxStr(const char* s, Vector<byte>& out, Size& sz) {
	if (*s == '\n') s++;
	
	out.SetCount(0);
	out.Reserve(10000);
	
	int line = 0;
	int max_col = 0;
	int col = 0;
	while (1) {
		int chr0 = *s++;
		
		if (chr0 == '\n') {
			line++;
			ASSERT(max_col == 0 || col == max_col);
			ASSERT(col > 0);
			max_col = max(max_col, col);
			col = 0;
		}
		else if (chr0 == 0)
			break;
		else {
			int n = HexDigitAny(chr0);
			out.Add(n);
			
			col++;
		}
	}
	
	sz = Size(max_col, line);
}

void Program::LoadBuiltinGfxStr(const char* s, Vector<uint16>& out, Size& sz) {
	if (*s == '\n') s++;
	
	out.SetCount(0);
	out.Reserve(10000);
	
	int line = 0;
	int max_col = 0;
	int col = 0;
	while (1) {
		int chr0 = *s++;
		
		if (chr0 == '\n') {
			line++;
			ASSERT(max_col == 0 || col == max_col);
			ASSERT(col > 0);
			max_col = max(max_col, col);
			col = 0;
		}
		else if (chr0 == 0)
			break;
		else {
			int chr1 = *s++;
			
			int n0 = HexDigitAny(chr0);
			int n1 = HexDigitAny(chr1);
			ASSERT(n0 >= 0 && n0 < 0x10);
			ASSERT(n1 >= 0 && n1 < 0x10);
			int n = (n0 << 4) | n1;
			out.Add(n);
			
			col++;
		}
	}
	
	sz = Size(max_col, line);
}



}

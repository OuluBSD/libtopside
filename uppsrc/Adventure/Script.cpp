#include "Adventure.h"

namespace Adventure {
	
	


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

void Program::Cutscene(SceneType type, HiValue* self, HiValue func_cutscene, HiValue func_override) {
	auto& global = ctx.global;
	
	/*cut = {
		flags = type,
		thrd = cocreate(func_cutscene),
		override_ = func_override,
		paused_cam_following = cam_following_actor
	};*/
	
	if (cutscene_override.IsVoid()) {
		cutscene_override = func_override;
		
		Script& cut = AddCutscene("cutscene0");
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

void Program::ClearCutsceneOverride(Script* s) {
	cutscene_override = HiValue();
	
	if (s == cutscene_curr)
		cutscene_curr = 0;
}


Script& Program::AddScript(String name, int group) {
	return ctx.CreateProgramT<Script>(name, group);
}

Script& Program::AddLocal(String name) {
	return AddScript(name, SCRIPT_LOCAL);
}

Script& Program::AddGlobal(String name) {
	return AddScript(name, SCRIPT_GLOBAL);
}

Script& Program::AddCutscene(String name) {
	return AddScript(name, SCRIPT_CUTSCENE);
}

void Program::StartScript(Gate0 func, bool bg, HiValue noun1, HiValue noun2) {
	RemoveStoppedScripts();
	
	// background || local?
	if (bg)
		AddGlobal("script").Set(func, noun1, noun2).Start();
	
	else
		AddLocal("script").Set(func, noun1, noun2).Start();
}

void Program::StartScriptHi(HiValue* self, HiValue script_name, bool bg, HiValue noun1, HiValue noun2) {
	auto& global = ctx.global;
	
	//LOG("Program::StartScriptHi: " << script_name);
	RemoveStoppedScripts();
	
	// background || local?
	if (bg)
		AddGlobal("hi-script").Set(global, self, script_name, noun1, noun2);
	
	else
		AddLocal("hi-script").Set(global, self, script_name, noun1, noun2);
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
	/*for(int i = 0; i < local_scripts.GetCount(); i++)
		if (&local_scripts[i] == &func)
			{local_scripts.Remove(i); break;}
			
	for(int i = 0; i < global_scripts.GetCount(); i++)
		if (&global_scripts[i] == &func)
			{global_scripts.Remove(i); break;}*/
	ctx.StopProgram(func);
}

void Program::RemoveStoppedScripts() {
	RemoveStoppedScripts(local_scripts);
	RemoveStoppedScripts(global_scripts);
	RemoveStoppedScripts(cutscenes);
}

void Program::RemoveStoppedScripts(int group) {
	for(int i = 0; i < scripts.GetCount(); i++)
		if (!scripts[i].running)
			scripts.Remove(i);
}

void Program::UpdateScripts(int group) {
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

bool Program::ParseGame(String content, String path) {
	auto& global = ctx.global;
	
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
	
	LOG(x << "," << y << ": " << txt);
	
	Animation& a = ctx.a;
	AnimPlayer& p = ctx.p;
	HiAnimProgram* prog = ctx.FindProgram(e);
	ASSERT(prog);
	
	AnimScene& s = a.GetActiveScene();
	AnimObject& parent = s.GetRoot();
	AnimObject& o = parent.Add();
	o.SetPosition(Point(x,y));
	o.SetText(txt, 20, Color(47, 98, 158));
	p.Recompile(parent);
	
	int ms = duration / 32.0 * 1000;
	p.AddTimedRemoveObject(ms, o, prog->ContinueVmCallback());
	
	//e.esc.hi.SleepReleasing(ms);
	e.esc.hi.SleepInfiniteReleasing();
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



	
}

#include "Animator.h"

NAMESPACE_TOPSIDE_BEGIN


Project::Project() {
	
}


bool Project::Init() {
	
	ctx.Clear();
	ctx.InitializeEmptyScene();
	
	if (!ctx.AddCodePath(GetDataFile("Tester.high")))
		return false;
	
	if (!ctx.Init(false))
		return false;
	
	//if (!AddHighFunctions())
	//	return false;
	
	// init all the rooms/objects/actors
	/*if (!InitGame())
		return false;
	
	if (!ReadGame())
		return false;*/
	
	ctx.KeepRunning();
	
	return true;
}


void Project::Update() {
	
	ctx.Iterate();
	
	#if 0
	HiValue selected_actor = GetSelectedActor();
	
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
	#endif
	
}

HiAnimProgram& Project::StartScript(Gate0 func, bool bg, HiValue noun1, HiValue noun2) {
	ctx.RemoveStopped();
	
	int group = bg;
	HiAnimProgram& s = ctx.CreateProgramT<HiAnimProgram>("native", group);
	s.Set(func, noun1, noun2);
	
	return s;
}

HiAnimProgram& Project::StartScriptHi(HiValue* self, HiValue script_name, bool bg, HiValue noun1, HiValue noun2) {
	ctx.RemoveStopped();
	
	int group = bg;
	HiAnimProgram& s = ctx.CreateProgramT<HiAnimProgram>(script_name, group);
	s.Set(self, script_name, noun1, noun2);
	
	return s;
}

void Project::HiPrintLine(HiEscape& e) {
	String txt = e[0].ToString();
	int x = e[1].GetInt();
	int y = e[2].GetInt();
	int col = e[3].GetInt();
	int align = e[4].GetInt();
	bool use_caps = e[5].GetInt();
	float duration = e[6].GetNumber();
	bool big_font = e[7].GetInt();
	
	if (txt.GetCount() >= 2 && txt[0] == '"')
		txt = txt.Mid(1, txt.GetCount()-2);
	
	AddTextObject(e, txt, x, y, col, align, use_caps, duration, big_font);
}

bool Project::InitGame() {
	auto& global = ctx.global;
	
	//game = HiValue();
	
	try {
		HiValue empty_lambda;
		empty_lambda.CreateLambda();
		Vector<HiValue> arg;
		Execute(global, 0, global.Get("main", empty_lambda), arg, INT_MAX);
		//RealizeGame();
		Execute(global, 0, global.Get("startup_script", empty_lambda), arg, INT_MAX);
	}
	catch(CParser::Error e) {
		LOG("Project::ParseGame: error: " << e << "\n");
		return false;
	}
	
	return true;
}

void Project::SetSelectedActor(HiValue o) {
	auto& global = ctx.global;
	global.GetAdd("selected_actor") = o;
}

HiValue Project::GetSelectedActor() {
	auto& global = ctx.global;
	//DUMPC(global.GetKeys());
	//ASSERT(global.Find("selected_actor") >= 0);
	return global.Get("selected_actor", HiValue());
}

void Project::AddTextObject(HiEscape& e, String txt, int x, int y, int col, int align, bool use_caps, float duration, bool big_font) {
	LOG("Project::AddTextObject: " << x << "," << y << ": " << txt);
	
	if (use_caps)
		txt = ToUpper(txt);
	
	int fnt_h = big_font ? 16 : 8;
	
	Animation& a = ctx.a;
	AnimPlayer& p = ctx.p;
	HiAnimProgram* prog = ctx.FindProgram(e);
	ASSERT(prog);
	
	AnimScene& s = a.GetActiveScene();
	AnimObject& parent = s.GetRoot();
	AnimObject& o = parent.Add();
	o.SetPosition(Point(x,y));
	o.SetText(txt, fnt_h, Color(47, 98, 158));
	p.Recompile(parent);
	
	int ms = duration / 32.0 * 1000;
	
	//ms *= dbg_sleep_multiplier;
	
	p.AddTimedRemoveObject(ms, o, prog->ContinueCallback());
	
	//e.esc.hi.SleepReleasing(ms);
	e.esc.hi.SleepInfiniteReleasing();
}



NAMESPACE_TOPSIDE_END

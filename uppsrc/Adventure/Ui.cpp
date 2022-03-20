#include "Adventure.h"

namespace Adventure {



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
	auto& global = ctx.global;
	
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

HiValue Program::RunLambda1(HiValue* self, const HiValue& l, const HiValue& arg0) {
	auto& global = ctx.global;
	
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


bool Program::IsPressed(GamepadButton b) const {
	ASSERT(b >= (GamepadButton)0 && b < BTN_COUNT);
	
	if (b >= (GamepadButton)0 && b < BTN_COUNT)
		return pressed[b];
	
	return false;
}

bool Program::IsMousePressed(MouseButtonMask m) const {
	return mouse_pressed & m;
}


}

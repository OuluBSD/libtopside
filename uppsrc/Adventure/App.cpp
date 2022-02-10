#include "Adventure.h"

namespace Adventure {






ProgramApp::ProgramApp() {
	Title("Program App");
	Sizeable().MaximizeBox().MinimizeBox();
	
	Add(draw.SizePos());
	
	tc.Set(-10, THISBACK(ProcessScript));
	
	draw.SetProgram(prog);
}

void ProgramApp::ProcessScript() {
	
	
	
	Sleep(1);
}







void ProgramDraw::Paint(Draw& w) {
	Size sz = GetSize();
	int cam_x = p->cam_x.x;
	int cam_shake_x = p->cam_shake_x;
	int cam_shake_y = p->cam_shake_y;
	int fade_iris = p->fade_iris;
	int stage_top = p->stage_top;
	const auto& dialog_curr = p->dialog_curr;
	int cutscene_cooloff = p->cutscene_cooloff;
	const auto& cutscene_curr = p->cutscene_curr;
	
	// clear screen every frame
	w.DrawRect(sz, White());
	
	// reposition camera (account for (shake, if (active)
	w.Offset(cam_x + cam_shake_x, 0 + cam_shake_y);
	
	// clip room bounds (also used for ("iris" transition)
	w.Clip(
		0 + fade_iris - cam_shake_x,
		stage_top + fade_iris - cam_shake_y,
		128 - fade_iris*2 - cam_shake_x,
		64 - fade_iris*2);
	    
	// draw room (bg + objects + actors)
	DrawRoom(w);
	
	// reset camera and clip bounds for ("static" content (ui, etc.)
	w.End();
	w.End();
	
	#if 0
	if (show_debuginfo) {
		PaintLog(w, "cpu: " + IntStr(100*stat(1)) + "%", 0, stage_top - 16, 8);
		PaintLog(w, "mem: " + IntStr(stat(0) / 1024*100) + "%", 0, stage_top - 8, 8);
		PaintLog(w, "x: " + IntStr(cursor_x + cam_x) + " y:" + cursor_y - stage_top, 80, stage_top - 8, 8);
	}
	#endif
	
	// if (show_depth {
	//  fillp(0b0011001111001100.1)
	//  line(0,room_curr.autodepth_pos[1]+stage_top,128,room_curr.autodepth_pos[1]+stage_top,1)
	//  print(room_curr.autodepth_scale[1], 0,room_curr.autodepth_pos[1]+stage_top+2)
	//  line(0,room_curr.autodepth_pos[2]+stage_top,128,room_curr.autodepth_pos[2]+stage_top,12)
	//  print(room_curr.autodepth_scale[2], 0,room_curr.autodepth_pos[2]+stage_top+2)
	//  fillp()
	// }
	
	// draw active/speech text
	DrawTalking(w);
	
	// in dialog mode?
	if (dialog_curr && dialog_curr.visible) {
		// draw dialog sentences?
		DrawDialog();
		DrawCursor();
		// skip rest
		return;
	}
	
	// hack:
	// skip draw if (just exited a cutscene
	// as could be going straight into a dialog
	// (would prefer a better way than this, but couldn't find one!)
	//
	if (cutscene_cooloff > 0) {
		cutscene_cooloff -= 1;
		return;
	}
	
	// draw current command (verb/object)
	if (!cutscene_curr)
		DrawCommand();
		
	// draw ui and inventory (only if (actor selected to use it!)
	if (!cutscene_curr
		? cutscene_curr->flags == 2 // quick-cut
		// and not just left a cutscene
		: cutscene_cooloff == 0) {
		DrawUI();
	}
	
	if (!cutscene_curr) DrawCursor();
	
}

void ProgramDraw::PaintLog(Draw& w, String s, int x, int y, int font_h) {
	Font fnt = SansSerif(font_h);
	w.DrawText(x, y, s, fnt);
}

void ProgramDraw::ResetPalette() {
	TODO
}

void ProgramDraw::DrawRoom(Draw& w) {
	const auto& cam_x = p->cam_x.x;
	const auto& stage_top = p->stage_top;
	
	// check for (current room
	if (!p->room_curr) {
		PaintLog(w, "-error-  no current room set", 5 + cam_x, 5 + stage_top, 8);
		return;
	}
	
	const SObj& room_curr = *p->room_curr;
	
	
	// set room background col (or black by default)
	w.DrawRect(0, stage_top, 127, stage_top + 64, ReadColor(room_curr, "bg_col", Black()));
	
	// draw each zplane, from back to front
	int begin_z = -64;
	int end_z = +64;
	for (int z = begin_z; z <= end_z; z++) {
	
		// draw bg layer?
		if (z == 0) {
			// replace colors?
			ReplaceColors(room_curr);
			
			Color trans_col;
			if (TryReadColor("trans_col", trans_col)) {
				//palt(0, false);
				//palt(room_curr.trans_col, true);
				TODO
			}
			TODO //map(room_curr.map[1], room_curr.map[2], 0, stage_top, room_curr.map_w, room_curr.map_h);
			
			ResetPalette();
			
			
			// ===============================================================
			// debug walkable areas
			
			// if (show_pathfinding {
			//	actor_cell_pos = GetCellPos(selected_actor)
			
			// //## need to correct this offset (in code above)
			// //actor_cell_pos[2] -= 2
			
			//	celx = flr((cursor_x + cam_x + 0) /8) + room_curr.map[1]
			//	cely = flr((cursor_y - stage_top + 0) /8 ) + room_curr.map[2]
			//	target_cell_pos = { celx, cely }
			
			//	path = find_path(actor_cell_pos, target_cell_pos)
			
			//	// finally, add our destination to list
			//	click_cell = GetCellPos({x=(cursor_x + cam_x), y=(cursor_y - stage_top)})
			//	if (IsCellWalkable(click_cell[1], click_cell[2]) {
			//	//if ((#path>0) {
			//		add(path, click_cell)
			//	}
			
			//	for (p in all(path)) {
			//		//printh("  > "..p[1]..","..p[2])
			//		rect(
			//			(p[1]-room_curr.map[1])*8,
			//			stage_top+(p[2]-room_curr.map[2])*8,
			//			(p[1]-room_curr.map[1])*8+7,
			//			stage_top+(p[2]-room_curr.map[2])*8+7, 11)
			//	}
			// }
			
			// ===============================================================
		}
		else {
			// draw other layers
			ZPlane& zplane = draw_zplanes[begin_z - z];
			
			// draw all objs/actors in current zplane
			for (SObj* p : zplane.objs) {
				SObj& obj = *p;
				
				// object || actor?
				SObj* classes = ReadKey(obj, "classes");
				if (classes && !ReadFlag(*classes, "class_actor")) {
					SObj* states = ReadKey(obj, "states");
					SObj* state = ReadKey(obj, "state");
					
					TODO
					/*if obj.states	  -- object has a state?
				    or (obj.state
					   and obj[obj.state]
					   and obj[obj.state] > 0)
					 and (not obj.dependent_on 			-- object has a valid dependent state?
						or obj.dependent_on.state == obj.dependent_on_state)
					 and not obj.owner   						-- object is not "owned"
					 or obj.draw
                     or obj.curr_anim
					then*/
					
					// object
					/*if (states	  // object has a state?
						|| (state &&
						? (State(obj)
						   && obj[State(obj)]
						   && obj[State(obj)] > 0)
						: (!obj.dependent_on			// object has a valid dependent state?
						   || obj.dependent_on.state == obj.dependent_on_state)
						? !obj.owner					// object is not "owned"
						: obj.draw
						|| obj.curr_anim) {
						// something to draw
						DrawObject(obj);
					}*/
				}
				else {
					// actor
					SObj* in_room = this->p->GetInRoom(obj);
					if (in_room == &room_curr)
						DrawActor(obj);
				}
				//show_collision_box(obj);
			}
		}
	}
}


void ProgramDraw::DrawTalking(Draw& d) {
	// alignment
	//   0 = no align
	//   1 = center
	TalkingState& talking_curr = p->talking_curr;
	
	if (talking_curr) {
		int line_offset_y = 0;
		for (const String& l : talking_curr.msg_lines) {
			int line_offset_x = 0;
			// center-align line
			if (talking_curr.align == 1) {
				int len = l.GetCount();
				line_offset_x = ((talking_curr.char_width * 4) - (len * 4)) / 2;
			}
			OutlineText(
				d,
				l,
				talking_curr.x + line_offset_x,
				talking_curr.y + line_offset_y,
				talking_curr.col,
				0,
				talking_curr.use_caps,
				talking_curr.big_font);
			line_offset_y += talking_curr.big_font ? 12 : 6;
		}
		// update message lifespan
		talking_curr.time_left -= 1;
		// remove text & reset actor's talk anim
		if (talking_curr.time_left <= 0)
			p->StopTalking();
	}
}


// draw ui and inventory
void ProgramDraw::DrawUI() {
	TODO
	
	// draw verbs
	/*local xpos, ypos, col_len = 0, 75, 0;

	for (v in all(verbs)) {
		local txtcol = v == hover_curr_verb ? verb_hovcol :
			(hover_curr_default_verb && v == hover_curr_default_verb ? verb_defcol :
			verb_maincol);

		// get verb info
		local vi = GetVerb(v);
		print(vi[3], xpos, ypos+stage_top+1, verb_shadcol);  // shadow
		print(vi[3], xpos, ypos+stage_top, txtcol);  // main

		// capture bounds
		v.x = xpos;
		v.y = ypos;
		RecalculateBounds(v, #vi[3]*4, 5, 0, 0);
		//show_collision_box(v)

		// auto-size column
		if (#vi[3] > col_len) col_len = #vi[3];

		ypos += 8;

		// move to next column
		if (ypos >= 95) {
			ypos = 75;
			xpos += (col_len + 1.0) * 4;
			col_len = 0;
		}
	}

	if (selected_actor) {
		// draw inventory
		xpos, ypos = 86, 76;
		// determine the inventory "window"
		local start_pos = selected_actor.inv_pos * 4;
		local end_pos = min(start_pos+8, #selected_actor.inventory);

		for (ipos = 1,8) {
			// draw inventory bg
			rectfill(xpos-1, stage_top+ypos-1, xpos+8, stage_top+ypos+8, verb_shadcol);

			obj = selected_actor.inventory[start_pos+ipos];
			if (obj) {
				// something to draw
				obj.x, obj.y = xpos, ypos;
				// draw object/sprite
				DrawObject(obj);
				// re-calculate bounds (as pos may have changed)
				RecalculateBounds(obj, obj.w*8, obj.h*8, 0, 0);
				//show_collision_box(obj)
			}
			xpos += 11;

			if (xpos >= 125) {
				ypos += 12;
				xpos = 86;
			}
			ipos += 1;
		}

		// draw arrows
		for (i = 1,2) {
			arrow = ui_arrows[i];
			pal(7, hover_curr_arrow == arrow ? verb_hovcol : verb_maincol);
			pal(5, verb_shadcol);
			DrawSprite(arrow.spr, arrow.x, arrow.y, 1, 1, 0);
			// capture bounds
			RecalculateBounds(arrow, 8, 7, 0, 0);
			//show_collision_box(arrow)
			pal(); //reset palette
		}
	}*/
}

void ProgramDraw::DrawDialog() {
	TODO
	/*local xpos, ypos = 0, 70;

	for (s in all(dialog_curr.sentences)) {
		if (s.char_width > 0) {
			// capture bounds
			s.x, s.y = xpos, ypos;
			RecalculateBounds(s, s.char_width*4, #s.lines*5, 0, 0);

			local txtcol = s == hover_curr_sentence ? dialog_curr.hlcol : dialog_curr.col;

			for (l in all(s.lines)) {
				print(SmallCaps(l), xpos, ypos+stage_top, txtcol);
				ypos += 5;
			}

			//show_collision_box(s)
			ypos += 2;
		}
	}*/
}

// draw cursor
void ProgramDraw::DrawCursor() {
	TODO
	/*col = ui_cursor_cols[cursor_colpos];
	// switch sprite color accordingly
	pal(7,col);
	spr(ui_cursorspr, cursor_x-4, cursor_y-3, 1, 1, 0);
	pal(); //reset palette

	cursor_tmr += 1;
	if (cursor_tmr > 7) {
		//reset timer
		cursor_tmr = 1;
		// move to next color?
		cursor_colpos = cursor_colpos % #ui_cursor_cols + 1;
	}*/
}

void ProgramDraw::DrawSprite(int n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale) {
	TODO
	/*
	// switch transparency
	SetTransCol(transcol); //, true)
	
	// draw zoomed sprite
//https://www.lexaloffle.com/bbs/?tid=2429
	local sx, sy = 8 * (n % 16), 8 * flr(n / 16);
	local sw, sh = 8 * w, 8 * h;
	local dz = scale || 1;
	local dw, dh = sw * dz, sh * dz;
	sspr(sx, sy, sw, sh, x, stage_top + y, dw, dh, flip_x, flip_y);
	
	// first scale, bottom-anchored
//sspr(sx, sy, sw, sh, x, stage_top + y +(sh-dh), dw, dh, flip_x, flip_y)

	//spr(n, x, stage_top + y, w, h, flip_x, flip_y) // orig method (pre-scale)
	
	//pal() // don't) {, affects lighting!
	*/
}

void ProgramDraw::DrawObject(SObj& obj) {
	TODO
	/*
	local sprnum = 0;
	// replace colors?
	ReplaceColors(obj);
	               
	// check for (custom draw
	if (obj.draw) {
		obj.draw(obj);
	}
	
	else {
		if (obj.curr_anim) {
			// update animation state
			Animate(obj);
			// choose walk anim frame
			sprnum = obj.curr_anim[obj.anim_pos];
				 }
				 // allow for (repeating
		for (h = 0, obj.repeat_x ? obj.repeat_x - 1 : 0) {
			// draw object (in its state!)
			if (State(obj)s) {
				sprnum = State(obj)s[State(obj)];
			}
			else if (sprnum == 0) {
				sprnum = obj[State(obj)];
			}
			DrawSprite(sprnum, obj.x + (h * (obj.w * 8)), obj.y, obj.w, obj.h, obj.trans_col, obj.flip_x, obj.scale);
		}
	}
     
// debug
	//pset(obj.x, obj.y + stage_top, 8)
     
	//reset palette
	pal();
	*/
 }


// draw actor(s)
void ProgramDraw::DrawActor(SObj& actor) {
	TODO
	/*
	local dirnum, sprnum = face_dirs[actor.face_dir];
	
	if (actor.curr_anim && (actor.moving == 1 || IsTable(actor.curr_anim)) {
	// update animation state
	Animate(actor)
		;
		// choose walk anim frame
		sprnum = actor.curr_anim[actor.anim_pos];
	}
	else {
	
		// idle
		sprnum = actor.idle[dirnum];
	}
	
	// replace colors?
	ReplaceColors(actor);
	
// auto-scaling for (depth?
	local factor = (actor.y - room_curr.autodepth_pos[1]) / (room_curr.autodepth_pos[2] - room_curr.autodepth_pos[1]);
	factor = room_curr.autodepth_scale[1] + (room_curr.autodepth_scale[2] - room_curr.autodepth_scale[1]) * factor;
	actor.auto_scale = mid(room_curr.autodepth_scale[1], factor, room_curr.autodepth_scale[2]);
	
// apply "zoom" to autoscale (e.g. camera further away)
//auto_scale *= (room_curr.scale || 1)


// calc scaling offset (to align to bottom-centered)
	local scale = actor.scale || actor.auto_scale;
	local scale_height, scale_width = (8 * actor.h), (8 * actor.w);
	local scaleoffset_y = scale_height - (scale_height * scale);
	local scaleoffset_x = scale_width - (scale_width * scale);
	local draw_x = actor.offset_x + flr(scaleoffset_x / 2);
	local draw_y = actor.offset_y + scaleoffset_y;
	
	DrawSprite(sprnum,
			draw_x,
			draw_y,
			actor.w ,
			actor.h,
			actor.trans_col,
			actor.flip,
			false,
			scale);
	        
	        
	// talking overlay
	if (talking_actor
		&& talking_actor == actor
	&& talking_actor.talk) {
	if (actor.talk_tmr < 7) {
			// note: scaling from top-left
			DrawSprite(actor.talk[dirnum],
					draw_x + (actor.talk[5] || 0),
					draw_y + flr((actor.talk[6] || 8)*scale),
					(actor.talk[7] || 1),
					(actor.talk[8] || 1),
					actor.trans_col,
					actor.flip,
					false,
					scale);
		}
		actor.talk_tmr = actor.talk_tmr % 14 + 1;
	}
	
// debug
// if (show_debuginfo {
	// pset(actor.x, actor.y + stage_top, 8)
	// pset(actor.offset_x, actor.offset_y+stage_top, 11)
// }

	//reset palette
	pal();
	*/
}


void ProgramDraw::DrawCommand() {
	TODO
	/*
	// draw current command
	local cmd_col, verb_curr_ref, command = verb_maincol, verb_curr[2], verb_curr ? verb_curr[3] : "";

	if (noun1_curr) {
		command = command.." "..noun1_curr.name;
		if (verb_curr_ref == V_USE && (!executing_cmd || noun2_curr)) {
			command = command.." with";
		}
		else if (verb_curr_ref == V_GIVE) {
			command = command.." to";
		}
	}
	if (noun2_curr) {
		command = command.." "..noun2_curr.name;
	}
	else if (hover_curr_object
		and hover_curr_object.name != ""
		// don't show use object with itself!
		and ( !noun1_curr || (noun1_curr != hover_curr_object) )
		// || walk-to objs in inventory!
		// && ( not hover_curr_object.owner or
		// 				or verb_curr_ref != GetVerb(verb_default)[2] )
  // || when already executing!
  && !executing_cmd)
	{
	  // default to look-at for (inventory items
	  if (hover_curr_object.owner && verb_curr_ref == GetVerb(verb_default)[2]) {
	   command = "look-at";
	  }
		command = command.." "..hover_curr_object.name;
	}
	cmd_curr = command;

	if (executing_cmd) {
		// highlight active command
		command = cmd_curr;
		cmd_col = verb_hovcol;
	}

	print( SmallCaps(command), 63.5-flr(#command*2), stage_top + 66, cmd_col );
	*/
}

void ProgramDraw::ReplaceColors(const SObj& obj) {
	TODO
}

void ProgramDraw::OutlineText(Draw& d, String str, int x, int y, int c0, int c1, bool use_caps, bool big_font) {
	TODO
	/*
	if (!use_caps) str = SmallCaps(str);
	if (big_font) str = "\^w\^t"..str;
	for (xx = -1, 1) {
		for (yy = -1, 1, xx == 0 ? 2 : 1) {
				print(str, x + xx, y + yy, c1);
			}
		}
	print(str, x, y, c0);
	*/
}


}

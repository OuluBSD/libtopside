#include "Adventure.h"

namespace Adventure {






ProgramApp::ProgramApp() {
	Title("Program App");
	Sizeable().MaximizeBox().MinimizeBox();
	
	Rect r = GetRect();
	SetRect(RectC(r.left, r.top, 512, 512));
	
	Add(draw.SizePos());
	
	tc.Set(-10, THISBACK(ProcessScript));
	
	draw.SetProgram(prog);
}

void ProgramApp::ProcessScript() {
	prog.Update();
	draw.Refresh();
}








ProgramDraw::ProgramDraw() {
	fnt = SansSerif(8);
	ResetPalette();
	LoadBuiltinGfx();
}

void ProgramDraw::ResetPalette() {
	for(int i = 0; i < PALETTE_SIZE; i++)
		dyn_palette[i] = i;
	for(int i = 0; i < PALETTE_SIZE; i++)
		palette[i] = GetPicoPalette(i);
}

void ProgramDraw::SetPalette(int idx, PaletteColor clr) {
	ASSERT(idx >= 0 && idx < PALETTE_SIZE);
	dyn_palette[idx] = clr;
}

void ProgramDraw::Paint(Draw& w) {
	Size sz = GetSize();
	int min_edge = min(sz.cx, sz.cy);
	Size tgt_sz(min_edge, min_edge);
	canvas_sz = Size(128, 128);
	ImageDraw d(128, 128);
	size_mul = (double)canvas_sz.cx / (double)tgt_sz.cx;
	
	int cam_x = p->cam.x;
	int cam_shake_x = p->cam_shake_x;
	int cam_shake_y = p->cam_shake_y;
	int fade_iris = p->fade_iris;
	int stage_top = p->stage_top;
	const auto& dialog_curr = p->dialog_curr;
	int& cutscene_cooloff = p->cutscene_cooloff;
	const auto& cutscene_curr = p->cutscene_curr;
	
	// clear screen every frame
	d.DrawRect(sz, Black());
	
	bool do_shake = false;
	
	if (do_shake) {
		// reposition camera (account for (shake, if (active)
		d.Offset(cam_x + cam_shake_x, 0 + cam_shake_y);
		
		// clip room bounds (also used for ("iris" transition)
		d.Clip(
			0 + fade_iris - cam_shake_x,
			stage_top + fade_iris - cam_shake_y,
			128 - fade_iris*2 - cam_shake_x,
			64 - fade_iris*2);
	}
	    
	// draw room (bg + objects + actors)
	PaintRoom(d);
	
	if (do_shake) {
		// reset camera and clip bounds for ("static" content (ui, etc.)
		d.End();
		d.End();
	}
	
	#if 0
	if (show_debuginfo) {
		PaintLog(d, "cpu: " + IntStr(100*stat(1)) + "%", 0, stage_top - 16, 8);
		PaintLog(d, "mem: " + IntStr(stat(0) / 1024*100) + "%", 0, stage_top - 8, 8);
		PaintLog(d, "x: " + IntStr(cursor_x + cam_x) + " y:" + cursor_y - stage_top, 80, stage_top - 8, 8);
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
	PaintTalking(d);
	
	// in dialog mode?
	if (dialog_curr && dialog_curr.visible) {
		// draw dialog sentences?
		PaintDialog(d);
		PaintCursor(d);
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
	}
	else {
		
		// draw current command (verb/object)
		if (!cutscene_curr)
			PaintCommand(d);
			
		// draw ui and inventory (only if (actor selected to use it!)
		if (cutscene_curr
			? cutscene_curr->flags == 2 // quick-cut
			// and not just left a cutscene
			: cutscene_cooloff == 0) {
			PaintUI(d);
		}
		
		if (!cutscene_curr)
			PaintCursor(d);
		
	}
	
	Image img = d;
	img = RescaleFilter(img, tgt_sz, FILTER_NEAREST);
	w.DrawImage(0,0, img);
}

void ProgramDraw::PaintLog(Draw& d, String s, int x, int y, PaletteColor clr) {
	Color c = GetPaletteColor(clr);
	d.DrawText(x, y, s, fnt, c);
}

void ProgramDraw::PaintRoom(Draw& d) {
	const auto& cam_x = p->cam.x;
	const auto& stage_top = p->stage_top;
	
	// check for (current room
	if (p->room_curr.IsVoid()) {
		PaintLog(d, "-error-  no current room set", 5 + cam_x, 5 + stage_top, 8);
		return;
	}
	
	const SObj& room_curr = p->room_curr;
	
	
	// set room background col (or black by default)
	d.DrawRect(0, stage_top, 127, stage_top + 64, ReadColor(room_curr, "bg_col", Black()));
	
	// draw each zplane, from back to front
	int begin_z = -64;
	int end_z = +64;
	for (int z = begin_z; z <= end_z; z++) {
	
		// draw bg layer?
		if (z == 0) {
			// replace colors?
			ReplaceColors(room_curr);
			
			Color trans_col;
			if (TryReadColor(room_curr, "trans_col", trans_col)) {
				//palt(0, false);
				//palt(room_curr.trans_col, true);
				TODO
			}
			HiValue map = room_curr.MapGet("data").MapGet("map");
			//LOG(room_curr.ToString()); LOG(map.ToString());
			ASSERT(map.IsArray());
			int map0 = map.ArrayGet(0).GetInt();
			int map1 = map.ArrayGet(1).GetInt();
			int map_w = 0, map_h = 0;
			if (map.GetArray().GetCount() >= 4) {
				map_w = map.ArrayGet(2).GetInt();
				map_h = map.ArrayGet(3).GetInt();
			}
			PaintMap(d, map0, map1, 0, stage_top, map_w, map_h);
			
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
			int idx = z - begin_z;
			ZPlane& zplane = p->draw_zplanes[idx];
			
			// draw all objs/actors in current zplane
			for (SObj& obj : zplane.objs) {
				//DUMP(obj);
				
				// object || actor?
				SObj classes = obj["classes"];
				if (classes.IsArray() && !HasArrayValue(classes, "class_actor")) {
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
						PaintObject(obj);
					}*/
				}
				else {
					// actor
					//DUMP(obj);
					SObj in_room = this->p->GetInRoom(obj);
					if (in_room == room_curr)
						PaintActor(d, obj);
				}
				//show_collision_box(obj);
			}
		}
	}
}


void ProgramDraw::PaintTalking(Draw& d) {
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
void ProgramDraw::PaintUI(Draw& d) {
	
	// draw verbs
	int xpos = 0;
	int ypos = 75;
	int col_len = 0;
	
	SObj hover_curr_verb = p->hover_curr_verb;
	SObj hover_curr_default_verb = p->hover_curr_default_verb;
	PaletteColor verb_shadcol = p->verb_shadcol;
	PaletteColor verb_hovcol = p->verb_hovcol;
	PaletteColor verb_defcol = p->verb_defcol;
	PaletteColor verb_maincol = p->verb_maincol;
	int stage_top = p->stage_top;
	SObj selected_actor = p->GetSelectedActor();
	const SObj& hover_curr_arrow = p->hover_curr_arrow;
	
	HiValue ea;
	ea.SetEmptyArray();
	
	for (int i = 0; i != p->V_COUNT; i++) {
		SObj v = p->verbs.ArrayGet(i);
		
		PaletteColor txtcol;
		if (v == hover_curr_verb)
			txtcol = verb_hovcol;
		else if (v == hover_curr_default_verb)
			txtcol = verb_defcol;
		else
			txtcol = verb_maincol;
		
		// get verb info
		String name = p->GetVerbString(v);
		int namelen = name.GetCount();
		PaintLog(d, name, xpos, ypos+stage_top+1, verb_shadcol);  // shadow
		PaintLog(d, name, xpos, ypos+stage_top, txtcol);  // main
		
		// capture bounds
		SObj obj;
		obj.MapSet("x", xpos);
		obj.MapSet("y", ypos);
		obj.MapSet("classes", ea);
		p->RecalculateBounds(obj, namelen*4, 5, 0, 0);
		//show_collision_box(obj)

		// auto-size column
		if (namelen > col_len)
			col_len = namelen;
		
		ypos += 8;
		
		// move to next column
		if (ypos >= 95) {
			ypos = 75;
			xpos += (col_len + 1.0) * 4;
			col_len = 0;
		}
	}
	
	if (selected_actor.IsMap()) {
		HiValue inventory = selected_actor.MapGet("inventory");
		if (!inventory.IsArray()) {DUMP(inventory);}
		ASSERT(inventory.IsArray());
		
		int inv_arr_len = inventory.GetArray().GetCount();
		
		// draw inventory
		int xpos = 86;
		int ypos = 76;
		
		// determine the inventory "window"
		int inv_pos = selected_actor.MapGet("inv_pos").GetInt();
		ASSERT(inv_pos >= 0 && inv_pos < 0x10000);
		int start_pos = inv_pos * 4;
		int end_pos = min(start_pos+8, inv_arr_len);

		for (int ipos = 0; ipos < 8; ipos++) {
			// draw inventory bg
			Color rect_clr = GetPaletteColor(verb_shadcol);
			d.DrawRect(xpos-1, stage_top+ypos-1, xpos+8, stage_top+ypos+8, rect_clr);

			SObj obj = inventory(start_pos+ipos, SObj());
			//DUMP(obj);
			if (obj) {
				// something to draw
				obj.MapSet("x", xpos);
				obj.MapSet("y", ypos);
				
				// draw object/sprite
				PaintObject(d, obj);
				
				// re-calculate bounds (as pos may have changed)
				int w = obj.MapGet("w").GetInt();
				int h = obj.MapGet("h").GetInt();
				ASSERT(w >= 0 && w < 0x10000);
				ASSERT(h >= 0 && h < 0x10000);
				p->RecalculateBounds(obj, w*8, h*8, 0, 0);
				//show_collision_box(obj)
			}
			xpos += 11;

			if (xpos >= 125) {
				ypos += 12;
				xpos = 86;
			}
		}

		// draw arrows
		for (int i = 0; i < 2; i++) {
			HiValue arrow = p->ui_arrows[i];
			int spr = arrow("spr");
			int x = arrow("x");
			int y = arrow("y");
			SetPalette(7, hover_curr_arrow == arrow ? verb_hovcol : verb_maincol);
			SetPalette(5, verb_shadcol);
			PaintSprite(d, gfx, spr, x, y, 1, 1, 0);
			
			// capture bounds
			p->RecalculateBounds(arrow, 8, 7, 0, 0);
			
			//show_collision_box(arrow)
			ResetPalette(); //reset palette
		}
	}
}

void ProgramDraw::PaintDialog(Draw& d) {
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
void ProgramDraw::PaintCursor(Draw& d) {
	PaletteColor col = p->ui_cursor_cols[p->cursor_colpos];
	
	// switch sprite color accordingly
	SetPalette(7, col);
	PaintSprite(d, gfx, p->ui_cursorspr, p->cursor_x-4, p->cursor_y-3, 1, 1, 0);
	ResetPalette(); //reset palette

	auto& cursor_tmr = p->cursor_tmr;
	auto& cursor_colpos = p->cursor_colpos;
	
	cursor_tmr += 1;
	if (cursor_tmr > 7) {
		//reset timer
		cursor_tmr = 1;
		
		// move to next color?
		cursor_colpos = cursor_colpos % Program::ui_cursor_cols_len + 1;
	}
}

void ProgramDraw::PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, bool flip_x, bool flip_y, int scale) {
	Size src_sz = src.GetSize();
	int src_cols = src_sz.cx / 8;
	ASSERT(src_sz.cx % 8 == 0);
	int row = n / src_cols;
	int col = n % src_cols;
	Point tl(col * 8, row * 8);
	int w = 8;
	int h = 8;
	Rect r = RectC(tl.x, tl.y, w, h);
	ASSERT(tl.x < src_sz.cx && tl.y < src_sz.cy);
	d.DrawImage(x, y, src, r);
}

void ProgramDraw::SetTransCol(int transcol) { //, enabled)
	/*
	// set transparency for (specific col
	palt(0, false);
	palt(transcol, true);
	*/
}

void ProgramDraw::PaintSprite(Draw& d, const Image& src, PaletteImage n, int x, int y, int w, int h, bool transcol, bool flip_x, bool flip_y, int scale) {
	Size src_sz = src.GetSize();
	int src_cols = src_sz.cx / 8;
	ASSERT(src_sz.cx % 8 == 0);
	int row = n / src_cols;
	int col = n % src_cols;
	Point tl(col * 8, row * 8);
	int sw = w * 8;
	int sh = h * 8;
	Rect r = RectC(tl.x, tl.y, sw, sh);
	ASSERT(tl.x < src_sz.cx && tl.y < src_sz.cy);
	
	// switch transparency
	SetTransCol(transcol); //, true)
	
	// draw zoomed sprite
	//https://www.lexaloffle.com/bbs/?tid=2429
	int sx = 8 * (n % 16);
	int sy = 8 * n / 16;
	int dz = scale ? scale : 1;
	int dw = sw * dz;
	int dh = sh * dz;
	
	
	d.DrawImage(x, y, dw, dh, src, r);
	
	//sspr(sx, sy, sw, sh, x, stage_top + y, dw, dh, flip_x, flip_y);
	
	// first scale, bottom-anchored
//sspr(sx, sy, sw, sh, x, stage_top + y +(sh-dh), dw, dh, flip_x, flip_y)

	//spr(n, x, stage_top + y, w, h, flip_x, flip_y) // orig method (pre-scale)
	
	//pal() // don't) {, affects lighting!
	
}

void ProgramDraw::PaintMap(Draw& d, int x, int y, int dst_x, int dst_y, int w, int h) {
	const uint16* m = map.Begin();
	int img_w = map_sz.cx;
	int img_h = map_sz.cy;
	
	int write_w = w >= 0 ? min(img_w, w) : img_w;
	int write_h = h >= 0 ? min(img_h, h) : img_h;
	
	int tiles_w = gfx.GetWidth() / 8;
	
	for (int y0 = y, y1 = 0; y0 < write_h; y0++, y1++) {
		const uint16* row = m + y0 * img_w;
		const uint16* it = row + x;
		for (int x0 = x, x1 = 0; x0 < write_w; x0++, x1++) {
			uint16 tile = *it++;
			int tile_x = tile % tiles_w;
			int tile_y = tile / tiles_w;
			int src_x = tile_x * 8;
			int src_y = tile_y * 8;
			Rect src = RectC(src_x, src_y, 8, 8);
			int x2 = dst_x + x1 * 8;
			int y2 = dst_y + y1 * 8;
			d.DrawImage(x2, y2, gfx, src);
		}
	}
}

void ProgramDraw::PaintObject(Draw& d, SObj& obj) {
	int sprnum = 0;
	
	// replace colors?
	ReplaceColors(obj);
	               
	// check for (custom draw
	if (obj("draw")) {
		TODO //obj.draw(obj);
	}
	
	else {
		SObj anim = obj("curr_anim");
		if (anim) {
			// update animation state
			Animate(obj);
			// choose walk anim frame
			int pos = obj("anim_pos", 1);
			sprnum = anim[pos];
		}
		// allow for (repeating
		int c = (int)obj("repeat_x", 1) - 1;
		for (int i = 0; i < c; i++) {
			// draw object (in its state!)
			SObj state = obj("state");
			if (state) {
				String s = state;
				TODO;
				//sprnum = state[State(obj)];
			}
			else if (sprnum == 0) {
				TODO
				//sprnum = obj[State(obj)];
			}
			int x = obj("x", 0);
			int y = obj("y", 0);
			int w = obj("w", 1);
			int h = obj("h", 1);
			int flip_x = obj("flip_x", 0);
			int trans_col = obj("trans_col", 0);
			double scale = obj("scale", 0.0);
			x = x + (h * (w * 8));
			PaintSprite(d, gfx, sprnum, x, y, w, h, trans_col, flip_x, 0, scale);
		}
	}
     
	// debug
	//pset(obj.x, obj.y + stage_top, 8)
     
	//reset palette
	ResetPalette();
	
 }


void ProgramDraw::Animate(SObj& obj) {
	TODO
	
	// animate the object
	// (update frames, looping as req)
	/*obj.tmr += 1;
	if (obj.tmr > obj.frame_delay) {
		obj.tmr = 1;
		obj.anim_pos = obj.anim_pos % #obj.curr_anim + 1;
	}*/
}

// draw actor(s)
void ProgramDraw::PaintActor(Draw& d, SObj& actor) {
	
	HiValue data = actor["data"];
	HiValue curr_anim = data["curr_anim"];
	FaceDir dirnum = Program::GetFaceDir(data);
	int sprnum;
	int moving = data["moving"];
	if (curr_anim.IsArray() && moving) {
		// update animation state
		Animate(actor);
		
		// choose walk anim frame
		int i = data["anim_pos"];
		sprnum = curr_anim[i];
	}
	else if (curr_anim) {
		sprnum = curr_anim;
	}
	else {
		// idle
		HiValue idle = data["idle"];
		//DUMP(data);
		ASSERT(idle);
		if (!idle) return;
		sprnum = idle[dirnum];
	}
	
	// replace colors?
	ReplaceColors(actor);
	
	// auto-scaling for (depth?
	HiValue adata = actor["data"];
	HiValue rdata = p->room_curr["data"];
	//DUMP(rdata);
	HiValue rc_autodepth_pos = rdata("autodepth_pos");
	HiValue rc_autodepth_scale = rdata("autodepth_scale");
	double pos0 = rc_autodepth_pos(0, 0);
	double pos1 = rc_autodepth_pos(1, canvas_sz.cx);
	double pos2 = rc_autodepth_pos(2, 0);
	double scale0 = rc_autodepth_scale(0, 0);
	double scale1 = rc_autodepth_scale(1, 1);
	double scale2 = rc_autodepth_scale(2, 0);
	double actor_y = adata("y", 0);
	double factor = (actor_y - pos0) / (pos1 - pos0);
	factor = scale0 + (scale1 - scale0) * factor;
	adata.MapSet("auto_scale", Mid(scale0, factor, scale1));
	
	// apply "zoom" to autoscale (e.g. camera further away)
	//auto_scale *= (room_curr.scale || 1)
	
	
	// calc scaling offset (to align to bottom-centered)
	HiValue a_scale = adata("scale");
	HiValue a_auto_scale = adata("auto_scale");
	ASSERT(a_scale || a_auto_scale);
	if (!a_scale && !a_auto_scale)
		return;
	double scale = a_scale ? a_scale : a_auto_scale;
	int a_w = adata("w", 0);
	int a_h = adata("h", 0);
	int a_offset_x = adata("offset_x", 0);
	int a_offset_y = adata("offset_y", 0);
	int a_trans_col = adata("trans_col", 0);
	int a_flip = adata("flip", 0);
	double scale_height = 8 * a_h;
	double scale_width = 8 * a_w;
	double scaleoffset_y = scale_height - (scale_height * scale);
	double scaleoffset_x = scale_width - (scale_width * scale);
	double draw_x = a_offset_x + floor(scaleoffset_x / 2);
	double draw_y = a_offset_y + scaleoffset_y;
	
	PaintSprite(
			d,
			gfx,
			sprnum,
			draw_x,
			draw_y,
			a_w ,
			a_h,
			a_trans_col,
			a_flip,
			false,
			scale);
    
    
	// talking overlay
	SObj talking_actor = p->talking_actor;
	if (talking_actor && talking_actor == actor && talking_actor("talk")) {
		int talk_tmr = adata("talk_tmr", 0);
		if (talk_tmr < 7) {
			// note: scaling from top-left
			HiValue talk = adata("talk");
			int trans_col = adata("trans_col", 0);
			int flip = adata("flip", 0);
			PaintSprite(
					d,
					gfx,
					talk("dirnum",0),
					draw_x + (double)(talk(4, 0)),
					draw_y + floor((double)(talk(5, 8)) * scale),
					talk(6, 1),
					talk(7, 1),
					trans_col,
					flip,
					false,
					scale);
		}
		adata.MapSet("talk_tmr", talk_tmr % 14 + 1);
	}
	
	// debug
	// if (show_debuginfo {
		// pset(adata.x, adata.y + stage_top, 8)
		// pset(adata.offset_x, adata.offset_y+stage_top, 11)
	// }

	//reset palette
	ResetPalette();
	
}


void ProgramDraw::PaintCommand(Draw& d) {

	// draw current command
	PaletteColor cmd_col = p->verb_maincol;
	SObj verb_curr_ref = p->verb_curr;
	String command = p->GetVerbString(verb_curr_ref);
	bool executing_cmd = p->executing_cmd;
	SObj* noun1_curr = p->noun1_curr;
	SObj* noun2_curr = p->noun2_curr;
	SObj hover_curr_object = p->hover_curr_object;
	int stage_top = p->stage_top;
	
	
	if (noun1_curr) {
		command << " " << noun1_curr->MapGet("name");
		if (verb_curr_ref == p->V_USE && (!executing_cmd || noun2_curr)) {
			command << " with";
		}
		else
			if (verb_curr_ref == p->V_GIVE) {
				command << " to";
			}
	}
	if (noun2_curr) {
		command << " " << noun2_curr->MapGet("name");
	}
	else if (hover_curr_object) {
		//DUMP(hover_curr_object);
		String name = hover_curr_object.MapGet("name");
		
		if (!name.IsEmpty()
			// don't show use object with itself!
			&& (!noun1_curr || (*noun1_curr != hover_curr_object))
			// || walk-to objs in inventory!
			// && ( not hover_curr_object.owner or
			//				or verb_curr_ref != GetVerb(verb_default)[2] )
			// || when already executing!
			&& !executing_cmd) {
			// default to look-at for (inventory items
			TODO // owner?
			/*if (hover_curr_object.owner && verb_curr_ref == GetVerb(verb_default)[2]) {
				command = "look-at";
			}*/
			command << " " << name;
		}
	}
	p->cmd_curr = command;
	
	if (executing_cmd) {
		// highlight active command
		command = p->cmd_curr;
		cmd_col = p->verb_hovcol;
	}
	
	int x = (int)(63.5 - command.GetCount()*2);
	int y = stage_top + 66;
	PaintLog(d, ToLower(command), x, y, cmd_col);
	
}

void ProgramDraw::ReplaceColors(const SObj& obj) {
	if (!obj.IsMap()) return;
	
	HiValue col_replace = obj.MapGet("col_replace");
	HiValue lighting = obj.MapGet("lighting");
	
	// replace colors (where defined)
	if (col_replace.IsArray()) {
		ASSERT(col_replace.GetArray().GetCount() == 2);
		int a = col_replace.ArrayGet(0).GetInt();
		int b = col_replace.ArrayGet(1).GetInt();
		SetPalette(a, b);
	}
	
	// also apply brightness (default to room-level, if (not set)
	if (lighting.IsInt()) {
		int a = lighting.GetInt();
		FadePalette(a);
	}
	else {
		HiValue in_room = obj.MapGet("in_room");
		if (in_room.IsMap()) {
			HiValue lighting = in_room.MapGet("lighting");
			if (lighting.IsInt()) {
				int a = lighting.GetInt();
				FadePalette(a);
			}
		}
	}
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

void ProgramDraw::FadePalette(float perc) {
	if (perc)
		perc = 1 - perc;
	
	int p = (int)(min(max(0.f, perc), 1.f) * 100.f);
	int dpal[15] = {
		0, 1, 1,
		2, 1, 13,
		6, 4, 4,
		9, 3, 13,
		1, 13, 14
	};
	
	for (int j = 0; j < 15; j++) {
		int col = j;
		int kmax = (p + ((j+1) * 1.46)) / 22;
		for (int k = 1; k <= kmax; k++) {
			ASSERT(col >= 0 && col < PALETTE_SIZE);
			col = dpal[col];
		}
		SetPalette(j, col);
	}
}

void ProgramDraw::MouseMove(Point p, dword keyflags) {
	if (this->p) {
		this->p->cursor_x = p.x * size_mul;
		this->p->cursor_y = p.y * size_mul;
	}
}

bool ProgramDraw::Key(dword key, int count) {
	
	
	return false;
}


}

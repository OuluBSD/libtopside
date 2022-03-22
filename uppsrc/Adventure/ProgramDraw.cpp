#include "Adventure.h"

namespace Adventure {



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
	this->img_draw = &d;
	size_mul = (double)canvas_sz.cx / (double)tgt_sz.cx;
	
	int cam_x = p->cam.x;
	int cam_shake_x = p->cam_shake_x;
	int cam_shake_y = p->cam_shake_y;
	int fade_iris = p->fade_iris;
	int stage_top = p->stage_top;
	const auto& dialog_curr = p->dialog_curr;
	int& cutscene_cooloff = p->cutscene_cooloff;
	const auto& cutscene_curr = p->cutscene_curr;
	
	double dt = frame_ts.Seconds();
	frame_ts.Reset();
	
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
	PaintTalking(d, dt);
	
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
			? cutscene_curr->user_flags == 2 // quick-cut
			// and not just left a cutscene
			: cutscene_cooloff == 0) {
			PaintUI(d);
		}
		
		if (!cutscene_curr)
			PaintCursor(d);
		
	}
	
	p->ctx.p.Paint(d);
	
	Image img = d;
	img = RescaleFilter(img, tgt_sz, FILTER_NEAREST);
	w.DrawImage(0,0, img);
	
	this->img_draw = 0;
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
			HiValue map = room_curr("map");
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
					SObj states = obj("states");
					SObj state = obj("state");
					SObj sdata = obj.MapGet(state);
					SObj dependent_on = obj("dependent_on");
					SObj owner = obj("owner");
					SObj draw = obj("draw");
					SObj curr_anim = obj("curr_anim");
					
					if (states	  // object has a state?
						or (state
							and sdata
							and sdata.GetInt() > 0)
						and (not dependent_on // object has a valid dependent state?
							or dependent_on("state") == obj("dependent_on_state"))
						and not owner // object is not "owned"
						or draw
                        or curr_anim) {
						if (states // object has a state?
							or (state
								and sdata
								and sdata.GetInt() > 0)
							and (not dependent_on // object has a valid dependent state?
								or dependent_on("state") == obj("dependent_on_state"))
							and not owner // object is not "owned"
							or draw) {
							// something to draw
							PaintObject(d, obj);
						}
                    }
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


void ProgramDraw::PaintTalking(Draw& d, double dt) {
	// alignment
	//   0 = no align
	//   1 = center
	if (p->talking_curr.GetCount()) {
		TalkingState& t = p->talking_curr[0];
		
		int line_offset_y = 0;
		for (const String& l : t.msg_lines) {
			int line_offset_x = 0;
			// center-align line
			if (t.align == 1) {
				int len = l.GetCount();
				line_offset_x = ((t.char_width * 4) - (len * 4)) / 2;
			}
			OutlineText(
				d,
				l,
				t.x + line_offset_x,
				t.y + line_offset_y,
				t.col,
				0,
				t.use_caps,
				t.big_font);
			line_offset_y += t.big_font ? 12 : 6;
		}
		
		// update message lifespan
		t.time_left -= dt;
		
		// remove text & reset actor's talk anim
		if (t.time_left <= 0) {
			if (p->talking_curr.GetCount() > 1)
				p->talking_curr.Remove(0);
			else
				p->StopTalking();
		}
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
		SObj o;
		o.Set("x", xpos);
		o.Set("y", ypos);
		o.Set("classes", ea);
		p->RecalculateBounds(o, namelen*4, 5, 0, 0);
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
		HiValue inventory = selected_actor["inventory"];
		if (!inventory.IsArray()) {DUMP(inventory);}
		ASSERT(inventory.IsArray());
		
		int inv_arr_len = inventory.GetArray().GetCount();
		
		// draw inventory
		int xpos = 86;
		int ypos = 76;
		
		// determine the inventory "window"
		int inv_pos = selected_actor("inv_pos").GetInt();
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
				obj.Set("x", xpos);
				obj.Set("y", ypos);
				
				// draw object/sprite
				PaintObject(d, obj);
				
				// re-calculate bounds (as pos may have changed)
				int w = obj["w"];
				int h = obj["h"];
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
			int spr = arrow["spr"];
			int x = arrow["x"];
			int y = arrow["y"];
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

void ProgramDraw::SetTransCol(int transcol, bool enabled) {
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
	SetTransCol(transcol, true);
	
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
	const uint16* m = p->map.Begin();
	int img_w = p->map_sz.cx;
	int img_h = p->map_sz.cy;
	
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

void ProgramDraw::PaintObject(Draw& d, SObj o) {
	auto& global = p->ctx.global;
	int sprnum = 0;
	
	// replace colors?
	ReplaceColors(o);
	               
	// check for (custom draw
	HiValue draw = o("draw");
	if (draw && draw.IsLambda()) {
		try {
			Vector<HiValue> arg;
			arg << o;
			Execute(p->ctx.global, 0, draw, arg, INT_MAX);
		}
		catch(CParser::Error e) {
			LOG("ProgramDraw::PaintObject: error: " << e << "\n");
			ASSERT(0);
		}
	}
	
	else {
		SObj anim = o("curr_anim");
		if (anim) {
			// update animation state
			Animate(o);
			// choose walk anim frame
			int pos = o("anim_pos", 1);
			sprnum = anim[pos];
		}
		// allow for (repeating
		int c = (int)o("repeat_x", 1) - 1;
		for (int i = 0; i < c; i++) {
			// draw object (in its state!)
			SObj state = o("state");
			if (state) {
				if (state.IsArray()) {
					String s = state;
					state = o(s);
					sprnum = state.GetInt();
				}
				else {
					sprnum = state.GetInt();
				}
			}
			else if (sprnum == 0) {
				TODO
				//sprnum = o[State(o)];
			}
			int x = o("x", 0);
			int y = o("y", 0);
			int w = o("w", 1);
			int h = o("h", 1);
			int flip_x = o("flip_x", 0);
			int trans_col = o("trans_col", 0);
			double scale = o("scale", 0.0);
			x = x + (h * (w * 8));
			PaintSprite(d, gfx, sprnum, x, y, w, h, trans_col, flip_x, 0, scale);
		}
	}
     
	// debug
	//pset(o.x, o.y + stage_top, 8)
     
	//reset palette
	ResetPalette();
	
 }


void ProgramDraw::Animate(SObj obj) {
	// animate the object
	// (update frames, looping as req)
	int tmr = obj("tmr");
	int frame_delay = obj("frame_delay");
	tmr += 1;
	if (tmr > frame_delay) {
		tmr = 1;
		HiValue curr_anim = obj("curr_anim");
		int anim_pos = obj("anim_pos").GetInt();
		if (curr_anim.IsArray()) {
			int anim_len = curr_anim.GetArray().GetCount();
			obj.Set("anim_pos", anim_pos % anim_len + 1);
		}
	}
	obj.Set("tmr", tmr);
}

void ProgramDraw::GetPaletteImage(const Vector<byte>& src, Size src_sz, Image& out) {
	ImageBuffer ib(src_sz);
	RGBA* it = ib.Begin();
	RGBA* end = ib.End();
	const byte* sit = src.Begin();
	
	while (it != end) {
		byte n = *sit;
		RGBA r;
		if (n > 0)
			r = GetPaletteColor(n);
		else {
			r.r = 0;
			r.g = 0;
			r.b = 0;
			r.a = 0;
		}
		*it = r;
		it++;
		sit++;
	}
	
	out = ib;
}

// draw actor(s)
void ProgramDraw::PaintActor(Draw& d, SObj a) {
	HiValue r = p->room_curr;
	HiValue curr_anim = a["curr_anim"];
	FaceDir dirnum = Program::GetFaceDir(a);
	int sprnum = 0;
	int moving = a["moving"];
	if (curr_anim.IsArray() && moving) {
		// update animation state
		Animate(a);
		
		// choose walk anim frame
		int i = a["anim_pos"];
		const auto& curr_anim_arr = curr_anim.GetArray();
		if (!curr_anim_arr.IsEmpty()) {
			i = i % curr_anim_arr.GetCount();
			sprnum = curr_anim[i];
		}
	}
	else if (curr_anim) {
		sprnum = curr_anim;
	}
	else {
		// idle
		HiValue idle = a["idle"];
		//DUMP(a);
		ASSERT(idle);
		if (!idle) return;
		sprnum = idle[dirnum];
	}
	
	// replace colors?
	ReplaceColors(a);
	
	// auto-scaling for (depth?
	//DUMP(r);
	HiValue rc_autodepth_pos = r("autodepth_pos");
	HiValue rc_autodepth_scale = r("autodepth_scale");
	double pos0 = rc_autodepth_pos(0, 0);
	double pos1 = rc_autodepth_pos(1, canvas_sz.cx);
	double pos2 = rc_autodepth_pos(2, 0);
	double scale0 = rc_autodepth_scale(0, 0);
	double scale1 = rc_autodepth_scale(1, 1);
	double scale2 = rc_autodepth_scale(2, 0);
	double actor_y = a("y", 0);
	double factor = (actor_y - pos0) / (pos1 - pos0);
	factor = scale0 + (scale1 - scale0) * factor;
	a.Set("auto_scale", Mid(scale0, factor, scale1));
	
	// apply "zoom" to autoscale (e.g. camera further away)
	//auto_scale *= (r.scale || 1)
	
	
	// calc scaling offset (to align to bottom-centered)
	HiValue a_scale = a("scale");
	HiValue a_auto_scale = a("auto_scale");
	ASSERT(a_scale || a_auto_scale);
	if (!a_scale && !a_auto_scale)
		return;
	double scale = a_scale ? a_scale : a_auto_scale;
	int a_w = a("w", 0);
	int a_h = a("h", 0);
	int a_offset_x = a("offset_x", 0);
	int a_offset_y = a("offset_y", 0);
	int a_trans_col = a("trans_col", 0);
	int a_flip = a("flip", 0);
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
	SObj t = p->talking_actor;
	if (t && t == a && t("talk")) {
		int talk_tmr = a("talk_tmr", 0);
		if (talk_tmr < 7) {
			// note: scaling from top-left
			HiValue talk = a("talk");
			int trans_col = a("trans_col", 0);
			int flip = a("flip", 0);
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
		a.Set("talk_tmr", talk_tmr % 14 + 1);
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
	SObj noun1_curr = p->noun1_curr;
	SObj noun2_curr = p->noun2_curr;
	SObj hover_curr_object = p->hover_curr_object;
	int stage_top = p->stage_top;
	
	
	if (noun1_curr) {
		DUMP(noun1_curr);
		command << " " << noun1_curr["name"];
		if (verb_curr_ref == p->V_USE && (!executing_cmd || noun2_curr)) {
			command << " with";
		}
		else
			if (verb_curr_ref == p->V_GIVE) {
				command << " to";
			}
	}
	if (noun2_curr) {
		command << " " << noun2_curr["name"];
	}
	else if (hover_curr_object) {
		//DUMP(hover_curr_object);
		String name = hover_curr_object["name"];
		
		if (!name.IsEmpty()
			// don't show use object with itself!
			&& (!noun1_curr || noun1_curr != hover_curr_object)
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

void ProgramDraw::ReplaceColors(SObj o) {
	if (!o.IsMap()) return;
	
	HiValue col_replace = o("col_replace");
	HiValue lighting = o("lighting");
	
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
		HiValue in_room = o("in_room");
		if (in_room.IsMap()) {
			HiValue lighting = in_room("lighting");
			if (lighting) {
				int a = lighting.GetInt();
				FadePalette(a);
			}
		}
	}
}

void ProgramDraw::OutlineText(Draw& d, String str, int x, int y, int c0, int c1, bool use_caps, bool big_font) {
	if (use_caps)
		str = ToUpper(str);
	
	Color clr = GetPaletteColor(c1);
	for (int yy = -1; yy <= 1; yy++) {
		for (int xx = -1; xx <= 1; xx += (yy == 0 ? 2 : 1)) {
			d.DrawText(x + xx, y + yy, str, clr);
		}
	}
	d.DrawText(x, y, str, clr);
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

void ProgramDraw::LeftDown(Point p, dword keyflags) {
	this->p->mouse_pressed |= MBMASK_LEFT;
}

void ProgramDraw::LeftUp(Point p, dword keyflags) {
	this->p->mouse_pressed &= ~(dword)MBMASK_LEFT;
}

void ProgramDraw::RightDouble(Point p, dword keyflags) {
	this->p->mouse_pressed |= MBMASK_RIGHT;
}

void ProgramDraw::RightUp(Point p, dword keyflags) {
	this->p->mouse_pressed &= ~(dword)MBMASK_RIGHT;
}


}

#include "CtrlLib.h"



#define STB_TEXTEDIT_IMPLEMENTATION
#include <ports/stb/stb_textedit.h>


NAMESPACE_UPP


TextCtrl::TextCtrl(bool multiline) {
	stb_textedit_initialize_state(&state, !multiline);
	fnt = StdFont(lineh);
}

void TextCtrl::LayoutRow(StbTexteditRow* r, int n) {
	memset(r, 0, sizeof(*r));
	
	if (n < 0 || n >= rows.GetCount())
		return;
	
	r->x0 = rows[n];
	if (n + 1 < rows.GetCount())
		r->x1 = rows[n + 1];
	else
		r->x1 = data.GetCount();
	
	r->baseline_y_delta = r->x0 * lineh;
	r->ymin = r->baseline_y_delta;
	r->ymax = r->baseline_y_delta + lineh;
	r->num_chars = r->x1 - r->x0;
}

float TextCtrl::GetWidth(int n, int i) {
	if (n < 0 || n >= rows.GetCount())
		return 0;
	int cursor = rows[n];
	if (cursor == GetCount())
		return 0;
	
	String s = ToString(data.Mid(cursor, 1));
	Size sz = GetTextSize(s, fnt);
	
	return sz.cx;
}

int TextCtrl::KeyToText(int k) {
	if (k >= 32 && k < 127)
		return k;
	return -1;
}

void TextCtrl::Remove(int i, int n) {
	data.Remove(i, n);
	RefreshRowBegins();
	Refresh();
}

bool TextCtrl::Insert(int i, const wchar_t* c, int n) {
	if (data.Insert(i, c, n)) {
		RefreshRowBegins();
		Refresh();
		return true;
	}
	return false;
}

void TextCtrl::RefreshRowBegins() {
	const wchar_t* it  = data.Begin();
	const wchar_t* end = data.End();
	
	rows.SetCount(0);
	rows.Add(0);
	int cursor = 0;
	while (it != end) {
		if (*it == '\n' && it + 1 != end)
			rows.Add(cursor + 1);
		cursor++;
		it++;
	}
}

bool TextCtrl::Intersects(int b0, int e0, int b1, int e1) {
	return
		(b0 <= b1 && b1 <= e0) ||
		(b0 <= e1 && e1 <= e0);
}

void TextCtrl::Paint(Draw& d) {
	Rect r = GetContentSize();
	
	Color bg = White();
	Color fg = Black();
	Color sel_bg = Color(28, 42, 150);
	Color sel_fg = White();
	
	d.DrawRect(r, bg);
	
	int sel_start = min(state.select_start, state.select_end);
	int sel_end = max(state.select_start, state.select_end);
	bool have_sel = sel_start < sel_end;
	
	if (data.GetCount()) {
		for(int row = 0;; row++) {
			StbTexteditRow r;
			LayoutRow(&r, row);
			
			int y = r.baseline_y_delta;
			int count = r.x1 - r.x0;
			String line = ToString(data.Mid(r.x0, count));
			
			/*if (sel_start != sel_end) {
				DUMP(sel_start);
				DUMP(sel_end);
				DUMP(r.x0);
				DUMP(r.x1);
			}*/
			if (have_sel && Intersects(sel_start, sel_end, r.x0, r.x1)) {
				int lc = max<int>(sel_start, r.x0);
				int rc = min<int>(sel_end, r.x1);
				int ld = lc - r.x0;
				int cd = rc - lc;
				int rd = r.x1 - rc;
				
				String lp = line.Mid(r.x0, ld);
				String cp = line.Mid(lc, cd);
				String rp = line.Mid(rc, rd);
				Size lp_sz = GetTextSize(lp, fnt);
				Size cp_sz = GetTextSize(cp, fnt);
				Size rp_sz = GetTextSize(rp, fnt);
				
				int lx = 0;
				int cx = lx + lp_sz.cx;
				int rx = cx + cp_sz.cx;
				Rect cr = RectC(cx, y, cp_sz.cx, cp_sz.cy);
				d.DrawRect(cr, sel_bg);
				
				d.DrawText(lx, y, lp, fnt, fg);
				d.DrawText(cx, y, cp, fnt, sel_fg);
				d.DrawText(rx, y, rp, fnt, fg);
			}
			else {
				//const wchar_t* it  = data.Begin() + (int)r.x0;
				//const wchar_t* end = data.Begin() + (int)r.x1;
				if (count > 0) {
					d.DrawText(0, y, line, fnt, fg);
				}
			}
			
			if (r.x1 >= data.GetCount())
				break;
		}
	}
	/*if (HasMouse())
		d.DrawRect(r, Color(128, 255, 128));
	
	d.DrawPolyline(v, 15, Color(128, 128, 255));
	
	
	d.DrawRect(100, 100, 100, 100, c);
	
	d.DrawLine(r.left, r.top, r.right, r.bottom, 1, Black());*/
}

void TextCtrl::LeftDown(Point p, dword keyflags) {
	//c = RandomColor(0, 256);
	SetFocus();
	
	Refresh();
}

bool TextCtrl::Key(dword key, int count) {
	TODO
	//Refresh();
	
	/*int dx = 0, dy = 0;
	if (key == K_LEFT)
		dx -= 10;
	else if (key == K_RIGHT)
		dx += 10;
	else if (key == K_UP)
		dy -= 10;
	else if (key == K_DOWN)
		dy += 10;
	
	Geom2DComponent* win = GetWindow();
	Rect r(win->GetFrameRect());
	
	r.left += dx;
	r.right += dx;
	r.top += dy;
	r.bottom += dy;
	
	win->SetFrameRect(r);*/
	
	stb_textedit_key(this, &state, key);
	RefreshRowBegins();
	
	Refresh();
	
	return true;
}

void TextCtrl::MouseMove(Point p, dword keyflags) {
	TODO
	/*Pointf& pt = v[3];
	pt.x = p.x;
	pt.y = p.y;*/
}

void TextCtrl::MouseWheel(Point p, int zdelta, dword keyflags) {
	TODO
	/*
	int dy = 0;
	if (zdelta > 0)
		dy -= 10;
	else
		dy += 10;
	
	Rect ownr = GetFrameRect();
	
	Geom2DComponent* win = GetWindow();
	Rect r(win->GetFrameRect());
	
	r.top += dy;
	r.bottom += dy;
	
	win->SetFrameRect(r);
	*/
}

void TextCtrl::SetData(Value v) {
	TODO
}

void TextCtrl::SetFont(Font fnt) {
	TODO
}

Value TextCtrl::GetData() const {
	TODO
}


END_UPP_NAMESPACE

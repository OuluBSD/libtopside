#if 0
#include "Internal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN


SubMenuFrame::SubMenuFrame(Windows* wins) : wins(wins) {
	height = 20;
	shift = 0;
	arrow_border = 12;
	
	left_arrow = false;
	right_arrow = false;
	
	clr_bg = GrayColor(255);
	clr_tr = GrayColor(128+64);
}

void SubMenuFrame::Close() {wins->QueueCloseWindow(clicked_id);}
void SubMenuFrame::Maximize() {wins->FocusWindowPos(clicked_id); wins->MaximizeWindow(clicked_id);}
void SubMenuFrame::Minimize() {wins->MinimizeWindow(clicked_id);}
void SubMenuFrame::CloseOthers() {wins->CloseOthers(clicked_id);}

void SubMenuFrame::Paint(Draw& id) {
	Size menu_sz(GetContentSize());
	
	id.DrawRect(0, 0, menu_sz.cx, menu_sz.cy, clr_bg);
	id.DrawLine(0, 0, menu_sz.cx-1, 0, 1, clr_tr);
	
	Font fnt = StdFont(15);
	
	int count = wins->GetCount();
	id_pos.SetCount(count);
	int x = -shift;
	int active_pos = wins->GetActiveWindowPos();
	
	
	
	bool draw_right_arrow = false;
	for(int i = 0; i < count; i++) {
		
		x += 5;
		if (i) {
			id.DrawLine(x, 3, x, height-2, 1, GrayColor());
			x += 5;
		}
		Geom2DComponent& sub = (*wins)[i];
		
		String title = sub.GetTitle();
		bool active = active_pos == i;
		Size sz = GetTextSize(title, fnt);
		
		if (x + sz.cx >= menu_sz.cx)
			draw_right_arrow = true;
		
		if (active)
			id.DrawRect(x-5+1, 0, sz.cx+10-1, sz.cy, GrayColor(128+64+32));
		
		id.DrawText(x, 0, title, fnt, Black());
		
		x += sz.cx;
		
		id_pos[i] = x;
	}
	
	// The last line at the right end
	if (count)
		id.DrawLine(x+5, 3, x+5, height-2, 1, GrayColor());
	
	// Draw shift arrows
	left_arrow = false;
	right_arrow = false;
	if (shift) {
		id.DrawRect(0, 0, arrow_border, menu_sz.cy, clr_bg);
		id.DrawText(0, 0, "<", fnt, Black());
		left_arrow = true;
	}
	if (draw_right_arrow) {
		id.DrawRect(menu_sz.cx - arrow_border, 0, arrow_border, menu_sz.cy, clr_bg);
		id.DrawText(menu_sz.cx - arrow_border, 0, ">", fnt, Black());
		right_arrow = true;
	}
	
}




void SubMenuFrame::LeftDown(Point p, dword keyflags) {
	int limit = GetFrameSize().cx - arrow_border;
	
	if (left_arrow && p.x < arrow_border) {
		shift -= 20;
		if (shift <= 0) shift = 0;
		Refresh();
		return;
	}
	else if (right_arrow && p.x >= limit) {
		shift += 20;
		Refresh();
		return;
	}
	
	int id = -1;
	for(int i = 0; i < id_pos.GetCount(); i++) {
		if (p.x < id_pos[i]) {id = i; break;}
	}
	if (id < 0) return;
	
	wins->FocusWindowPos(id);
}

void SubMenuFrame::RightDown(Point p, dword keyflags) {
	clicked_id = -1;
	for(int i = 0; i < id_pos.GetCount(); i++) {
		if (p.x < id_pos[i]) {clicked_id = i; break;}
	}
	if (clicked_id >= 0)
		clicked_id = wins->GetPosId(clicked_id);
	MenuBar::Execute(THISBACK(LocalMenu));
}

void SubMenuFrame::MouseWheel(Point p, int zdelta, dword keyflags) {
	if (right_arrow && zdelta > 0) {
		shift += zdelta / 40 * 10;
		Refresh();
	}
	else if (left_arrow && zdelta < 0) {
		shift += zdelta / 40 * 10;
		if (shift <= 0) shift = 0;
		Refresh();
	}
}

void SubMenuFrame::LocalMenu(Bar& bar) {
	if (clicked_id >= 0) {
		bar.Add("Close", THISBACK(Close));
		bar.Separator();
		bar.Add("Maximize / Restore", THISBACK(Maximize));
		bar.Add("Minimize", THISBACK(Minimize));
		bar.Separator();
		bar.Add("Close All", callback(wins, &Windows::CloseAll));
		bar.Add("Close Others", THISBACK(CloseOthers));
	}
	bar.Add("Tile Windows", callback(wins, &Windows::OrderTileWindows));
	
}


NAMESPACE_ECS_END

#endif
#endif

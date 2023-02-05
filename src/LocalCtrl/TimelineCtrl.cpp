#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN


TimelineRowCtrl::TimelineRowCtrl() {
	WantFocus();
	
}

void TimelineRowCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	
	bool has_focus = HasFocus();
	d.DrawRect(sz, has_focus ? owner->bg_focused : owner->bg);
	
	Font fnt = SansSerif(sz.cy-6);
	fnt.Bold();
	d.DrawText(2, 2, title, fnt, owner->text);
	
	int col = owner->GetColumnWidth();
	int x = owner->title_tab_w + 1;
	int kp_i = owner->hsb / col;
	
	int* kp_iter = keypoints.Begin();
	int* kp_end = keypoints.End();
	int selected_i = owner->selected_col;
	
	for(; kp_i < owner->length; kp_i++) {
		bool first_in_second = (kp_i % owner->kps) == 0;
		
		bool is_keypoint = false;
		if (kp_iter != kp_end) {
			while (*kp_iter < kp_i && kp_iter != kp_end)
				kp_iter++;
			if (kp_iter != kp_end && *kp_iter == kp_i)
				is_keypoint = true;
		}
		
		if (/*has_focus &&*/ selected_i == kp_i)
			d.DrawRect(x, 0, col, sz.cy, owner->bg_focused_keypoint);
		
		Color line_clr = first_in_second ?
			owner->kp_second_accent :
			owner->kp_col_accent;
			
		int line_width = first_in_second ? 2 : 1;
		d.DrawLine(x, 0, x, sz.cy-1, line_width, line_clr);
		
		int pad = 2;
		int rad = col - pad * 2;
		d.DrawEllipse(x + pad, pad, rad, rad, Black());
		
		if (!is_keypoint) {
			pad = 3;
			rad = col - pad * 2;
			d.DrawEllipse(x + pad, pad, rad, rad, White());
		}
		
		x += col;
	}
	
	d.DrawLine(0, sz.cy-1, sz.cx-1, sz.cy-1, 1, owner->accent);
	d.DrawLine(owner->title_tab_w, 0, owner->title_tab_w, sz.cy-1, 1, owner->accent);
}

bool TimelineRowCtrl::Key(dword key, int) {
	
	return true;
}

void TimelineRowCtrl::LeftDown(Point p, dword keyflags) {
	int col = owner->GetColumnWidth();
	int x = p.x - owner->title_tab_w - 1;
	int kp_i = x / col;
	
	bool kp_changes = false;
	if (kp_i >= 0 && kp_i < owner->length && kp_i != owner->selected_col) {
		kp_changes = true;
		owner->selected_col = kp_i;
	}
	
	if (!HasFocus())
		SetFocus();
	else
		Refresh();
	
	if (kp_changes)
		owner->WhenCursor(kp_i);
	
}

void TimelineRowCtrl::RightDown(Point p, dword keyflags) {
	
}

void TimelineRowCtrl::GotFocus() {
	Refresh();
	
}

void TimelineRowCtrl::LostFocus() {
	Refresh();
	
}

void TimelineRowCtrl::SetKeypoints(const Vector<int>& keypoints) {
	this->keypoints.SetCount(keypoints.GetCount());
	if (!keypoints.IsEmpty())
		memcpy(this->keypoints.Begin(), keypoints.Begin(), sizeof(int) * keypoints.GetCount());
	Refresh();
}









TimelineCtrl::TimelineCtrl() {
	bg = Color(218, 222, 228);
	bg_focused = Color(218-64, 222-64, 228-64);
	bg_focused_keypoint = Color(218-128, 222-128, 255);
	accent = Color(82, 87, 91);
	text = Color(33, 34, 36);
	kp_second_accent = text;
	kp_col_accent = accent;
	
	AddFrame(vsb);
	AddFrame(hsb.Horz());
	
	vsb.WhenScroll = THISBACK(OnScroll);
	vsb.SetLine(GetLineHeight());
	hsb.WhenScroll = THISBACK(OnScroll);
	hsb.SetLine(GetColumnWidth());
}

void TimelineCtrl::OnScroll() {
	Refresh();
}

void TimelineCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	
	d.DrawRect(sz, bg);
	
}

void TimelineCtrl::LeftDown(Point p, dword keyflags) {
	
}

void TimelineCtrl::RightDown(Point p, dword keyflags) {
	
}

void TimelineCtrl::MouseWheel(Point p, int zdelta, dword keyflags) {
	if (keyflags & K_SHIFT)
		hsb.Wheel(zdelta);
	else
		vsb.Wheel(zdelta);
}

bool TimelineCtrl::Key(dword key, int) {
	return vsb.VertKey(key) || hsb.HorzKey(key);
}

/*TimelineRowCtrl& TimelineCtrl::GetAddRow(int id) {
	int i = rows.Find(id);
	if (i >= 0)
		return rows[i];
	
	TimelineRowCtrl& row = rows.GetAdd(id);
	row.owner = this;
	row.id = id;
	
	sb.SetTotal(rows.GetCount() * GetLineHeight());
	
	Ctrl::Add(row);
	Layout();
	
	return row;
}*/

void TimelineCtrl::SetCount(int c) {
	int old_count = rows.GetCount();
	rows.SetCount(c);
	
	for(int i = old_count; i < c; i++) {
		rows[i].owner = this;
		rows[i].id = i;
		Add(rows[i]);
	}
	
	vsb.SetTotal(rows.GetCount() * GetLineHeight());
	Layout();
}

void TimelineCtrl::SetLength(int i) {
	length = i;
	
	hsb.SetTotal(length * GetColumnWidth());
}

void TimelineCtrl::SetKeypointColumnWidth(int i) {
	kp_col = i;
	Layout();
	Refresh();
}

TimelineRowCtrl& TimelineCtrl::GetRowIndex(int i) {
	return rows[i];
}

void TimelineCtrl::Layout() {
	Size sz = GetSize();
	vsb.SetPage(sz.cy);

	int fcy = GetLineHeight();
	int i = vsb / fcy;
	int y = i * fcy - vsb;
	
	Size row_sz(sz.cx, fcy);
	for(; i < rows.GetCount(); i++) {
		TimelineRowCtrl& row = rows[i];
		
		row.SetRect(RectC(0, y, row_sz.cx, row_sz.cy));
		
		y += fcy;
	}
}


NAMESPACE_TOPSIDE_END

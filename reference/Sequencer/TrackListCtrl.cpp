#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


TrackListCtrl::TrackListCtrl() {
	WantFocus();
	
	ExprParentCtrl::Set(root);
	AddFrame(vsb);
	AddFrame(hsb);
	hsb.Horz();
	
	vsb.WhenScroll = THISBACK(Layout);
	hsb.WhenScroll = THISBACK(Layout);
}

void TrackListCtrl::Layout() {
	try {
		Session& ses = GetEditor().GetSession();
		
		Size sz = GetSize();
		
		hsb.SetLine(100);
		hsb.SetTotal(GetPxFromShift(BARSIZE * 100));
		hsb.SetPage(sz.cx);
		vsb.SetLine(3 * row_height);
		vsb.SetTotal(row_height * ses.GetTrackCount());
		vsb.SetPage(sz.cy);
		
		ExprParentCtrl::Layout();
		Refresh();
	}
	catch (Exc e) {
		
	}
}

void TrackListCtrl::MouseWheel(Point, int zdelta, dword) {
	vsb.Wheel(zdelta);
}

void TrackListCtrl::SubBar(Bar& bar) {
	bar.Add("Add track", SequencerImg::addtrack(), THISBACK(AddTrack)).Key(K_CTRL_T);
	bar.Add("Remove track", SequencerImg::removetrack(), THISBACK(RemoveTrack)).Key(K_CTRL|K_SHIFT|K_T);
}

void TrackListCtrl::AddTrack() {
	SessionEditor& e = GetEditor();
	Session& ses = e.GetSession();
	System& sys = ses.GetSystem();
	
	
	Op op;
	op.SetInt(0, OP_ADDTRACK);
	op.SetInt(1, sys.Find<SimpleOscillator>());
	
	ses.Do(op);
	
	Data();
}

void TrackListCtrl::RemoveTrack() {
	SessionEditor& e = GetEditor();
	Session& ses = e.GetSession();
	
	for(int i = 0; i < root.header.tracks.GetCount(); i++) {
		TrackHeaderCtrl& trackctrl = root.header.tracks[i];
		if (trackctrl.IsSelected()) {
			Track& track = ses.GetTrack(i);
			
			Op op;
			op.SetInt(0, OP_REMOVETRACK);
			op.SetInt(1, i);
			op.Store(track);
			ses.Do(op);
			
			Data();
		}
	}
}









TrackListExprCtrl::TrackListExprCtrl() {
	Add(list);
	Add(header);
	Add(timeline);
	Add(timectrl);
	
}

void TrackListExprCtrl::Layout() {
	Size sz(GetSize());
	header.SetRect(0, time_h, head_w, sz.cy - time_h);
	timeline.SetRect(head_w, 0, sz.cx - head_w, time_h);
	list.SetRect(head_w, time_h, sz.cx - head_w, sz.cy - time_h);
}

void TrackListExprCtrl::TimeChanges() {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	SessionEditor& se = tlc.GetEditor();
	Session& ses = se.GetSession();
	int time_cursor = ses.GetTimeCursor();
	int shift = time_cursor * BARSIZE / 4.0 / ses.GetTempo() * 60.0 / 1000;
	int px = head_w - tlc.GetScroll() + tlc.GetPxFromShift(shift);
	Size sz(GetSize());
	timectrl.SetRect(px, 0, 2, sz.cy);
	tlc.Refresh();
}






void TimelineCtrl::Paint(Draw& w) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	int scroll = tlc.GetScroll();
	Size sz(GetSize());
	
	w.DrawRect(0, 0, sz.cx, sz.cy, Color(56, 85, 150));
	
	
	int h = 20;
	
	for (int x = 0; x < sz.cx; x++) {
		int px = scroll + x;
		int shift = tlc.GetShiftFromPx(px);
		int draw_h = 0;
		if (shift % 64 == 0) {
			draw_h = 4;
		}
		else if (shift % 16 == 0) {
			draw_h = 2;
		}
		else if (shift % 4 == 0) {
			draw_h = 1;
		}
		
		if (draw_h != 0) {
			int lx = x;
			int y0 = 0;
			int y1 = draw_h * h / 5;
			w.DrawLine(lx, y0, lx, y1, 1, White);
		}
	}
}

void TimelineCtrl::LeftDown(Point p, dword keyflags) {
	SetPosition(p);
	SetCapture();
}

void TimelineCtrl::LeftUp(Point p, dword keyflags) {
	SetPosition(p);
	ReleaseCapture();
}

void TimelineCtrl::MouseMove(Point p, dword keyflags) {
	if (IsCaptured())
		SetPosition(p);
}

void TimelineCtrl::SetPosition(Point p) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	
	int scroll = tlc.GetScroll();
	//int pad_shift = TrackListExprCtrl::head_w;
	int block_shift = tlc.GetScroll();
	int x = p.x;
	int px = scroll + x;
	int shift = tlc.GetShiftFromPx(px) /*- pad_shift*/ + block_shift;
	int time = ses.GetTimeFromShift(shift);
	ses.Seek(time);
}






TrackHeaderList::TrackHeaderList() {
	
}

void TrackHeaderList::Layout() {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	SessionEditor& e = tlc.GetEditor();
	Session& ses = e.GetSession();
	int row_height = tlc.GetRowHeight();
	Size sz(GetSize());
	
	for(int i = tracks.GetCount(); i < ses.GetTrackCount(); i++) {
		Track& track = ses.GetTrack(i);
		Add(tracks.Add());
	}
	
	for(int i = tracks.GetCount() - 1; i >= ses.GetTrackCount(); i--) {
		RemoveChild(&tracks[i]);
		tracks.Remove(i);
	}
	
	for(int i = 0; i < tracks.GetCount(); i++) {
		Track& track = ses.GetTrack(i);
		TrackHeaderCtrl& hc = tracks[i];
		hc.SetId(i);
		hc.SetRect(0, i * row_height, sz.cx, row_height);
	}
	
}







TrackList::TrackList() {
	
}

void TrackList::Paint(Draw& w) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	
	int row_height = tlc.GetRowHeight();
	int scroll = tlc.GetScroll();
	Size sz(GetSize());
	
	for(int i = 0; i < ses.GetTrackCount(); i++) {
		int y = i * row_height;
		
		for(int j = 0; j < row_height; j++) {
			Color clr = GrayColor(128 + 64 + j * 32 / row_height);
			w.DrawLine(0, y, sz.cx, y, 1, clr);
			y++;
		}
	}
	
	int tracks_height = ses.GetTrackCount() * row_height;
	
	Color vline_clr;
	for (int x = 0; x < sz.cx; x++) {
		int px = scroll + x;
		int shift = tlc.GetShiftFromPx(px);
		int draw_h = 0;
		if (shift % 64 == 0) {
			draw_h = 4;
			vline_clr = GrayColor(255);
		}
		else if (shift % 16 == 0) {
			draw_h = 2;
			vline_clr = GrayColor(256-32);
		}
		/*else if (shift % 4 == 0) {
			draw_h = 1;
		}*/
		
		if (draw_h != 0) {
			int lx = x;
			int y0 = 0;
			int y1 = tracks_height;
			w.DrawLine(lx, y0, lx, y1, 1, vline_clr);
		}
	}
	
}

void TrackList::LeftDown(Point p, dword keyflags) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	
	int row_height = tlc.GetRowHeight();
	int track = p.y / row_height;
	if (track < 0 || track >= ses.GetTrackCount()) return;
	
	Track& t = ses.GetTrack(track);
	
	int snap = tlc.GetSnap();
	int px = tlc.GetScroll() + p.x;
	px -= px % snap;
	int shift = tlc.GetShiftFromPx(px);
	
	Op op;
	op.SetInt(0, OP_ADDBLOCK);
	op.SetInt(1, track);
	op.SetInt(2, shift);
	
	ses.Do(op);
	
	Layout();
}

void TrackList::Layout() {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	SessionEditor& e = tlc.GetEditor();
	Session& ses = e.GetSession();
	
	for(int i = 0; i < ses.GetTrackCount() && i < blocks.GetCount(); i++) {
		Track& track = ses.GetTrack(i);
		Array<BlockCtrl>& b = blocks[i];
		
		for(int j = b.GetCount(); j < track.GetBlockCount(); j++) {
			Add(b.Add());
		}
		
		for(int j = b.GetCount() - 1; j >= track.GetBlockCount(); j--) {
			RemoveChild(&b[j]);
			b.Remove(j);
		}
	}
	
	for(int i = blocks.GetCount(); i < ses.GetTrackCount(); i++) {
		Track& track = ses.GetTrack(i);
		Array<BlockCtrl>& b = blocks.Add();
		b.SetCount(track.GetBlockCount());
		for(int j = 0; j < b.GetCount(); j++)
			Add(b[j]);
	}
	
	for(int i = blocks.GetCount() - 1; i >= ses.GetTrackCount(); i--) {
		Array<BlockCtrl>& b = blocks[i];
		for(int j = 0; j < b.GetCount(); j++)
			RemoveChild(&b[i]);
		blocks.Remove(i);
	}
	
	Size sz(GetSize());
	int global_shift = tlc.GetScrollShift();
	int row_height = tlc.GetRowHeight();
	
	for(int i = 0; i < blocks.GetCount(); i++) {
		Track& track = ses.GetTrack(i);
		Array<BlockCtrl>& b = blocks[i];
		b.SetCount(track.GetBlockCount());
		int y = i * row_height;
		for(int j = 0; j < b.GetCount(); j++) {
			BlockCtrl& blockctrl = b[j];
			Block& block = track.GetBlock(j);
			
			blockctrl.SetId(i, j);
			
			int block_shift = block.GetShift();
			int block_size = block.GetSize();
			int screen_shift = block_shift - global_shift;
			int left = tlc.GetPxFromShift(screen_shift);
			int right = tlc.GetPxFromShift(screen_shift + block_size);
			
			blockctrl.SetRect(Rect(left, y, right, y + row_height));
		}
	}
}







TrackHeaderCtrl::TrackHeaderCtrl() {
	
}


void TrackHeaderCtrl::Paint(Draw& w) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	Track& t = ses.GetTrack(id);
	
	Size sz(GetSize());
	
	w.DrawRect(sz, Color(56, 85, 150));
	
	Font fnt = StdFont(12);
	w.DrawText(4, 4, t.GetTitle(), fnt, Black());
	w.DrawText(2, 2, t.GetTitle(), fnt, White());
}

void TrackHeaderCtrl::LeftDown(Point p, dword keyflags) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	Track& t = ses.GetTrack(id);
	
	String title = t.GetTitle();
	EditText(title, "Title of the track", "Title");
	t.SetTitle(title);
	Refresh();
}














BlockCtrl::BlockCtrl() {
	WantFocus();
	
}

void BlockCtrl::Data() {
	
	
	
}

void BlockCtrl::Paint(Draw& w) {
	Size sz = GetSize();
	
	if (HasFocus())
		w.DrawRect(sz, Color(108, 137, 226));
	else
		w.DrawRect(sz, Color(172, 179, 222));
	
	w.DrawLine(0, 0, sz.cx-1, 0, 1, Black);
	w.DrawLine(0, sz.cy-1, sz.cx-1, sz.cy-1, 1, Black);
	w.DrawLine(0, 0, 0, sz.cy-1, 1, Black);
	w.DrawLine(sz.cx-1, 0, sz.cx-1, sz.cy-1, 1, Black);
	
}

void BlockCtrl::LeftDown(Point p, dword keyflags) {
	SetFocus();
	Refresh();
	
	Rect r = GetSize();
	
	SetCapture();
	prev_mouse_pt = p + GetScreenRect().TopLeft();
	prev_mouse_rect = GetRect();
	
	if (p.x >= r.right - 20) {
		mouse_mode = 1;
	} else {
		mouse_mode = 2;
	}
}

void BlockCtrl::MouseMove(Point p, dword keyflags) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	p += GetScreenRect().TopLeft();
	int xdiff = p.x - prev_mouse_pt.x;
	int ydiff = p.y - prev_mouse_pt.y;
	
	if (mouse_mode == 1) {
		Rect r = prev_mouse_rect;
		int snap = tlc.GetSnap();
		r.right += xdiff;
		r.right -= r.right % snap;
		if (r.right < r.left + snap) r.right = r.left + snap;
		SetRect(r);
		Refresh();
	}
	if (mouse_mode == 2) {
		Rect r = prev_mouse_rect;
		int ystep = ydiff / r.Height();
		int snap = tlc.GetSnap();
		int w = r.Width();
		int h = r.Height();
		r.top += ystep * h;
		r.bottom += ystep * h;
		r.left += xdiff;
		r.left -= r.left % snap;
		if (r.left < 0) r.left = 0;
		r.right = r.left + w;
		SetRect(r);
		Refresh();
	}
	
}

void BlockCtrl::LeftUp(Point p, dword keyflags) {
	ReleaseCapture();
	if (mouse_mode != 0)
		Backward();
	mouse_mode = 0;
}

void BlockCtrl::LeftDouble(Point p, dword keyflags) {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	SessionEditor& se = tlc.GetEditor();
	se.SetMidiEditor(track, block);
	
}

void BlockCtrl::Backward() {
	TrackListCtrl& tlc = CastRef<TrackListCtrl>(*GetParentCtrl());
	Session& ses = tlc.GetEditor().GetSession();
	Track& t = ses.GetTrack(track);
	Block& block = t.GetBlock(this->block);
	
	int global_shift = tlc.GetScrollShift();
	int snap = tlc.GetSnap();
	
	Rect r = GetRect();
	int new_track = tlc.GetTrackFromPx(r.top);
	int screen_shift = tlc.GetShiftFromPx(r.left);
	int block_shift = max(0, screen_shift + global_shift);
	int block_size = r.right - screen_shift;
	
	block_shift -= block_shift % snap;
	block_size  -= block_size  % snap;
	
	Op op;
	op.SetInt(0, OP_MOVEBLOCK);
	op.SetInt(1, track);
	op.SetInt(2, this->block);
	op.SetInt(3, block_shift);
	op.SetInt(4, block_size);
	op.SetInt(5, block.GetShift());
	op.SetInt(6, block.GetSize());
	ses.Do(op);
	
	if (track != new_track && new_track >= 0 && new_track < ses.GetTrackCount()) {
		Op op;
		op.SetInt(0, OP_MOVEBLOCKTRACK);
		op.SetInt(1, track);
		op.SetInt(2, this->block);
		op.SetInt(3, new_track);
		ses.Do(op);
	}
}


NAMESPACE_TOPSIDE_END

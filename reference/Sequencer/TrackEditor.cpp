#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


TrackEditorCtrl::TrackEditorCtrl() {
	WantFocus();
	
	ExprParentCtrl::Set(root);
	AddFrame(vsb);
	AddFrame(hsb);
	hsb.Horz();
	
	vsb.WhenScroll = THISBACK(Layout);
	hsb.WhenScroll = THISBACK(Layout);
	
	
}

void TrackEditorCtrl::Set(int track, int block) {
	this->track = track;
	this->block = block;
	Data();
}

void TrackEditorCtrl::Data() {
	
	
	Layout();
	Refresh();
}

Block& TrackEditorCtrl::GetBlock() {
	Session& ses = GetEditor().GetSession();
	Track& t = ses.GetTrack(track);
	Block& block = t.GetBlock(this->block);
	return block;
}

void TrackEditorCtrl::Layout() {
	try {
		Session& ses = GetEditor().GetSession();
		Track& t = ses.GetTrack(track);
		Block& block = t.GetBlock(this->block);
		
		Size sz(GetSize());
		
		hsb.SetLine(100);
		hsb.SetTotal(GetPxFromShift(left_pad + right_pad + block.GetSize()));
		hsb.SetPage(sz.cx);
		vsb.SetLine(3 * row_height);
		vsb.SetTotal(row_count * row_height);
		vsb.SetPage(sz.cy);
		
		
		ExprParentCtrl::Layout();
		Refresh();
	}
	catch (Exc e) {
		//PromptOK(e);
	}
}

void TrackEditorCtrl::SubBar(Bar& bar) {
	bar.Add("Select note", SequencerImg::selnote(), THISBACK(SelectNote)).Key(K_1);
	bar.Add("Add note", SequencerImg::addnote(), THISBACK(AddNote0)).Key(K_2);
	bar.Add("Remove note", SequencerImg::remnote(), THISBACK(RemoveNote0)).Key(K_3);
	
}

void TrackEditorCtrl::AddNote0() {
	mode = MODE_ADD;
}

void TrackEditorCtrl::RemoveNote0() {
	mode = MODE_REM;
}

void TrackEditorCtrl::SelectNote() {
	mode = MODE_SELECT;
}

void TrackEditorCtrl::LeftDown(Point p, dword keyflags) {
	ExprParentCtrl::LeftDown(p, keyflags);
}

void TrackEditorCtrl::GetMouseShiftPitch(Point pt, int& shift, int& pitch) {
	int screen_vshift = GetVScroll();
	shift = GetShiftFromPx(pt.x) + GetScrollShift() - GetLeftPadShift();
	pitch = row_count - 1 - (pt.y + screen_vshift) / row_height;
}

void TrackEditorCtrl::AddNote(int shift, int pitch) {
	int track_id = GetTrackId();
	int block_id = GetBlockId();
	Session& ses = GetEditor().GetSession();
	
	shift -= shift % (int)snap;
	
	Op op;
	op.SetInt(0, OP_ADDNOTE);
	op.SetInt(1, track_id);
	op.SetInt(2, block_id);
	op.SetInt(3, shift);
	op.SetInt(4, snap);
	op.SetInt(5, pitch);
	
	
	ses.Do(op);
	
	Refresh();
}

void TrackEditorCtrl::RemoveNote(int shift, int pitch) {
	Session& ses = GetEditor().GetSession();
	int track_id = GetTrackId();
	int block_id = GetBlockId();
	
	ses.DoBegin();
	
	Block& b = GetBlock();
	for(int i = 0; i < b.GetNoteCount(); i++) {
		Note& n = b.GetNote(i);
		if (n.GetPitch() == pitch) {
			int begin = n.GetShift();
			int end = begin + n.GetLength();
			if (shift >= begin && shift < end) {
				Op op;
				op.SetInt(0, OP_REMNOTE);
				op.SetInt(1, track_id);
				op.SetInt(2, block_id);
				op.SetInt(3, i);
				op.Store(n);
				ses.Do(op);
			}
		}
	}
	
	ses.DoEnd();
	
	Data();
}

bool TrackEditorCtrl::Key(dword key, int count) {
	if (key == K_DELETE) {
		root.seq.RemoveSelected();
	}
	
	return false;
}

void TrackEditorCtrl::LeftUp(Point p, dword keyflags) {
	ExprParentCtrl::LeftUp(p, keyflags);
}

void TrackEditorCtrl::MouseMove(Point p, dword keyflags) {
	ExprParentCtrl::MouseMove(p, keyflags);
}

void TrackEditorCtrl::MouseWheel(Point p, int zdelta, dword keyflags) {
	if (!keyflags) {
		vsb.Wheel(zdelta);
	}
	else if (keyflags & K_CTRL && keyflags & K_SHIFT) {
		if (zdelta < 0)
			zoom *= 0.5;
		else
			zoom *= 2;
		Data();
	}
	else if (keyflags & K_CTRL) {
		hsb.Wheel(zdelta);
	}
}









TrackExprCtrl::TrackExprCtrl() {
	Add(pianoroll);
	Add(seq);
	Add(timebar);
	Add(timectrl);
	
}

void TrackExprCtrl::Layout() {
	Size sz(GetSize());
	
	timebar.SetRect(pr_w, 0, sz.cx - pr_w, 20);
	pianoroll.SetRect(0, 20, pr_w, sz.cy - 20);
	seq.SetRect(pr_w, 20, sz.cx - pr_w, sz.cy - 20);
	
}

void TrackExprCtrl::TimeChanges() {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	SessionEditor& se = tec.GetEditor();
	Session& ses = se.GetSession();
	Block& block = tec.GetBlock();
	int time_cursor = ses.GetTimeCursor();
	int shift = time_cursor * BARSIZE / 4.0 / ses.GetTempo() * 60.0 / 1000;
	shift += tec.left_pad - block.GetShift();
	int px = pr_w + tec.GetPxFromShift(shift);
	Size sz(GetSize());
	timectrl.SetRect(px, 0, 2, sz.cy);
	tec.Refresh();
}










SequencerCtrl::SequencerCtrl() {
	
}

void SequencerCtrl::LeftDown(Point p, dword keyflags) {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	int mode = tec.GetMode();
	
	left_down_pt = p;
	SetCapture();
	SetFocus();
	
	if (keyflags & K_SHIFT) {
		SelectAdd(p);
		
	}
	else {
		if (mode == TrackEditorCtrl::MODE_SELECT) {
			if (!Intersects(p)) {
				Select(RectC(0,0,0,0));
				Add(selctrl);
				capture_sel = true;
			}
			else {
				if (!IsSelected(p)) {
					Select(p);
				}
				capture_note = true;
				PushSelection();
				//ExprParentCtrl::LeftDown(p, keyflags);
			}
		}
		else if (mode == TrackEditorCtrl::MODE_ADD) {
			int shift, pitch;
			tec.GetMouseShiftPitch(p, shift, pitch);
			tec.AddNote(shift, pitch);
		}
		else if (mode == TrackEditorCtrl::MODE_REM) {
			int shift, pitch;
			tec.GetMouseShiftPitch(p, shift, pitch);
			tec.RemoveNote(shift, pitch);
		}
		
		
	}
}

void SequencerCtrl::LeftUp(Point p, dword keyflags) {
	ReleaseCapture();
	
	if (keyflags & K_SHIFT) {
		
	}
	else {
		if (capture_sel) {
			RemoveChild(&selctrl);
			capture_sel = false;
		}
		
		if (capture_note) {
			capture_note = false;
			BackwardStack();
		}
		
		if (p == left_down_pt) {
			Select(p);
		}
	}
	
	Refresh();
}

void SequencerCtrl::MouseMove(Point p, dword keyflags) {
	if (capture_sel) {
		Rect r;
		r.left = min(left_down_pt.x, p.x);
		r.top = min(left_down_pt.y, p.y);
		r.right = max(left_down_pt.x, p.x);
		r.bottom = max(left_down_pt.y, p.y);
		
		Select(r);
		Refresh();
	}
	else if (capture_note) {
		Point diff = p - left_down_pt;
		MoveStack(diff);
		Refresh();
	}
}

void SequencerCtrl::Layout() {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	Block& block = tec.GetBlock();
	
	int vsb = tec.GetVScroll();
	int hsb = tec.GetHScroll();
	int row_count = tec.GetRowCount();
	int row_height = tec.GetRowHeight();
	int left_pad = tec.GetLeftPadShift();
	
	for(int i = notes.GetCount(); i < block.GetNoteCount(); i++) {
		NoteCtrl& nc = notes.Add();
		Add(nc);
	}
	
	for(int i = notes.GetCount()-1; i >= block.GetNoteCount(); i--) {
		RemoveChild(&notes[i]);
		notes.Remove(i);
	}
	
	for(int i = 0; i < block.GetNoteCount(); i++) {
		NoteCtrl& nc = notes[i];
		nc.SetId(i);
		Note& n = block.GetNote(i);
		int y = -vsb + (row_count - 1 - n.GetPitch()) * row_height;
		int x = -hsb + tec.GetPxFromShift(left_pad + n.GetShift());
		int w = tec.GetPxFromShift(n.GetLength());
		nc.SetRect(RectC(x, y, w, row_height));
	}
	
}

void SequencerCtrl::Paint(Draw& w) {
	try {
		Size sz = GetSize();
		w.DrawRect(sz, Color(217, 227, 255));
		
		TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
		Block& block = tec.GetBlock();
		int scroll = tec.GetHScroll();
		
		int x0 = -scroll + tec.GetPxFromShift(tec.left_pad);
		int x1 = -scroll + tec.GetPxFromShift(tec.left_pad + block.GetSize());
		int y = -tec.vsb;
		int pitch = tec.row_count - 1;
		while (y < 0) {
			y += tec.row_height;
			pitch--;
		}
		while (y < sz.cy) {
			int pmod = pitch % 12;
			bool is_white = false;
			switch (pmod) {
				case 0:
				case 2:
				case 4:
				case 5:
				case 7:
				case 9:
				case 11: is_white = true; break;
			}
			
			w.DrawRect(x0, y, x1 - x0, tec.row_height, is_white ? Color(232, 239, 255) : Color(187, 193, 225));
			
			w.DrawLine(0, y, sz.cx, y, 1, GrayColor(128));
			y += tec.row_height;
			pitch--;
		}
		
		int prev_type = -1; // avoid bold lines: GetShiftFromPx gives same shift from x range
		for (int x = 0; x < sz.cx; x++) {
			int px = scroll + x;
			int shift = tec.GetShiftFromPx(px);
			Color clr;
			if (shift % 64 == 0) {
				if (prev_type != 1)
					w.DrawLine(x, 0, x, sz.cy, 1, GrayColor(32));
				prev_type = 1;
			}
			else if (shift % 16 == 0) {
				if (prev_type != 2)
					w.DrawLine(x, 0, x, sz.cy, 1, GrayColor(64));
				prev_type = 2;
			}
			else if (shift % 4 == 0) {
				if (prev_type != 3)
					w.DrawLine(x, 0, x, sz.cy, 1, GrayColor(128));
				prev_type = 3;
			}
			else {
				prev_type = 0;
			}
		}
	}
	catch (Exc e) {
		
	}
}

void SequencerCtrl::Select(Rect r) {
	selctrl.SetRect(r);
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (r.Contains(n.GetRect()))
			n.Select();
		else
			n.Select(false);
	}
}

void SequencerCtrl::Select(Point pt) {
	for(int i = 0; i < notes.GetCount(); i++)
		notes[i].Select(false);
	
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (n.GetRect().Contains(pt)) {
			n.Select();
			break;
		}
	}
}

void SequencerCtrl::SelectAdd(Point pt) {
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (n.GetRect().Contains(pt))
			n.Select();
	}
}

bool SequencerCtrl::Intersects(Point p) {
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (n.GetRect().Contains(p))
			return true;
	}
	return false;
}

bool SequencerCtrl::IsSelected(Point p) {
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (n.GetRect().Contains(p) && n.IsSelected())
			return true;
	}
	return false;
}

void SequencerCtrl::PushSelection() {
	sel_notes.SetCount(0);
	for(int i = 0; i < notes.GetCount(); i++) {
		NoteCtrl& n = notes[i];
		if (n.IsSelected()) {
			sel_notes.Add(NoteSel(i, n.GetRect()));
		}
	}
}

void SequencerCtrl::MoveStack(Point p) {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	
	p.y -= p.y % tec.row_height;
	p.x -= p.x % (int)tec.snap;
	
	for(int i = 0; i < sel_notes.GetCount(); i++) {
		NoteSel sel = sel_notes[i];
		if (sel.a < notes.GetCount()) {
			NoteCtrl& n = notes[sel.a];
			Rect r = sel.b;
			r.left += p.x;
			r.right += p.x;
			r.top += p.y;
			r.bottom += p.y;
			n.SetRect(r);
		}
	}
	
	Refresh();
}

void SequencerCtrl::BackwardStack() {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	Session& ses = tec.GetEditor().GetSession();
	ses.DoBegin();
	
	for(int i = 0; i < sel_notes.GetCount(); i++) {
		NoteSel sel = sel_notes[i];
		if (sel.a < notes.GetCount()) {
			NoteCtrl& n = notes[sel.a];
			n.Backward();
		}
	}
	
	ses.DoEnd();
}

void SequencerCtrl::RemoveSelected() {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	SessionEditor& se = tec.GetEditor();
	Session& ses = se.GetSession();
	Block& block = tec.GetBlock();
	int track_id = tec.GetTrackId();
	int block_id = tec.GetBlockId();
	
	PushSelection();
	
	ses.DoBegin();
	
	for (int i = sel_notes.GetCount() - 1; i >= 0; i--) {
		NoteSel sel = sel_notes[i];
		Note& n = block.GetNote(sel.a);
		Op op;
		op.SetInt(0, OP_REMNOTE);
		op.SetInt(1, track_id);
		op.SetInt(2, block_id);
		op.SetInt(3, sel.a);
		op.Store(n);
		ses.Do(op);
	}
	Unselect();
	
	ses.DoEnd();
	
	tec.Data();
}

void SequencerCtrl::Unselect() {
	sel_notes.Clear();
	for(int i = 0; i < notes.GetCount(); i++)
		notes[i].Select(false);
}












SelectionCtrl::SelectionCtrl() {
	
}

void SelectionCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	ImageBuffer ib(sz);
	RGBA* it = ib.Begin();
	for(int y = 0; y < sz.cy; y++) {
		for(int x = 0; x < sz.cx; x++) {
			it->r = 28;
			it->g = 170;
			it->b = 255;
			it->a = 94;
			it++;
		}
	}
	d.DrawImage(0, 0, ib);
}






NoteCtrl::NoteCtrl() {
	WantFocus(false);
}
	
void NoteCtrl::Paint(Draw& w) {
	Size sz = GetSize();
	
	if (is_selected)
		w.DrawRect(sz, Blue);
	else
		w.DrawRect(sz, Red);
	
}

void NoteCtrl::LeftDown(Point p, dword keyflags) {
	WhenAction();
	is_selected = true;
	Refresh();
}

TrackEditorCtrl& NoteCtrl::GetTrackEditor() {
	return CastRef<TrackEditorCtrl>(*GetParentCtrl());
}

void NoteCtrl::Backward() {
	TrackEditorCtrl& tec = GetTrackEditor();
	int track_id = tec.GetTrackId();
	int block_id = tec.GetBlockId();
	Session& ses = tec.GetEditor().GetSession();
	Track& t = ses.GetTrack(track_id);
	Block& block = t.GetBlock(block_id);
	Note& note = block.GetNote(id);
	
	int global_shift = tec.GetScrollShift();
	int left_offset = tec.GetLeftPadShift();
	int snap = tec.GetSnap();
	
	Rect r = GetRect();
	int screen_shift = tec.GetShiftFromPx(r.left);
	int note_shift = max(0, screen_shift + global_shift - left_offset);
	int note_size = tec.GetShiftFromPx(r.right) - screen_shift;
	
	int vscroll_shift = tec.GetVScroll();
	int pitch = tec.GetRowCount() - 1 - (r.top + vscroll_shift) / tec.GetRowHeight();
	
	note_shift -= note_shift % snap;
	note_size  -= note_size  % snap;
	if (note_size <= 0) note_size = snap;
	
	Op op;
	op.SetInt(0, OP_MOVENOTE);
	op.SetInt(1, track_id);
	op.SetInt(2, block_id);
	op.SetInt(3, id);
	op.SetInt(4, note_shift);
	op.SetInt(5, note_size);
	op.SetInt(6, pitch);
	op.Store(note);
	
	ses.Do(op);
}





void TimebarCtrl::Paint(Draw& d) {
	try {
		TrackEditorCtrl& pc = CastRef<TrackEditorCtrl>(*GetParentCtrl());
		
		int scroll = pc.GetScroll();
		int pad_shift = pc.GetLeftPadShift();
		int block_shift = pc.GetBlockShift();
		
		Size sz(GetSize());
		
		d.DrawRect(sz, Color(56, 85, 150));
		
		int prev_draw_h = -1;
		for (int x = 0; x < sz.cx; x++) {
			int px = scroll + x;
			int shift = pc.GetShiftFromPx(px) - pad_shift + block_shift;
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
			
			if (draw_h != 0 && prev_draw_h != draw_h) {
				int lx = x;
				int y0 = 0;
				int y1 = draw_h * sz.cy / 5;
				d.DrawLine(lx, y0, lx, y1, 1, White);
			}
			prev_draw_h = draw_h;
		}
	}
	catch (...) {
		
	}
}

void TimebarCtrl::LeftDown(Point p, dword keyflags) {
	SetPosition(p);
	SetCapture();
}

void TimebarCtrl::LeftUp(Point p, dword keyflags) {
	SetPosition(p);
	ReleaseCapture();
}

void TimebarCtrl::MouseMove(Point p, dword keyflags) {
	if (IsCaptured())
		SetPosition(p);
}

void TimebarCtrl::SetPosition(Point p) {
	TrackEditorCtrl& pc = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	Session& ses = pc.GetEditor().GetSession();
	
	int scroll = pc.GetScroll();
	int pad_shift = pc.GetLeftPadShift();
	int block_shift = pc.GetBlockShift();
	int x = p.x;
	int px = scroll + x;
	int shift = pc.GetShiftFromPx(px) - pad_shift + block_shift;
	int time = ses.GetTimeFromShift(shift);
	ses.Seek(time);
}
















void PianorollCtrl::Paint(Draw& w) {
	try {
		Size sz = GetSize();
		w.DrawRect(sz, Color(217, 227, 255));
		
		TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
		Block& block = tec.GetBlock();
		
		int x0 = 0;
		int x1 = sz.cx;
		int y = -tec.vsb;
		int pitch = tec.row_count - 1;
		while (y < 0) {
			y += tec.row_height;
			pitch--;
		}
		while (y < sz.cy) {
			int pmod = pitch % 12;
			bool is_white = false;
			switch (pmod) {
				case 0:
				case 2:
				case 4:
				case 5:
				case 7:
				case 9:
				case 11: is_white = true; break;
			}
			
			
			w.DrawRect(x0, y, x1 - x0, tec.row_height, is_white ? GrayColor(256-32) : GrayColor(32));
			
			w.DrawLine(0, y, sz.cx, y, 1, GrayColor(128));
			y += tec.row_height;
			pitch--;
		}
	}
	catch (Exc e) {
		
	}
}

void PianorollCtrl::LeftDown(Point p, dword keyflags) {
	SetCapture();
	NoteOn(p);
}

void PianorollCtrl::LeftUp(Point p, dword keyflags) {
	ReleaseCapture();
	NoteOff(p);
}

void PianorollCtrl::MouseMove(Point p, dword keyflags) {
	if (IsCaptured())
		NoteOn(p);
}

void PianorollCtrl::NoteOn(Point p) {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	Session& ses = tec.GetEditor().GetSession();
	int y = tec.vsb + p.y;
	int pitch = tec.row_count - 1 - y / tec.row_height;
	if (pitch_on == pitch) return;
	double freq = Note::GetFrequencyPitch(pitch);
	int track_id = tec.GetTrackId();
	Bus& bus = ses.GetSystem().GetSource(track_id);
	if (pitch_on >= 0) {
		double freq = Note::GetFrequencyPitch(pitch_on);
		bus.NoteOff(freq);
	}
	pitch_on = pitch;
	bus.NoteOn(freq);
}

void PianorollCtrl::NoteOff(Point p) {
	TrackEditorCtrl& tec = CastRef<TrackEditorCtrl>(*GetParentCtrl());
	Session& ses = tec.GetEditor().GetSession();
	int track_id = tec.GetTrackId();
	Bus& bus = ses.GetSystem().GetSource(track_id);
	if (pitch_on >= 0) {
		double freq = Note::GetFrequencyPitch(pitch_on);
		bus.NoteOff(freq);
	}
	pitch_on = -1;
}


NAMESPACE_TOPSIDE_END


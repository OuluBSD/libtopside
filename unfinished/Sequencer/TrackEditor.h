#ifndef _Sequencer_TrackEditor_h_
#define _Sequencer_TrackEditor_h_


NAMESPACE_TOPSIDE_BEGIN


class TrackEditorCtrl;

class NoteCtrl : public ExprCtrl {
	Point prev_mouse_pt;
	Rect prev_mouse_rect;
	Rect selrect;
	int mouse_mode = 0;
	int id = -1;
	bool is_selected = false;
	
public:
	typedef NoteCtrl CLASSNAME;
	NoteCtrl();
	
	virtual void Paint(Draw& d);
	
	virtual void LeftDown(Point p, dword keyflags);
	virtual void GotFocus() {is_selected = true; Refresh();}
	virtual void LostFocus() {is_selected = false; Refresh();}

	void Select(bool b=true) {is_selected = b;}
	bool IsSelected() const {return is_selected;}
	void SetId(int i) {id = i;}
	void Backward();
	TrackEditorCtrl& GetTrackEditor();
	
	Callback WhenAction;
};

class SelectionCtrl : public ExprCtrl {
	
	
public:
	SelectionCtrl();
	virtual void Paint(Draw& d);
	
	
};

class TimecursorCtrl : public ExprCtrl {
	
public:
	TimecursorCtrl() {}
	virtual void Paint(Draw& d) {d.DrawRect(GetSize(), Black());}
	
	
};

class TimebarCtrl : public ExprCtrl {
	
public:
	TimebarCtrl() {}
	
	virtual void Paint(Draw& d);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	
	void SetPosition(Point p);
};

class PianorollCtrl : public ExprCtrl {
	int pitch_on = -1;
	
public:
	virtual void Paint(Draw& d);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	
	void NoteOn(Point p);
	void NoteOff(Point p);
};

class SequencerCtrl : public ExprCtrl {
	typedef Tuple<int, Rect> NoteSel;
	
protected:
	friend class TrackEditorCtrl;
	Array<NoteCtrl> notes;
	Vector<NoteSel> sel_notes;
	SelectionCtrl selctrl;
	Point left_down_pt;
	bool capture_sel = false;
	bool capture_note = false;
	
	
	
public:
	SequencerCtrl();
	virtual void Paint(Draw& d);
	virtual void Layout();
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	
	void Select(Rect r);
	void Select(Point pt);
	void SelectAdd(Point pt);
	void Unselect();
	bool Intersects(Point p);
	bool IsSelected(Point p);
	void MoveStack(Point p);
	void PushSelection();
	void BackwardStack();
	void RemoveSelected();
	
};

class TrackExprCtrl : public ExprCtrl {
	
	static const int pr_w = 50;
	
protected:
	friend class TrackEditorCtrl;
	SequencerCtrl seq;
	TimecursorCtrl timectrl;
	TimebarCtrl timebar;
	PianorollCtrl pianoroll;
	
	virtual void Layout();
	
	
public:
	typedef TrackExprCtrl CLASSNAME;
	TrackExprCtrl();
	
	
	void TimeChanges();
};

class TrackEditorCtrl : public ExprParentCtrl {
	
protected:
	friend class TrackExprCtrl;
	friend class SequencerCtrl;
	friend class PianorollCtrl;
	
	static const int left_pad = BARSIZE;
	static const int right_pad = BARSIZE;
	
	enum {MODE_SELECT, MODE_ADD, MODE_REM};
	
	ScrollBar hsb, vsb;
	TrackExprCtrl root;
	double zoom = 0.25;
	double snap = 4;
	int row_height = 10;
	int row_count = 12*8;
	int track = -1, block = -1;
	int mode = MODE_SELECT;
	
public:
	typedef TrackEditorCtrl CLASSNAME;
	TrackEditorCtrl();
	
	void Data();
	
	void Set(int track, int block);
	void SubBar(Bar& bar);
	void AddNote0();
	void RemoveNote0();
	void SelectNote();
	
	virtual void Layout();
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual bool Key(dword key, int count);

	void TimeChanges() {root.TimeChanges();}
	int GetScroll() {return hsb;}
	int GetVScroll() {return vsb;}
	int GetHScroll() {return hsb;}
	int GetScrollShift() {return GetShiftFromPx(hsb);}
	int GetShiftFromPx(int px) {return px * zoom;}
	int GetPxFromShift(int shift) {return shift / zoom;}
	int GetSnap() const {return snap;}
	Block& GetBlock();
	int GetBlockShift() {return GetBlock().GetShift();}
	int GetTrackId() const {return track;}
	int GetBlockId() const {return block;}
	int GetLeftPadShift() const {return left_pad;}
	int GetRowHeight() const {return row_height;}
	int GetRowCount() const {return row_count;}
	int GetMode() const {return mode;}
	void GetMouseShiftPitch(Point pt, int& shift, int& pitch);
	void AddNote(int shift, int pitch);
	void RemoveNote(int shift, int pitch);
};


NAMESPACE_TOPSIDE_END


#endif

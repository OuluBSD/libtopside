#ifndef _Sequencer_TrackListCtrl_h_
#define _Sequencer_TrackListCtrl_h_


NAMESPACE_TOPSIDE_BEGIN

class TrackHeaderCtrl : public ExprCtrl {
	int id = -1;
	bool selected = 0;
	
public:
	typedef TrackHeaderCtrl CLASSNAME;
	TrackHeaderCtrl();
	
	void EditTitle();
	
	void SetId(int i) {id = i;}
	
	int GetId() const {return id;}
	bool IsSelected() {return selected;}
	
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword keyflags);
};


class BlockCtrl : public ExprCtrl {
	int track = -1, block = -1;
	int mouse_mode = 0;
	Point prev_mouse_pt;
	Rect prev_mouse_rect;
	
public:
	BlockCtrl();
	
	void Data();
	void Backward();
	
	void SetId(int t, int b) {track = t; block = b;}
	
	int GetTrackId() {return track;}
	int GetBlockId() {return block;}
	
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void LeftDouble(Point p, dword keyflags);

};

class TimelineCtrl : public ExprCtrl {
	
public:
	TimelineCtrl() {}
	
	virtual void Paint(Draw& w);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	
	void SetPosition(Point p);
};

class TrackHeaderList : public ExprCtrl {
	
protected:
	friend class TrackListCtrl;
	Array<TrackHeaderCtrl> tracks;
	
public:
	TrackHeaderList();
	virtual void Layout();
	
};

class TrackList : public ExprCtrl {
	Array<Array<BlockCtrl> > blocks;
	
public:
	TrackList();
	
	virtual void Paint(Draw& w);
	virtual void Layout();
	virtual void LeftDown(Point p, dword keyflags);

};

class TrackListExprCtrl : public ExprCtrl {
	
protected:
	friend class TrackListCtrl;
	
	TrackList list;
	TrackHeaderList header;
	TimecursorCtrl timectrl;
	TimelineCtrl timeline;
	
public:
	TrackListExprCtrl();
	
	virtual void Layout();
	
	void TimeChanges();
	
	static const int head_w = 200;
	static const int time_h = 20;
};

class TrackListCtrl : public ExprParentCtrl {
	TrackListExprCtrl root;
	ScrollBar vsb, hsb;
	double zoom = 1;
	double snap = 16;
	int row_height = 90;
	
	
public:
	typedef TrackListCtrl CLASSNAME;
	TrackListCtrl();
	
	void Data() {Layout(); Refresh();}
	void AddTrack();
	void RemoveTrack();
	
	virtual void Layout();
	virtual void MouseWheel(Point, int zdelta, dword);
	void SubBar(Bar& bar);
	void TimeChanges() {root.TimeChanges();}
	
	int GetScroll() {return hsb;}
	int GetScrollShift() {return GetShiftFromPx(hsb);}
	int GetShiftFromPx(int px) {return px * zoom;}
	int GetTrackFromPx(int px) {int h = px + hsb; return h / row_height;}
	int GetPxFromShift(int shift) {return shift / zoom;}
	int GetSnap() const {return snap;}
	int GetRowHeight() const {return row_height;}
	
};

NAMESPACE_TOPSIDE_END

#endif

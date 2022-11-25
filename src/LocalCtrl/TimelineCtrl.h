#ifndef _LocalCtrl_TimelineCtrl_h_
#define _LocalCtrl_TimelineCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


class TimelineCtrl;


class TimelineRowCtrl : public Ctrl {
	
protected:
	friend class TimelineCtrl;
	TimelineCtrl* owner = 0;
	Vector<int> keypoints;
	int id = -1;
	String title;
	
public:
	typedef TimelineRowCtrl CLASSNAME;
	TimelineRowCtrl();
	
	void Paint(Draw& d) override;
	bool Key(dword key, int) override;
	void LeftDown(Point p, dword keyflags) override;
	void RightDown(Point p, dword keyflags) override;
	void GotFocus() override;
	void LostFocus() override;

	void SetTitle(String s) {title = s;}
	void SetKeypoints(const Vector<int>& keypoints);
	
};


class TimelineCtrl : public Ctrl {
	//ArrayMap<int, TimelineRowCtrl> rows;
	Array<TimelineRowCtrl> rows;
	ScrollBar vsb, hsb;
	int line_height = 20;
	int kps = 25;
	int length = 0;
	
protected:
	friend class TimelineRowCtrl;
	Color bg, bg_focused, bg_focused_keypoint, accent, text;
	Color kp_second_accent, kp_col_accent;
	int title_tab_w = 200;
	int kp_col = 10;
	int selected_col = 0;
	
public:
	typedef TimelineCtrl CLASSNAME;
	TimelineCtrl();
	
	//TimelineRowCtrl& GetAddRow(int id);
	TimelineRowCtrl& GetRowIndex(int i);
	int GetLineHeight() const {return line_height;}
	int GetColumnWidth() const {return kp_col;}
	
	void SetCount(int i);
	void SetLineHeight(int h) {line_height = h;}
	void SetKeypointRate(int kps) {this->kps = kps;}
	void SetLength(int i);
	void SetKeypointColumnWidth(int i);
	void SetSelectedColumn(int i) {selected_col = i;}
	
	void Paint(Draw& d) override;
	bool Key(dword key, int) override;
	void LeftDown(Point p, dword keyflags) override;
	void RightDown(Point p, dword keyflags) override;
	void MouseWheel(Point p, int zdelta, dword keyflags) override;
	void Layout() override;
	
	Callback1<int> WhenCursor;
	
};


NAMESPACE_TOPSIDE_END

#endif

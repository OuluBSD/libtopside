#ifndef _DesktopSuite_Tester_h_
#define _DesktopSuite_Tester_h_


NAMESPACE_TOPSIDE_BEGIN


class CtrlTester_Ctrl : public Ctrl {
	Color clr;
	String txt;
public:
	void Paint(Draw& d) override;
	void MouseMove(Point p, dword keyflags) override;
	void SetLabel(String s) {txt = s;}
};

class CtrlTesterApp : public TopWindow {
	CtrlTester_Ctrl b;
	
	CtrlTester_Ctrl c0;
	DocEdit c1;
	
public:
	CtrlTesterApp();
	
};

class GuiTesterApp : public TopWindow {
	EditString edit;
	TimeCallback tc;
	
	Vector<Point> v;
	Color c;
	Point test_rect_tl;
	
public:
	typedef GuiTesterApp CLASSNAME;
	GuiTesterApp();
	void TimedToggle();
	
	bool Key(dword key, int count) override;
	void Paint(Draw& d) override;
	void MouseMove(Point p, dword keyflags) override;
	void MouseWheel(Point p, int zdelta, dword keyflags) override;
	void MouseLeave() override {Refresh();}
	void LeftDown(Point p, dword keyflags) override;
	void RightDown(Point p, dword keyflags) override;

};


NAMESPACE_TOPSIDE_END


#endif

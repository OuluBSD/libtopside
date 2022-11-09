#ifndef _DesktopSuite_Tester_h_
#define _DesktopSuite_Tester_h_



NAMESPACE_TOPSIDE_BEGIN

class GuiTesterApp : public TopWindow {
	EditString edit;
	
	
	Vector<Point> v;
	Color c;
	
public:
	GuiTesterApp();
	virtual bool Key(dword key, int count);
	virtual void Paint(Draw& d);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void MouseLeave() {Refresh();}
	virtual void LeftDown(Point p, dword keyflags);

};

NAMESPACE_TOPSIDE_END



#endif

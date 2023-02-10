#ifndef _DesktopSuite_Events_h_
#define _DesktopSuite_Events_h_

NAMESPACE_TOPSIDE_BEGIN


using namespace Upp;

String GetKeyDescEx(int key);

struct EventsTester : TopWindow {
	ArrayCtrl  log;

	EventsTester();
	~EventsTester();
	void Log(const String& s);
	virtual void   Activate();
	virtual void   Deactivate();
	virtual Image  FrameMouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual Image  MouseEvent(int event, Point p, int zdelta, dword keyflags);
	virtual void   MouseEnter(Point p, dword keyflags);
	virtual void   MouseMove(Point p, dword keyflags);
	virtual void   LeftDown(Point p, dword keyflags);
	virtual void   LeftDouble(Point p, dword keyflags);
	virtual void LeftTriple(Point p, dword keyflags);
	virtual void LeftDrag(Point p, dword keyflags);
	virtual void LeftHold(Point p, dword keyflags);
	virtual void   LeftRepeat(Point p, dword keyflags);
	virtual void   LeftUp(Point p, dword keyflags);
	virtual void   RightDown(Point p, dword keyflags);
	virtual void   RightDouble(Point p, dword keyflags);
	virtual void RightTriple(Point p, dword keyflags);
	virtual void RightDrag(Point p, dword keyflags);
	virtual void RightHold(Point p, dword keyflags);
	virtual void   RightRepeat(Point p, dword keyflags);
	virtual void   RightUp(Point p, dword keyflags);
	virtual void   MiddleDown(Point p, dword keyflags);
	virtual void   MiddleDouble(Point p, dword keyflags);
	virtual void MiddleTriple(Point p, dword keyflags);
	virtual void MiddleDrag(Point p, dword keyflags);
	virtual void MiddleHold(Point p, dword keyflags);
	virtual void   MiddleRepeat(Point p, dword keyflags);
	virtual void   MiddleUp(Point p, dword keyflags);
	virtual void   MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void   MouseLeave();
	virtual Image  CursorImage(Point p, dword keyflags);
	virtual bool   Key(dword key, int count);
	virtual void   GotFocus();
	virtual void   LostFocus();
	virtual bool   HotKey(dword key);
	virtual void   ChildGotFocus();
	virtual void   ChildLostFocus();
	virtual void   Layout();
};

NAMESPACE_TOPSIDE_END

#endif

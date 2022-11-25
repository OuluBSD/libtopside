#ifndef _VirtualGui3D01_VirtualGui3D01_h_
#define _VirtualGui3D01_VirtualGui3D01_h_

#include <Complete/Complete.h>
using namespace UPP;

NAMESPACE_TOPSIDE_BEGIN

class CoreWindowTesterApp {
	
	
public:
	typedef CoreWindowTesterApp CLASSNAME;
	CoreWindowTesterApp(int test_idx);
	
	void Run();
	void Test_WindowOpenClose();
	
};

class VirtualGuiTesterApp : public TopWindow {
	TimeCallback tc;
	int test_idx = 0;
	
public:
	typedef VirtualGuiTesterApp CLASSNAME;
	VirtualGuiTesterApp(int test_idx);
	void TimedToggle();
	virtual bool Key(dword key, int count);
	virtual void Paint(Draw& d);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void MouseLeave() {Refresh();}
	virtual void LeftDown(Point p, dword keyflags);
	virtual void RightDown(Point p, dword keyflags);

};

NAMESPACE_TOPSIDE_END


#endif

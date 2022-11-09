#include "DesktopSuite.h"

NAMESPACE_TOPSIDE_BEGIN


GuiTesterApp::GuiTesterApp() {
	v	<< Point(10, 10)
		<< Point(100, 50)
		<< Point(30, 50)
		<< Point(200, 10)
		;
}

void GuiTesterApp::Paint(Draw& d) {
	Rect r = GetSize();
	
	if (HasMouse())
		d.DrawRect(r, Color(128, 255, 128));
	
	d.DrawPolyline(v, 15, Color(128, 128, 255));
	
	
	d.DrawRect(100, 100, 100, 100, c);
	
	d.DrawLine(r.left, r.top, r.right, r.bottom, 1, Black());
}

void GuiTesterApp::LeftDown(Point p, dword keyflags) {
	c = RandomColor(0, 256);
	Refresh();
}

bool GuiTesterApp::Key(dword key, int count) {
	//Refresh();
	int dx = 0, dy = 0;
	if (key == K_LEFT)
		dx -= 10;
	else if (key == K_RIGHT)
		dx += 10;
	else if (key == K_UP)
		dy -= 10;
	else if (key == K_DOWN)
		dy += 10;
	
	Rect r(GetRect());
	
	r.left += dx;
	r.right += dx;
	r.top += dy;
	r.bottom += dy;
	
	SetRect(r);
	
	return false;
}

void GuiTesterApp::MouseMove(Point p, dword keyflags) {
	Point& pt = v[3];
	pt.x = p.x;
	pt.y = p.y;
	Refresh();
}

void GuiTesterApp::MouseWheel(Point p, int zdelta, dword keyflags) {
	int dy = 0;
	if (zdelta > 0)
		dy -= 10;
	else
		dy += 10;
	
	Rect r(GetRect());
	
	r.top += dy;
	r.bottom += dy;
	
	SetRect(r);
	
}

NAMESPACE_TOPSIDE_END

#include "GuboSuite.h"

NAMESPACE_GUBO_BEGIN


GuiTesterApp::GuiTesterApp() {
	v	<< Point(10, 10)
		<< Point(100, 50)
		<< Point(30, 50)
		<< Point(200, 10)
		;
	
	test_rect_tl = Point(100,100);
	
	tc.Set(-1000, THISBACK(TimedToggle));
}

void GuiTesterApp::TimedToggle() {
	test_rect_tl.x = (test_rect_tl.x + 100) % 200;
	test_rect_tl.y = (test_rect_tl.y + 30) % 200;
	
	Refresh();
}

void GuiTesterApp::Paint(Draw& d) {
	Rect r = GetSize();
	
	if (HasMouse())
		d.DrawRect(r, Color(128, 255, 128));
	
	d.DrawPolyline(v, 15, Color(128, 128, 255));
	d.DrawRect(test_rect_tl.x, test_rect_tl.y, 100, 100, c);
	d.DrawLine(r.left, r.top, r.right, r.bottom, 1, Black());
}

void GuiTesterApp::LeftDown(Point p, dword keyflags) {
	c = RandomColor(0, 256);
	Refresh();
}

void GuiTesterApp::RightDown(Point p, dword keyflags) {
	#if 0
	Size base(320,240);
	Size cur = GetSize();
	cur -= base;
	cur.cx = (cur.cx + 30) % 120;
	cur.cy = (cur.cy + 30) % 120;
	cur += base;
	
	Rect r = GetRect();
	r.right = r.left + cur.cx;
	r.bottom = r.top + cur.cy;
	
	#else
	Rect r = GetRect();
	Size sz = r.GetSize();
	Point pt = r.TopLeft();
	pt.x += Random(21) - 10;
	pt.y += Random(21) - 10;
	sz.cx += Random(21) - 10;
	sz.cy += Random(21) - 10;
	r = RectC(pt.x, pt.y, sz.cx, sz.cy);
	#endif
	
	SetRect(r);
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


NAMESPACE_GUBO_END

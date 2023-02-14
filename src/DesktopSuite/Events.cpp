#include "DesktopSuite.h"

NAMESPACE_TOPSIDE_BEGIN


String GetKeyDescEx(int key)
{
	String desc = GetKeyDesc(key & ~K_KEYUP);
	if(key & K_KEYUP)
		desc << " UP";
	return desc;
}


EventsTester::EventsTester()
{
	SetFrame(InsetFrame());
	AddFrame(InsetFrame());
	AddFrame(InsetFrame());
	AddFrame(InsetFrame());
	log.AddColumn("");
	log.NoHeader();
	log.SetLineCy(20);
	Add(log.HSizePos().BottomPosZ(0, 200));
}

EventsTester::~EventsTester()
{
	Shutdown();
}

void EventsTester::Log(const String& s)
{
	log.Add(s);
	log.GoEnd();
}

void EventsTester::Activate()
{
	Log("Activate");
}

void EventsTester::Deactivate()
{
	Log("Deactivate");
}

Image EventsTester::FrameMouseEvent(int event, Point p, int zdelta, dword keyflags)
{
	if(event != CURSORIMAGE)
		Log(Format("FrameMouseEvent(%d, Point(%d, %d), %d, %x)",
		           event, p.x, p.y, zdelta, (int)keyflags));
	return TopWindow::FrameMouseEvent(event, p, zdelta, keyflags);
}

Image EventsTester::MouseEvent(int event, Point p, int zdelta, dword keyflags)
{
	if(event != CURSORIMAGE)
		Log(Format("MouseEvent(%d, Point(%d, %d), %d, %x)",
		           event, p.x, p.y, zdelta, (int)keyflags));
	return TopWindow::MouseEvent(event, p, zdelta, keyflags);
}

void EventsTester::MouseEnter(Point p, dword keyflags)
{
	Log(Format("MouseEnter(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MouseMove(Point p, dword keyflags)
{
	Log(Format("MouseMove(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftDown(Point p, dword keyflags)
{
	Log(Format("LeftDown(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	SetFocus();
}

void EventsTester::LeftDouble(Point p, dword keyflags)
{
	Log(Format("LeftDouble(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftTriple(Point p, dword keyflags)
{
	Log(Format("LeftTriple(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftDrag(Point p, dword keyflags) {
	Log(Format("LeftDrag(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftHold(Point p, dword keyflags) {
	Log(Format("LeftHold(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftRepeat(Point p, dword keyflags)
{
	Log(Format("LeftRepeat(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::LeftUp(Point p, dword keyflags)
{
	Log(Format("LeftUp(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightDown(Point p, dword keyflags)
{
	Log(Format("RightDown(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightDouble(Point p, dword keyflags)
{
	Log(Format("RightDouble(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightTriple(Point p, dword keyflags)
{
	Log(Format("RightTriple(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightDrag(Point p, dword keyflags) {
	Log(Format("RightDrag(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightHold(Point p, dword keyflags) {
	Log(Format("RightHold(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightRepeat(Point p, dword keyflags)
{
	Log(Format("RightRepeat(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::RightUp(Point p, dword keyflags)
{
	Log(Format("RightUp(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleDown(Point p, dword keyflags)
{
	Log(Format("MiddleDown(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleDouble(Point p, dword keyflags)
{
	Log(Format("MiddleDouble(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleTriple(Point p, dword keyflags)
{
	Log(Format("MiddleTriple(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleDrag(Point p, dword keyflags) {
	Log(Format("MiddleDrag(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleHold(Point p, dword keyflags) {
	Log(Format("MiddleHold(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleRepeat(Point p, dword keyflags)
{
	Log(Format("MiddleRepeat(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MiddleUp(Point p, dword keyflags)
{
	Log(Format("MiddleUp(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
}

void EventsTester::MouseWheel(Point p, int zdelta, dword keyflags)
{
	Log(Format("MouseWheel(Point(%d, %d), %d, %x)", p.x, p.y, zdelta, (int)keyflags));
}

void EventsTester::MouseLeave()
{
	Log("MouseLeave");
}

Image EventsTester::CursorImage(Point p, dword keyflags)
{
	return keyflags & K_CTRL ? CtrlImg::swap_color_cursor() : Image::Arrow();
}

bool EventsTester::Key(dword key, int count)
{
	Log(Format("Key(%x, %d) ", (int)key, count) + GetKeyDescEx(key));
	return false;
}

void EventsTester::GotFocus()
{
	Log("GotFocus");
}

void EventsTester::LostFocus()
{
	Log("LostFocus");
}

bool EventsTester::HotKey(dword key)
{
	Log(Format("HotKey(%x) ", (int)key) + GetKeyDescEx(key));
	return false;
}

void EventsTester::ChildGotFocus()
{
	Log("ChildGotFocus");
}

void EventsTester::ChildLostFocus()
{
	Log("ChildLostFocus");
}

void EventsTester::Layout()
{
	Log("Layout");
}


NAMESPACE_TOPSIDE_END

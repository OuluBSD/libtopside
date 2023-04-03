#include "CtrlCore.h"

NAMESPACE_UPP_BEGIN

//VirtualGui* VirtualGuiPtr;


Bar::Bar() {
	TODO
}

Bar& Bar::Add(String title, Callback cb) {
	TODO
}

Bar& Bar::Separator() {
	TODO
}



Ctrl* Ctrl::captureCtrl;
Ctrl* Ctrl::LoopCtrl;

//Ptr<Ctrl>      Ctrl::desktop;
Ptr<Ctrl>      Ctrl::focusCtrl;
//Vector<Ctrl *> Ctrl::topctrl;

//bool           Ctrl::invalid;
bool           Ctrl::ignoreclick;
bool           Ctrl::inloop;

//Point          Ctrl::fbCursorPos;
//Image          Ctrl::fbCursorImage;

//Rect           Ctrl::fbCaretRect;
//int            Ctrl::fbCaretTm;
//bool           Ctrl::fbEndSession;
//int            Ctrl::PaintLock;
dword          Ctrl::EndSessionLoopNo;
dword          Ctrl::EventLoopNo;
dword          Ctrl::LoopLevel;

/*bool GetMouseLeft() {
	return false;
}

Point GetMousePos() {
	return Point(0,0);
}

void Ctrl::DoMouseFB(int event, Point p, int zdelta) {
	TODO
}

bool Ctrl::DoKeyFB(dword key, int cnt) {
	TODO
}*/

/*void Ctrl::MouseEventFB(Ptr<Ctrl> t, int event, Point p, int zdelta) {
	
}*/



void EnterGuiMutex() {}
bool TryEnterGuiMutex() {return 0;}
void LeaveGuiMutex() {}


NAMESPACE_UPP_END

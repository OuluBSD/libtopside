#include "CtrlCore.h"

NAMESPACE_UPP_BEGIN

VirtualGui* VirtualGuiPtr;


Bar::Bar() {
	TODO
}

Bar& Bar::Add(String title, Callback cb) {
	TODO
}

Bar& Bar::Separator() {
	TODO
}




bool GetMouseLeft() {
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
}

void Ctrl::PaintAll() {
	TODO
}

void Ctrl::EndSession() {
	TODO
}


NAMESPACE_UPP_END

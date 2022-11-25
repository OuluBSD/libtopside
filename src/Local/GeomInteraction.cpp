#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


String GeomInteraction::GetDesc() const {
	return String();
}

bool GeomInteraction::IsGeomDrawBegin() {
	return false;
}

bool GeomInteraction::Key(dword key, int count) {
	return false;
}

bool GeomInteraction::HotKey(dword key) {
	return false;
}





Image GeomInteraction2D::FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

Image GeomInteraction2D::MouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

void GeomInteraction2D::MouseEnter(Point frame_p, dword keyflags) {
	if (do_debug_draw)
		Refresh();
}

void GeomInteraction2D::MouseLeave() {
	if (do_debug_draw)
		Refresh();
}

Image GeomInteraction2D::CursorImage(Point p, dword keyflags) {
	return DefaultImages::Arrow;
}


NAMESPACE_TOPSIDE_END

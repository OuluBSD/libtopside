#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


GeomInteraction3D::GeomInteraction3D() {
	ignore_mouse = false;
	hidden = false;
	pending_redraw = true;
	pending_layout = true;
	pending_fx_redraw = true;
	
}

bool GeomInteraction3D::Is3D() const {
	return true;
}

GeomInteraction3D* GeomInteraction3D::Get3D() {
	return this;
}

bool GeomInteraction3D::Redraw(bool only_pending) {
	TODO
}

GeomInteraction3D* GeomInteraction3D::At(int i) {
	TODO
}

Point3f GeomInteraction3D::GetContentPoint(const Point& pt) {
	TODO
}

Image GeomInteraction3D::FrameMouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

Image GeomInteraction3D::MouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

void GeomInteraction3D::DeepMouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseWheelInFrame(Point3f p, int zdelta, dword keyflags) {
	TODO
}

void GeomInteraction3D::MouseEnter(Point3f frame_p, dword keyflags) {
	TODO
}

Image GeomInteraction3D::CursorImage(Point3f p, dword keyflags) {
	TODO
}

bool GeomInteraction3D::Dispatch(const CtrlEvent& e) {
	GeomInteraction::Dispatch(e);
	TODO
}


NAMESPACE_TOPSIDE_END

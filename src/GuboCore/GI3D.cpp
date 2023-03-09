#include "GuboCore.h"


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

Point3f GeomInteraction3D::GetContentPoint(const Point3f& pt) {
	TODO
}

Image GeomInteraction3D::FrameMouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

Image GeomInteraction3D::MouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

bool GeomInteraction3D::DeepMouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::DeepMouseMove(const Point3f& pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::DeepMouseWheel(const Point3f& pt, int zdelta, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseEventInFrameCaptured(int mouse_code, const Point3f& pt, dword keyflags) {
	TODO
}

bool GeomInteraction3D::MouseEventInFrame(int mouse_code, const Point3f& pt, dword keyflags) {
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

void GeomInteraction3D::SetFrameBox(const Cubf& c) {
	this->frame = c;
}

void GeomInteraction3D::Refresh() {
	TODO
}

GeomInteraction3D& GeomInteraction3D::HSizePos(int l, int r) {
	pos.htype = LogPos::HORZ;
	pos.l = l;
	pos.r = r;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::VSizePos(int t, int b) {
	pos.vtype = LogPos::VERT;
	pos.t = t;
	pos.b = b;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::BottomPos(int i, int size) {
	pos.vtype = LogPos::BOTTOM;
	pos.b = i;
	pos.h = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::TopPos(int i, int size) {
	pos.vtype = LogPos::TOP;
	pos.t = i;
	pos.h = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::LeftPos(int i, int size) {
	pos.htype = LogPos::LEFT;
	pos.l = i;
	pos.w = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::RightPos(int i, int size) {
	pos.htype = LogPos::RIGHT;
	pos.r = i;
	pos.w = size;
	return *this;
}


NAMESPACE_TOPSIDE_END

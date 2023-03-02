#include "CuboidCore.h"


NAMESPACE_TOPSIDE_BEGIN

bool      Gubo::do_debug_draw;


Gubo::Gubo() {
	/*ignore_mouse = false;
	hidden = false;
	pending_redraw = true;
	pending_layout = true;
	pending_fx_redraw = true;*/
	
}

void Gubo::AddFrame(GuboFrame& c) {
	// TODO
}

bool Gubo::Is3D() const {
	return true;
}

Gubo* Gubo::Get3D() {
	return this;
}

bool Gubo::Redraw(bool only_pending) {
	TODO
}

Gubo* Gubo::At(int i) {
	TODO
}

Point3f Gubo::GetContentPoint(const Point& pt) {
	TODO
}

Image Gubo::FrameMouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

Image Gubo::MouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	TODO
}

bool Gubo::DeepMouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool Gubo::DeepMouseMove(const Point3f& pt, dword keyflags) {
	TODO
}

bool Gubo::MouseMoveInFrame(Point3f pt, dword keyflags) {
	TODO
}

bool Gubo::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	TODO
}

bool Gubo::MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) {
	TODO
}

bool Gubo::MouseWheelInFrame(Point3f p, int zdelta, dword keyflags) {
	TODO
}

void Gubo::MouseEnter(Point3f frame_p, dword keyflags) {
	TODO
}

Image Gubo::CursorImage(Point3f p, dword keyflags) {
	TODO
}

bool Gubo::Dispatch(const CtrlEvent& e) {
	//GeomInteraction::Dispatch(e);
	TODO
}

void Gubo::SetFrameBox(const Cubf& c) {
	TODO //this->frame = c;
}

void Gubo::Refresh() {
	TODO
}

void Gubo::Close() {
	TODO
}

void Gubo::Layout() {
	TODO
}

void Gubo::CancelMode() {
	TODO
}

void Gubo::MouseLeave() {
	TODO
}

Cubf Gubo::GetFrameBox() const {
	TODO
}

Volf Gubo::GetFrameSize() const {
	TODO
}

bool Gubo::HasCapture() const {
	TODO
}

bool Gubo::HasMouse() const {
	TODO
}

bool Gubo::ReleaseCapture() {
	TODO
}

NAMESPACE_TOPSIDE_END


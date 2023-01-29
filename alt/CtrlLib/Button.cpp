#include "CtrlLib.h"


NAMESPACE_UPP

Button::Button() {

}

void Button::SetImage(Image& img) {
	this->img = img;
}

void Button::Paint(Draw& d) {
	Size sz = GetSize();
	Color bg = HasMouse() ? GrayColor(256 - 127) : GrayColor(256 - 64);
	d.DrawRect(sz, bg);
	
	if (img) {
		Size isz = img.GetSize();
		int x = (sz.cx - isz.cx) / 2;
		int y = (sz.cy - isz.cy) / 2;
		d.DrawImage(x, y, img);
	}
	
	d.DrawLine(0, 0, sz.cx - 1, 0, 1, White());
	d.DrawLine(0, 0, 0, sz.cy - 1, 1, White());
	d.DrawLine(0, sz.cy - 1, sz.cx - 1, sz.cy - 1, 1, Black());
	d.DrawLine(sz.cx - 1, 0, sz.cx - 1, sz.cy - 1, 1, Black());
}

void Button::LeftDown(Point p, dword keyflags) {
	is_pressed = true;
	Refresh();
}

void Button::LeftUp(Point p, dword keyflags) {
	WhenAction();
	is_pressed = false;
	Refresh();
}

void Button::MouseEnter(Point p, dword keyflags) {
	Refresh();
}

void Button::MouseLeave() {
	is_pressed = false;
	Refresh();
}

void Button::MouseMove(Point content_p, dword keyflags) {
	Refresh();
}









ButtonOption::ButtonOption() {

}

void ButtonOption::Tip(String s) {
	TODO
}

void ButtonOption::SetImage(Image i) {
	TODO
}

void ButtonOption::Set(bool b) {
	TODO
}

END_UPP_NAMESPACE

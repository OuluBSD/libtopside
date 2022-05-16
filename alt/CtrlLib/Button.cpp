#include "CtrlLib.h"


NAMESPACE_UPP

Button::Button() {
	
}

void Button::SetImage(Image& img) {
	this->img = img;
}

void Button::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, GrayColor(256-64));
	if (img) {
		Size isz = img.GetSize();
		int x = (sz.cx - isz.cx) / 2;
		int y = (sz.cy - isz.cy) / 2;
		d.DrawImage(x, y, img);
	}
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

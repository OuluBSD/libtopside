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

CH_STYLE(Button, Style, StyleNormal)
{
	CtrlsImageLook(look, CtrlsImg::I_B);
	monocolor[0] = monocolor[1] = monocolor[2] = monocolor[3] =
		Blend(Blend(SColorHighlight, SColorShadow), SColorLabel, 80);
	textcolor[0] = textcolor[1] = textcolor[2] = SColorLabel();
	textcolor[3] = SColorDisabled();
	font = StdFont();
	pressoffset = Point(0, 0);
	focusmargin = 3;
	overpaint = 0;
	transparent = true;
	focus_use_ok = true;
}

CH_STYLE(Button, Style, StyleEdge)
{
	Assign(Button::StyleNormal());
	CtrlsImageLook(look, CtrlsImg::I_EB);
}

Button& Button::SetStyle(const Button::Style& s)
{
	if(style != &s) {
		style = &s;
		RefreshLayout();
		Refresh();
	}
	return *this;
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

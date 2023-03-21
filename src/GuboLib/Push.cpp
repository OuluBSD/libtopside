#include "GuboLib.h"

NAMESPACE_UPP_BEGIN


Button2::Button2() {

}

void Button2::SetImage(Image& img) {
	this->img = img;
}

void Button2::Paint(Draw& d) {
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

void Button2::LeftDown(Point p, dword keyflags) {
	is_pressed = true;
	Refresh();
}

void Button2::LeftUp(Point p, dword keyflags) {
	WhenAction();
	is_pressed = false;
	Refresh();
}

void Button2::MouseEnter(Point p, dword keyflags) {
	Refresh();
}

void Button2::MouseLeave() {
	is_pressed = false;
	Refresh();
}

void Button2::MouseMove(Point content_p, dword keyflags) {
	Refresh();
}






void Button3::Paint(Draw3& d) {
	LOG("Button3::Paint: TODO");
}


NAMESPACE_UPP_END

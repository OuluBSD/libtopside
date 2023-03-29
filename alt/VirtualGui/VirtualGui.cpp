#include <CtrlCore/CtrlCore.h>


NAMESPACE_TOPSIDE_BEGIN


bool GetCtrl() {TODO}
bool GetAlt() {TODO}
bool GetShift() {TODO}


NAMESPACE_TOPSIDE_END



NAMESPACE_UPP


dword VirtualGui::GetOptions()
{
	return 0;
}

void VirtualGui::SetMouseCursor(const Image& image) {}
void VirtualGui::SetCaret(const Rect& caret) {}

#define FBIMG(x) const Image& FBImg::x() {static Image i; return i;}
FBIMG(close)
FBIMG(maximize)
FBIMG(overlap)
FBIMG(border)
FBIMG(title)
FBIMG(bgtitle)
FBIMG(Arrow)
FBIMG(Wait)
FBIMG(IBeam)
FBIMG(No)
FBIMG(SizeAll)
FBIMG(SizeHorz)
FBIMG(SizeVert)
FBIMG(SizeTopLeft)
FBIMG(SizeTop)
FBIMG(SizeTopRight)
FBIMG(SizeLeft)
FBIMG(SizeRight)
FBIMG(SizeBottomLeft)
FBIMG(SizeBottom)
FBIMG(SizeBottomRight)
FBIMG(Hand)
#undef FBIMG


#define STD_CURSOR(x) const Image& Image::x() {static Image i; return i;}
STD_CURSOR(Arrow)
STD_CURSOR(Wait)
STD_CURSOR(IBeam)
STD_CURSOR(No)
STD_CURSOR(SizeAll)
STD_CURSOR(SizeHorz)
STD_CURSOR(SizeVert)
STD_CURSOR(SizeTopLeft)
STD_CURSOR(SizeTop)
STD_CURSOR(SizeTopRight)
STD_CURSOR(SizeLeft)
STD_CURSOR(SizeRight)
STD_CURSOR(SizeBottomLeft)
STD_CURSOR(SizeBottom)
STD_CURSOR(SizeBottomRight)
STD_CURSOR(Hand)
#undef STD_CURSOR


END_UPP_NAMESPACE

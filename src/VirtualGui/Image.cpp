#include <CtrlCore/CtrlCore.h>

#ifdef VIRTUALGUI

NAMESPACE_UPP

#define LTIMING(x) // RTIMING(x)

void SetSurface(SystemDraw& w, int x, int y, int cx, int cy, const RGBA *pixels)
{
	GuiLock __;
	// Empty as CanSetSurface is false
}

void SetSurface(SystemDraw& w, const Rect& dest, const RGBA *pixels, Size psz, Point poff)
{
	GuiLock __;
	// Empty as CanSetSurface is false
}

#define IMAGECLASS FBImg
#define IMAGEFILE <VirtualGui/FB.iml>
#include <Draw/iml_source.h>

#define STD_CURSOR(name) \
const Image& Image::name() { return FBImg::name(); }

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


#if IS_TS_CORE
#define FBIMG(x) const Image& FBImg::x() {\
	static Image img;\
	if (img.IsEmpty())\
		img = StreamRaster::LoadFileAny(TS::ShareDirFile("imgs" DIR_SEPS "icons" DIR_SEPS #x ".png")); \
	return img;\
}
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
#endif

END_UPP_NAMESPACE

#endif

#ifndef _CtrlCore_Image_h_
#define _CtrlCore_Image_h_


NAMESPACE_UPP_BEGIN


struct FBImg {
	#define FBIMG(x) static const Image& x();// {static Image i; return i;}
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
};

struct CtrlImg {
	#define IMG(x) static const Image& x() {static Image i; return i;}
	IMG(Network)
	IMG(Dir)
	IMG(swap_color_cursor)
	#undef IMG
};

NAMESPACE_UPP_END

#endif

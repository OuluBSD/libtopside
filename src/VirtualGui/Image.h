#ifndef _VirtualGui_Image_h_
#define _VirtualGui_Image_h_

#if IS_TS_CORE

NAMESPACE_UPP_BEGIN


struct FBImg {
	
	
	#define FBIMG(x) static Image& x();
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


NAMESPACE_UPP_END

#endif

#endif

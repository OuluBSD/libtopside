#ifndef _CtrlCore_Image_h_
#define _CtrlCore_Image_h_


NAMESPACE_UPP_BEGIN


struct FBImg {
	#define IMG(x) static const Image& x() {static Image i; return i;}
	IMG(overlap)
	IMG(maximize)
	IMG(minimize)
	#undef IMG
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

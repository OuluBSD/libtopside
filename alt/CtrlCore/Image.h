#ifndef _CtrlCore_Image_h_
#define _CtrlCore_Image_h_


NAMESPACE_UPP_BEGIN


struct FBImg {
	#define IMG(x) static const Image& x();
	IMG(overlap)
	IMG(maximize)
	IMG(minimize)
	#undef IMG
};

NAMESPACE_UPP_END

#endif

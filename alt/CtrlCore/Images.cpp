#include "CtrlCore.h"


NAMESPACE_UPP

#define CTRLIMG(x) const Image& CtrlImg::x() {\
	static Image img;\
	if (img.IsEmpty())\
		img = StreamRaster::LoadFileAny(TS::ShareDirFile("imgs" DIR_SEPS "icons" DIR_SEPS #x ".png")); \
	return img;\
}
CTRLIMG(Network)
CTRLIMG(Dir)
CTRLIMG(swap_color_cursor)
#undef CTRLIMG

#define CTRLIMG(x) const Image& CtrlsImg::x() {\
	static Image img;\
	if (img.IsEmpty())\
		img = StreamRaster::LoadFileAny(TS::ShareDirFile("imgs" DIR_SEPS "ctrls" DIR_SEPS #x ".png")); \
	return img;\
}
CTRLIMG(I_B)
CTRLIMG(I_EB)
#undef CTRLIMG

END_UPP_NAMESPACE

#include "CtrlCore.h"


NAMESPACE_UPP

#define CTRLIMG(x) const Image& CtrlImg::x() {TODO}
CTRLIMG(Network)
CTRLIMG(Dir)
CTRLIMG(swap_color_cursor)
#undef CTRLIMG

END_UPP_NAMESPACE

#include "CtrlCore.h"


NAMESPACE_UPP

#define CTRLIMG(x) const Image& CtrlImg::x() {TODO}
CTRLIMG(Network)
CTRLIMG(Dir)
CTRLIMG(swap_color_cursor)
#undef CTRLIMG

#define CTRLIMG(x) const Image& CtrlsImg::x() {TODO}
CTRLIMG(I_B)
CTRLIMG(I_EB)
#undef CTRLIMG

END_UPP_NAMESPACE

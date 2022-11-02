#if 0
#include "EcsVirtualGui.h"
#include <Local/Local.h>

NAMESPACE_UPP

MAKE_STATIC(EcsVirtualGui, def_vgui);

END_UPP_NAMESPACE


INITBLOCK_(EcsVirtualGui) {
	TS::VirtualGui3DPtr = &UPP::def_vgui;
}
#endif

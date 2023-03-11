#include "GuboLib.h"

NAMESPACE_TOPSIDE_BEGIN


AtomVirtualGui3D::AtomVirtualGui3D() {
	
}

AtomVirtualGui3D::~AtomVirtualGui3D() {
	
}

bool AtomVirtualGui3D::Create(const Rect& rect, const char *title) {
	TODO
}

void AtomVirtualGui3D::Destroy() {
	TODO
}

dword       AtomVirtualGui3D::GetOptions() {TODO}
Size        AtomVirtualGui3D::GetSize() {TODO}
void        AtomVirtualGui3D::Quit() {TODO}


#if IS_TS_CORE

bool GetCtrl() {TODO}
bool GetAlt() {TODO}
bool GetShift() {TODO}

#endif

NAMESPACE_TOPSIDE_END

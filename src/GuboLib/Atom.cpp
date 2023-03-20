#include "GuboLib.h"
#include <SerialLib/SerialLib.h>


NAMESPACE_TOPSIDE_BEGIN
using namespace Serial;


AtomVirtualGui3D::AtomVirtualGui3D() {
	
}

AtomVirtualGui3D::~AtomVirtualGui3D() {
	Destroy();
}

bool AtomVirtualGui3D::Create(const Rect& rect, const char *title) {
	Machine& mach = TS::Serial::GetActiveMachine();
	wins = mach.Get<Gu::SurfaceSystem>();
	if (!wins)
		return false;
	
	mgr = wins->GetActiveScope();
	if (!mgr)
		return false;
	
	Size mgr_rect = rect.GetSize();
	mgr->SetFrameBox(mgr_rect);
	
	return true;
}

void AtomVirtualGui3D::Destroy() {
	mgr.Clear();
	wins.Clear();
}

dword AtomVirtualGui3D::GetOptions() {
	return 0;
}

Size AtomVirtualGui3D::GetSize() {
	ASSERT(mgr);
	if (mgr)
		return mgr->GetSize();
	return Size(0,0);
}

void AtomVirtualGui3D::Quit() {
	
}


#if IS_TS_CORE

bool GetCtrl() {TODO}
bool GetAlt() {TODO}
bool GetShift() {TODO}

#endif

NAMESPACE_TOPSIDE_END

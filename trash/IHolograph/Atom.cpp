#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


SpatialInteractionAtom::SpatialInteractionAtom() {
	
}

bool SpatialInteractionAtom::Initialize(const Script::WorldState& ws) {
	//if (SpatialInteractionManager::GetForCurrentView() == 0)
	//	SpatialInteractionManager::SetCurrentView(&mgr);
	
	return true;
}

void SpatialInteractionAtom::Uninitialize() {
	//if (SpatialInteractionManager::GetForCurrentView() == &mgr)
	//	SpatialInteractionManager::SetCurrentView(0);
	
}

bool SpatialInteractionAtom::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	TODO
	
}







HolographicScope& GetGlobalHolographicScope(int idx) {
	static const int count = 1;
	static HolographicScope scopes[count];
	if (idx >= 0 && idx < count)
		return scopes[idx];
	Panic("Invalid holographic scope index");
	NEVER();
}


template <class Gfx>
bool HolographicFboAtomT<Gfx>::Initialize(const Script::WorldState& ws) {
	TODO
	#if 0
	if (!FboAtomT<Gfx>::Initialize(ws))
		return false;
	#endif
	
	
	
	return true;
}

template <class Gfx>
bool HolographicFboAtomT<Gfx>::PostInitialize() {
	TODO
	#if 0
	if (!FboAtomT<Gfx>::PostInitialize())
		return false;
	#endif
	
	return true;
}

template <class Gfx>
void HolographicFboAtomT<Gfx>::Uninitialize() {
	TODO
	#if 0
	FboAtomT<Gfx>::Uninitialize();
	#endif
	
}

/*

TODO
dev_res.DeviceNotify::OnDeviceLost()
dev_res.DeviceNotify::OnDeviceRestored()
*/
GFX3D_EXCPLICIT_INITIALIZE_CLASS(HolographicFboAtomT)


NAMESPACE_PARALLEL_END


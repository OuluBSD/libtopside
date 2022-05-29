#include "IHolograph.h"

NAMESPACE_PARALLEL_BEGIN


SpatialInteractionAtom::SpatialInteractionAtom() {
	
}

bool SpatialInteractionAtom::Initialize(const Script::WorldState& ws) {
	if (SpatialInteractionManager::GetForCurrentView() == 0)
		SpatialInteractionManager::SetCurrentView(&mgr);
	
	return true;
}

void SpatialInteractionAtom::Uninitialize() {
	if (SpatialInteractionManager::GetForCurrentView() == &mgr)
		SpatialInteractionManager::SetCurrentView(0);
	
}

bool SpatialInteractionAtom::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	TODO
	
}


NAMESPACE_PARALLEL_END

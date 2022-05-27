#include "IHolograph.h"

NAMESPACE_PARALLEL_BEGIN


Callback VirtualRoomAnchor::WhenActiveChanged;


VirtualRoomAnchor::VirtualRoomAnchor() {
	
	#ifdef flagDX11
	dx11 = SpatialStageFrameOfReference::Current();
	TODO // set SpatialStageFrameOfReference::CurrentChanged event
	// maybe icpp initializer with this?
	#endif
	
	
	
}

void VirtualRoomAnchor::Clear() {
	
}



MAKE_STATIC(VirtualRoomAnchor, __def_vr_anchor);

VirtualRoomAnchor* GetActiveVirtualRoomAnchor() {
	return &__def_vr_anchor;
}





SpatialDynamicAnchor::SpatialDynamicAnchor() {
	parent = 0;
	position = vec3(0,0,0);
}

void SpatialDynamicAnchor::Clear() {
	
}

SpatialDynamicAnchor SpatialDynamicAnchor::GetRelative(const vec3& position) {
	SpatialDynamicAnchor a;
	#ifdef flagDX11
	TODO // from SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(vec3)
	#endif
	a.parent = this;
	a.position = position;
	return a;
}

SpatialDynamicAnchor* virt_dyn_anchor;
MAKE_STATIC(SpatialDynamicAnchor, hmd_anchor);

//NOTE: dx11 SpatialLocator::GetDefault()
SpatialDynamicAnchor& GetActiveSpatialDynamicAnchor() {
	if (!virt_dyn_anchor)
		virt_dyn_anchor = &hmd_anchor;
	return *virt_dyn_anchor;
}



NAMESPACE_PARALLEL_END

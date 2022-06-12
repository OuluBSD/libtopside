#include "IHolograph.h"

#if 0

NAMESPACE_PARALLEL_BEGIN


Callback SpatialStageFrameOfReference::WhenActiveChanged;


SpatialStageFrameOfReference::SpatialStageFrameOfReference() {
	
	#ifdef flagDX11
	dx11 = SpatialStageFrameOfReference::Current();
	TODO // set SpatialStageFrameOfReference::CurrentChanged event
	// maybe icpp initializer with this?
	#endif
	
	
	
}

void SpatialStageFrameOfReference::Clear() {
	
}

SpatialCoordinateSystem& SpatialStageFrameOfReference::GetCoordinateSystem() const {
	return *sys;
}



MAKE_STATIC(SpatialStageFrameOfReference, __def_vr_anchor);

SpatialStageFrameOfReference* GetActiveSpatialStageFrameOfReference() {
	return &__def_vr_anchor;
}





SpatialLocator::SpatialLocator() {
	parent = 0;
	position = vec3(0,0,0);
}

void SpatialLocator::Clear() {
	
}

SpatialCoordinateSystem& SpatialLocator::GetCoordinateSystem() const {
	return *sys;
}

SpatialLocator SpatialLocator::GetRelative(const vec3& position) {
	SpatialLocator a;
	#ifdef flagDX11
	TODO // from SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(vec3)
	#endif
	a.parent = this;
	a.position = position;
	return a;
}

SpatialLocator* virt_dyn_anchor;
MAKE_STATIC(SpatialLocator, hmd_anchor);

//NOTE: dx11 SpatialLocator::GetDefault()
SpatialLocator& GetActiveSpatialLocator() {
	if (!virt_dyn_anchor)
		virt_dyn_anchor = &hmd_anchor;
	return *virt_dyn_anchor;
}


SpatialInteractionSourceLocation* SpatialInteractionSourceProperties::TryGetLocation(const SpatialCoordinateSystem& coord_system) {
	TODO
}

const Array<SpatialInteractionSourceState>& SpatialInteractionManager::GetDetectedSourcesAtTimestamp(const PerceptionTimestamp& ts) {
	return detected_source_states;
}
	
	
	




void HolographicFramePrediction::operator=(const HolographicFramePrediction& s) {
	camera_poses <<= s.camera_poses;
	timestamp = s.timestamp;
}





HolographicFrame::HolographicFrame() {
	
}

HolographicFrame::HolographicFrame(const HolographicFrame& f) {
	*this = f;
}

void HolographicFrame::operator=(const HolographicFrame& s) {
	current = s.current;
	params = s.params;
}

const HolographicFramePrediction& HolographicFrame::GetCurrentPrediction() const {
	return current;
}

const HolographicCameraRenderingParameters& HolographicFrame::GetRenderingParameters(const HolographicCameraPose& cam_pose) const {
	TODO
	return params;
}

HolographicFramePresentResult HolographicFrame::PresentUsingCurrentPrediction() {
	TODO
}

void HolographicFrame::UpdateCurrentPrediction() {
	LOG("HolographicFrame::UpdateCurrentPrediction: TODO");
}






void HolographicSpace::CreateNextFrame() {
	
	
}








SpatialInteractionManager* cur_spatial_mgr;

SpatialInteractionManager* SpatialInteractionManager::GetForCurrentView() {
	//ASSERT(cur_spatial_mgr);
	return cur_spatial_mgr;
}

void SpatialInteractionManager::SetCurrentView(SpatialInteractionManager* mgr) {
	cur_spatial_mgr = mgr;
}


NAMESPACE_PARALLEL_END

#endif

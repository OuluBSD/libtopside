#include "EcsLib.h"


#if 0

NAMESPACE_OULU_BEGIN


HolographicScene::HolographicScene(
	Machine& core,
	HolographicSpace holographicSpace) :
		System(core) {}
		
bool HolographicScene::Initialize() {
	/*m_stageFrameOfReference = SpatialStageFrameOfReference::Current();
	
	// Create a fallback frame of reference 1.5 meters under the HMD when we start-up
	m_stationaryFrameOfReference = SpatialLocator::GetDefault().CreateStationaryFrameOfReferenceAtCurrentLocation(
				vec3 {0.0f, -1.5f, 0.0f});
	            
	m_spatialStageCurrentChanged = SpatialStageFrameOfReference::CurrentChanged(
				std::bind(&HolographicScene::OnCurrentStageChanged, this));*/
	return true;
}

void HolographicScene::Start() {
	//not here AddPredictionUpdateListener(engine.Get<MotionControllerSystem>()->As<IPredictionUpdateListener>());
}

void HolographicScene::Update(float) {
	//m_currentFrame = holospace.CreateNextFrame();
	
	OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicSpaceCreateNextFrame);
}

void HolographicScene::Uninitialize() {
	//SpatialStageFrameOfReference::CurrentChanged(m_spatialStageCurrentChanged);
	
	/*m_currentFrame = nullptr;
	m_stationaryFrameOfReference = nullptr;
	m_stageFrameOfReference = nullptr;*/
}

void HolographicScene::UpdateCurrentPrediction() {
	//m_currentFrame.UpdateCurrentPrediction();
	
	OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason::HolographicFrameUpdatePrediction);
}

void HolographicScene::OnCurrentStageChanged() {
	//std::unique_lock<std::shared_mutex> lock(m_mutex);
	//m_stageFrameOfReference = SpatialStageFrameOfReference::Current();
	Panic("TODO");
}

void HolographicScene::OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason) {
	HolographicFramePrediction prediction;
	prediction.ts.ts = timer.Seconds();
	
	for (const auto& listener : prediction_update_listeners.PurgeAndGetListeners()) {
		listener->OnPredictionUpdated(reason, prediction);
	}
}

void HolographicScene::AddPredictionUpdateListener(Ref<IPredictionUpdateListener> listener) {
	prediction_update_listeners.Add(std::move(listener));
}

void HolographicScene::RemovePredictionUpdateListener(Ref<IPredictionUpdateListener> listener) {
	prediction_update_listeners.Remove(std::move(listener));
}

/*SpatialCoordinateSystem HolographicScene::WorldCoordinateSystem() const {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	
	if (m_stageFrameOfReference) {
		return m_stageFrameOfReference.CoordinateSystem();
	}
	
	else {
		return m_stationaryFrameOfReference.CoordinateSystem();
	}
}*/

PerceptionTimestamp HolographicScene::CurrentTimestamp() const {
	return GetCurrentFrame().CurrentPrediction().Timestamp();
}

HolographicFrame HolographicScene::GetCurrentFrame() const {
	return cur_frame;
}

HolographicSpace HolographicScene::GetHolographicSpace() const {
	return holospace;
}


NAMESPACE_OULU_END

#endif

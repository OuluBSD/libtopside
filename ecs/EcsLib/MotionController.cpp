#include "EcsLib.h"

#if 0

using namespace SDK;

namespace {
	
String ControllerModelKeyToString(const Tuple<uint16, uint16, uint16, ControllerSourceHandedness>& tuple) {
	StringStream ss;
	
	ss << "MotionController_"
		<< Get<0>(tuple) << "_"
		<< Get<1>(tuple) << "_"
		<< Get<2>(tuple) << "_"
		<< static_cast<uint16>(Get<3>(tuple));
	
	return ss.GetResult();
}

void LoadAndCacheModel(
	const ControllerSource& source,
	Machine& engine) {
	Panic("TODO");
	/*const auto controllerModelName = ControllerModelKeyToString(GetControllerModelKey(source));
	
	auto pbrModelCache = machine.Get<PbrModelCache>();
	
	if (!pbrModelCache->ModelExists(controllerModelName)) {
		const auto pbrResources = machine.Get<HolographicRenderer>()->GetPbrResources();
		
		
		const auto model = co_await TryLoadRenderModelAsync(pbrResources, source);
		
		if (model) {
			pbrModelCache->RegisterModel(controllerModelName, model->Clone(*pbrResources));
		}
		
		else {
			debug_log("Failed to load model for source %d", source.Id());
		}
	}*/
}

}

NAMESPACE_OULU_BEGIN

void MotionControllerSystem::Start() {
	machine.Get<HolographicScene>()->AddPredictionUpdateListener(GetRefFromThis().As<IPredictionUpdateListener>());
	machine.Get<ControllerSystem>()->AddListener(GetRefFromThis().As<ControllerListenerInterface>());
}

void MotionControllerSystem::OnPredictionUpdated(
	IPredictionUpdateListener::PredictionUpdateReason /*reason*/,
	const HolographicFramePrediction& prediction) const {
	// Update the positions of the controllers based on the current timestamp.
	
	for (auto& sourceState : machine.Get<ControllerSystem>()->GetDetectedSourcesAtTimestamp(prediction.Timestamp())) {
	
		for (auto& componentSet : machine.Get<EntityStore>()->GetComponents<Transform, MotionControllerComponent>()) {
			auto[transform, controller] = componentSet;
			
			RefreshComponentsForSource(sourceState.Source());
			
			if (controller->IsSource(sourceState.Source())) {
				const ControllerSourceLocation location = sourceState.GetLocation();
				
				controller->location = location;
				
				if (location) {
					transform->position = location.GetPosition();
					transform->orientation = location.GetOrientation();
				}
			}
		}
	}
}

void MotionControllerSystem::Stop() {
	machine.Get<HolographicScene>()->RemovePredictionUpdateListener(GetRefFromThis().As<IPredictionUpdateListener>());
	machine.Get<ControllerSystem>()->RemoveListener(GetRefFromThis().As<ControllerListenerInterface>());
}

void MotionControllerSystem::RefreshComponentsForSource(const ControllerSourceDevice& source) const {

	for (auto& componentSet : machine.Get<EntityStore>()->GetComponentsWithEntity<MotionControllerComponent>()) {
		auto[entity, controller] = componentSet;
		
		ASSERT(controller->requestedHandedness != ControllerSourceHandedness::Unspecified, "Unspecified is not supported yet");
		
		int src = source.Handedness();
		int dst = controller->requestedHandedness;
		if (!controller->source && source.Handedness() == controller->requestedHandedness) {
			controller->source = source;
			LOG("Attached source id " << source.Id() << " to entity " << entity->Id() << " with requested handedness " << static_cast<uint32>(controller->requestedHandedness));
		}
	}
}

void MotionControllerSystem::OnSourceUpdated(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
	
		/*for (auto& componentSet : machine.Get<EntityStore>()->GetComponents<Model, MotionControllerComponent>()) {
			auto[pbr, controller] = componentSet;
			
			if (controller->IsSource(args.State().Source()) && controller->attachControllerModel) {
				// If we don't have a model yet, set the ModelName so PbrModelCache will update the model
				if (!pbr->model) {
					//pbr->ResetModel(ControllerModelKeyToString(GetControllerModelKey(controller->source)));
					Panic("TODO");
				}
				
				else {
					//ArticulateControllerModel(GetArticulateValues(args.State()), *pbr->model);
					Panic("TODO");
				}
			}
		}*/
	}
}

void MotionControllerSystem::OnSourceDetected(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
		// Attempt to load any controller models into the PbrModelCache
		(void)LoadAndCacheModel(args.State().Source(), engine);
		
		// Update any components with their new Source
		RefreshComponentsForSource(args.State().Source());
	}
}

void MotionControllerSystem::OnSourceLost(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
	
	for (auto& componentSet : machine.Get<EntityStore>()->GetComponents<MotionControllerComponent>()) {
			auto[controller] = componentSet;
			
			if (controller->IsSource(args.State().Source())) {
				controller->source.SetValid(false);
				controller->location.SetValid(false);
			}
		}
	}
}

bool MotionControllerComponent::IsSource(const ControllerSourceDevice& rhs) const {
	return (this->source && rhs) ? this->source.Id() == rhs.Id() : false;
}


NAMESPACE_OULU_END

#endif

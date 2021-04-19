#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


String ControllerModelKeyToString(const Tuple<uint16, uint16, uint16, ControllerSourceHandedness>& tuple) {
	StringStream ss;
	
	ss << "MotionController_"
	<< tuple.Get<0>() << "_"
	<< tuple.Get<1>() << "_"
	<< tuple.Get<2>() << "_"
	<< static_cast<uint16>(tuple.Get<3>());
	
	return ss.GetResult();
}

void LoadAndCacheModel(const ControllerSourceDevice& source, Machine& m) {
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


void MotionControllerSystem::Start() {
	machine.Get<HolographicScene>()->AddPredictionUpdateListener(GetSharedFromThis().As<IPredictionUpdateListener>());
	machine.Get<ControllerSystem>()->AddListener(GetSharedFromThis().As<ControllerListenerInterface>());
}

void MotionControllerSystem::OnPredictionUpdated(
	IPredictionUpdateListener::PredictionUpdateReason /*reason*/,
	const HolographicFramePrediction& prediction) const {
	
	for (auto& sourceState : machine.Get<ControllerSystem>()->GetDetectedSourcesAtTimestamp(prediction.Timestamp())) {
		EntityComponentVisitor<Transform, MotionControllerComponent> visitor(machine);
		for (; visitor; visitor++) {
			auto transform = visitor.Get<Transform>();
			auto controller = visitor.Get<MotionControllerComponent>();
			
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
	machine.Get<HolographicScene>()->RemovePredictionUpdateListener(GetSharedFromThis().As<IPredictionUpdateListener>());
	machine.Get<ControllerSystem>()->RemoveListener(GetSharedFromThis().As<ControllerListenerInterface>());
}

void MotionControllerSystem::RefreshComponentsForSource(const ControllerSourceDevice& source) const {
	EntityComponentVisitor<MotionControllerComponent> visitor(machine);
	
	for (; visitor; visitor++) {
		auto entity = *visitor;
		auto controller = visitor.Get<MotionControllerComponent>();
		
		ASSERT_(controller->requestedHandedness != ControllerSourceHandedness::Unspecified, "Unspecified is not supported yet");
		
		int src = source.Handedness();
		int dst = controller->requestedHandedness;
		if (!controller->source && source.Handedness() == controller->requestedHandedness) {
			controller->source = source;
			LOG("Attached source id " << source.Id() << " to entity " << (int)entity->Id() << " with requested handedness " << static_cast<uint32>(controller->requestedHandedness));
		}
	}
}

void MotionControllerSystem::OnSourceUpdated(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
		EntityComponentVisitor<Renderable, MotionControllerComponent> visitor(machine);
		
		for (; visitor; visitor++) {
			auto pbr = visitor.Get<Renderable>();
			auto controller = visitor.Get<MotionControllerComponent>();
			
			if (controller->IsSource(args.State().Source()) && controller->attachControllerModel) {
				/*if (!pbr->model) {
					//pbr->ResetModel(ControllerModelKeyToString(GetControllerModelKey(controller->source)));
					Panic("TODO");
				}
				
				else*/
				{
					//ArticulateControllerModel(GetArticulateValues(args.State()), *pbr->model);
					Panic("TODO");
				}
			}
		}
	}
}

void MotionControllerSystem::OnSourceDetected(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
		(void)LoadAndCacheModel(args.State().Source(), machine);
		
		RefreshComponentsForSource(args.State().Source());
	}
}

void MotionControllerSystem::OnSourceLost(const ControllerEventArgs& args) {
	if (args.State().Source().Kind() == ControllerSourceKind::Controller) {
		EntityComponentVisitor<MotionControllerComponent> visitor(machine);
	
		for (; visitor; visitor++) {
			auto controller = visitor.Get<MotionControllerComponent>();
			
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

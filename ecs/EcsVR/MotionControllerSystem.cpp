#include "EcsVR.h"


NAMESPACE_ECS_BEGIN



void MotionControllerComponent::Initialize() {
	Engine& e = GetEngine();
	Ref<MotionControllerSystem> sys = e.Get<MotionControllerSystem>();
	sys->Attach(this);
}

void MotionControllerComponent::Uninitialize() {
	Engine& e = GetEngine();
	Ref<MotionControllerSystem> sys = e.Get<MotionControllerSystem>();
	sys->Detach(this);
}

	
String ControllerModelKeyToString(const std::tuple<uint16, uint16, uint16, SpatialInteractionSourceHandedness>& tuple)
{
    String ss;

    ss << "MotionController_"
        << std::get<0>(tuple) << "_"
        << std::get<1>(tuple) << "_"
        << std::get<2>(tuple) << "_"
        << static_cast<uint16>(std::get<3>(tuple));

    return ss;
}

#if 0
Future<void> LoadAndCacheModel(
    const SpatialInteractionSource& source,
    Engine& engine)
{
	TODO
	/*
    const auto ctrl_model_name = ControllerModelKeyToString(ControllerRenderingT<Holo>::GetControllerModelKey(source));

    auto pbr_model_cache = engine.Get<PbrModelCache>();
    if (!pbr_model_cache->ModelExists(ctrl_model_name.c_str()))
    {
        const auto pbr_res = engine.Get<HolographicRenderingSystem>()->GetPbrResources();

        TODO //const auto model = co_await ControllerRenderingT<Holo>::TryLoadRenderModelAsync(pbr_res, source);

        if (model)
        {
            pbr_model_cache->RegisterModel(ctrl_model_name, model->Copy(*pbr_res));
        }
        else
        {
            LOG("Failed to load model for source %d", source.Id());
        }
    }
    */
}
#endif



void MotionControllerSystem::Attach(MotionControllerComponent* comp) {
	VectorFindAdd(comps, comp);
}

void MotionControllerSystem::Detach(MotionControllerComponent* comp) {
	VectorRemoveKey(comps, comp);
}


bool MotionControllerSystem::Initialize()
{
	if (!HolographicScopeBinder::Initialize())
		return false;
	
	return true;
}


void MotionControllerSystem::Uninitialize()
{
	HolographicScopeBinder::Uninitialize();
}

void MotionControllerSystem::Start()
{
	Engine& e = GetEngine();
    e.Get<HolographicScene>()->AddPredictionUpdateListener(AsRefT<PredictionUpdateListener>());
    e.Get<SpatialInteractionSystem>()->AddListener(AsRefT<SpatialInteractionListener>());
}


void MotionControllerSystem::OnPredictionUpdated(
    PredictionUpdateReason reason,
    const SpatialCoordinateSystem& coord_system,
    const HolographicFramePrediction& prediction)
{
	Engine& e = GetEngine();
	
    // Update the positions of the controllers based on the current timestamp.
    for (auto& src_state : s->spatial_interaction_manager.GetDetectedSourcesAtTimestamp(prediction.GetTimestamp()))
    {
        for (MotionControllerComponent* controller : comps) {
            TransformRef transform = controller->GetEntity()->Find<Transform>();

            RefreshComponentsForSource(src_state.GetSource());

            if (controller->IsSource(src_state.GetSource()))
            {
                SpatialInteractionSourceLocation* location = src_state.GetProperties().TryGetLocation(coord_system);

                controller->location = location;

                if (location && transform) {
                    transform->position = location->GetPosition();
                    transform->orientation = location->GetOrientation();
                }
            }
        }
    }
}

void MotionControllerSystem::Stop()
{
	TODO
    //machine.Get<HolographicScene>()->RemovePredictionUpdateListener(shared_from_this());
    //machine.Get<SpatialInteractionSystem>()->RemoveListener(shared_from_this());
}

void MotionControllerSystem::RefreshComponentsForSource(const SpatialInteractionSource& source)
{
	Engine& e = GetEngine();
	Ref<MotionControllerSystem> sys = e.Get<MotionControllerSystem>();
	const Vector<MotionControllerComponent*>& comps = sys->GetComponents();
	
	for (MotionControllerComponent* controller : comps) {
		EntityRef entity = controller->GetEntity();
		
        ASSERT_(controller->req_hand != SpatialInteractionSourceHandedness::Unspecified, "Unspecified is not supported yet");

        if (controller->source == nullptr && source.GetHandedness() == controller->req_hand)
        {
            controller->source = &source;
            LOG("Attached source id " << source.GetId() << " to entity " << entity->GetId() << " with requested handedness " << static_cast<uint32>(controller->req_hand));
        }
    }
}

#if 0
void MotionControllerSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args)
{
    if (args.State().Source().Kind() == SpatialInteractionSourceKind::Controller)
    {
        for (auto& comp_set : machine.Get<EntityStore>()->GetComponents<PbrRenderable, MotionControllerComponent>())
        {
            auto[pbr, controller] = comp_set;

            if (controller->IsSource(args.State().Source()) && controller->attach_ctrl_model)
            {
                // If we don't have a model yet, set the ModelName so PbrModelCache will update the model
                if (!pbr->Model)
                {
                    pbr->ResetModel(ControllerModelKeyToString(ControllerRenderingT<Holo>::GetControllerModelKey(controller->source)));
                }
                else
                {
                    ControllerRenderingT<Holo>::ArticulateControllerModel(ControllerRenderingT<Holo>::GetArticulateValues(args.State()), *pbr->Model);
                }
            }
        }
    }
}

void MotionControllerSystem::OnSourceDetected(const SpatialInteractionSourceEventArgs& args)
{
    if (args.State().Source().Kind() == SpatialInteractionSourceKind::Controller)
    {
        // Attempt to load any controller models into the PbrModelCache
        (void)LoadAndCacheModel(args.State().Source(), machine);

        // Update any components with their new Source
        RefreshComponentsForSource(args.State().Source());
    }
}

void MotionControllerSystem::OnSourceLost(const SpatialInteractionSourceEventArgs& args)
{
    if (args.State().Source().Kind() == SpatialInteractionSourceKind::Controller)
    {
        for (auto& comp_set : machine.Get<EntityStore>()->GetComponents<MotionControllerComponent>())
        {
            auto[controller] = comp_set;

            if (controller->IsSource(args.State().Source()))
            {
                controller->source = nullptr;
                controller->location = nullptr;
            }
        }
    }
}
#endif

bool MotionControllerComponent::IsSource(const SpatialInteractionSource& rhs) const
{
    return (this->source /*&& rhs*/) ? this->source->GetId() == rhs.GetId() : false;
}


NAMESPACE_ECS_END

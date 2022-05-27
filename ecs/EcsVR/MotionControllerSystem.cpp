#include "EcsVR.h"


NAMESPACE_ECS_BEGIN



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
        const auto pbr_res = engine.Get<HolographicRenderer>()->GetPbrResources();

        TODO //const auto model = co_await ControllerRenderingT<Holo>::TryLoadRenderModelAsync(pbr_res, source);

        if (model)
        {
            pbr_model_cache->RegisterModel(ctrl_model_name, model->Clone(*pbr_res));
        }
        else
        {
            LOG("Failed to load model for source %d", source.Id());
        }
    }
    */
}
#endif




void MotionControllerSystem::Start()
{
	TODO // func overrides
    //machine.Get<HolographicScene>()->AddPredictionUpdateListener(shared_from_this());
    //machine.Get<SpatialInteractionSystem>()->AddListener(shared_from_this());
}

#if 0
void MotionControllerSystem::OnPredictionUpdated(
    IPredictionUpdateListener::PredictionUpdateReason /*reason*/,
    const SpatialCoordinateSystem& coord_system,
    const HolographicFramePrediction& prediction)
{
    // Update the positions of the controllers based on the current timestamp.
    for (auto& src_state : machine.Get<SpatialInteractionSystem>()->GetInteractionManager().GetDetectedSourcesAtTimestamp(prediction.Timestamp()))
    {
        for (auto& comp_set : machine.Get<EntityStore>()->GetComponents<Transform, MotionControllerComponent>())
        {
            auto[transform, controller] = comp_set;

            RefreshComponentsForSource(src_state.Source());

            if (controller->IsSource(src_state.Source()))
            {
                const SpatialInteractionSourceLocation location = src_state.Properties().TryGetLocation(coord_system);

                controller->location = location;

                if (location)
                {
                    transform->position = location_util::position(location);
                    transform->orientation = location_util::orientation(location);
                }
            }
        }
    }
}
#endif

void MotionControllerSystem::Stop()
{
	TODO
    //machine.Get<HolographicScene>()->RemovePredictionUpdateListener(shared_from_this());
    //machine.Get<SpatialInteractionSystem>()->RemoveListener(shared_from_this());
}

#if 0
void MotionControllerSystem::RefreshComponentsForSource(const SpatialInteractionSource& source)
{
    for (auto& comp_set : machine.Get<EntityStore>()->GetComponentsWithEntity<MotionControllerComponent>())
    {
        auto[entity, controller] = comp_set;

        fail_fast_if(controller->req_hand == SpatialInteractionSourceHandedness::Unspecified, "Unspecified is not supported yet");

        if (controller->source == nullptr && source.Handedness() == controller->req_hand)
        {
            controller->source = source;
            LOG("Attached source id %d to entity %lld with requested handedness %d", source.Id(), entity->Id(), static_cast<uint32>(controller->req_hand));
        }
    }
}

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

bool MotionControllerComponent::IsSource(const SpatialInteractionSource& rhs) const
{
    return (this->source && rhs) ? this->source.Id() == rhs.Id() : false;
}

#endif

NAMESPACE_ECS_END
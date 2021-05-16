#include "WinLib.h"



namespace {

std::string ControllerModelKeyToString(const std::tuple<uint16_t, uint16_t, uint16_t, SpatialInteractionSourceHandedness>& tuple)
{
    std::stringstream ss;

    ss << "MotionController_"
        << std::get<0>(tuple) << "_"
        << std::get<1>(tuple) << "_"
        << std::get<2>(tuple) << "_"
        << static_cast<uint16_t>(std::get<3>(tuple));

    return ss.str();
}

std::future<void> LoadAndCacheModel(
    const SpatialInteractionSource& source,
    Engine& engine)
{
    const auto controllerModelName = ControllerModelKeyToString(ControllerRendering::GetControllerModelKey(source));

    auto pbr_model_cache = engine.Get<PbrModelCache>();
    if (!pbr_model_cache->ModelExists(controllerModelName.c_str()))
    {
        const auto pbr_res = engine.Get<HolographicRenderer>()->GetPbrResources();

        const auto model = co_await ControllerRendering::TryLoadRenderModelAsync(pbr_res, source);

        if (model) 
        {
            pbr_model_cache->RegisterModel(controllerModelName, model->Clone(*pbr_res));
        }
        else
        {
            debug_log("Failed to load model for source %d", source.Id());
        }
    }
}

}

NAMESPACE_TOPSIDE_BEGIN

void MotionControllerSystem::Start()
{
    machine.Get<HolographicScene>()->AddPredictionUpdateListener(shared_from_this());
    machine.Get<SpatialInteractionSystem>()->AddListener(shared_from_this());
}

void MotionControllerSystem::OnPredictionUpdated(
    IPredictionUpdateListener::PredictionUpdateReason /*reason*/,
    const SpatialCoordinateSystem& coordinateSystem,
    const HolographicFramePrediction& prediction)
{
    // Update the positions of the controllers based on the current timestamp.
    for (auto& sourceState : machine.Get<SpatialInteractionSystem>()->GetInteractionManager().GetDetectedSourcesAtTimestamp(prediction.Timestamp()))
    {
        for (auto& comp_set : machine.Get<EntityStore>()->GetComponents<Transform, MotionControllerComponent>())
        {
            auto[transform, controller] = comp_set;

            RefreshComponentsForSource(sourceState.Source());

            if (controller->IsSource(sourceState.Source()))
            {
                const SpatialInteractionSourceLocation location = sourceState.Properties().TryGetLocation(coordinateSystem);

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

void MotionControllerSystem::Stop()
{
    machine.Get<HolographicScene>()->RemovePredictionUpdateListener(shared_from_this());
    machine.Get<SpatialInteractionSystem>()->RemoveListener(shared_from_this());
}

void MotionControllerSystem::RefreshComponentsForSource(const SpatialInteractionSource& source)
{
    for (auto& comp_set : machine.Get<EntityStore>()->GetComponentsWithEntity<MotionControllerComponent>())
    {
        auto[entity, controller] = comp_set;

        fail_fast_if(controller->req_hand == SpatialInteractionSourceHandedness::Unspecified, "Unspecified is not supported yet");

        if (controller->source == nullptr && source.Handedness() == controller->req_hand)
        {
            controller->source = source;
            debug_log("Attached source id %d to entity %lld with requested handedness %d", source.Id(), entity->Id(), static_cast<uint32_t>(controller->req_hand));
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

            if (controller->IsSource(args.State().Source()) && controller->attachControllerModel)
            {
                // If we don't have a model yet, set the ModelName so PbrModelCache will update the model
                if (!pbr->Model)
                {
                    pbr->ResetModel(ControllerModelKeyToString(ControllerRendering::GetControllerModelKey(controller->source)));
                }
                else
                {
                    ControllerRendering::ArticulateControllerModel(ControllerRendering::GetArticulateValues(args.State()), *pbr->Model);
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

NAMESPACE_TOPSIDE_END

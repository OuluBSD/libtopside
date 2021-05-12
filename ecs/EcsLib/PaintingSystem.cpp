#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


void PaintingInteractionSystem::Start()
{
    GetMachine().Get<ToolboxSystem>()->AddToolSystem(AsRefT());
}

void PaintingInteractionSystem::Stop()
{
    GetMachine().Get<ToolboxSystem>()->RemoveToolSystem(AsRefT());
}

String PaintingInteractionSystem::GetInstructions() const 
{
    return "Press and hold trigger to paint.\n\n"
           "Touch and press touchpad to choose brush color.\n\n"
           "Hold grasp button to move strokes around. While holding grasp tilt thumbstick forward/backward to translate strokes.\n\n"
           "Push thumbstick down to delete strokes.\n\n";
}

String PaintingInteractionSystem::GetDisplayName() const
{
    return "Painting";
}

EntityRef PaintingInteractionSystem::CreateToolSelector() const
{
    auto selector = GetMachine().Get<EntityStore>()->GetRoot()->Create<ToolSelectorPrefab>();

    selector->Get<PbrRenderable>()->ResetModel("PaintBrush");
    selector->Get<Transform>()->orientation = MakeQuaternionFromAxisAngle({ 1, 0, 0 }, M_PI / 1.5f);
    selector->Get<ToolSelectorKey>()->type = GetType();

    return selector;
}

void PaintingInteractionSystem::Register(LinkedList<EntityRef>& entities)
{
    ToolSystem::Register(std::move(entities));

    auto es = GetMachine().Get<EntityStore>();

    for (auto& entity : m_entities)
    {
        const auto& selected_color = colors[0];

        auto paint_brush = es->GetRoot()->Create<PaintBrush>();
        paint_brush->Get<PbrRenderable>()->color = selected_color;
        paint_brush->Get<MotionControllerComponent>()->req_hand = entity->Get<MotionControllerComponent>()->req_hand;

        auto touchpad_indicator = es->GetRoot()->Create<StaticSphere>();
        touchpad_indicator->Get<Transform>()->size = { 0.005f, 0.005f, 0.005f };
        touchpad_indicator->Get<PbrRenderable>()->color = Colors::Gray;

        PaintComponentRef paint = entity->Get<PaintComponent>();

        paint->selected_color = selected_color;
        paint->paint_brush = paint_brush;
        paint->touchpad_indicator = touchpad_indicator;
        
        for (auto color : colors)
        {
            auto colorPicker = es->GetRoot()->Create<StaticSphere>();
            colorPicker->Get<Transform>()->size = { 0.01f, 0.01f, 0.01f };
            colorPicker->Get<PbrRenderable>()->color = color;
            paint->clr_pick_objects.Add(colorPicker);
        }

        paint->beam = es->GetRoot()->Create<StaticCube>();
        paint->beam->Get<Transform>()->size = { 0.005f, 0.005f, 10.0f };
        paint->beam->Get<PbrRenderable>()->color = Colors::Aquamarine;

        paint->SetEnabled(false);
    }

    GetMachine().Get<SpatialInteractionSystem>()->AddListener(AsRefT());
}

void PaintingInteractionSystem::Activate(EntityRef entity)
{
    ToolSystem::Activate(entity);

    // Stop rendering the controller
    entity->Get<PbrRenderable>()->SetEnabled(false);
}

void PaintingInteractionSystem::Deactivate(EntityRef entity)
{
    entity->Get<PbrRenderable>()->SetEnabled(true);

    PaintComponentRef paint = entity->Get<PaintComponent>();

    // Copy out the strokes from the component so they can persist in the world.
    if (paint->stroke_in_progress)
    {
        paint->strokes.Add(std::move(paint->stroke_in_progress));
    }

    if (paint->strokes.GetCount())
    {
        persistent_strokes.Add(std::move(paint->strokes));
    }

    ToolSystem::Deactivate(entity);
}

void PaintingInteractionSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args)
{
    if (args.PressKind() == SpatialInteractionPressKind::Thumbstick)
    {
        // Destroy all the paint strokes currently active
        for (auto& enabledEntity : GetEnabledEntities())
        {
            auto entity = enabledEntity.Get<EntityRef>();
            auto paint = enabledEntity.Getget<PaintComponentRef>();
            
            for (auto& stroke : paint->strokes)
            {
                stroke->Destroy();
            }

            paint->strokes.Clear();

            if (paint->stroke_in_progress)
            {
                paint->stroke_in_progress->Destroy();
                paint->stroke_in_progress.Clear();
            }
        }

        // Destroy all the persistent strokes
        for (auto& strokeGroup : persistent_strokes)
        {
            for (auto& stroke : strokeGroup)
            {
                stroke->Destroy();
            }
        }

        persistent_strokes.Clear();
    }
}

void PaintingInteractionSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args)
{
    const auto& sourceState = args.State();
    const auto& source = sourceState.Source();

    if (auto enabledEntity = TryGetEntityFromSource(source))
    {
        bool newStrokeStarted = false;
        auto entity = std::get<Entity*>(*enabledEntity);
        auto paint = std::get<PaintComponent*>(*enabledEntity);

        const auto& paint_brushModel = paint->paint_brush->Get<PbrRenderable>()->Model;
        if (paint_brushModel && !paint->brush_tip_offset_from_holding_pose)
        {
            Optional<Pbr::NodeIndex_t> touchNode = paint_brushModel->FindFirstNode("PaintTip");
            if (touchNode)
            {
                // Calcluate paint tip offset from holding pose
                // we use offset as it does not rely on the current transform of the model
                // we initialize it once as the value will not change
                const auto brushTipWorldTransform = paint_brushModel->GetNodeWorldTransform(touchNode.value());
                const auto paint_brushWorldTransform = paint_brushModel->GetNode(Pbr::RootNodeIndex).GetTransform();
                paint->brush_tip_offset_from_holding_pose = brushTipWorldTransform * XMMatrixInverse(nullptr, paint_brushWorldTransform);
            }
        }

        const auto controller = entity->Get<MotionControllerComponent>();
        if (controller->IsSource(source))
        {
            const auto& controllerProperties = sourceState.ControllerProperties();

            paint->touchpad_x = static_cast<float>(controllerProperties.TouchpadX());
            paint->touchpad_y = static_cast<float>(controllerProperties.TouchpadY());

            paint->thumbstick_x = static_cast<float>(controllerProperties.ThumbstickX());
            paint->thumbstick_y = static_cast<float>(controllerProperties.ThumbstickY());

            if (paint->cur_state == PaintComponent::State::Idle)
            {
                if (sourceState.IsSelectPressed())
                {
                    paint->cur_state = PaintComponent::State::Painting;
                    newStrokeStarted = true;
                }
                else if (sourceState.IsGrasped())
                {
                    paint->cur_state = PaintComponent::State::Manipulating;
                }
                else if (controllerProperties.IsTouchpadTouched())
                {
                    paint->cur_state = PaintComponent::State::ColorSelection;
                }
            }
            else if (paint->cur_state == PaintComponent::State::Painting)
            {
                if (sourceState.IsSelectPressed() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;
                }
            }
            else if (paint->cur_state == PaintComponent::State::Manipulating)
            {
                if (sourceState.IsGrasped() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;

                    paint->prev_manip_loc = nullptr;
                }
            }
            else if (paint->cur_state == PaintComponent::State::ColorSelection)
            {
                if (paint->wait_touchpad_release == false)
                {
                    if (controllerProperties.IsTouchpadPressed())
                    {
                        paint->wait_touchpad_release = true;
                        paint->selected_color = SelectColor(paint->touchpad_x, paint->touchpad_y);

                        SpatialInputUtilities::Haptics::SendContinuousBuzzForDuration(sourceState.Source(), 100ms);
                    }
                }

                if (controllerProperties.IsTouchpadPressed() == false)
                {
                    paint->wait_touchpad_release = false;
                }

                if (controllerProperties.IsTouchpadTouched() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;
                }
            }

            if (paint->cur_state == PaintComponent::State::Painting)
            {
                // Start new stroke
                if (newStrokeStarted)
                {
                    paint->stroke_in_progress = GetMachine().Get<EntityStore>()->Create<PaintStroke>();
                    paint->stroke_in_progress->Get<PbrRenderable>()->Color = paint->selected_color;

                    paint->strokes.Add(paint->stroke_in_progress);
                }

                auto properties = sourceState.Properties();

                // We generate stroke points in source updated using the arguments provided by the event
                // This will result in a smoother paint stroke
                if (auto location = properties.TryGetLocation(GetMachine().Get<HolographicScene>()->WorldCoordinateSystem()))
                {
                    if (paint->brush_tip_offset_from_holding_pose && paint->stroke_in_progress)
                    {
                        mat4 paintToWorld;
                        XMStoreFloat4x4(&paintToWorld, *paint->brush_tip_offset_from_holding_pose * XMLoadFloat4x4(&location_util::matrix(location)));

                        paint->stroke_in_progress->Get<PaintStrokeComponent>()->AddPoint(mat4_util::remove_scale(paintToWorld), paint_tip_thickness);
                    }
                }
            }
        }
    }
}

void PaintingInteractionSystem::OnSourceReleased(const SpatialInteractionSourceEventArgs& args)
{
}

void PaintingInteractionSystem::Update(double dt)
{
    for (auto& enabledEntity : GetEnabledEntities())
    {
        auto entity = std::get<Entity*>(enabledEntity);
        auto paint = std::get<PaintComponent*>(enabledEntity);

        const MotionControllerComponent* controller = entity->Get<MotionControllerComponent>();

        paint->beam->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::Manipulating);

        // Set properties required for rendering
        paint->touchpad_indicator->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
        for (auto& go : paint->clr_pick_objects)
        {
            go->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
        }

        const bool showController = paint->cur_state == PaintComponent::State::Manipulating;
            
        entity->Get<PbrRenderable>()->SetEnabled(showController);
        paint->paint_brush->Get<PbrRenderable>()->SetEnabled(!showController);

        if (auto location = controller->location)
        {
            const vec3 position = location_util::position(location);
            const quaternion orientation = location_util::orientation(location);

            const mat32 paintTipColor = paint->cur_state == PaintComponent::State::ColorSelection ? SelectColor(paint->touchpad_x, paint->touchpad_y) : paint->selected_color;
            paint->paint_brush->Get<PbrRenderable>()->Color = paintTipColor;

            if (paint->cur_state == PaintComponent::State::Manipulating)
            {
                // Update the paint strokes based on the change in location
                if (paint->prev_manip_loc)
                {
                    const vec3 previousPosition = location_util::position(paint->prev_manip_loc);
                    const quaternion previousOrientation = location_util::orientation(paint->prev_manip_loc);

                    const quaternion orientationDelta = orientation * inverse(previousOrientation);

                    const mat4 manipulationTransform = make_mat4_translation(-previousPosition) * make_mat4_from_quaternion(orientationDelta) * make_mat4_translation(position);

                    for (auto stroke : paint->strokes)
                    {
                        stroke->Get<Transform>()->SetFromMatrix(stroke->Get<Transform>()->GetMatrix() * manipulationTransform);
                    }
                }

                paint->prev_manip_loc = location;

                // Move the paint strokes based on manipulation changes

                constexpr double ThumbstickMovementThresholdPercent = 0.2f; // Deadzone to prevent slight thumbstick movement
                constexpr float MovementSpeedInMetersPerSecond = 2.5f;

                if (auto pointerPose = location.SourcePointerPose())
                {
                    const vec3 position = pointerPose.Position();
                    const vec3 forward = pointerPose.ForwardDirection();

                    if (abs(paint->thumbstick_y) > ThumbstickMovementThresholdPercent)
                    {
                        const vec3 forwardMovement = forward * paint->thumbstick_y * MovementSpeedInMetersPerSecond * dt;

                        // Move all paintings along beam path
                        for (auto& stroke : paint->strokes)
                        {
                            stroke->Get<Transform>()->position += forwardMovement;
                        }
                    }

                    paint->beam->Get<Transform>()->position = position + forward * (paint->beam->Get<Transform>()->scale.z * 0.5f);
                    paint->beam->Get<Transform>()->orientation = pointerPose.Orientation();
                }
            }
            else if (paint->cur_state == PaintComponent::State::ColorSelection)
            {
                constexpr float colorpickerDiameter = 0.025f;
                constexpr float colorpickerHeight = 0.015f;

                const mat4 paint_brushToWorld = paint->paint_brush->Get<Transform>()->GetMatrix();

                const vec3 touchpad_indicatorOnPaintBrush = { paint->touchpad_x * colorpickerDiameter, colorpickerHeight, paint->touchpad_y * colorpickerDiameter * -1 };
                const vec3 touchpad_indicatorInWorld = transform(touchpad_indicatorOnPaintBrush, paint_brushToWorld);

                paint->touchpad_indicator->Get<Transform>()->position = touchpad_indicatorInWorld;

                // Color picker plane defined as slightly above the touchpad with the same orientation as the touchpad
                const int numColors = static_cast<int>(paint->clr_pick_objects.GetCount());

                for (int i = 0; i < numColors; ++i)
                {
                    const float angle = (static_cast<float>(i*-1 - 1) / static_cast<float>(numColors)) * (2 * M_PI) - M_PI;
                    const float nextAngle = (static_cast<float>((i + 1)*-1 - 1) / static_cast<float>(numColors)) * (2 * M_PI) - M_PI;
                    const float angleDelta = (nextAngle - angle) / 2; // Want color icon to appear in the middle of the segment, not the start.
                    const float finalAngle = angle - angleDelta;

                    const vec3 colorIndicatorOnPaintBrush = { std::cos(finalAngle) * colorpickerDiameter, colorpickerHeight, std::sin(finalAngle) * colorpickerDiameter };
                    const vec3 colorIndicatorInWorld = transform(colorIndicatorOnPaintBrush, paint_brushToWorld);

                    paint->clr_pick_objects[i]->Get<Transform>()->position = colorIndicatorInWorld;
                }
            }
        }
    }
}

vec4 PaintingInteractionSystem::SelectColor(double x, double y)
{
    if (x == 0 && y == 0)
    {
        return colors.back();
    }

    constexpr double min = -M_PI;
    constexpr double max = +M_PI;
    double angle = std::atan2(y, x);
    int index = static_cast<int>(std::round((angle - min) / (max - min) * (colors.GetCount() - 1)));
    return colors[index];
}

void PaintComponent::SetEnabled(bool enable)
{
    Enableable::SetEnabled(enable);

    for (auto& colorPicker : clr_pick_objects) {
        colorPicker->SetEnabled(enable);
    }

    if (touchpad_indicator) {
        touchpad_indicator->SetEnabled(enable);
    }

    if (paint_brush) {
        paint_brush->SetEnabled(enable);
    }

    if (beam) {
        beam->SetEnabled(enable);
    }
}

void PaintComponent::Destroy() 
{
    Destroyable::Destroy();

    for (auto& colorPicker : clr_pick_objects) {
        colorPicker->Destroy();
    }

    if (touchpad_indicator) {
        touchpad_indicator->Destroy();
    }

    if (paint_brush) {
        paint_brush->Destroy();
    }

    if (beam) {
        beam->Destroy();
    }
}


NAMESPACE_OULU_END

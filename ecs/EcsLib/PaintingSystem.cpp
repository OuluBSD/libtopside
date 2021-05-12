#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


void PaintingInteractionSystem::Start()
{
    GetMachine().Get<ToolboxSystem>()->AddToolSystem(AsRef<ToolSystemBase>());
}

void PaintingInteractionSystem::Stop()
{
    GetMachine().Get<ToolboxSystem>()->RemoveToolSystem(AsRef<ToolSystemBase>());
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

void PaintingInteractionSystem::Register(const LinkedList<EntityRef>& entities)
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
            auto color_picker = es->GetRoot()->Create<StaticSphere>();
            color_picker->Get<Transform>()->size = { 0.01f, 0.01f, 0.01f };
            color_picker->Get<PbrRenderable>()->color = color;
            paint->clr_pick_objects.Add(color_picker);
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
        for (auto& enabled_entity : GetEnabledEntities())
        {
            auto entity = enabled_entity.Get<EntityRef>();
            auto paint = enabled_entity.Getget<PaintComponentRef>();
            
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
        for (auto& stroke_group : persistent_strokes)
        {
            for (auto& stroke : stroke_group)
            {
                stroke->Destroy();
            }
        }

        persistent_strokes.Clear();
    }
}

void PaintingInteractionSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args)
{
    const auto& source_state = args.State();
    const auto& source = source_state.Source();

    if (auto enabled_entity = TryGetEntityFromSource(source))
    {
        bool new_stroke_started = false;
        auto entity = std::get<Entity*>(*enabled_entity);
        auto paint = std::get<PaintComponent*>(*enabled_entity);

        const auto& paint_brush_model = paint->paint_brush->Get<PbrRenderable>()->Model;
        if (paint_brush_model && !paint->brush_tip_offset_from_holding_pose)
        {
            Optional<Pbr::NodeIndex_t> touch_node = paint_brush_model->FindFirstNode("PaintTip");
            if (touch_node)
            {
                // Calcluate paint tip offset from holding pose
                // we use offset as it does not rely on the current transform of the model
                // we initialize it once as the value will not change
                const auto brush_tip_world_transform = paint_brush_model->GetNodeWorldTransform(touch_node.value());
                const auto paint_brush_world_transform = paint_brush_model->GetNode(Pbr::RootNodeIndex).GetTransform();
                paint->brush_tip_offset_from_holding_pose = brush_tip_world_transform * XMMatrixInverse(nullptr, paint_brush_world_transform);
            }
        }

        const auto controller = entity->Get<MotionControllerComponent>();
        if (controller->IsSource(source))
        {
            const auto& controller_properties = source_state.ControllerProperties();

            paint->touchpad_x = static_cast<float>(controller_properties.TouchpadX());
            paint->touchpad_y = static_cast<float>(controller_properties.TouchpadY());

            paint->thumbstick_x = static_cast<float>(controller_properties.ThumbstickX());
            paint->thumbstick_y = static_cast<float>(controller_properties.ThumbstickY());

            if (paint->cur_state == PaintComponent::State::Idle)
            {
                if (source_state.IsSelectPressed())
                {
                    paint->cur_state = PaintComponent::State::Painting;
                    new_stroke_started = true;
                }
                else if (source_state.IsGrasped())
                {
                    paint->cur_state = PaintComponent::State::Manipulating;
                }
                else if (controller_properties.IsTouchpadTouched())
                {
                    paint->cur_state = PaintComponent::State::ColorSelection;
                }
            }
            else if (paint->cur_state == PaintComponent::State::Painting)
            {
                if (source_state.IsSelectPressed() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;
                }
            }
            else if (paint->cur_state == PaintComponent::State::Manipulating)
            {
                if (source_state.IsGrasped() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;

                    paint->prev_manip_loc = nullptr;
                }
            }
            else if (paint->cur_state == PaintComponent::State::ColorSelection)
            {
                if (paint->wait_touchpad_release == false)
                {
                    if (controller_properties.IsTouchpadPressed())
                    {
                        paint->wait_touchpad_release = true;
                        paint->selected_color = SelectColor(paint->touchpad_x, paint->touchpad_y);

                        SpatialInputUtilities::Haptics::SendContinuousBuzzForDuration(source_state.Source(), 100ms);
                    }
                }

                if (controller_properties.IsTouchpadPressed() == false)
                {
                    paint->wait_touchpad_release = false;
                }

                if (controller_properties.IsTouchpadTouched() == false)
                {
                    paint->cur_state = PaintComponent::State::Idle;
                }
            }

            if (paint->cur_state == PaintComponent::State::Painting)
            {
                // Start new stroke
                if (new_stroke_started)
                {
                    paint->stroke_in_progress = GetMachine().Get<EntityStore>()->Create<PaintStroke>();
                    paint->stroke_in_progress->Get<PbrRenderable>()->Color = paint->selected_color;

                    paint->strokes.Add(paint->stroke_in_progress);
                }

                auto properties = source_state.Properties();

                // We generate stroke points in source updated using the arguments provided by the event
                // This will result in a smoother paint stroke
                if (auto location = properties.TryGetLocation(GetMachine().Get<HolographicScene>()->WorldCoordinateSystem()))
                {
                    if (paint->brush_tip_offset_from_holding_pose && paint->stroke_in_progress)
                    {
                        mat4 paint_to_world;
                        XMStoreFloat4x4(&paint_to_world, *paint->brush_tip_offset_from_holding_pose * XMLoadFloat4x4(&location_util::matrix(location)));

                        paint->stroke_in_progress->Get<PaintStrokeComponent>()->AddPoint(mat4_util::remove_scale(paint_to_world), paint_tip_thickness);
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
    for (auto& enabled_entity : GetEnabledEntities())
    {
        auto entity = std::get<Entity*>(enabled_entity);
        auto paint = std::get<PaintComponent*>(enabled_entity);

        const MotionControllerComponent* controller = entity->Get<MotionControllerComponent>();

        paint->beam->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::Manipulating);

        // Set properties required for rendering
        paint->touchpad_indicator->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
        for (auto& go : paint->clr_pick_objects)
        {
            go->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
        }

        const bool show_controller = paint->cur_state == PaintComponent::State::Manipulating;
            
        entity->Get<PbrRenderable>()->SetEnabled(show_controller);
        paint->paint_brush->Get<PbrRenderable>()->SetEnabled(!show_controller);

        if (auto location = controller->location)
        {
            const vec3 position = location_util::position(location);
            const quaternion orientation = location_util::orientation(location);

            const mat32 paint_tip_color = paint->cur_state == PaintComponent::State::ColorSelection ? SelectColor(paint->touchpad_x, paint->touchpad_y) : paint->selected_color;
            paint->paint_brush->Get<PbrRenderable>()->Color = paint_tip_color;

            if (paint->cur_state == PaintComponent::State::Manipulating)
            {
                // Update the paint strokes based on the change in location
                if (paint->prev_manip_loc)
                {
                    const vec3 previous_position = location_util::position(paint->prev_manip_loc);
                    const quaternion previous_orientation = location_util::orientation(paint->prev_manip_loc);

                    const quaternion orientation_delta = orientation * inverse(previous_orientation);

                    const mat4 manipulation_transform = make_mat4_translation(-previous_position) * make_mat4_from_quaternion(orientation_delta) * make_mat4_translation(position);

                    for (auto stroke : paint->strokes)
                    {
                        stroke->Get<Transform>()->SetFromMatrix(stroke->Get<Transform>()->GetMatrix() * manipulation_transform);
                    }
                }

                paint->prev_manip_loc = location;

                // Move the paint strokes based on manipulation changes

                constexpr double ThumbstickMovementThresholdPercent = 0.2f; // Deadzone to prevent slight thumbstick movement
                constexpr float MovementSpeedInMetersPerSecond = 2.5f;

                if (auto pointer_pose = location.SourcePointerPose())
                {
                    const vec3 position = pointer_pose.Position();
                    const vec3 forward = pointer_pose.ForwardDirection();

                    if (abs(paint->thumbstick_y) > ThumbstickMovementThresholdPercent)
                    {
                        const vec3 forward_movement = forward * paint->thumbstick_y * MovementSpeedInMetersPerSecond * dt;

                        // Move all paintings along beam path
                        for (auto& stroke : paint->strokes)
                        {
                            stroke->Get<Transform>()->position += forward_movement;
                        }
                    }

                    paint->beam->Get<Transform>()->position = position + forward * (paint->beam->Get<Transform>()->scale.z * 0.5f);
                    paint->beam->Get<Transform>()->orientation = pointer_pose.Orientation();
                }
            }
            else if (paint->cur_state == PaintComponent::State::ColorSelection)
            {
                constexpr float colorpicker_diameter = 0.025f;
                constexpr float colorpicker_height = 0.015f;

                const mat4 paint_brush_to_world = paint->paint_brush->Get<Transform>()->GetMatrix();

                const vec3 touchpad_indicator_on_paint_brush = { paint->touchpad_x * colorpicker_diameter, colorpicker_height, paint->touchpad_y * colorpicker_diameter * -1 };
                const vec3 touchpad_indicator_in_world = transform(touchpad_indicator_on_paint_brush, paint_brush_to_world);

                paint->touchpad_indicator->Get<Transform>()->position = touchpad_indicator_in_world;

                // Color picker plane defined as slightly above the touchpad with the same orientation as the touchpad
                const int num_colors = static_cast<int>(paint->clr_pick_objects.GetCount());

                for (int i = 0; i < num_colors; ++i)
                {
                    const float angle = (static_cast<float>(i*-1 - 1) / static_cast<float>(num_colors)) * (2 * M_PI) - M_PI;
                    const float next_angle = (static_cast<float>((i + 1)*-1 - 1) / static_cast<float>(num_colors)) * (2 * M_PI) - M_PI;
                    const float angle_delta = (next_angle - angle) / 2; // Want color icon to appear in the middle of the segment, not the start.
                    const float final_angle = angle - angle_delta;

                    const vec3 color_indicator_on_paint_brush = { std::cos(final_angle) * colorpicker_diameter, colorpicker_height, std::sin(final_angle) * colorpicker_diameter };
                    const vec3 color_indicator_in_world = transform(color_indicator_on_paint_brush, paint_brush_to_world);

                    paint->clr_pick_objects[i]->Get<Transform>()->position = color_indicator_in_world;
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

    for (auto& color_picker : clr_pick_objects) {
        color_picker->SetEnabled(enable);
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

    for (auto& color_picker : clr_pick_objects) {
        color_picker->Destroy();
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

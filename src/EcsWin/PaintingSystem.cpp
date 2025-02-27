#if 0
#include "EcsWin.h"


NAMESPACE_ECS_BEGIN




using namespace DirectX;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::literals::chrono_literals;

void PaintingInteractionSystem::Start()
{
	Engine& m_engine = GetEngine();
    m_engine.Get<ToolboxSystem>()->AddToolSystem(*this);
}

void PaintingInteractionSystem::Stop()
{
	Engine& m_engine = GetEngine();
    m_engine.Get<ToolboxSystem>()->RemoveToolSystem(*this);
}

std::wstring_view PaintingInteractionSystem::GetInstructions() const 
{
    return L"Press and hold trigger to paint.\n\n"
           L"Touch and press touchpad to choose brush color.\n\n"
           L"Hold grasp button to move strokes around. While holding grasp tilt thumbstick forward/backward to translate strokes.\n\n"
           L"Push thumbstick down to delete strokes.\n\n";
}

std::wstring_view PaintingInteractionSystem::GetDisplayName() const
{
    return L"Painting";
}

EntityRef PaintingInteractionSystem::CreateToolSelector() const
{
	Engine& m_engine = GetEngine();
    auto selector = m_engine.Get<EntityStore>()->GetRoot()->Create<ToolSelectorPrefab>();

    selector->Get<PbrRenderable>()->ResetModel("PaintBrush");
    selector->Get<Transform>()->data.orientation = AxisAngleQuat(vec3(1, 0, 0), M_PIf / 1.5f);
    selector->Get<ToolSelectorKey>()->type = GetTypeId();

    return selector;
}

void PaintingInteractionSystem::Register(Array<EntityRef>& entities)
{
	Engine& m_engine = GetEngine();
    ToolSystem::Register(entities);

    EntityStoreRef entityStore = m_engine.Get<EntityStore>();

    for (auto& entity : m_entities)
    {
        const auto& selectedColor = m_colors[0];

		auto pool = entityStore->GetRoot();
        auto paintBrush = pool->Create<PaintBrush>();
        paintBrush->Get<PbrRenderable>()->Color = selectedColor;

        paintBrush->Get<MotionControllerComponent>()->requestedHandedness = entity->Get<MotionControllerComponent>()->requestedHandedness;

        auto touchpadIndicator = pool->Create<StaticSphere>();
        touchpadIndicator->Get<Transform>()->size = { 0.005f, 0.005f, 0.005f };
        touchpadIndicator->Get<PbrRenderable>()->Color = DirectX::Colors::Gray;

        Array<EntityRef> colorPickersObjects;
        for (auto color : m_colors)
        {
            EntityRef colorPicker = pool->Create<StaticSphere>();
            colorPicker->Get<Transform>()->size = { 0.01f, 0.01f, 0.01f };
            colorPicker->Get<PbrRenderable>()->Color = color;
            colorPickersObjects.Add(colorPicker);
        }

        auto beam = pool->Create<StaticCube>();
        beam->Get<Transform>()->size = { 0.005f, 0.005f, 10.0f };
        beam->Get<PbrRenderable>()->Color = DirectX::Colors::Aquamarine;

        PaintComponentRef paint = entity->Get<PaintComponent>();

        paint->selectedColor = selectedColor;
        paint->paintBrush = std::move(paintBrush);
        paint->touchpadIndicator = std::move(touchpadIndicator);
        paint->colorPickerObjects <<= colorPickersObjects;
        paint->beam = beam;

        paint->SetEnabled(false);
    }

    m_engine.Get<SpatialInteractionSystem>()->AddListener(*this);
}

void PaintingInteractionSystem::Activate(Entity& entity)
{
    ToolSystem::Activate(entity);

    // Stop rendering the controller
    entity.Get<PbrRenderable>()->SetEnabled(false);
}

void PaintingInteractionSystem::Deactivate(Entity& entity)
{
    entity.Get<PbrRenderable>()->SetEnabled(true);

    PaintComponentRef paint = entity.Get<PaintComponent>();

    // Copy out the strokes from the component so they can persist in the world.
    if (paint->strokeInProgress)
    {
        paint->strokes.Add(paint->strokeInProgress);
    }

    if (paint->strokes.GetCount())
    {
        m_persistentStrokes.Add() <<= paint->strokes;
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
            auto entity = std::get<Entity*>(enabledEntity);
            auto paint = std::get<PaintComponent*>(enabledEntity);
            
            for (auto& stroke : paint->strokes)
            {
                stroke->Destroy();
            }

            paint->strokes.Clear();

            if (paint->strokeInProgress)
            {
                paint->strokeInProgress->Destroy();
                paint->strokeInProgress.Clear();
            }
        }

        // Destroy all the persistent strokes
        for (auto& strokeGroup : m_persistentStrokes)
        {
            for (auto& stroke : strokeGroup)
            {
                stroke->Destroy();
            }
        }

        m_persistentStrokes.Clear();
    }
}

void PaintingInteractionSystem::OnSourceUpdated(const SpatialInteractionSourceEventArgs& args)
{
	Engine& m_engine = GetEngine();
    const auto& sourceState = args.State();
    const auto& source = sourceState.Source();

    if (auto enabledEntity = TryGetEntityFromSource(source))
    {
        bool newStrokeStarted = false;
        auto entity = std::get<Entity*>(*enabledEntity);
        auto paint = std::get<PaintComponent*>(*enabledEntity);

        const auto& paintBrushModel = paint->paintBrush->Get<PbrRenderable>()->Model;
        if (paintBrushModel && !paint->brushTipOffsetFromHoldingPose)
        {
            std::optional<Pbr::NodeIndex_t> touchNode = paintBrushModel->FindFirstNode("PaintTip");
            if (touchNode)
            {
                // Calcluate paint tip offset from holding pose
                // we use offset as it does not rely on the current transform of the model
                // we initialize it once as the value will not change
                const mat4 brush_tip_world_transform = ToTs(paintBrushModel->GetNodeWorldTransform(touchNode.value()));
                const mat4 paint_brush_world_transform = ToTs(paintBrushModel->GetNode(Pbr::RootNodeIndex).GetTransform());
                paint->brushTipOffsetFromHoldingPose =
				        brush_tip_world_transform *
				        paint_brush_world_transform.GetInverse();
                    /*ToTs(
	                    brushTipWorldTransform *
	                    XMMatrixInverse(nullptr, paintBrushWorldTransform)
                    );*/
            }
        }

        const auto controller = entity->Get<MotionControllerComponent>();
        if (controller->IsSource(source))
        {
            const auto& controllerProperties = sourceState.ControllerProperties();

            paint->touchpadX = static_cast<float>(controllerProperties.TouchpadX());
            paint->touchpadY = static_cast<float>(controllerProperties.TouchpadY());

            paint->thumbstickX = static_cast<float>(controllerProperties.ThumbstickX());
            paint->thumbstickY = static_cast<float>(controllerProperties.ThumbstickY());

            if (paint->currentState == PaintComponent::State::Idle)
            {
                if (sourceState.IsSelectPressed())
                {
                    paint->currentState = PaintComponent::State::Painting;
                    newStrokeStarted = true;
                }
                else if (sourceState.IsGrasped())
                {
                    paint->currentState = PaintComponent::State::Manipulating;
                }
                else if (controllerProperties.IsTouchpadTouched())
                {
                    paint->currentState = PaintComponent::State::ColorSelection;
                }
            }
            else if (paint->currentState == PaintComponent::State::Painting)
            {
                if (sourceState.IsSelectPressed() == false)
                {
                    paint->currentState = PaintComponent::State::Idle;
                }
            }
            else if (paint->currentState == PaintComponent::State::Manipulating)
            {
                if (sourceState.IsGrasped() == false)
                {
                    paint->currentState = PaintComponent::State::Idle;

                    paint->previousManipulationLocation = nullptr;
                }
            }
            else if (paint->currentState == PaintComponent::State::ColorSelection)
            {
                if (paint->waitForTouchpadRelease == false)
                {
                    if (controllerProperties.IsTouchpadPressed())
                    {
                        paint->waitForTouchpadRelease = true;
                        paint->selectedColor = SelectColor(paint->touchpadX, paint->touchpadY);

                        SpatialInputUtilities::Haptics::SendContinuousBuzzForDuration(sourceState.Source(), 100ms);
                    }
                }

                if (controllerProperties.IsTouchpadPressed() == false)
                {
                    paint->waitForTouchpadRelease = false;
                }

                if (controllerProperties.IsTouchpadTouched() == false)
                {
                    paint->currentState = PaintComponent::State::Idle;
                }
            }

            if (paint->currentState == PaintComponent::State::Painting)
            {
                // Start new stroke
                if (newStrokeStarted)
                {
                    paint->strokeInProgress = m_engine.Get<EntityStore>()->GetRoot()->Create<PaintStroke>();
                    paint->strokeInProgress->Get<PbrRenderable>()->Color = paint->selectedColor;

                    paint->strokes.Add(paint->strokeInProgress);
                }

                auto properties = sourceState.Properties();

                // We generate stroke points in source updated using the arguments provided by the event
                // This will result in a smoother paint stroke
                if (auto location = properties.TryGetLocation(m_engine.Get<HolographicScene>()->WorldCoordinateSystem()))
                {
                    if (paint->brushTipOffsetFromHoldingPose && paint->strokeInProgress)
                    {
                        mat4 paintToWorld =
                            *paint->brushTipOffsetFromHoldingPose *
                             ToTs(location_util::matrix(location));

                        paint->strokeInProgress->Get<PaintStrokeComponent>()->AddPoint(
                            RemoveScale(paintToWorld), PaintTipThickness
                        );
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

        MotionControllerComponentRef controller = entity->Get<MotionControllerComponent>();

        paint->beam->Get<PbrRenderable>()->SetEnabled(paint->currentState == PaintComponent::State::Manipulating);

        // Set properties required for rendering
        paint->touchpadIndicator->Get<PbrRenderable>()->SetEnabled(paint->currentState == PaintComponent::State::ColorSelection);
        for (auto& go : paint->colorPickerObjects)
        {
            go->Get<PbrRenderable>()->SetEnabled(paint->currentState == PaintComponent::State::ColorSelection);
        }

        const bool showController = paint->currentState == PaintComponent::State::Manipulating;
            
        entity->Get<PbrRenderable>()->SetEnabled(showController);
        paint->paintBrush->Get<PbrRenderable>()->SetEnabled(!showController);

        if (auto location = controller->location)
        {
            const vec3 pos = ToTs(location_util::position(location));
            const quat orient = ToTs(location_util::orientation(location));

            const DirectX::XMVECTORF32 paintTipColor = paint->currentState == PaintComponent::State::ColorSelection ? SelectColor(paint->touchpadX, paint->touchpadY) : paint->selectedColor;
            paint->paintBrush->Get<PbrRenderable>()->Color = paintTipColor;

            if (paint->currentState == PaintComponent::State::Manipulating)
            {
                // Update the paint strokes based on the change in location
                if (paint->previousManipulationLocation)
                {
                    vec3 prev_pos = ToTs(location_util::position(paint->previousManipulationLocation));
                    quat prev_orient = ToTs(location_util::orientation(paint->previousManipulationLocation));
                    quat orient_diff = orient * Inverse(prev_orient);
					vec3 pos_diff = pos - prev_pos;
					
                    for (auto stroke : paint->strokes) {
                        stroke->Get<Transform>()->data.
							Move(pos_diff).
							Rotate(orient_diff);
                    }
                }

                paint->previousManipulationLocation = location;

                // Move the paint strokes based on manipulation changes

                constexpr double ThumbstickMovementThresholdPercent = 0.2f; // Deadzone to prevent slight thumbstick movement
                constexpr float MovementSpeedInMetersPerSecond = 2.5f;

                if (auto pointerPose = location.SourcePointerPose())
                {
                    const vec3 position = ToTs(pointerPose.Position());
                    const vec3 forward = ToTs(pointerPose.ForwardDirection());

                    if (abs(paint->thumbstickY) > ThumbstickMovementThresholdPercent)
                    {
                        const vec3 forwardMovement =
                            forward *
                            paint->thumbstickY *
                            MovementSpeedInMetersPerSecond *
                            (float)dt;

                        // Move all paintings along beam path
                        for (auto& stroke : paint->strokes) {
                            stroke->Get<Transform>()->data.Move(forwardMovement);
                        }
                    }
					
					TransformRef trans = paint->beam->Get<Transform>();
                    trans->data.position = position + forward * (trans->size[2] * 0.5f);
                    trans->data.orientation = ToTs(pointerPose.Orientation());
                }
            }
            else if (paint->currentState == PaintComponent::State::ColorSelection)
            {
                constexpr float colorpickerDiameter = 0.025f;
                constexpr float colorpickerHeight = 0.015f;

                const mat4 paintBrushToWorld = paint->paintBrush->Get<Transform>()->GetMatrix();

                const vec3 touchpadIndicatorOnPaintBrush = { paint->touchpadX * colorpickerDiameter, colorpickerHeight, paint->touchpadY * colorpickerDiameter * -1 };
                const vec3 touchpadIndicatorInWorld = VectorTransform(touchpadIndicatorOnPaintBrush, paintBrushToWorld);
				
				TransformRef trans = paint->touchpadIndicator->Get<Transform>();
                trans->data.position = touchpadIndicatorInWorld;

                // Color picker plane defined as slightly above the touchpad with the same orientation as the touchpad
                const int numColors = static_cast<int>(paint->colorPickerObjects.GetCount());

                for (int i = 0; i < numColors; ++i)
                {
                    const float angle = (static_cast<float>(i*-1 - 1) / static_cast<float>(numColors)) * (2 * DirectX::XM_PI) - DirectX::XM_PI;
                    const float nextAngle = (static_cast<float>((i + 1)*-1 - 1) / static_cast<float>(numColors)) * (2 * DirectX::XM_PI) - DirectX::XM_PI;
                    const float angleDelta = (nextAngle - angle) / 2; // Want color icon to appear in the middle of the segment, not the start.
                    const float finalAngle = angle - angleDelta;

                    const vec3 colorIndicatorOnPaintBrush = { std::cos(finalAngle) * colorpickerDiameter, colorpickerHeight, std::sin(finalAngle) * colorpickerDiameter };
                    const vec3 colorIndicatorInWorld = VectorTransform(colorIndicatorOnPaintBrush, paintBrushToWorld);
					
					TransformRef trans = paint->colorPickerObjects[i]->Get<Transform>();
                    trans->data.position = colorIndicatorInWorld;
                }
            }
        }
    }
}

DirectX::XMVECTORF32 PaintingInteractionSystem::SelectColor(double x, double y)
{
    if (x == 0 && y == 0)
    {
        return m_colors.back();
    }

    constexpr double min = -DirectX::XM_PI;
    constexpr double max = +DirectX::XM_PI;
    double angle = std::atan2(y, x);
    int index = static_cast<int>(std::round((angle - min) / (max - min) * (m_colors.size() - 1)));
    return m_colors[index];
}

void PaintComponent::SetEnabled(bool enable) 
{
    Enableable::SetEnabled(enable);

    for (auto& colorPicker : colorPickerObjects) {
        colorPicker->SetEnabled(enable);
    }

    if (touchpadIndicator) {
        touchpadIndicator->SetEnabled(enable);
    }

    if (paintBrush) {
        paintBrush->SetEnabled(enable);
    }

    if (beam) {
        beam->SetEnabled(enable);
    }
}

void PaintComponent::Destroy() 
{
    Destroyable::Destroy();

    for (auto& colorPicker : colorPickerObjects) {
        colorPicker->Destroy();
    }

    if (touchpadIndicator) {
        touchpadIndicator->Destroy();
    }

    if (paintBrush) {
        paintBrush->Destroy();
    }

    if (beam) {
        beam->Destroy();
    }
}


NAMESPACE_ECS_END
#endif

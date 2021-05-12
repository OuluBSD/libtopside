#include "EcsLib.h"


struct MotionControllerPrefab : EntityPrefab<Transform, PbrRenderable, MotionControllerComponent, ToolComponent>
{};

struct TextDisplay : EntityPrefab<Transform, TextRenderable>
{};

static const String InstructionalText = "Press the menu button to bring interaction objects toward you.\n\nGrasp (grasp button) an interaction object to use it.";

namespace  {
	
bool HitTest(vec3 positionA, vec3 positionB, float diameter)
{
    auto distance = length(positionA - positionB);
    return distance < diameter;
}

}

void ToolboxSystem::AddToolSystem(ToolSystemBaseRef system)
{
    system->Register({ m_controllers[Left].Controller, m_controllers[Right].Controller });

    m_selectorObjects.emplace(system->type(), system->CreateToolSelector());

    m_selectors.emplace(system->type(), system);
    
    for (auto& context : m_controllers)
    {
        SwitchToolType(*context.Controller, system->type());
    }
}

void ToolboxSystem::RemoveToolSystem(const ToolSystemBaseRef& system)
{
    m_selectors.erase(system->type());

    m_selectorObjects.erase(system->type());

    system->Unregister();
}

void ToolboxSystem::Start()
{
    auto m_es = GetMachine().Get<EntityStore>();

    for (size_t i = 0; i < m_controllers.GetCount(); ++i)
    {
        const ControllerHand hand = static_cast<ControllerHand>(i);

        m_controllers[i].Hand = hand;
        m_controllers[i].Controller = m_es->GetRoot()->Create<MotionControllerPrefab>();
        m_controllers[i].Controller->Get<MotionControllerComponent>()->req_hand = ControllerHandToHandedness(hand);
        m_controllers[i].Controller->Get<MotionControllerComponent>()->attachControllerModel = true;
    }

    instruction_text = m_es->GetRoot()->Create<TextDisplay>();
    instruction_text->Get<TextRenderable>()->Text = InstructionalText;
    instruction_text->Get<Transform>()->position = { 0, 1.5f, -5.f };
    instruction_text->Get<Transform>()->scale = vec3{ 2.0f };

    m_controllers[Left].DebugText = m_es->GetRoot()->Create<TextDisplay>();
    m_controllers[Left].DebugText->Get<Transform>()->position = { -2.5, 1.25f, -4.f };
    m_controllers[Left].DebugText->Get<Transform>()->orientation = MakeQuaternionFromAxisAngle({ 0, 1, 0 }, M_PI * 0.15f);
    m_controllers[Left].DebugText->Get<Transform>()->scale = vec3{ 2.0f };
    m_controllers[Left].DebugText->Get<TextRenderable>()->font_size = 52.0f;

    m_controllers[Right].DebugText = m_es->GetRoot()->Create<TextDisplay>();
    m_controllers[Right].DebugText->Get<Transform>()->position = { 2.5, 1.25f, -4.f };
    m_controllers[Right].DebugText->Get<Transform>()->orientation = MakeQuaternionFromAxisAngle({ 0, 1, 0 }, -M_PI * 0.15f);
    m_controllers[Right].DebugText->Get<Transform>()->scale = vec3{ 2.0f };
    m_controllers[Right].DebugText->Get<TextRenderable>()->font_size = 52.0f;

    GetMachine().Get<SpatialInteractionSystem>()->AddListener(shared_from_this());
}

void ToolboxSystem::Stop()
{
    GetMachine().Get<SpatialInteractionSystem>()->RemoveListener(shared_from_this());
}

void ToolboxSystem::Update(double dt)
{
    static float fps[32] = {};
    static uint32 currFps = 0;
    fps[currFps++] = dt;
    currFps %= _countof(fps);

    const float avgDt = std::accumulate(std::begin(fps), std::end(fps), 0.0f) / _countof(fps);

    instruction_text->Get<TextRenderable>()->Text = std::to_wstring(static_cast<int>(std::round(1.0f / avgDt))) + L" FPS\n\n" + InstructionalText.data();

    if (!m_showToolbox)
    {
        {
            int i = 0;
            for (auto& selectorPair : m_selectorObjects)
            {
                auto selector = selectorPair.second;

                const float offset = (i - floorf(m_selectorObjects.GetCount() / 2.f)) / m_selectorObjects.GetCount();
                selector->Get<Easing>()->TargetPosition = vec3{ offset, 1.25f, -5.f };

                ++i;
            }
        }

        // Update the debug text for each Controller based on the currently selected tool
        for (size_t i = 0; i < m_controllers.GetCount(); ++i)
        {
            String displayedText = String(ControllerHandToString(m_controllers[i].Hand)) + L": ";

            if (auto tool = m_controllers[i].Controller->Get<ToolComponent>())
            {
                displayedText += tool->title + L"\n\n" + tool->description;
            }

            m_controllers[i].DebugText->Get<TextRenderable>()->Text = displayedText;
        }
    }
    else
    {
        for (size_t i = 0; i < m_controllers.GetCount(); ++i)
        {
            String displayedText = String(ControllerHandToString(m_controllers[i].Hand)) + L" switch to: ";

            const vec3 controllerPosition = m_controllers[i].Controller->Get<Transform>()->position;

            for (auto[transform, selector] : GetMachine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>())
            {
                if (HitTest(controllerPosition, transform->position, 0.15f))
                {
                    auto it = m_selectors.find(selector->type);
                    if (it != m_selectors.end())
                    {
                        displayedText += it->second->GetDisplayName();
                        displayedText += L"\n\n";
                        displayedText += it->second->GetInstructions();
                    }
                }
            }

            m_controllers[i].DebugText->Get<TextRenderable>()->Text = displayedText;
        }
    }
}


void ToolboxSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args)
{
    if (args.State().Source().Kind() != SpatialInteractionSourceKind::Controller)
        return;

    auto controller = FindController(args.State().Source());

    if (!controller)
        return;

    // Bring the toolbox in front of user
    if (args.PressKind() == SpatialInteractionPressKind::Menu)
    {
        m_showToolbox = !m_showToolbox;
        if (m_showToolbox)
        {
            auto holoScene = GetMachine().Get<HolographicScene>();
            if (SpatialPointerPose pointerPose = SpatialPointerPose::TryGetAtTimestamp(holoScene->WorldCoordinateSystem(), holoScene->CurrentTimestamp()))
            {
                const vec3 headPosition = pointerPose.Head().Position();
                const vec3 forward = pointerPose.Head().ForwardDirection();
                const vec3 headUp = pointerPose.Head().UpDirection();

                const vec3 headDirection = normalize(vec3{ forward.x, 0.0f, forward.z });

                vec3 headRight = cross(headDirection, headUp);
                headRight.y = 0;
                headRight = normalize(headRight);

                const vec3 toolkitCenter = headDirection * 0.5f;

                {
                    int i = 0;
                    for (auto& selectorPair : m_selectorObjects)
                    {
                        auto selector = selectorPair.second;

                        const float offset = (i - floorf(m_selectorObjects.GetCount() / 2.f)) / m_selectorObjects.GetCount();
                        const vec3 targetPosition = toolkitCenter + headPosition + headRight * offset + vec3{ 0, -0.3f, 0 };
                        selector->Get<Easing>()->TargetPosition = targetPosition;

                        ++i;
                    }
                }
            }
        }
    }
    else if (args.PressKind() == SpatialInteractionPressKind::Grasp && m_showToolbox)
    {
        if (const SpatialInteractionSourceLocation& location = controller->Get<MotionControllerComponent>()->location)
        {
            if (location.Position())
            {
                const vec3 position = location.Position().Value();

                for (auto[transform, selector] : GetMachine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>())
                {
                    if (HitTest(position, transform->position, 0.15f))
                    {
                        SwitchToolType(*controller, selector->type);
                        m_showToolbox = false;
                        break;
                    }
                }
            }
        }
    }
}

String ToolboxSystem::ControllerHandToString(ControllerHand hand) 
{
    return hand == Left ? L"Left" : L"Right";
}

SpatialInteractionSourceHandedness ToolboxSystem::ControllerHandToHandedness(ControllerHand hand) 
{
    return hand == Left ? SpatialInteractionSourceHandedness::Left : SpatialInteractionSourceHandedness::Right;
}

void ToolboxSystem::SwitchToolType(Entity& entity, const detail::type_id& newType)
{
    ToolComponent* tool = entity.Get<ToolComponent>();

    { // Disable old tool
        auto it = m_selectors.find(tool->tool_type);
        if (it != m_selectors.end())
        {
            it->second->Deactivate(entity);
        }
    }

    { // Enable new tool
        auto it = m_selectors.find(newType);
        if (it != m_selectors.end())
        {
            it->second->Activate(entity);
            tool->tool_type = it->second->type();
            tool->description = it->second->GetInstructions();
            tool->title = it->second->GetDisplayName();
        }
    }
}

EntityRef ToolboxSystem::FindController(const SpatialInteractionSource& source)
{
    for (auto& context : m_controllers)
    {
        if (context.Controller->Get<MotionControllerComponent>()->IsSource(source))
        {
            return context.Controller;
        }
    }

    return nullptr;
}


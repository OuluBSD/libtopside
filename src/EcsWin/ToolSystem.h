#pragma once


NAMESPACE_WIN_BEGIN


////////////////////////////////////////////////////////////////////////////////
// ToolSystemBase
// Base abstract class for all ToolSystems
class ToolSystemBase abstract : public SystemBase
{
public:
    using SystemBase::SystemBase;

    virtual std::wstring_view GetInstructions() const = 0;
    virtual std::wstring_view GetDisplayName() const = 0;
    
    virtual EntityRef CreateToolSelector() const = 0;

    virtual void Register(Array<EntityRef>& entities) = 0;
    virtual void Unregister() = 0;
    virtual void Activate(Entity& entity) = 0;
    virtual void Deactivate(Entity& entity) = 0;
};

struct ToolSelectorKey : Component<ToolSelectorKey>
{
    detail::type_id type{ typeid(nullptr_t) };
};

struct ToolSelectorPrefab : EntityPrefab<Transform, PbrRenderable, ToolSelectorKey, RigidBody, Easing>
{
    static Components Make(Entity& e);
};

// CRTP implementation helper
// Usage: class MyToolSystem : ToolSystem<MyToolSystem> { /* functions + data members */ };
// Adds functionality to automatically register to listeners and helpers to access entities 
// that actually have the associated ToolComponent attached and enabled
template<typename T, typename ToolComponent>
class ToolSystem abstract :
    public ToolSystemBase,
    public ISpatialInteractionListener
    //public std::enable_shared_from_this<T>
{
public:
    using ToolSystemBase::ToolSystemBase;
	
	RTTI_DECL2(ToolSystem, ToolSystemBase, ISpatialInteractionListener)
	
    // System
    //detail::type_id type() const override {return typeid(T);}

protected:
    // System
    void Start() override
    {
        GetEngine().Get<ToolboxSystem>()->AddToolSystem(AsRefT());
    }

    void Stop() override
    {
        GetEngine().Get<ToolboxSystem>()->RemoveToolSystem(AsRefT());
    }

    // ToolSystemBase
    void Register(Array<EntityRef>& entities) override
    {
        m_entities = std::move(entities);

        for (auto& entity : m_entities)
        {
            entity->Add<ToolComponent>()->SetEnabled(false);
        }

        GetEngine().Get<SpatialInteractionSystem>()->AddListener(AsRefT());
    }

    void Unregister() override
    {
        GetEngine().Get<SpatialInteractionSystem>()->RemoveListener(AsRefT());

        for (auto& entity : m_entities)
        {
            entity->Remove<ToolComponent>();
        }

        m_entities.clear();
    }

    void Activate(Entity& entity) override
    {
        entity.Get<ToolComponent>()->SetEnabled(true);
    }

    void Deactivate(Entity& entity) override
    {
        entity.Get<ToolComponent>()->SetEnabled(false);
    }

    // Internal helpers
    std::vector<std::tuple<Entity*, ToolComponent*>> GetEnabledEntities() const
    {
        std::vector<std::tuple<Entity*, ToolComponent*>> entities;

        for (auto& entity : m_entities)
        {
            auto comp = entity->Get<ToolComponent>();
            if (comp->IsEnabled())
            {
                entities.push_back(std::make_tuple(entity.get(), std::move(comp)));
            }
        }

        return entities;
    }

    std::optional<std::tuple<Entity*, ToolComponent*>> TryGetEntityFromSource(const winrt::Windows::UI::Input::Spatial::SpatialInteractionSource& source) const
    {
        for (auto& entity : m_entities)
        {
            auto comp = entity->Get<ToolComponent>();
            if (comp->IsEnabled())
            {
                if (entity->Get<MotionControllerComponent>()->IsSource(source))
                {
                    return std::make_tuple(entity.get(), std::move(comp));
                }
            }
        }
        
        return std::nullopt;
    }

    Array<EntityRef> m_entities;
};


NAMESPACE_WIN_END

#if 0
#pragma once


NAMESPACE_ECS_BEGIN


////////////////////////////////////////////////////////////////////////////////
// ToolSystemBase
// Base abstract class for all ToolSystems
class ToolSystemBase abstract :
	public SystemBase
{
public:
	RTTI_DECL1(ToolSystemBase, SystemBase)
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
	COPY_PANIC(ToolSelectorKey)
	
    //detail::type_id type{ typeid(nullptr_t) };
    TypeCls type;
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
	using ToolSystemT = ToolSystem<T,ToolComponent>;
    using ToolSystemBase::ToolSystemBase;
	
	RTTI_DECL2(ToolSystemT, ToolSystemBase, ISpatialInteractionListener)
	
    // System
    //detail::type_id type() const override {return typeid(T);}

protected:
    // System
    void Start() override
    {
        GetEngine().Get<ToolboxSystem>()->AddToolSystem(*this);
    }

    void Stop() override
    {
        GetEngine().Get<ToolboxSystem>()->RemoveToolSystem(*this);
    }

    // ToolSystemBase
    void Register(Array<EntityRef>& entities) override
    {
        m_entities <<= entities;

        for (auto& entity : m_entities) {
            entity->Add<ToolComponent>()->SetEnabled(false);
        }

        GetEngine().Get<SpatialInteractionSystem>()->AddListener(*this);
    }

    void Unregister() override
    {
        GetEngine().Get<SpatialInteractionSystem>()->RemoveListener(*this);

        for (auto& entity : m_entities)
        {
            entity->Remove<ToolComponent>();
        }

        m_entities.Clear();
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


NAMESPACE_ECS_END
#endif

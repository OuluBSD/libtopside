#pragma once


NAMESPACE_OULU_BEGIN

////////////////////////////////////////////////////////////////////////////////
// ToolSystemBase
// Base abstract class for all ToolSystems
class ToolSystemBase : public SystemBase
{
public:
    using SystemBase::SystemBase;

    virtual String GetInstructions() const = 0;
    virtual String GetDisplayName() const = 0;
    
    virtual EntityRef CreateToolSelector() const = 0;

    virtual void Register(LinkedList<EntityRef>& entities) = 0;
    virtual void Unregister() = 0;
    virtual void Activate(EntityRef entity) = 0;
    virtual void Deactivate(EntityRef entity) = 0;
};

struct ToolSelectorKey : Component<ToolSelectorKey>
{
    TypeId type{ typeid(nullptr_t) };
};

struct ToolSelectorPrefab :
	EntityPrefab<Transform, PbrRenderable, ToolSelectorKey, RigidBody, Easing>
{
    static ComponentMap Make(ComponentStore& store);
};

// CRTP implementation helper
// Usage: class MyToolSystem : ToolSystem<MyToolSystem> { /* functions + data members */ };
// Adds functionality to automatically register to listeners and helpers to access entities 
// that actually have the associated ToolComponent attached and enabled
template<typename T, typename ToolComponent>
class ToolSystem :
    public ToolSystemBase,
    public ISpatialInteractionListener,
    public EnableSharedFromThis<T>
{

protected:
    // System
    void Start() override
    {
        GetMachine().Get<ToolboxSystem>()->AddToolSystem(shared_from_this());
    }

    void Stop() override
    {
        GetMachine().Get<ToolboxSystem>()->RemoveToolSystem(shared_from_this());
    }

    // ToolSystemBase
    void Register(LinkedList<EntityRef>& entities) override
    {
        m_entities = std::move(entities);

        for (auto& entity : m_entities)
        {
            entity->Add<ToolComponent>()->SetEnabled(false);
        }

        GetMachine().Get<SpatialInteractionSystem>()->AddListener(shared_from_this());
    }

    void Unregister() override 
    {
        GetMachine().Get<SpatialInteractionSystem>()->RemoveListener(shared_from_this());

        for (auto& entity : m_entities)
        {
            entity->Remove<ToolComponent>();
        }

        m_entities.clear();
    }

    void Activate(EntityRef entity) override
    {
        entity.Get<ToolComponent>()->SetEnabled(true);
    }

    void Deactivate(EntityRef entity) override
    {
        entity.Get<ToolComponent>()->SetEnabled(false);
    }

    // Internal helpers
    Vector<RTuple<EntityRef, ToolComponent*>> GetEnabledEntities() const
    {
        Vector<RTuple<EntityRef, ToolComponent*>> entities;

        for (auto& entity : m_entities)
        {
            auto comp = entity->Get<ToolComponent>();
            if (comp->IsEnabled())
            {
                entities.Add(std::make_tuple(entity.get(), std::move(comp)));
            }
        }

        return entities;
    }

    Optional<RTuple<EntityRef, ToolComponent*>> TryGetEntityFromSource(const SpatialInteractionSource& source) const
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

    LinkedList<EntityRef> m_entities;
};

NAMESPACE_OULU_END

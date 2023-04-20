#pragma once


NAMESPACE_ECS_BEGIN

#if 0
class Engine;

class EntityStore;
class Entity;
using EntityRef = std::shared_ptr<Entity>;

////////////////////////////////////////////////////////////////////////////////
// Entity
// An Entity is a collection of Components and represents a single object in the world
// It does not contain any logic, only helper functions to Get/Add/Remove Components from an Entity
class Entity : public Destroyable, public Enableable, public std::enable_shared_from_this<Entity>
{
public:
    using EntityId = uint64_t;

    template<typename T>
    T* Get() {
        return m_components.Get<T>();
    }

    template<typename T>
    void Remove() {
        m_components.Remove<T>();
    }

    template<typename T>
    T* Add() {
        return m_components.Add<T>(m_engine.Get<ComponentStore>()->CreateComponent<T>());
    }

    template<typename... ComponentTs>
    std::tuple<ComponentTs*...> TryGetComponents() {
        return std::make_tuple(m_components.TryGet<ComponentTs>()...);
    }

    Entity(ComponentMap components, EntityId id, Engine& core);
    virtual ~Entity();

    EntityRef Clone() const;

    EntityId Id() const { return m_id; }

    void Destroy() override;
    void SetEnabled(bool) override;

private:
    ComponentMap m_components;
    EntityId m_id;
    Engine& m_engine;
};

////////////////////////////////////////////////////////////////////////////////
// EntityPrefab
// Instead of deriving from Entity to define new objects we use Prefabs to specify 
// what components an entity should have, and what the initial values should be

// Example, an Entity 
// Declaration: 
// struct GiantBall : EntityPrefab<Transform, BallComponent> {
//     static Components Make(Entity& e) {
//         auto components = EntityPrefab::Make(e);
//         components.Get<Transform>()->size = { 500.0f, 500.0f, 500.0f };
//         return components;
//     }
// };

// Usage: 
// auto giantBall = m_engine.Get<EntityStore>()->Create<GiantBall>();
// Now "giantBall->Get<Transform>()->scale" will be set to "{ 500.0f, 500.0f, 500.0f }"
template<typename... ComponentTs>
struct EntityPrefab
{
    static_assert(detail::all_components<ComponentTs...>::value, "All components should derive from Component");

    using Components = std::tuple<ComponentTs...>;

    static Components Make(Entity& e) {
        #if 0
        ComponentStoreRef store = e.GetEngine().Get<ComponentStore>();
        ASSERT(store);
        return store->template CreateComponentMap<ComponentTs...>();
        #else
        Pool& p = e.GetPool();
        EntityRef e = p->template Create<EntityPrefab<ComponentTs...>>();
        return e->template TryGetComponents<ComponentTs...>();
        #endif
    }
};

#endif

NAMESPACE_ECS_END


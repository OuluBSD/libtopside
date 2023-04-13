#if 0
#include "EcsWin.h"




SharedEntity EntityStore::CreateFromComponentMap(ComponentMap components)
{
    return AddEntity(std::make_shared<Entity>(std::move(components), GetNextId(), m_engine));
}

void EntityStore::Update(double)
{
    Destroyable::PruneFromContainer(&m_objects);
}

SharedEntity EntityStore::AddEntity(SharedEntity obj)
{
    m_objects.push_back(obj);
    return obj;
}

Entity::EntityId EntityStore::GetNextId()
{
    return ++m_nextId;
}

#endif

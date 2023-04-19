#include "EcsCore.h"


NAMESPACE_ECS_BEGIN

void EntityStore::InitRoot() {
	root.Clear();
	Pool& p = root.Add();
	p.SetParent(PoolParent(this,0));
	p.SetName("root");
	p.SetId(Pool::GetNextId());
}

bool EntityStore::Initialize() {
	return true;
}

void EntityStore::Uninitialize() {
	GetRoot()->Clear();
}

void EntityStore::Update(double dt) {
	// Slow: GetRoot()->PruneFromContainer();
	
	if (this->destroy_list.GetCount()) {
		Vector<Entity*> destroy_list;
		Swap(this->destroy_list, destroy_list);
		for (Entity* e : destroy_list) {
			if (e)
				e->GetPool().RemoveEntity(e);
		}
	}
	
	
}

void EntityStore::AddToDestroyList(Entity* e) {
	VectorFindAdd(destroy_list, e);
}

EntityRef EntityStore::FindEntity(String path) {
	Vector<String> parts = Split(path, ".", false);
	
	PoolRef pool = GetRoot();
	for(int i = 0; i < parts.GetCount(); i++) {
		PoolRef new_pool;
		for(int c = i+1; c <= parts.GetCount(); c++) {
			bool is_ent = c == parts.GetCount();
			String p = parts[i];
			for(int j = i+1; j < c; j++)
				p << "." << parts[j];
			
			if (is_ent) {
				return pool->FindEntityByName(p);
			}
			else {
				new_pool = pool->FindPool(p);
				if (new_pool)
					break;
			}
		}
		if (!new_pool)
			break;
		pool = new_pool;
	}
	return EntityRef();
}


NAMESPACE_ECS_END


NAMESPACE_PARALLEL_BEGIN


Ecs::Engine& Machine::GetEngine() {
	EntitySystemRef es = Get<EntitySystem>();
	if (es)
		return es->GetEngine();
	
	Panic("No EntitySystem in machine");
	return *(Ecs::Engine*)0;
}


NAMESPACE_PARALLEL_END

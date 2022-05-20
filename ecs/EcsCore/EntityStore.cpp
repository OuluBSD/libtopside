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
	GetRoot()->PruneFromContainer();
	
	
	/*if (refresh_poolcomps[WRITE]) {
		lock.Enter();
		MemSwap(refresh_poolcomps[READ], refresh_poolcomps[WRITE]);
		refresh_poolcomps[WRITE].Clear();
		lock.Leave();
		
		for (ConnectorBase* comp : refresh_poolcomps[READ])
			comp->Update(dt);
	}*/
	
}

EntityRef EntityStore::FindEntity(String path) {
	Vector<String> parts = Split(path, ".", false);
	
	PoolRef pool = GetRoot();
	for(int i = 0; i < parts.GetCount(); i++) {
		bool is_ent = i == parts.GetCount()-1;
		const String& p = parts[i];
		
		if (is_ent) {
			return pool->FindEntityByName(p);
		}
		else {
			pool = pool->FindPool(p);
			if (!pool)
				break;
		}
	}
	return EntityRef();
}

/*int64 EntityStore::PostRefresh(int64 last_refresh, ConnectorBase* comp) {
	Engine& mach = GetEngine();
	
	// Don't add refresh if EntityStore haven't called previous refresh yet
	int64 cur_ticks = mach.GetTicks();
	if (last_refresh >= cur_ticks)
		return last_refresh;
	
	lock.Enter();
	refresh_poolcomps[WRITE].Add(comp);
	lock.Leave();
	
	return cur_ticks;
}*/



NAMESPACE_ECS_END

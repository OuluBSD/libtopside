#include "EcsCore.h"


NAMESPACE_TOPSIDE_BEGIN

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
	
	
	if (refresh_poolcomps[WRITE]) {
		lock.Enter();
		MemSwap(refresh_poolcomps[READ], refresh_poolcomps[WRITE]);
		refresh_poolcomps[WRITE].Clear();
		lock.Leave();
		
		for (ConnectorBase* comp : refresh_poolcomps[READ])
			comp->Update(dt);
	}
	
}

int64 EntityStore::PostRefresh(int64 last_refresh, ConnectorBase* comp) {
	Machine& mach = GetMachine();
	
	// Don't add refresh if EntityStore haven't called previous refresh yet
	int64 cur_ticks = mach.GetTicks();
	if (last_refresh >= cur_ticks)
		return last_refresh;
	
	lock.Enter();
	refresh_poolcomps[WRITE].Add(comp);
	lock.Leave();
	
	return cur_ticks;
}



NAMESPACE_TOPSIDE_END

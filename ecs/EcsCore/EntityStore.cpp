#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

bool EntityStore::Initialize() {
	GetRoot()->SetName("root");
	return true;
}

void EntityStore::Uninitialize() {
	GetRoot()->Clear();
}

void EntityStore::Update(double dt) {
	GetRoot()->PruneFromContainer();
	
	
	if (refresh_poolcomps[WRITE]) {
		lock.Enter();
		Swap(refresh_poolcomps[READ], refresh_poolcomps[WRITE]);
		refresh_poolcomps[WRITE].Clear();
		lock.Leave();
		
		for (PoolComponentBase* comp : refresh_poolcomps[READ])
			comp->Update(dt);
	}
	
}

int64 EntityStore::PostRefresh(int64 last_refresh, PoolComponentBase* comp) {
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



NAMESPACE_OULU_END

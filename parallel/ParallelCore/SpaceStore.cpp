#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN


void SpaceStore::InitRoot() {
	root.Clear();
	Space& p = root.Add();
	p.SetParent(SpaceParent(this,0));
	p.SetName("root");
	p.SetId(Space::GetNextId());
}

bool SpaceStore::Initialize() {
	return true;
}

void SpaceStore::Stop() {
	GetRoot()->StopDeep();
}

void SpaceStore::Uninitialize() {
	GetRoot()->Clear();
}

void SpaceStore::Update(double dt) {
	// pass
}


NAMESPACE_PARALLEL_END

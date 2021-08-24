#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


void LoopStore::InitRoot() {
	root.Clear();
	Loop& p = root.Add();
	p.SetParent(LoopParent(this,0));
	p.SetName("root");
	p.SetId(Loop::GetNextId());
}

bool LoopStore::Initialize() {
	return true;
}

void LoopStore::Uninitialize() {
	GetRoot()->Clear();
}

void LoopStore::Update(double dt) {
	//GetRoot()->PruneFromContainer();
	
	
	/*if (refresh_poolcomps[WRITE]) {
		lock.Enter();
		MemSwap(refresh_poolcomps[READ], refresh_poolcomps[WRITE]);
		refresh_poolcomps[WRITE].Clear();
		lock.Leave();
		
		for (ConnectorBase* comp : refresh_poolcomps[READ])
			comp->Update(dt);
	}*/
	
}




NAMESPACE_SERIAL_END

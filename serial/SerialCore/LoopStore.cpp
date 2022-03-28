#include "SerialCore.h"


NAMESPACE_SERIAL_BEGIN


void LoopStore::InitRoot() {
	root.Clear();
	Loop& p = root.Add();
	p.SetParent(LoopParent(this,0));
	p.SetName("root");
	p.SetId(Loop::GetNextId());
	
	Ref<SpaceStore> ss = GetMachine().Find<SpaceStore>();
	if (ss) {
		p.space = &*ss->GetRoot();
	}
}

bool LoopStore::Initialize() {
	return true;
}

void LoopStore::Uninitialize() {
	GetRoot()->Clear();
}

void LoopStore::Update(double dt) {
	// pass
}




NAMESPACE_SERIAL_END

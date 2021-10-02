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
	// pass
}




NAMESPACE_SERIAL_END

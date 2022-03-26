#include "ParallelCore.h"

  
NAMESPACE_PARALLEL_BEGIN




bool AtomSystem::Initialize() {
	
	return true;
}

void AtomSystem::Start() {
	
}

void AtomSystem::Update(double dt) {
	
	for (AtomBaseRef& c : updated) {
		c->Update(dt);
	}
	
}


void AtomSystem::Stop() {
	
}

void AtomSystem::Uninitialize() {
	
	WhenUninit()();
}

void AtomSystem::AddUpdated(AtomBaseRef p) {
	if (p)
		updated.FindAdd(p);
}

void AtomSystem::RemoveUpdated(AtomBaseRef p) {
	updated.RemoveKey(p);
}



NAMESPACE_PARALLEL_END

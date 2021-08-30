#include "Internal.h"

  
NAMESPACE_SERIAL_BEGIN


SYS_DEF_VISIT_I(AtomSystem, vis && customers)


bool AtomSystem::Initialize() {
	
	return true;
}

void AtomSystem::Start() {
	
}

void AtomSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
	for (Once& o : cbs) {
		WhenEnterOnceForward(o.fwd);
		
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++) {
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveOnceForward();
	}
	
	int dbg_i = 0;
	for (CustomerAtomRef& c : customers) {
		RTLOG("AtomSystem::Update: customer #" << dbg_i);
		c->UpdateConfig(dt);
		WhenEnterAtomForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, c->GetConfig()); scope; scope++) {
			RTLOG("AtomSystem::Update: customer #" << dbg_i << " fwd #" << dbg_j++);
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveAtomForward();
		dbg_i++;
	}
	
}

void AtomSystem::Stop() {
	
}

void AtomSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
	
	WhenUninit()();
}

void AtomSystem::Add(CustomerAtomRef p) {
	if (p)
		customers.FindAdd(p);
}

void AtomSystem::Remove(CustomerAtomRef p) {
	customers.RemoveKey(p);
}

void AtomSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	Once& o = once_cbs.Add();
	o.fwd = &fwd;
	o.cfg = &cfg;
	lock.Leave();
}


NAMESPACE_SERIAL_END

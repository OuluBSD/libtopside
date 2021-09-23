#include "Internal.h"

  
NAMESPACE_SERIAL_BEGIN


SYS_DEF_VISIT_I(AtomSystem, vis && customers)


bool AtomSystem::Initialize() {
	
	return true;
}

void AtomSystem::Start() {
	
}

void AtomSystem::ForwardAtoms(double dt, const char* id, LinkedList<AtomBaseRef>& atoms) {
	int dbg_i = 0;
	for (AtomBaseRef& c : atoms) {
		RealtimeSourceConfig* cfg = c->GetConfig();
		if (!cfg)
			continue;
		
		RTLOG("AtomSystem::Update: " << (String)id << " #" << dbg_i << " (" << c->ToString() << ")");
		
		WhenEnterAtomForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, *cfg); scope; scope++) {
			RTLOG("AtomSystem::Update: " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveAtomForward();
		dbg_i++;
	}
}

void AtomSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
	for (AtomBaseRef& c : updated) {
		c->Update(dt);
	}
	
	for (AtomBaseRef& c : customers) {
		c->UpdateConfig(dt);
	}
	
	for (Once& o : cbs) {
		WhenEnterOnceForward(o.fwd);
		
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++) {
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveOnceForward();
	}
	
	
	ForwardAtoms(dt, "customer", customers);
	ForwardAtoms(dt, "driver", drivers);
	ForwardAtoms(dt, "poller", pollers);
	
}

void AtomSystem::Stop() {
	
}

void AtomSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
	
	WhenUninit()();
}

void AtomSystem::AddCustomer(AtomBaseRef p) {
	if (p)
		customers.FindAdd(p);
}

void AtomSystem::AddDriver(AtomBaseRef p) {
	if (p)
		drivers.FindAdd(p);
}

void AtomSystem::AddPolling(AtomBaseRef p) {
	if (p)
		pollers.FindAdd(p);
}

void AtomSystem::AddUpdated(AtomBaseRef p) {
	if (p)
		updated.FindAdd(p);
}

void AtomSystem::RemoveCustomer(AtomBaseRef p) {
	customers.RemoveKey(p);
}

void AtomSystem::RemoveDriver(AtomBaseRef p) {
	drivers.RemoveKey(p);
}

void AtomSystem::RemovePolling(AtomBaseRef p) {
	pollers.RemoveKey(p);
}

void AtomSystem::RemoveUpdated(AtomBaseRef p) {
	updated.RemoveKey(p);
}


void AtomSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	bool found = false;
	for (Once& o : once_cbs) {
		if (o.fwd == &fwd && o.cfg == &cfg) {
			found = true;
			break;
		}
	}
	if (!found) {
		Once& o = once_cbs.Add();
		o.fwd = &fwd;
		o.cfg = &cfg;
	}
	lock.Leave();
}


NAMESPACE_SERIAL_END

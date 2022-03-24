#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


SYS_DEF_VISIT_I(LoopSystem, vis && customers)


void LoopSystem::ForwardAtoms(double dt, const char* id, LinkedList<AtomBaseRef>& atoms) {
	TODO // rename to ForwardLinks
	/*
	int dbg_i = 0;
	for (AtomBaseRef& c : atoms) {
		RealtimeSourceConfig* cfg = c->GetConfig();
		if (!cfg) {
			RTLOG("LoopSystem::ForwardAtoms: warning: GetConfig returns NULL");
			continue;
		}
		
		RTLOG("LoopSystem::ForwardAtoms: begin " << (String)id << " #" << dbg_i << " (" << c->ToString() << " " << HexStr(&*c) << ")");
		
		WhenEnterAtomForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, *cfg); scope; scope++) {
			RTLOG("LoopSystem::ForwardAtoms: loop id=" << c->GetId() << " " << HexStr(&*c) << " packets: " << GetDebugPacketString(c, cfg));
			
			if (!scope.IsBreak()) {
				RTLOG("LoopSystem::ForwardAtoms: " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.Forward();
				
				WhenLeaveFwdScopeForward();
			}
			else {
				RTLOG("LoopSystem::ForwardAtoms: weak try fwd " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.ForwardWeak();
				
				WhenLeaveFwdScopeForward();
			}
			
			if (scope.IsLoopComplete()) {
				RTLOG("LoopSystem::ForwardAtoms: loop complete");
			}
			else if (!scope) {
				RTLOG("LoopSystem::ForwardAtoms: scope flag dump: " << scope.GetFlagString());
			}
		}
		
		WhenLeaveAtomForward();
		dbg_i++;
	}*/
}


bool LoopSystem::Initialize() {
	
	return true;
}

void LoopSystem::Start() {
	
}

void LoopSystem::Update(double dt) {
	LinkedList<Once> cbs;
	lock.Enter();
	MemSwap(cbs, once_cbs);
	lock.Leave();
	
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

void LoopSystem::Stop() {
	
}

void LoopSystem::Uninitialize() {
	once_cbs.Clear();
	customers.Clear();
	
	WhenUninit()();
}

void LoopSystem::AddCustomer(AtomBaseRef p) {
	if (p)
		customers.FindAdd(p);
}

void LoopSystem::AddDriver(AtomBaseRef p) {
	if (p)
		drivers.FindAdd(p);
}

void LoopSystem::AddPolling(AtomBaseRef p) {
	if (p)
		pollers.FindAdd(p);
}

void LoopSystem::RemoveCustomer(AtomBaseRef p) {
	customers.RemoveKey(p);
}

void LoopSystem::RemoveDriver(AtomBaseRef p) {
	drivers.RemoveKey(p);
}

void LoopSystem::RemovePolling(AtomBaseRef p) {
	pollers.RemoveKey(p);
}


void LoopSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
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

#include "SerialMach.h"


NAMESPACE_SERIAL_BEGIN


SYS_DEF_VISIT_I(LoopSystem, vis && customers)


void LoopSystem::ForwardLinks(double dt, const char* id, LinkedList<LinkBaseRef>& atoms) {
	int dbg_i = 0;
	for (LinkBaseRef& c : atoms) {
		RealtimeSourceConfig* cfg = c->GetConfig();
		if (!cfg) {
			RTLOG("LoopSystem::ForwardLinks: warning: GetConfig returns NULL");
			continue;
		}
		
		RTLOG("LoopSystem::ForwardLinks: begin " << (String)id << " #" << dbg_i << " (" << c->ToString() << " " << HexStr(&*c) << ")");
		
		WhenEnterLinkForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, *cfg); scope; scope++) {
			RTLOG("LoopSystem::ForwardLinks: loop id=" << c->GetId() << " " << HexStr(&*c) << " packets: " << GetDebugPacketString(c, cfg));
			
			if (!scope.IsBreak()) {
				RTLOG("LoopSystem::ForwardLinks: " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.Forward();
				
				WhenLeaveFwdScopeForward();
			}
			else {
				RTLOG("LoopSystem::ForwardLinks: weak try fwd " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.ForwardWeak();
				
				WhenLeaveFwdScopeForward();
			}
			
			if (scope.IsLoopComplete()) {
				RTLOG("LoopSystem::ForwardLinks: loop complete");
			}
			else if (!scope) {
				RTLOG("LoopSystem::ForwardLinks: scope flag dump: " << scope.GetFlagString());
			}
		}
		
		WhenLeaveLinkForward();
		dbg_i++;
	}
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
	
	for (Once& o : cbs) {
		WhenEnterOnceForward(o.fwd);
		
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++) {
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveOnceForward();
	}
	
	for (LinkBaseRef& c : customers) {
		c->atom->UpdateConfig(dt);
	}
	
	ForwardLinks(dt, "customer", customers);
	ForwardLinks(dt, "driver", drivers);
	ForwardLinks(dt, "poller", pollers);
	
}

void LoopSystem::Stop() {
	
}

void LoopSystem::Uninitialize() {
	ASSERT(customers.IsEmpty());
	ASSERT(drivers.IsEmpty());
	ASSERT(pollers.IsEmpty());
	once_cbs.Clear();
	customers.Clear();
	
	WhenUninit()();
}

void LoopSystem::AddCustomer(LinkBaseRef p) {
	if (p)
		customers.FindAdd(p);
}

void LoopSystem::AddDriver(LinkBaseRef p) {
	if (p)
		drivers.FindAdd(p);
}

void LoopSystem::AddPolling(LinkBaseRef p) {
	if (p)
		pollers.FindAdd(p);
}

void LoopSystem::RemoveCustomer(LinkBaseRef p) {
	customers.RemoveKey(p);
}

void LoopSystem::RemoveDriver(LinkBaseRef p) {
	drivers.RemoveKey(p);
}

void LoopSystem::RemovePolling(LinkBaseRef p) {
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

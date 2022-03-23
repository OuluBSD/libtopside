#include "Internal.h"

  
NAMESPACE_PARALLEL_BEGIN


SYS_DEF_VISIT_I(AtomSystem, vis && customers)


bool AtomSystem::Initialize() {
	
	return true;
}

void AtomSystem::Start() {
	
}

String AtomSystem::GetDebugPacketString(AtomBaseRef& c, RealtimeSourceConfig* cfg) {
	int dbg_j = 0;
	String line;
	for (FwdScope scope(*c, *cfg); scope; scope++) {
		scope.ForwardAddNext();
		AtomBase* ab = CastPtr<AtomBase>(scope.GetCurrent());
		if (ab) {
			int sink_pk = 0;
			int src_pk = 0;
			
			line << (line.IsEmpty() ? "| " : " | ");
			
			InterfaceSinkRef sink_iface = ab->GetSink();
			int c = sink_iface->GetSinkCount();
			for(int i = 0; i < c; i++) {
				if (i) line << "+";
				line << sink_iface->GetValue(i).GetQueueSize();
			}
			
			line << "__";
			
			InterfaceSourceRef src_iface = ab->GetSource();
			c = src_iface->GetSourceCount();
			for(int i = 0; i < c; i++) {
				if (i) line << "+";
				line << src_iface->GetSourceValue(i).GetQueueSize();
			}
			
		}
	}
	line << " |";
	return line;
}

void AtomSystem::ForwardAtoms(double dt, const char* id, LinkedList<AtomBaseRef>& atoms) {
	int dbg_i = 0;
	for (AtomBaseRef& c : atoms) {
		RealtimeSourceConfig* cfg = c->GetConfig();
		if (!cfg) {
			RTLOG("AtomSystem::ForwardAtoms: warning: GetConfig returns NULL");
			continue;
		}
		
		RTLOG("AtomSystem::ForwardAtoms: begin " << (String)id << " #" << dbg_i << " (" << c->ToString() << " " << HexStr(&*c) << ")");
		
		WhenEnterAtomForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, *cfg); scope; scope++) {
			RTLOG("AtomSystem::ForwardAtoms: loop id=" << c->GetId() << " " << HexStr(&*c) << " packets: " << GetDebugPacketString(c, cfg));
			
			if (!scope.IsBreak()) {
				RTLOG("AtomSystem::ForwardAtoms: " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.Forward();
				
				WhenLeaveFwdScopeForward();
			}
			else {
				RTLOG("AtomSystem::ForwardAtoms: weak try fwd " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.ForwardWeak();
				
				WhenLeaveFwdScopeForward();
			}
			
			if (scope.IsLoopComplete()) {
				RTLOG("AtomSystem::ForwardAtoms: loop complete");
			}
			else if (!scope) {
				RTLOG("AtomSystem::ForwardAtoms: scope flag dump: " << scope.GetFlagString());
			}
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


NAMESPACE_PARALLEL_END

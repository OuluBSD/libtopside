#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


SYS_DEF_VISIT_I(LinkSystem, vis && updated && customers && drivers && pollers)


void LinkSystem::ForwardLinks(double dt, const char* id, LinkedList<LinkBaseRef>& atoms) {
	int dbg_i = 0;
	for (LinkBaseRef& c : atoms) {
		RTLOG("LinkSystem::ForwardLinks: begin " << (String)id << " #" << dbg_i << " (" << c->ToString() << " " << HexStr(&*c) << ")");
		
		RealtimeSourceConfig* cfg = c->GetConfig();
		if (!cfg) {
			ASSERT(0); // this is not fatal necessarily. Probably some atom is stuck and won't send packets
			RTLOG("LinkSystem::ForwardLinks: warning: GetConfig returns NULL");
			continue;
		}
		
		WhenEnterLinkForward(&*c);
		
		int dbg_j = 0;
		for (FwdScope scope(*c, *cfg); scope; scope++) {
			RTLOG("LinkSystem::ForwardLinks: loop id=" << c->GetId() << " " << HexStr(&*c) << " packets: " << GetDebugPacketString(c, cfg));
			
			if (!scope.IsBreak()) {
				RTLOG("LinkSystem::ForwardLinks: " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.Forward();
				
				WhenLeaveFwdScopeForward();
			}
			else {
				RTLOG("LinkSystem::ForwardLinks: weak try fwd " << (String)id << " #" << dbg_i << " fwd #" << dbg_j++);
				WhenEnterFwdScopeForward(scope);
				
				scope.ForwardWeak();
				
				WhenLeaveFwdScopeForward();
			}
			
			if (scope.IsLoopComplete()) {
				RTLOG("LinkSystem::ForwardLinks: loop complete");
			}
			else if (!scope) {
				RTLOG("LinkSystem::ForwardLinks: scope flag dump: " << scope.GetFlagString());
			}
		}
		
		WhenLeaveLinkForward();
		dbg_i++;
	}
}


bool LinkSystem::Initialize() {
	ASSERT_(!GetMachine().Find<LinkStore>().IsEmpty(), "LinkStore must be added before LinkSystem");
	once_cbs.Create();
	return true;
}

void LinkSystem::Start() {
	
}

void LinkSystem::Update(double dt) {
	One<LinkedList<Once>> cbs;
	lock.Enter();
	cbs = once_cbs.Detach();
	once_cbs.Create();
	lock.Leave();
	
	for (Once& o : *cbs) {
		WhenEnterOnceForward(o.fwd);
		
		for (FwdScope scope(o.fwd, *o.cfg); scope; scope++) {
			WhenEnterFwdScopeForward(scope);
			
			scope.Forward();
			
			WhenLeaveFwdScopeForward();
		}
		
		WhenLeaveOnceForward();
	}
	
	for (LinkBaseRef& c : updated) {
		c->Update(dt);
	}
	
	for (LinkBaseRef& c : customers) {
		c->atom->UpdateConfig(dt);
	}
	
	ForwardLinks(dt, "customer", customers);
	ForwardLinks(dt, "driver", drivers);
	ForwardLinks(dt, "poller", pollers);
	ForwardLinks(dt, "updated", updated);
}


void LinkSystem::Stop() {
	
}

void LinkSystem::Uninitialize() {
	//Don't assert as empty... LinkSystem is uninitialized first, so go ahead....
	once_cbs.Clear();
	updated.Clear();
	customers.Clear();
	drivers.Clear();
	pollers.Clear();
	
	WhenUninit()();
}

void LinkSystem::AddUpdated(LinkBaseRef p) {
	if (p)
		updated.FindAdd(p);
}

void LinkSystem::AddCustomer(LinkBaseRef p) {
	if (p)
		customers.FindAdd(p);
}

void LinkSystem::AddDriver(LinkBaseRef p) {
	if (p)
		drivers.FindAdd(p);
}

void LinkSystem::AddPolling(LinkBaseRef p) {
	if (p)
		pollers.FindAdd(p);
}

void LinkSystem::RemoveUpdated(LinkBaseRef p) {
	updated.RemoveKey(p);
}

void LinkSystem::RemoveCustomer(LinkBaseRef p) {
	customers.RemoveKey(p);
}

void LinkSystem::RemoveDriver(LinkBaseRef p) {
	drivers.RemoveKey(p);
}

void LinkSystem::RemovePolling(LinkBaseRef p) {
	pollers.RemoveKey(p);
}


void LinkSystem::AddOnce(PacketForwarder& fwd, RealtimeSourceConfig& cfg) {
	lock.Enter();
	bool found = false;
	for (Once& o : *once_cbs) {
		if (o.fwd == &fwd && o.cfg == &cfg) {
			found = true;
			break;
		}
	}
	if (!found) {
		Once& o = once_cbs->Add();
		o.fwd = &fwd;
		o.cfg = &cfg;
	}
	lock.Leave();
}

String LinkSystem::GetDebugPacketString(LinkBaseRef& c, RealtimeSourceConfig* cfg) {
	int dbg_j = 0;
	
	String line;
	for (FwdScope scope(*c, *cfg); scope; scope++) {
		scope.ForwardAddNext();
		LinkBase* lb = CastPtr<LinkBase>(scope.GetCurrent());
		if (lb) {
			AtomBase* ab = lb->GetAtom();
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


NAMESPACE_SERIAL_END

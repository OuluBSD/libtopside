#include "ParallelCore.h"

  
NAMESPACE_PARALLEL_BEGIN




bool AtomSystem::Initialize() {
	
	return true;
}

void AtomSystem::Start() {
	
}

/*String AtomSystem::GetDebugPacketString(AtomBaseRef& c, RealtimeSourceConfig* cfg) {
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
}*/

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

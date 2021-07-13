#include "EonCore.h"

NAMESPACE_EON_BEGIN


SystemLoader::SystemLoader(Loader& parent, int id, GlobalScope& def) :
	Base(parent, id, def)
{
	
	for (MachineDefinition& mach : def.machs) {
		MachineLoader& loader = machs.Add(new MachineLoader(*this, machs.GetCount(), mach));
	}
	
}

String SystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (MachineLoader& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetStatusLine(indent+1, status);
	
	return s;
}

void SystemLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	for (MachineLoader& loader : machs) {
		Status s = loader.GetStatus();
		if (s != Status::OUTPUT_IS_WAITING &&
			s != Status::INPUT_IS_WAITING &&
			s != Status::READY) {
			loader.Forward();
		}
	}
}

void SystemLoader::LoopStatus() {
	for (MachineLoader& loader : machs) {
		CheckStatus(loader.GetStatus());
	}
}

void SystemLoader::GetLoops(Vector<LoopLoader*>& v) {
	for (MachineLoader& loader : machs) {
		loader.GetLoops(v);
	}
}

void SystemLoader::SetRetryDeep() {
	if (status == Status::READY)
		return;
	status = Status::IN_BEGINNING;
	for (MachineLoader& loader : machs)
		loader.SetRetryDeep();
}


NAMESPACE_EON_END

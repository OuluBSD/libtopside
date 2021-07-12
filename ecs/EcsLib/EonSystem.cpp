#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonSystemLoader::EonSystemLoader(EonLoader& parent, int id, Eon::GlobalScope& def) :
	Base(parent, id, def)
{
	
	for (Eon::MachineDefinition& mach : def.machs) {
		EonMachineLoader& loader = machs.Add(new EonMachineLoader(*this, machs.GetCount(), mach));
	}
	
}

String EonSystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (EonMachineLoader& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetEonStatusLine(indent+1, status);
	
	return s;
}

void EonSystemLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	for (EonMachineLoader& loader : machs) {
		EonStatus s = loader.GetStatus();
		if (s != EonStatus::OUTPUT_IS_WAITING &&
			s != EonStatus::INPUT_IS_WAITING &&
			s != EonStatus::READY) {
			loader.Forward();
		}
	}
}

void EonSystemLoader::LoopStatus() {
	for (EonMachineLoader& loader : machs) {
		CheckStatus(loader.GetStatus());
	}
}

void EonSystemLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	for (EonMachineLoader& loader : machs) {
		loader.GetLoops(v);
	}
}

void EonSystemLoader::SetRetryDeep() {
	if (status == EonStatus::READY)
		return;
	status = EonStatus::IN_BEGINNING;
	for (EonMachineLoader& loader : machs)
		loader.SetRetryDeep();
}


NAMESPACE_ECS_END

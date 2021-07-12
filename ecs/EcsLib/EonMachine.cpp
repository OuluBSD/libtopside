#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonMachineLoader::EonMachineLoader(EonSystemLoader& parent, int id, Eon::MachineDefinition& def) :
	Base(parent, id, def)
{
	
	for (Eon::ChainDefinition& chain : def.chains) {
		EonTopChainLoader& loader = chains.Add(new EonTopChainLoader(0, *this, 0, chains.GetCount(), chain));
	}
	
}

String EonMachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (EonTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetEonStatusLine(indent+1, status);
	
	return s;
}

void EonMachineLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	for (EonTopChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
}

void EonMachineLoader::ForwardLoops() {
	for (EonTopChainLoader& loader : chains) {
		EonStatus s = loader.GetStatus();
		if (s != EonStatus::OUTPUT_IS_WAITING &&
			s != EonStatus::INPUT_IS_WAITING &&
			s != EonStatus::READY) {
			loader.Forward();
		}
	}
}

void EonMachineLoader::LoopStatus() {
	for (EonTopChainLoader& loader : chains) {
		CheckStatus(loader.GetStatus());
	}
}

void EonMachineLoader::SetRetryDeep() {
	if (status == EonStatus::READY)
		return;
	status = EonStatus::IN_BEGINNING;
	for (EonTopChainLoader& loader : chains)
		loader.SetRetryDeep();
}


NAMESPACE_ECS_END

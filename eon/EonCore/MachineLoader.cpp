#include "EonCore.h"

NAMESPACE_EON_BEGIN


MachineLoader::MachineLoader(SystemLoader& parent, int id, MachineDefinition& def) :
	Base(parent, id, def)
{
	
	for (ChainDefinition& chain : def.chains) {
		TopChainLoader& loader = chains.Add(new TopChainLoader(0, *this, 0, chains.GetCount(), chain));
	}
	
}

String MachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (TopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetStatusLine(indent+1, status);
	
	return s;
}

void MachineLoader::GetLoops(Vector<LoopLoader*>& v) {
	for (TopChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
}

void MachineLoader::ForwardLoops() {
	for (TopChainLoader& loader : chains) {
		Status s = loader.GetStatus();
		if (s != Status::OUTPUT_IS_WAITING &&
			s != Status::INPUT_IS_WAITING &&
			s != Status::READY) {
			loader.Forward();
		}
	}
}

void MachineLoader::LoopStatus() {
	for (TopChainLoader& loader : chains) {
		CheckStatus(loader.GetStatus());
	}
}

void MachineLoader::SetRetryDeep() {
	if (status == Status::READY)
		return;
	status = Status::IN_BEGINNING;
	for (TopChainLoader& loader : chains)
		loader.SetRetryDeep();
}


NAMESPACE_EON_END

#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonMachineLoader::EonMachineLoader(EonSystemLoader& parent, int id, Eon::Machine& mach) :
	parent(parent),
	id(id),
	mach(mach)
{
	
	for (Eon::ChainDefinition& chain : mach.chains) {
		EonChainLoader& loader = chains.Add(new EonChainLoader(*this, 0, chains.GetCount(), chain));
	}
	
}

EonLoader& EonMachineLoader::GetLoader() {return parent.GetLoader();}

String EonMachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (EonChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	return s;
}

void EonMachineLoader::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		
		for (EonChainLoader& loader : chains) {
			loader.Forward();
		}
		
	}
	else {
		TODO
	}
	
}


NAMESPACE_ECS_END

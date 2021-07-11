#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonSystemLoader::EonSystemLoader(EonLoader& parent, int id, Eon::GlobalScope& glob) :
	parent(parent),
	id(id),
	glob(glob)
{
	
	for (Eon::Machine& mach : glob.machs) {
		EonMachineLoader& loader = machs.Add(new EonMachineLoader(*this, machs.GetCount(), mach));
	}
	
}

EonLoader& EonSystemLoader::GetLoader() {return parent;}

String EonSystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (EonMachineLoader& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	return s;
}

void EonSystemLoader::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		
		for (EonMachineLoader& loader : machs) {
			loader.Forward();
		}
		
	}
	else {
		TODO
	}
	
}


NAMESPACE_ECS_END

#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonChainLoader::EonChainLoader(EonTopChainLoader& parent, int id, Eon::ChainDefinition& def) :
	Base(parent, id, def)
{
	
	for (Eon::LoopDefinition& loop : def.loops) {
		EonLoopLoader& loader = loops.Add(new EonLoopLoader(*this, loops.GetCount(), loop));
	}
	
}

String EonChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Chain " << id;
	s.Cat('\n');
	for (EonLoopLoader& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetEonStatusLine(indent+1, status);
	
	return s;
}

void EonChainLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	for (EonLoopLoader& loader : loops) {
		v.Add(&loader);
	}
}

void EonChainLoader::ForwardLoops() {
	for (EonLoopLoader& loader : loops) {
		EonStatus s = loader.GetStatus();
		if (s != EonStatus::OUTPUT_IS_WAITING &&
			s != EonStatus::INPUT_IS_WAITING &&
			s != EonStatus::READY) {
			loader.Forward();
		}
	}
}

void EonChainLoader::LoopStatus() {
	for (EonLoopLoader& loader : loops) {
		CheckStatus(loader.GetStatus());
	}
}

void EonChainLoader::SetRetryDeep() {
	if (status == EonStatus::READY)
		return;
	status = EonStatus::IN_BEGINNING;
	for (EonLoopLoader& loader : loops)
		loader.SetRetryDeep();
}


NAMESPACE_ECS_END

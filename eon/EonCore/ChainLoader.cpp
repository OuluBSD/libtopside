#include "EonCore.h"

NAMESPACE_EON_BEGIN



ChainLoader::ChainLoader(TopChainLoader& parent, int id, ChainDefinition& def) :
	Base(parent, id, def)
{
	
	for (LoopDefinition& loop : def.loops) {
		LoopLoader& loader = loops.Add(new LoopLoader(*this, loops.GetCount(), loop));
	}
	
}

String ChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Chain " << id;
	s.Cat('\n');
	for (LoopLoader& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetStatusLine(indent+1, status);
	
	return s;
}

void ChainLoader::GetLoops(Vector<LoopLoader*>& v) {
	for (LoopLoader& loader : loops) {
		v.Add(&loader);
	}
}

void ChainLoader::ForwardLoops() {
	for (LoopLoader& loader : loops) {
		Status s = loader.GetStatus();
		if (s != Status::OUTPUT_IS_WAITING &&
			s != Status::INPUT_IS_WAITING &&
			s != Status::READY) {
			loader.Forward();
		}
	}
}

void ChainLoader::LoopStatus() {
	for (LoopLoader& loader : loops) {
		CheckStatus(loader.GetStatus());
	}
}

void ChainLoader::SetRetryDeep() {
	if (status == Status::READY)
		return;
	status = Status::IN_BEGINNING;
	for (LoopLoader& loader : loops)
		loader.SetRetryDeep();
}



NAMESPACE_EON_END

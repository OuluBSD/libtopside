#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonChainLoader::EonChainLoader(EonMachineLoader& mach_parent, EonChainLoader* chain_parent, int id, Eon::ChainDefinition& chain) :
	mach_parent(mach_parent),
	chain_parent(chain_parent),
	id(id),
	chain(chain)
{
	
	for (Eon::LoopDefinition& loop : chain.loops) {
		EonLoopLoader& loader = loops.Add(new EonLoopLoader(loops.GetCount(), this, loop));
	}
	
	for (Eon::ChainDefinition& chain : chain.subchains) {
		EonChainLoader& loader = chains.Add(new EonChainLoader(mach_parent, this, chains.GetCount(), chain));
	}
	
}

EonLoader& EonChainLoader::GetLoader() {return mach_parent.GetLoader();}

String EonChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Chain " << id;
	s.Cat('\n');
	for (EonChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	for (EonLoopLoader& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	return s;
}

void EonChainLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	for (EonChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
	for (EonLoopLoader& loader : loops) {
		v.Add(&loader);
	}
}

void EonChainLoader::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		
		for (EonLoopLoader& loader : loops) {
			loader.Forward();
			
			if (loader.GetStatus() == EonStatus::WAITING_SIDE_INPUT_LOOP ||
				loader.GetStatus() == EonStatus::WAITING_SIDE_OUTPUT_LOOP) {
				status = EonStatus::SOLVE_INTERNAL_CONNECTIONS;
			}
		}
		
		for (EonChainLoader& loader : chains) {
			loader.Forward();
			
			if (loader.GetStatus() == EonStatus::WAITING_SIDE_INPUT_LOOP ||
				loader.GetStatus() == EonStatus::WAITING_SIDE_OUTPUT_LOOP) {
				status = EonStatus::SOLVE_INTERNAL_CONNECTIONS;
			}
		}
		
		if (status == EonStatus::SOLVE_INTERNAL_CONNECTIONS) {
			EonConnectionSolver conn(GetLoader().tmp_side_id_counter);
			if (conn.Solve(this)) {
				status = EonStatus::RETRY;
			}
			else {
				if (conn.IsMissingInput()) {
					status = EonStatus::WAITING_SIDE_INPUT_CHAIN;
				}
				else if (conn.IsMissingOutput()) {
					status = EonStatus::WAITING_SIDE_OUTPUT_CHAIN;
				}
				else {
					LOG(conn.GetError());
					// check error and not-found
					TODO
				}
			}
		}
	}
	else {
		TODO
	}
	
}


NAMESPACE_ECS_END

#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonTopChainLoader::EonTopChainLoader(int mode, EonMachineLoader& parent, EonTopChainLoader* chain_parent, int id, Eon::ChainDefinition& def) :
	Base(parent, id, def),
	chain_parent(chain_parent)
{
	if (mode == NORMAL) {
		if (def.loops.GetCount()) {
			use_subchains = true;
			EonTopChainLoader& for_subchains = subchains.Add(new EonTopChainLoader(SPLITTED_CHAIN, parent, this, subchains.GetCount(), def));
			EonTopChainLoader& for_loops = subchains.Add(new EonTopChainLoader(SPLITTED_LOOPS, parent, this, subchains.GetCount(), def));
		}
		else {
			mode = SPLITTED_CHAIN;
		}
	}
	
	if (mode == SPLITTED_CHAIN) {
		bool all_subchains_terminal = true;
		for (Eon::ChainDefinition& subchain : def.subchains)
			if (!subchain.subchains.IsEmpty())
				all_subchains_terminal = false;
		
		if (all_subchains_terminal) {
			use_subchains = false;
			for (Eon::ChainDefinition& subchain : def.subchains) {
				EonChainLoader& loader = chains.Add(new EonChainLoader(*this, chains.GetCount(), subchain));
			}
		}
		else {
			use_subchains = true;
			for (Eon::ChainDefinition& subchain : def.subchains) {
				EonTopChainLoader& loader = subchains.Add(new EonTopChainLoader(NORMAL, parent, this, subchains.GetCount(), subchain));
			}
		}
			
	}
	else if (mode == SPLITTED_LOOPS) {
		use_subchains = false;
		EonChainLoader& loader = chains.Add(new EonChainLoader(*this, chains.GetCount(), def));
	}
}

String EonTopChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "TopChain " << id;
	s.Cat('\n');
	if (use_subchains) {
		ASSERT(chains.IsEmpty());
		for (EonTopChainLoader& loader : subchains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	else {
		ASSERT(subchains.IsEmpty());
		for (EonChainLoader& loader : chains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	s << GetEonStatusLine(indent+1, status);
	
	return s;
}

void EonTopChainLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	if (use_subchains) {
		for (EonTopChainLoader& loader : subchains) {
			loader.GetLoops(v);
		}
	}
	else {
		for (EonChainLoader& loader : chains) {
			loader.GetLoops(v);
		}
	}
}

void EonTopChainLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (use_subchains)
		ForwardSubchainLoops();
	else
		ForwardChainLoops();
}

void EonTopChainLoader::LoopStatus() {
	if (use_subchains) {
		for (EonTopChainLoader& loader : subchains) {
			CheckStatus(loader.GetStatus());
		}
	}
	else {
		for (EonChainLoader& loader : chains) {
			CheckStatus(loader.GetStatus());
		}
	}
}

void EonTopChainLoader::SetRetryDeep() {
	if (status == EonStatus::READY)
		return;
	status = EonStatus::IN_BEGINNING;
	if (use_subchains) {
		for (EonTopChainLoader& loader : subchains)
			loader.SetRetryDeep();
	}
	else {
		for (EonChainLoader& loader : chains)
			loader.SetRetryDeep();
	}
}

void EonTopChainLoader::ForwardSubchainLoops() {
	for (EonTopChainLoader& loader : subchains) {
		EonStatus s = loader.GetStatus();
		if (s != EonStatus::OUTPUT_IS_WAITING &&
			s != EonStatus::INPUT_IS_WAITING &&
			s != EonStatus::READY) {
			loader.Forward();
		}
	}
}


void EonTopChainLoader::ForwardChainLoops() {
	for (EonChainLoader& loader : chains) {
		EonStatus s = loader.GetStatus();
		if (s != EonStatus::OUTPUT_IS_WAITING &&
			s != EonStatus::INPUT_IS_WAITING &&
			s != EonStatus::READY) {
			loader.Forward();
		}
	}
}
/*
void EonTopChainLoader::ForwardSubchain() {
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		bool any_waiting = false;
		bool any_retrying = false;
		
		for (EonTopChainLoader& loader : subchains) {
			EonStatus s = loader.GetStatus();
			if (s != EonStatus::CHAIN_OUTPUT_IS_WAITING &&
				s != EonStatus::CHAIN_INPUT_IS_WAITING) {
				loader.Forward();
			}
			
			s = loader.GetStatus();
			if (s == EonStatus::CHAIN_OUTPUT_IS_WAITING ||
				s == EonStatus::CHAIN_INPUT_IS_WAITING) {
				any_waiting = true;
			}
			else if (s == EonStatus::IN_BEGINNING || s == EonStatus::RETRY) {
				any_retrying = true;
			}
		}
		
		if (any_retrying) {
			status = EonStatus::IN_BEGINNING;
			return;
		}
		else if (any_waiting) {
			status = EonStatus::SOLVE_INTERNAL_CONNECTIONS;
		}
		
		SolveInternal();
	}
	else {
		TODO
	}
}

void EonTopChainLoader::ForwardChain() {
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		bool any_waiting = false;
		bool any_retrying = false;
		
		for (EonChainLoader& loader : chains) {
			EonStatus s = loader.GetStatus();
			if (s != EonStatus::CHAIN_OUTPUT_IS_WAITING &&
				s != EonStatus::CHAIN_INPUT_IS_WAITING) {
				loader.Forward();
			}
			
			s = loader.GetStatus();
			if (s == EonStatus::CHAIN_OUTPUT_IS_WAITING ||
				s == EonStatus::CHAIN_INPUT_IS_WAITING) {
				any_waiting = true;
			}
			else if (s == EonStatus::IN_BEGINNING || s == EonStatus::RETRY) {
				any_retrying = true;
			}
		}
		
		if (any_retrying) {
			status = EonStatus::IN_BEGINNING;
			return;
		}
		else if (any_waiting) {
			status = EonStatus::SOLVE_INTERNAL_CONNECTIONS;
		}
		
		SolveInternal();
	}
	else if (status == EonStatus::CHAIN_INPUT_IS_WAITING) {
		
		TODO
		
	}
	else {
		TODO
	}
	
}*/




NAMESPACE_ECS_END

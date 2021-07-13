#include "EonCore.h"


NAMESPACE_EON_BEGIN


TopChainLoader::TopChainLoader(int mode, MachineLoader& parent, TopChainLoader* chain_parent, int id, ChainDefinition& def) :
	Base(parent, id, def),
	chain_parent(chain_parent)
{
	if (mode == NORMAL) {
		if (def.loops.GetCount()) {
			use_subchains = true;
			TopChainLoader& for_subchains = subchains.Add(new TopChainLoader(SPLITTED_CHAIN, parent, this, subchains.GetCount(), def));
			TopChainLoader& for_loops = subchains.Add(new TopChainLoader(SPLITTED_LOOPS, parent, this, subchains.GetCount(), def));
		}
		else {
			mode = SPLITTED_CHAIN;
		}
	}
	
	if (mode == SPLITTED_CHAIN) {
		bool all_subchains_terminal = true;
		for (ChainDefinition& subchain : def.subchains)
			if (!subchain.subchains.IsEmpty())
				all_subchains_terminal = false;
		
		if (all_subchains_terminal) {
			use_subchains = false;
			for (ChainDefinition& subchain : def.subchains) {
				ChainLoader& loader = chains.Add(new ChainLoader(*this, chains.GetCount(), subchain));
			}
		}
		else {
			use_subchains = true;
			for (ChainDefinition& subchain : def.subchains) {
				TopChainLoader& loader = subchains.Add(new TopChainLoader(NORMAL, parent, this, subchains.GetCount(), subchain));
			}
		}
			
	}
	else if (mode == SPLITTED_LOOPS) {
		use_subchains = false;
		ChainLoader& loader = chains.Add(new ChainLoader(*this, chains.GetCount(), def));
	}
}

String TopChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "TopChain " << id;
	s.Cat('\n');
	if (use_subchains) {
		ASSERT(chains.IsEmpty());
		for (TopChainLoader& loader : subchains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	else {
		ASSERT(subchains.IsEmpty());
		for (ChainLoader& loader : chains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	s << GetStatusLine(indent+1, status);
	
	return s;
}

void TopChainLoader::GetLoops(Vector<LoopLoader*>& v) {
	if (use_subchains) {
		for (TopChainLoader& loader : subchains) {
			loader.GetLoops(v);
		}
	}
	else {
		for (ChainLoader& loader : chains) {
			loader.GetLoops(v);
		}
	}
}

void TopChainLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (use_subchains)
		ForwardSubchainLoops();
	else
		ForwardChainLoops();
}

void TopChainLoader::LoopStatus() {
	if (use_subchains) {
		for (TopChainLoader& loader : subchains) {
			CheckStatus(loader.GetStatus());
		}
	}
	else {
		for (ChainLoader& loader : chains) {
			CheckStatus(loader.GetStatus());
		}
	}
}

void TopChainLoader::SetRetryDeep() {
	if (status == Status::READY)
		return;
	status = Status::IN_BEGINNING;
	if (use_subchains) {
		for (TopChainLoader& loader : subchains)
			loader.SetRetryDeep();
	}
	else {
		for (ChainLoader& loader : chains)
			loader.SetRetryDeep();
	}
}

void TopChainLoader::ForwardSubchainLoops() {
	for (TopChainLoader& loader : subchains) {
		Status s = loader.GetStatus();
		if (s != Status::OUTPUT_IS_WAITING &&
			s != Status::INPUT_IS_WAITING &&
			s != Status::READY) {
			loader.Forward();
		}
	}
}


void TopChainLoader::ForwardChainLoops() {
	for (ChainLoader& loader : chains) {
		Status s = loader.GetStatus();
		if (s != Status::OUTPUT_IS_WAITING &&
			s != Status::INPUT_IS_WAITING &&
			s != Status::READY) {
			loader.Forward();
		}
	}
}
/*
void TopChainLoader::ForwardSubchain() {
	
	if (status == Status::IN_BEGINNING || status == Status::RETRY) {
		bool any_waiting = false;
		bool any_retrying = false;
		
		for (TopChainLoader& loader : subchains) {
			Status s = loader.GetStatus();
			if (s != Status::CHAIN_OUTPUT_IS_WAITING &&
				s != Status::CHAIN_INPUT_IS_WAITING) {
				loader.Forward();
			}
			
			s = loader.GetStatus();
			if (s == Status::CHAIN_OUTPUT_IS_WAITING ||
				s == Status::CHAIN_INPUT_IS_WAITING) {
				any_waiting = true;
			}
			else if (s == Status::IN_BEGINNING || s == Status::RETRY) {
				any_retrying = true;
			}
		}
		
		if (any_retrying) {
			status = Status::IN_BEGINNING;
			return;
		}
		else if (any_waiting) {
			status = Status::SOLVE_INTERNAL_CONNECTIONS;
		}
		
		SolveInternal();
	}
	else {
		TODO
	}
}

void TopChainLoader::ForwardChain() {
	
	if (status == Status::IN_BEGINNING || status == Status::RETRY) {
		bool any_waiting = false;
		bool any_retrying = false;
		
		for (ChainLoader& loader : chains) {
			Status s = loader.GetStatus();
			if (s != Status::CHAIN_OUTPUT_IS_WAITING &&
				s != Status::CHAIN_INPUT_IS_WAITING) {
				loader.Forward();
			}
			
			s = loader.GetStatus();
			if (s == Status::CHAIN_OUTPUT_IS_WAITING ||
				s == Status::CHAIN_INPUT_IS_WAITING) {
				any_waiting = true;
			}
			else if (s == Status::IN_BEGINNING || s == Status::RETRY) {
				any_retrying = true;
			}
		}
		
		if (any_retrying) {
			status = Status::IN_BEGINNING;
			return;
		}
		else if (any_waiting) {
			status = Status::SOLVE_INTERNAL_CONNECTIONS;
		}
		
		SolveInternal();
	}
	else if (status == Status::CHAIN_INPUT_IS_WAITING) {
		
		TODO
		
	}
	else {
		TODO
	}
	
}*/


NAMESPACE_EON_END

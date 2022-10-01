#include "Internal.h"

#if 0

NAMESPACE_SERIAL_BEGIN


ScriptTopChainLoader::ScriptTopChainLoader(int mode, ScriptMachineLoader& parent, ScriptTopChainLoader* chain_parent, int id, Script::ChainDefinition& def) :
	Base(parent, id, def),
	chain_parent(chain_parent)
{
	if (mode == NORMAL) {
		if (def.loops.GetCount()) {
			use_subchains = true;
			ScriptTopChainLoader& for_subchains = subchains.Add(new ScriptTopChainLoader(SPLITTED_CHAIN, parent, this, subchains.GetCount(), def));
			ScriptTopChainLoader& for_loops = subchains.Add(new ScriptTopChainLoader(SPLITTED_LOOPS, parent, this, subchains.GetCount(), def));
		}
		else {
			mode = SPLITTED_CHAIN;
		}
	}
	
	if (mode == SPLITTED_CHAIN) {
		bool all_subchains_terminal = true;
		for (Script::ChainDefinition& subchain : def.subchains)
			if (!subchain.subchains.IsEmpty())
				all_subchains_terminal = false;
		
		if (all_subchains_terminal) {
			use_subchains = false;
			for (Script::ChainDefinition& subchain : def.subchains) {
				ScriptChainLoader& loader = chains.Add(new ScriptChainLoader(*this, chains.GetCount(), subchain));
			}
		}
		else {
			use_subchains = true;
			for (Script::ChainDefinition& subchain : def.subchains) {
				ScriptTopChainLoader& loader = subchains.Add(new ScriptTopChainLoader(NORMAL, parent, this, subchains.GetCount(), subchain));
			}
		}
			
	}
	else if (mode == SPLITTED_LOOPS) {
		use_subchains = false;
		ScriptChainLoader& loader = chains.Add(new ScriptChainLoader(*this, chains.GetCount(), def));
	}
}

String ScriptTopChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "TopChain " << id;
	s.Cat('\n');
	if (use_subchains) {
		ASSERT(chains.IsEmpty());
		for (ScriptTopChainLoader& loader : subchains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	else {
		ASSERT(subchains.IsEmpty());
		for (ScriptChainLoader& loader : chains) {
			s << loader.GetTreeString(indent+1);
		}
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptTopChainLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	if (use_subchains) {
		for (ScriptTopChainLoader& loader : subchains) {
			loader.GetLoops(v);
		}
	}
	else {
		for (ScriptChainLoader& loader : chains) {
			loader.GetLoops(v);
		}
	}
}

void ScriptTopChainLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	if (use_subchains) {
		for (ScriptTopChainLoader& loader : subchains) {
			loader.GetStates(v);
		}
	}
	else {
		for (ScriptChainLoader& loader : chains) {
			loader.GetStates(v);
		}
	}
}

void ScriptTopChainLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (use_subchains)
		ForwardSubchainLoops();
	else
		ForwardChainLoops();
}

void ScriptTopChainLoader::LoopStatus() {
	if (use_subchains) {
		for (ScriptTopChainLoader& loader : subchains) {
			CheckStatus(loader.GetStatus());
		}
	}
	else {
		for (ScriptChainLoader& loader : chains) {
			CheckStatus(loader.GetStatus());
		}
	}
}

void ScriptTopChainLoader::CheckStatusDeep() {
	if (use_subchains) {
		for (ScriptTopChainLoader& loader : subchains)
			loader.CheckStatusDeep();
	}
	else {
		for (ScriptChainLoader& loader : chains)
			loader.CheckStatusDeep();
	}
	
	CheckFlags();
}

void ScriptTopChainLoader::ForwardSubchainLoops() {
	if (status == WAITING_CHILDREN) {
		for (ScriptTopChainLoader& loader : subchains) {
			loader.Forward();
		}
	}
	else TODO
}

void ScriptTopChainLoader::ForwardChainLoops() {
	if (status == WAITING_CHILDREN) {
		for (ScriptChainLoader& loader : chains) {
			loader.Forward();
		}
	}
	else TODO
}


NAMESPACE_SERIAL_END

#endif

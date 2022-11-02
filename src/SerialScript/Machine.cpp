#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptMachineLoader::ScriptMachineLoader(ScriptSystemLoader& parent, int id, Script::MachineDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::ChainDefinition& chain : def.chains) {
		ScriptTopChainLoader& loader = chains.Add(new ScriptTopChainLoader(0, *this, 0, chains.GetCount(), chain));
	}
	
}

bool ScriptMachineLoader::Load() {
	TODO
}

String ScriptMachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (ScriptTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	
	return s;
}

void ScriptMachineLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptTopChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
}

void ScriptMachineLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	for (ScriptTopChainLoader& loader : chains) {
		loader.GetStates(v);
	}
}


NAMESPACE_SERIAL_END

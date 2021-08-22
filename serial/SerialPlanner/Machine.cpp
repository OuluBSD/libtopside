#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN


ScriptMachineLoader::ScriptMachineLoader(ScriptSystemLoader& parent, int id, Script::MachineDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::ChainDefinition& chain : def.chains) {
		ScriptTopChainLoader& loader = chains.Add(new ScriptTopChainLoader(0, *this, 0, chains.GetCount(), chain));
	}
	
}

String ScriptMachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (ScriptTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptMachineLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptTopChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
}

void ScriptMachineLoader::ForwardLoops() {
	for (ScriptTopChainLoader& loader : chains) {
		ScriptStatus s = loader.GetStatus();
		if (s != ScriptStatus::OUTPUT_IS_WAITING &&
			s != ScriptStatus::INPUT_IS_WAITING &&
			s != ScriptStatus::READY) {
			loader.Forward();
		}
	}
}

void ScriptMachineLoader::LoopStatus() {
	for (ScriptTopChainLoader& loader : chains) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptMachineLoader::SetRetryDeep() {
	if (status == ScriptStatus::READY)
		return;
	status = ScriptStatus::IN_BEGINNING;
	for (ScriptTopChainLoader& loader : chains)
		loader.SetRetryDeep();
}


NAMESPACE_SERIAL_END

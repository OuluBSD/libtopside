#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptMachineLoader::ScriptMachineLoader(ScriptSystemLoader& parent, int id, Script::MachineDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::DriverDefinition& drv : def.drivers) {
		drivers.Add(new ScriptDriverLoader(*this, drivers.GetCount(), drv));
	}
	
	for (Script::ChainDefinition& chain : def.chains) {
		ScriptTopChainLoader& loader = chains.Add(new ScriptTopChainLoader(0, *this, 0, chains.GetCount(), chain));
	}
	
}

String ScriptMachineLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Machine " << id;
	s.Cat('\n');
	for (ScriptDriverLoader& loader : drivers) {
		s << loader.GetTreeString(indent+1);
	}
	for (ScriptTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptMachineLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptDriverLoader& loader : drivers) {
		loader.GetLoops(v);
	}
	for (ScriptTopChainLoader& loader : chains) {
		loader.GetLoops(v);
	}
}

void ScriptMachineLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	for (ScriptDriverLoader& loader : drivers) {
		loader.GetDrivers(v);
	}
}

void ScriptMachineLoader::ForwardLoops() {
	
	for (ScriptDriverLoader& loader : drivers) {
		ScriptStatus s = loader.GetStatus();
		if (s != ScriptStatus::SINK_IS_WAITING &&
			s != ScriptStatus::SOURCE_IS_WAITING &&
			s != ScriptStatus::READY) {
			loader.Forward();
		}
	}
	
	for (ScriptTopChainLoader& loader : chains) {
		ScriptStatus s = loader.GetStatus();
		if (s != ScriptStatus::SINK_IS_WAITING &&
			s != ScriptStatus::SOURCE_IS_WAITING &&
			s != ScriptStatus::READY) {
			loader.Forward();
		}
	}
	
}

void ScriptMachineLoader::LoopStatus() {
	
	for (ScriptDriverLoader& loader : drivers) {
		CheckStatus(loader.GetStatus());
	}
	
	for (ScriptTopChainLoader& loader : chains) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptMachineLoader::SetRetryDeep() {
	if (status == ScriptStatus::READY)
		return;
	
	SetStatus(ScriptStatus::IN_BEGINNING);
	
	TODO
	
	for (ScriptTopChainLoader& loader : chains)
		loader.SetRetryDeep();
}


NAMESPACE_SERIAL_END

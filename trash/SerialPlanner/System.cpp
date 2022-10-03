#include "SerialScript.h"


NAMESPACE_SERIAL_BEGIN


ScriptSystemLoader::ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& def) :
	Base(parent, id, def)
{
	
	for (Script::MachineDefinition& mach : def.machs) {
		ScriptMachineLoader& loader = machs.Add(new ScriptMachineLoader(*this, machs.GetCount(), mach));
	}
	
	for (Script::EngineDefinition& eng : def.engs) {
		ScriptEngineLoader& loader = engs.Add(new ScriptEngineLoader(*this, engs.GetCount(), eng));
	}
	
}

bool ScriptSystemLoader::LoadEcs() {
	
	if (engs.GetCount() > 1) {
		SetError("Only one engine is supported currently, and script got " + IntStr(engs.GetCount()));
		return false;
	}
	
	if (engs.GetCount() && !__ecs_script_loader) {
		SetError("Script defines ecs engines, but no ecs loading is built-in to the executable program.");
		return false;
	}
	
	for (ScriptEngineLoader& e : engs) {
		if (!__ecs_script_loader->Load(e)) {
			SetError(__ecs_script_loader->GetErrorString());
			return false;
		}
	}
	
	return true;
}

String ScriptSystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (ScriptMachineLoader& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

/*void ScriptSystemLoader::ForwardLoops() {
	if (status == WAITING_CHILDREN) {
		for (ScriptMachineLoader& loader : machs) {
			loader.Forward();
		}
	}
	else TODO
}*/

/*void ScriptSystemLoader::LoopStatus() {
	for (ScriptMachineLoader& loader : machs) {
		CheckStatus(loader.GetStatus());
	}
}*/

void ScriptSystemLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptMachineLoader& loader : machs) {
		loader.GetLoops(v);
	}
}

void ScriptSystemLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	for (ScriptMachineLoader& loader : machs) {
		loader.GetDrivers(v);
	}
}

void ScriptSystemLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	for (ScriptMachineLoader& loader : machs) {
		loader.GetStates(v);
	}
}

void ScriptSystemLoader::CheckStatusDeep() {
	for (ScriptMachineLoader& loader : machs)
		loader.CheckStatusDeep();
	
	CheckFlags();
}


NAMESPACE_SERIAL_END

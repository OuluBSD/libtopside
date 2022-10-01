#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


ScriptSystemLoader::ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& def) :
	Base(parent, id, def)
{
	for (Script::LoopDefinition& loop : def.loops) {
		ScriptLoopLoader& loader = loops.Add(new ScriptLoopLoader(*this, loops.GetCount(), loop));
	}
	
	for (Script::DriverDefinition& driver : def.drivers) {
		ScriptDriverLoader& loader = drivers.Add(new ScriptDriverLoader(*this, drivers.GetCount(), driver));
	}
	
	for (Script::StateDeclaration& state : def.states) {
		ScriptStateLoader& loader = states.Add(new ScriptStateLoader(*this, states.GetCount(), state));
	}
	
}

bool ScriptSystemLoader::Load() {
	for (auto& loader : states) {
		if (!loader.Load())
			return false;
	}
	for (auto& loader : drivers) {
		if (!loader.Load())
			return false;
	}
	for (auto& loader : loops) {
		if (!loader.Load())
			return false;
	}
	return true;
}

bool ScriptSystemLoader::LoadEcs() {
	
	TODO
	/*if (engs.GetCount() > 1) {
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
	}*/
	
	return true;
}

String ScriptSystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (auto& loader : states) {
		s << loader.GetTreeString(indent+1);
	}
	for (auto& loader : drivers) {
		s << loader.GetTreeString(indent+1);
	}
	for (auto& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	//s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptSystemLoader::ForwardLoops() {
	TODO
	/*
	if (status == WAITING_CHILDREN) {
		for (ScriptMachineLoader& loader : machs) {
			loader.Forward();
		}
	}
	else TODO*/
}

void ScriptSystemLoader::LoopStatus() {
	TODO
	/*for (ScriptMachineLoader& loader : machs) {
		CheckStatus(loader.GetStatus());
	}*/
}

void ScriptSystemLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (auto& loader : loops) {
		v.Add(&loader);
	}
}

void ScriptSystemLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	for (auto& loader : drivers) {
		v.Add(&loader);
	}
}

void ScriptSystemLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	for (auto& loader : states) {
		v.Add(&loader);
	}
}

void ScriptSystemLoader::CheckStatusDeep() {
	TODO
	/*for (ScriptMachineLoader& loader : machs)
		loader.CheckStatusDeep();
	
	CheckFlags();*/
}


NAMESPACE_SERIAL_END

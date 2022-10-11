#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


ScriptSystemLoader::ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& def) :
	Base(parent, id, def)
{
	
	for (Script::MachineDefinition& mach : def.machs) {
		ScriptMachineLoader& loader = machs.Add(new ScriptMachineLoader(*this, machs.GetCount(), mach));
	}
	
	for (Script::WorldDefinition& world : def.worlds) {
		ScriptWorldLoader& loader = worlds.Add(new ScriptWorldLoader(*this, worlds.GetCount(), world));
	}
	
	/*for (Script::LoopDefinition& loop : def.loops) {
		ScriptLoopLoader& loader = loops.Add(new ScriptLoopLoader(*this, loops.GetCount(), loop));
	}
	
	for (Script::DriverDefinition& driver : def.drivers) {
		ScriptDriverLoader& loader = drivers.Add(new ScriptDriverLoader(*this, drivers.GetCount(), driver));
	}
	
	for (Script::StateDeclaration& state : def.states) {
		ScriptStateLoader& loader = states.Add(new ScriptStateLoader(*this, states.GetCount(), state));
	}*/
	
}

bool ScriptSystemLoader::Load() {
	for (auto& loader : machs) {
		if (!loader.Load())
			return false;
	}
	for (auto& loader : worlds) {
		if (!loader.Load())
			return false;
	}
	/*for (auto& loader : states) {
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
	}*/
	
	//status = READY;
	return true;
}

bool ScriptSystemLoader::LoadEcs() {
	
	if (worlds.GetCount() > 1) {
		AddError(def.loc, "Only one world is supported currently, and script got " + IntStr(worlds.GetCount()));
		return false;
	}
	
	for (ScriptWorldLoader& e : worlds) {
		if (!__ecs_script_loader) {
			AddError(def.loc, "no ecs script loader present in system");
			return false;
		}
		
		if (!__ecs_script_loader->Load(e)) {
			AddError(def.loc, __ecs_script_loader->GetErrorString());
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
	/*for (auto& loader : states) {
		s << loader.GetTreeString(indent+1);
	}
	for (auto& loader : drivers) {
		s << loader.GetTreeString(indent+1);
	}
	for (auto& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}*/
	for (auto& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	for (auto& loader : worlds) {
		s << loader.GetTreeString(indent+1);
	}
	//s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptSystemLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (auto& loader : machs) {
		loader.GetLoops(v);
	}
}

void ScriptSystemLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	for (auto& loader : machs) {
		loader.GetDrivers(v);
	}
}

void ScriptSystemLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	for (auto& loader : machs) {
		loader.GetStates(v);
	}
}


NAMESPACE_SERIAL_END

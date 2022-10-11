#include "SerialScript.h"


NAMESPACE_SERIAL_BEGIN


ScriptWorldLoader::ScriptWorldLoader(ScriptSystemLoader& parent, int id, Script::WorldDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::EcsSysDefinition& sys : def.systems) {
		systems.Add(new ScriptEcsSystemLoader(*this, systems.GetCount(), sys));
	}
	
	for (Script::PoolDefinition& pool : def.pools) {
		pools.Add(new ScriptPoolLoader(*this, 0, pools.GetCount(), pool));
	}
	
}

bool ScriptWorldLoader::Load() {
	TODO
}

String ScriptWorldLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Engine " << id;
	s.Cat('\n');
	for (ScriptEcsSystemLoader& loader : systems) {
		s << loader.GetTreeString(indent+1);
	}
	for (ScriptPoolLoader& loader : pools) {
		s << loader.GetTreeString(indent+1);
	}
	//s << GetScriptStatusLine(indent+1, status);
	
	return s;
}




ExtScriptEcsLoaderBase* __ecs_script_loader;


/*
void ScriptWorldLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	
}

void ScriptWorldLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	
}

void ScriptWorldLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	
}

void ScriptWorldLoader::ForwardLoops() {
	
	if (status == WAITING_CHILDREN) {
		for (ScriptEcsSystemLoader& loader : systems) {
			loader.Forward();
		}
		
		for (ScriptPoolLoader& loader : pools) {
			loader.Forward();
		}
	}
	else TODO
	
}

void ScriptWorldLoader::LoopStatus() {
	
	for (ScriptEcsSystemLoader& loader : systems) {
		CheckStatus(loader.GetStatus());
	}
	
	for (ScriptPoolLoader& loader : pools) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptWorldLoader::CheckStatusDeep() {
	
	CheckFlags();
}
*/

NAMESPACE_SERIAL_END


#include "SerialScript.h"

#if 0

NAMESPACE_SERIAL_BEGIN


ScriptEngineLoader::ScriptEngineLoader(ScriptSystemLoader& parent, int id, Script::EngineDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::EcsSysDefinition& sys : def.systems) {
		systems.Add(new ScriptEcsSystemLoader(*this, systems.GetCount(), sys));
	}
	
	for (Script::PoolDefinition& pool : def.pools) {
		pools.Add(new ScriptPoolLoader(*this, 0, pools.GetCount(), pool));
	}
	
}

String ScriptEngineLoader::GetTreeString(int indent) {
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




ExtScriptEngineLoaderBase* __ecs_script_loader;


/*
void ScriptEngineLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	
}

void ScriptEngineLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	
}

void ScriptEngineLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	
}

void ScriptEngineLoader::ForwardLoops() {
	
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

void ScriptEngineLoader::LoopStatus() {
	
	for (ScriptEcsSystemLoader& loader : systems) {
		CheckStatus(loader.GetStatus());
	}
	
	for (ScriptPoolLoader& loader : pools) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptEngineLoader::CheckStatusDeep() {
	
	CheckFlags();
}
*/

NAMESPACE_SERIAL_END

#endif

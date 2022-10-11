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
	
	return s;
}


ExtScriptEcsLoaderBase* __ecs_script_loader;



NAMESPACE_SERIAL_END


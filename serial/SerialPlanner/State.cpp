#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN


ScriptStateLoader::ScriptStateLoader(ScriptChainLoader& parent, int id, Script::StateDeclaration& def):
	Base(parent, id, def)
{
	
}

String ScriptStateLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "state " << id.ToString() << "\n";
	return s;
}

bool ScriptStateLoader::Load() {
	id = def.id;
	
	Script::Id parent_id = parent.GetDeepId();
	
	ScriptLoader& loader = GetLoader();
	
	LoopRef l = loader.ResolveLoop(parent_id);
	
	EnvStateRef env = l->GetAddEnv(id.ToString());
	ASSERT(env);
	
	// ready
	
	LOG("ScriptStateLoader::Load: loaded path: " << parent_id.ToString() << "  +  " << id.ToString());
	
	return true;
}

bool ScriptStateLoader::PostInitialize() {
	return true;
}


NAMESPACE_SERIAL_END

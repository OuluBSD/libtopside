#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN

ScriptPoolLoader::ScriptPoolLoader(ScriptEngineLoader& parent, ScriptPoolLoader* chain_parent, int id, Script::PoolDefinition& def) :
	Base(parent, id, def),
	chain_parent(chain_parent)
{
	
	for (Script::EntityDefinition& e : def.ents) {
		entities.Add(new ScriptEntityLoader(*this, entities.GetCount(), e));
	}
	
	for (Script::PoolDefinition& p : def.pools) {
		pools.Add(new ScriptPoolLoader(parent, this, pools.GetCount(), p));
	}
	
}

bool ScriptPoolLoader::Load() {
	
	TODO
	
}

NAMESPACE_SERIAL_END

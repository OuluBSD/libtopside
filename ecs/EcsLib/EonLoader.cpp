#include "EcsLib.h"



NAMESPACE_SERIAL_BEGIN
using namespace Ecs;


bool ExtScriptEngineLoader::Load(ScriptEngineLoader& l) {
	Ecs::Engine& eng = Ecs::GetActiveEngine();
	
	for (ScriptEcsSystemLoader& loader : l.systems) {
		String id = loader.def.id.ToString();
		RTLOG("ScriptEngineLoader::Load: " << id);
		
		Ref<Ecs::SystemBase> sys = eng.GetAdd(id, false); // skip startup
		if (sys.IsEmpty()) {
			l.SetError("could not find ecs system with id '" + id + "'");
			return false;
		}
		
		if (!Load(loader, *sys)) {
			l.SetError(l.def.id.ToString() + ": " + loader.GetErrorString());
			return false;
		}
	}
	
	EntityStoreRef ents = eng.Get<EntityStore>();
	PoolRef pool = ents->GetRoot();
	
	for (ScriptPoolLoader& loader : l.pools) {
		String name = loader.def.id.ToString();
		PoolRef pool0 = pool->GetAddPool(name);
		ASSERT(pool0);
		if (!Load(loader, *pool0)) {
			l.SetError(l.def.id.ToString() + ": " + loader.GetErrorString());
			return false;
		}
	}
	
	return true;
}

bool ExtScriptEngineLoader::Load(ScriptEcsSystemLoader& l, Ecs::SystemBase& sys) {
	
	TODO/*for (Script::Statement& stmt : l.def.stmts) {
		String key = stmt.id.ToString();
		if (stmt.value) {
			if (!sys.Arg(key, stmt.value->ToObject()))
				return false;
		}
	}*/
	
	Ecs::Engine& eng = Ecs::GetActiveEngine();
	TypeCls type = sys.GetTypeId();
	eng.SystemStartup(type, &sys);
	
	return true;
}

bool ExtScriptEngineLoader::Load(ScriptPoolLoader& l, Ecs::Pool& pool) {
	EntityVec& ents = pool.GetEntities();
	PoolVec& pools = pool.GetPools();
	
	for (ScriptEntityLoader& e : l.entities) {
		String name = e.def.id.ToString();
		EntityRef ent = pool.GetAddEmpty(name);
		ASSERT(ent);
		if (!Load(e, *ent))
			return false;
	}
	
	for (ScriptPoolLoader& p : l.pools) {
		String name = p.def.id.ToString();
		PoolRef pool0 = pool.GetAddPool(name);
		ASSERT(pool0);
		if (!Load(p, *pool0))
			return false;
	}
	
	return true;
}

bool ExtScriptEngineLoader::Load(ScriptEntityLoader& l, Ecs::Entity& ent) {
	
	for (ScriptComponentLoader& c : l.comps) {
		String name = c.def.id.ToString();
		ComponentBaseRef cb = ent.CreateEon(name);
		if (!cb) {
			SetError("could not create component with id '" + name + "'");
			return false;
		}
		
		if (!Load(c, *cb))
			return false;
	}
	
	return true;
}

bool ExtScriptEngineLoader::Load(ScriptComponentLoader& l, Ecs::ComponentBase& cb) {
	
	TODO/*for (Script::Statement& stmt : l.def.stmts) {
		String key = stmt.id.ToString();
		if (stmt.value) {
			if (!cb.Arg(key, stmt.value->ToObject()))
				return false;
		}
	}*/
	
	return true;
}




NAMESPACE_SERIAL_END


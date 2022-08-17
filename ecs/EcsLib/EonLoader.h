#ifndef _EcsLib_EonLoader_h_
#define _EcsLib_EonLoader_h_

#if 0



NAMESPACE_SERIAL_BEGIN


struct ExtScriptEngineLoader : ExtScriptEngineLoaderBase {
	
	
	
	bool Load(ScriptEngineLoader& l) override;
	bool Load(ScriptEcsSystemLoader& l, Ecs::SystemBase& sys);
	bool Load(ScriptPoolLoader& l, Ecs::Pool& pool);
	bool Load(ScriptEntityLoader& l, Ecs::Entity& ent);
	bool Load(ScriptComponentLoader& l, Ecs::ComponentBase& ent);
	
};


NAMESPACE_SERIAL_END


#endif
#endif

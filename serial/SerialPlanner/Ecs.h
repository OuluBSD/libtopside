#ifndef _SerialPlanner_Ecs_h_
#define _SerialPlanner_Ecs_h_

NAMESPACE_SERIAL_BEGIN

class ScriptEngineLoader;
class ScriptPoolLoader;
class ScriptEntityLoader;


template <class ParserDef, class LoaderParent>
class EcsLoaderBase : RTTIBase {
	
public:
	RTTI_DECL0(EcsLoaderBase)
	virtual ~EcsLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	String						err_str;
	int							id = -1;
	
	EcsLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) {TODO}
	virtual bool		Load() = 0;
	void				SetError(String s) {err_str = s;}
	String				GetErrorString() const {return err_str;}
	
};


class ScriptEcsSystemLoader : public EcsLoaderBase<Script::EcsSysDefinition, ScriptEngineLoader> {
public:
	using Base = EcsLoaderBase<Script::EcsSysDefinition, ScriptEngineLoader>;
	RTTI_DECL1(ScriptEcsSystemLoader, Base)
	
public:
	
	
	ScriptEcsSystemLoader(ScriptEngineLoader& parent, int id, Script::EcsSysDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {/*vis | systems | pools;*/}
	bool		Load() override;
	/*String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptComponentLoader : public EcsLoaderBase<Script::ComponentDefinition, ScriptEntityLoader> {
public:
	using Base = EcsLoaderBase<Script::ComponentDefinition, ScriptEntityLoader>;
	RTTI_DECL1(ScriptComponentLoader, Base)
	
public:
	
	
	ScriptComponentLoader(ScriptEntityLoader& parent, int id, Script::ComponentDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {/*vis | comps;*/}
	bool		Load() override;
	/*String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptEntityLoader : public EcsLoaderBase<Script::EntityDefinition, ScriptPoolLoader> {
public:
	using Base = EcsLoaderBase<Script::EntityDefinition, ScriptPoolLoader>;
	RTTI_DECL1(ScriptEntityLoader, Base)
	
public:
	Array<ScriptComponentLoader>	comps;
	
	
	ScriptEntityLoader(ScriptPoolLoader& parent, int id, Script::EntityDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | comps;}
	bool		Load() override;
	/*String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptPoolLoader : public EcsLoaderBase<Script::PoolDefinition, ScriptEngineLoader> {
public:
	using Base = EcsLoaderBase<Script::PoolDefinition, ScriptEngineLoader>;
	RTTI_DECL1(ScriptPoolLoader, Base)
	
public:
	//enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<ScriptEntityLoader>		entities;
	Array<ScriptPoolLoader>			pools;
	ScriptPoolLoader*				chain_parent;
	bool							use_subpools = false;
	
	
	ScriptPoolLoader(ScriptEngineLoader& parent, ScriptPoolLoader* chain_parent, int id, Script::PoolDefinition& def);
	void		ForwardSubchainLoops();
	void		ForwardChainLoops();
	
	void		Visit(RuntimeVisitor& vis) override {vis | entities | pools;}
	bool		Load() override;
	/*String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptEngineLoader : public EcsLoaderBase<Script::EngineDefinition, ScriptSystemLoader> {
public:
	using Base = EcsLoaderBase<Script::EngineDefinition, ScriptSystemLoader>;
	RTTI_DECL1(ScriptEngineLoader, Base)
	
public:
	Array<ScriptEcsSystemLoader>	systems;
	Array<ScriptPoolLoader>			pools;
	
	
	ScriptEngineLoader(ScriptSystemLoader& parent, int id, Script::EngineDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | systems | pools;}
	String		GetTreeString(int indent) override;
	bool		Load() override;
	/*void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};


NAMESPACE_SERIAL_END

#endif
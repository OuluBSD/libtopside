#ifndef _SerialScript_Ecs_h_
#define _SerialScript_Ecs_h_


NAMESPACE_SERIAL_BEGIN


class ScriptWorldLoader;
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
	
	virtual bool		Load() = 0;
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) {TODO}
	void				SetError(String s) {err_str = s;}
	String				GetErrorString() const {return err_str;}
	
};


class ScriptEcsSystemLoader : public EcsLoaderBase<Script::EcsSysDefinition, ScriptWorldLoader> {
public:
	using Base = EcsLoaderBase<Script::EcsSysDefinition, ScriptWorldLoader>;
	RTTI_DECL1(ScriptEcsSystemLoader, Base)
	
	ArrayMap<String, Object> args;
	
public:
	
	
	ScriptEcsSystemLoader(ScriptWorldLoader& parent, int id, Script::EcsSysDefinition& def);
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

class ScriptPoolLoader : public EcsLoaderBase<Script::PoolDefinition, ScriptWorldLoader> {
public:
	using Base = EcsLoaderBase<Script::PoolDefinition, ScriptWorldLoader>;
	RTTI_DECL1(ScriptPoolLoader, Base)
	
public:
	//enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<ScriptEntityLoader>		entities;
	Array<ScriptPoolLoader>			pools;
	ScriptPoolLoader*				chain_parent;
	bool							use_subpools = false;
	
	
	ScriptPoolLoader(ScriptWorldLoader& parent, ScriptPoolLoader* chain_parent, int id, Script::PoolDefinition& def);
	/*void		ForwardSubchainLoops();
	void		ForwardChainLoops();*/
	
	void		Visit(RuntimeVisitor& vis) override {vis | entities | pools;}
	bool		Load() override;
	/*String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptWorldLoader : public EcsLoaderBase<Script::WorldDefinition, ScriptSystemLoader> {
public:
	using Base = EcsLoaderBase<Script::WorldDefinition, ScriptSystemLoader>;
	RTTI_DECL1(ScriptWorldLoader, Base)
	
public:
	Array<ScriptEcsSystemLoader>	systems;
	Array<ScriptPoolLoader>			pools;
	
	
	ScriptWorldLoader(ScriptSystemLoader& parent, int id, Script::WorldDefinition& def);
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


struct ExtScriptEcsLoaderBase {
	String err_str;
	
	virtual ~ExtScriptEcsLoaderBase() {}
	
	virtual bool Load(ScriptWorldLoader& l) = 0;
	virtual void Clear() {}
	
	void SetError(String s) {err_str = s;}
	
	String GetErrorString() const {return err_str;}
	
};


extern ExtScriptEcsLoaderBase* __ecs_script_loader;


NAMESPACE_SERIAL_END


#endif

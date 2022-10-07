#ifndef _SerialScript_Loader_h_
#define _SerialScript_Loader_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Serial {


namespace Script {
class WorldState;
class Action;
}

class ScriptLoader;
class ScriptLoopLoader;
class ScriptDriverLoader;
class ScriptStateLoader;
class ScriptSystemLoader;
class ScriptTopChainLoader;
class ScriptChainLoader;
class ScriptMachineLoader;
class ScriptEngineLoader;

void GetAtomActions(const Script::WorldState& src, Vector<Script::Action>& acts);


using namespace Parallel;


/*typedef enum {
	UNASSIGNED,

	IN_BEGINNING,

	READY,
	FAILED,
} ScriptStatus;

inline const char* GetScriptStatusString(ScriptStatus status) {
	const char* t = "<invalid status>";
	switch (status) {
		case IN_BEGINNING:					t = "In beginning"; break;
		case READY:							t = "Ready"; break;
		case FAILED:						t = "Failed"; break;
		case UNASSIGNED:					t = "Unassigned"; break;
		default: break;
	}
	return t;
}*/






class ScriptLoader;


template <class ParserDef, class LoaderParent>
class ScriptLoaderBase : RTTIBase {
	
	
protected:
	//void ResetFlags() {any_waiting_parent = false; any_waiting_children = false; any_linking = false; any_routing = false; all_ready = true; any_failed = false;}
	//void CheckFlags();
	//void CheckStatus(ScriptStatus s);
	
	int							iter = 0;
	
	
public:
	RTTI_DECL0(ScriptLoaderBase)
	virtual ~ScriptLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	//ScriptStatus				status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	/*bool						any_waiting_parent = false;
	bool						any_waiting_children = false;
	bool						any_linking = false;
	bool						any_routing = false;
	bool						all_ready = false;
	bool						any_failed = false;
	int							prev_segment_count = 0;*/
	
	ScriptLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	//void				Forward();
	
	//void				SetStatusRetry() {SetStatus(RETRY);}
	//void				SetError(String s) {err_str = s; SetStatus(FAILED); LOG("ScriptLoaderBase::SetError: this=" << HexStr(this) << ": " << s); }
	
	/*bool				IsFailed() const {return status == FAILED;}
	bool				IsReady() const {return status == READY;}
	bool				IsStatus(ScriptStatus s) const {return status == s;}*/
	int					GetId() const {return id;}
	//ScriptStatus		GetStatus() const {return status;}
	ScriptLoader&		GetLoader() {return parent.GetLoader();}
	String				GetErrorString() const {return err_str;}
	void				AddError(const FileLocation& loc, String msg) {parent.AddError(loc, msg);}
	
	virtual Script::Id	GetDeepId() const {ASSERT(!def.id.IsEmpty()); Script::Id id = parent.GetDeepId(); id.Append(def.id); return id;}
	//virtual void		SetStatus(ScriptStatus s) {status = s;}
	
	virtual bool		Load() = 0;
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<ScriptLoopLoader*>& v) = 0;
	//virtual void		ForwardLoops() = 0;
	/*virtual void		LoopStatus() = 0;
	virtual void		CheckStatusDeep() = 0;*/
	virtual void		GetDrivers(Vector<ScriptDriverLoader*>& v) {Panic("not implemented");}
	virtual void		GetStates(Vector<ScriptStateLoader*>& v) {Panic("not implemented");}
	
};





class ScriptLoopLoader : public ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader> {
	
protected:
	
	// Implement found loop
	struct AddedAtom {
		AtomBaseRef		a;
		LinkBaseRef		l;
		IfaceConnTuple	iface;
	};
	
	Array<AddedAtom>		added_atoms;
	
public:
	using Base = ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader>;
	RTTI_DECL1(ScriptLoopLoader, Base)
	
	
protected:
	friend class ScriptLoader;
	friend class ScriptConnectionSolver;
	friend class MachineVerifier;
	
	struct SideLink : Moveable<SideLink> {
		ScriptLoopLoader*	link = 0;
		ValDevCls			vd;
		bool				is_user_conditional = false;
		bool				is_user_stmt = false;
		bool				is_required = false;
	};
	
	struct AtomSideLinks : Moveable<AtomSideLinks> {
		Vector<SideLink>	src_side_conns;
		Vector<SideLink>	sink_side_conns;
		AtomTypeCls			type;
		
	};
	
	Array<AtomBaseRef>				atoms;
	Vector<AtomSideLinks>			atom_links;
	
	
	void SetSideSourceConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& sink);
	void SetSideSinkConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& src);
	bool IsAllSidesConnected() const;
	bool IsTopSidesConnected() const;
	//bool SetWorldState(Script::WorldState& ws, const Script::Statement& stmt);
	
	
public:
	ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def);
	
	
	void		Forward();
	void		InitSegments();
	void		SearchNewSegment();
	void		PruneSegmentGoals();
	void		DumpLoop();
	//bool		PassSideConditionals(const Script::Statement& side_stmt);
	
	
	bool		Start();
	bool		Parse();
	bool		PostInitialize();
	void		UpdateLoopLimits();
	int			GetAtomLinkCount() const {return atom_links.GetCount();}
	
	bool		Load() override;
	void		Visit(RuntimeVisitor& vis) override {vis && atoms;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;
	void		SetStatus(ScriptStatus status) override;*/
};

class ScriptChainLoader : public ScriptLoaderBase<Script::ChainDefinition, ScriptTopChainLoader> {
	
public:
	using Base = ScriptLoaderBase<Script::ChainDefinition, ScriptTopChainLoader>;
	RTTI_DECL1(ScriptChainLoader, Base)
	
public:
	Array<ScriptLoopLoader>			loops;
	Array<ScriptStateLoader>		states;
	
	
	ScriptChainLoader(ScriptTopChainLoader& parent, int id, Script::ChainDefinition& def);
	
	void		Forward();
	void		MakeOptionLinkVector();
	void		FindAcceptedLinks();
	void		LinkPlanner();
	void		Linker();
	
	void		Visit(RuntimeVisitor& vis) override {vis | loops | states;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;
	bool		Load() override;*/
	Script::Id	GetDeepId() const override;
	bool		Load() override;
	
};


class ScriptTopChainLoader : public ScriptLoaderBase<Script::ChainDefinition, ScriptMachineLoader> {
public:
	using Base = ScriptLoaderBase<Script::ChainDefinition, ScriptMachineLoader>;
	RTTI_DECL1(ScriptTopChainLoader, Base)
	
public:
	enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<ScriptChainLoader>		chains;
	Array<ScriptTopChainLoader>		subchains;
	ScriptTopChainLoader*			chain_parent;
	bool							use_subchains = false;
	
	
	ScriptTopChainLoader(int mode, ScriptMachineLoader& parent, ScriptTopChainLoader* chain_parent, int id, Script::ChainDefinition& def);
	/*void		ForwardSubchainLoops();
	void		ForwardChainLoops();*/
	
	void		Visit(RuntimeVisitor& vis) override {vis | subchains | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	bool		Load() override;
	
};

class ScriptStateLoader : public ScriptLoaderBase<Script::StateDeclaration, ScriptChainLoader> {
	
protected:
	Script::Id		id;
	
public:
	using Base = ScriptLoaderBase<Script::StateDeclaration, ScriptChainLoader>;
	RTTI_DECL1(ScriptStateLoader, Base)
	
public:
	
	
	ScriptStateLoader(ScriptChainLoader& parent, int id, Script::StateDeclaration& def);
	void		Visit(RuntimeVisitor& vis) override {}
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override {}
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override {}
	void		GetStates(Vector<ScriptStateLoader*>& v) override {}
	//void		ForwardLoops() override {}
	/*void		LoopStatus() override {}
	void		CheckStatusDeep() override {}*/
	String		GetTreeString(int indent) override;
	bool		Load() override;
	void		Forward() {}
	bool		PostInitialize();
	
};

class ScriptDriverLoader : public ScriptLoaderBase<Script::DriverDefinition, ScriptMachineLoader> {
	
protected:
	struct AddedAtom {
		AtomBaseRef		a;
		LinkBaseRef		l;
	};
	
	Vector<Script::WorldState>	atoms;
	Array<AddedAtom>			added_atoms;
	
	void		FindAtoms();
	
public:
	using Base = ScriptLoaderBase<Script::DriverDefinition, ScriptMachineLoader>;
	RTTI_DECL1(ScriptDriverLoader, Base)
	
public:
	
	
	ScriptDriverLoader(ScriptMachineLoader& parent, int id, Script::DriverDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {} //vis | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override {}
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;
	void		Forward();*/
	bool		Load() override;
	bool		PostInitialize();
	bool		Start();
	
};

class ScriptMachineLoader : public ScriptLoaderBase<Script::MachineDefinition, ScriptSystemLoader> {
public:
	using Base = ScriptLoaderBase<Script::MachineDefinition, ScriptSystemLoader>;
	RTTI_DECL1(ScriptMachineLoader, Base)
	
public:
	Array<ScriptTopChainLoader>		chains;
	Array<ScriptDriverLoader>		drivers;
	
	
	ScriptMachineLoader(ScriptSystemLoader& parent, int id, Script::MachineDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | chains | drivers;}
	bool		Load() override;
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	
};

class ScriptSystemLoader : public ScriptLoaderBase<Script::GlobalScope, ScriptLoader> {
public:
	using Base = ScriptLoaderBase<Script::GlobalScope, ScriptLoader>;
	RTTI_DECL1(ScriptSystemLoader, Base)
	
public:
	Array<ScriptMachineLoader>		machs;
	Array<ScriptEngineLoader>		engs;
	
	
	ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& glob);
	
	void		Visit(RuntimeVisitor& vis) override {vis | machs | engs;}
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	String		GetTreeString(int indent=0) override;
	//void		ForwardLoops() override;
	/*void		LoopStatus() override;
	void		CheckStatusDeep() override;*/
	bool		Load() override;
	bool		LoadEcs();
	
	void		Dump() {LOG(GetTreeString());}
	
};



class ScriptLoader :
	public System<ScriptLoader>,
	public ErrorSource
{
protected:
	friend class ScriptLoopLoader;
	friend class ScriptChainLoader;
	friend class ScriptTopChainLoader;
	friend class ScriptMachineLoader;
	static int loop_counter;
	
	//LinkedList<ScriptScope> scopes;
	One<ScriptSystemLoader> loader;
	
	int tmp_side_id_counter = 0;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	//Script::CompilationUnit root;
	LoopStoreRef es;
	SpaceStoreRef ss;
	Script::CompilationUnit cunit;
	
	
	//Vector<ScriptError> errs;
	bool collect_errors = false;
	
	
	//void AddError(String msg);
	//void AddError(ScriptLoopLoader* ll, String msg);
	//void ReleaseErrorBuffer();
	//void ClearErrorBuffer();
	//void CollectErrorBuffer(bool b) {collect_errors = b;}
	//void EnterScope();
	//bool LeaveScope();
	bool GetPathId(Script::Id& script_id, AstNode* from, AstNode* to);
	
public:
	SYS_RTTI(ScriptLoader)
	typedef ScriptLoader CLASSNAME;
	ScriptLoader(Machine& m);
	SYS_DEF_VISIT_((vis & es & ss); if (!loader.IsEmpty()) vis % *loader;)
	
	void PostLoadFile(const String& path) {post_load_file << path;}
	void PostLoadString(const String& s) {post_load_string << s;}
	
	ScriptLoader&	GetLoader() {return *this;}
	int&			GetSideIdCounter() {return tmp_side_id_counter;}
	int				NewConnectionId() {return tmp_side_id_counter++;}
	void			AddError(const FileLocation& loc, String msg) {ErrorSource::AddError(loc, msg);}
	
	
	//static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::SCRIPT_LOADER_SYSTEM;}
	
protected:
	
	~ScriptLoader();
    bool		Initialize() override;
    void		Start() override;
    void		Update(double dt) override;
    void		Stop() override;
    void		Uninitialize() override;
    
    void		LogMessage(ProcMsg msg);
    void		Cleanup();
    //void		DumpErrors();
    bool		DoPostLoad();
	bool		LoadFile(String path);
	bool		Load(const String& content, const String& filepath="temp");
	bool		ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1);
	bool		ImplementScript();
	
	bool		LoadCompilationUnit(AstNode* root);
	bool		LoadGlobalScope(Script::GlobalScope& glob, AstNode* root);
	bool		LoadChain(Script::ChainDefinition& chain, AstNode* root);
	bool		LoadMachine(Script::MachineDefinition& mach, AstNode* root);
	bool		LoadEngine(Script::EngineDefinition& def, AstNode* n);
	bool		LoadDriver(Script::DriverDefinition& def, AstNode* n);
	bool		LoadTopChain(Script::ChainDefinition& def, AstNode* n);
	bool		LoadEcsSystem(Script::EcsSysDefinition& def, AstNode* n);
	bool		LoadPool(Script::PoolDefinition& def, AstNode* n);
	bool		LoadState(Script::StateDeclaration& def, AstNode* n);
	bool		LoadEntity(Script::EntityDefinition& def, AstNode* n);
	
	//Script::State*	FindState(const Script::Id& id);
	
	
	
protected:
	friend class ScriptDriverLoader;
	friend class ScriptStateLoader;
	
	LoopRef		ResolveLoop(Script::Id& id);
	
	
public:
	
	
	Callback1<SystemBase&>	WhenEnterScriptLoad;
	Callback				WhenLeaveScriptLoad;
	
	Script::Id	GetDeepId() const {return Script::Id();}
	
};

using ScriptLoaderRef = Ref<ScriptLoader, SerialSystemParent>;


}
NAMESPACE_TOPSIDE_END

#endif

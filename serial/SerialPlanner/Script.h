#ifndef _SerialLib_Script_h_
#define _SerialLib_Script_h_

NAMESPACE_SERIAL_BEGIN


class ScriptLoader;



struct ScriptError : Moveable<ScriptError> {
	ScriptLoopLoader* ll = 0;
	String msg;
	int status = -1;
	
};






/*class ScriptScope {
protected:
	friend class ScriptLoader;
	friend class ScriptLoopLoader;
	
	Script::WorldState			current_state;
	Script::LoopDefinition*	loop = 0;
	Script::ChainDefinition*	chain = 0;
	Script::Machine*			mach = 0;
	Script::GlobalScope*		glob = 0;
public:
	ScriptScope() {}
	
	void SetCurrentState(const Script::WorldState& s) {current_state = s;}
	
	
};*/



class ScriptLoopSegment {
public:
	AStar<Script::ActionNode>		as;
	Script::Plan					ep;
	Script::APlanNode*				start_node = 0;
	const Script::ActionNode*		stop_node = 0;
	ScriptLoopLoader*				side_conn = 0;
	
	
	String GetTreeString(int id, int indent);
	
};

typedef enum {
	IN_BEGINNING,
	OUTPUT_IS_WAITING,
	INPUT_IS_WAITING,
	RETRY,
	SOLVE_INTERNAL_CONNECTIONS,
	READY,
	FAILED,
} ScriptStatus;

inline const char* GetScriptStatusString(ScriptStatus status) {
	const char* t = "<invalid status>";
	switch (status) {
		case IN_BEGINNING:					t = "In beginning"; break;
		case OUTPUT_IS_WAITING:				t = "Side output is waiting"; break;
		case INPUT_IS_WAITING:				t = "Side input is waiting"; break;
		case RETRY:							t = "Retry"; break;
		case SOLVE_INTERNAL_CONNECTIONS:	t = "Solve internal connections"; break;
		case READY:							t = "Ready"; break;
		case FAILED:						t = "Failed"; break;
		default: break;
	}
	return t;
}

String GetScriptStatusLine(int indent, ScriptStatus status, String extra_str=String());

class ScriptSystemLoader;
class ScriptMachineLoader;
class ScriptChainLoader;
class ScriptTopChainLoader;
class ScriptLoader;

template <class ParserDef, class LoaderParent>
class ScriptLoaderBase : RTTIBase {
	
	
protected:
	void ResetFlags() {any_waiting = false; any_retrying = false; all_ready = true; any_failed = false;}
	void CheckFlags(bool allow_internal);
	void CheckStatus(ScriptStatus s);
	
public:
	RTTI_DECL0(ScriptLoaderBase)
	virtual ~ScriptLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	ScriptStatus					status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	bool						any_waiting = false;
	bool						any_retrying = false;
	bool						all_ready = false;
	bool						any_failed = false;
	
	
	ScriptLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	void		Forward();
	void		SolveInternal();
	
	void		SetStatus(int s) {status = (ScriptStatus)s;}
	void		SetStatusRetry() {status = RETRY;}
	void		SetError(String s) {err_str = s; status = FAILED;}
	
	bool		IsFailed() const {return status == FAILED;}
	bool		IsReady() const {return status == READY;}
	bool		IsStatus(ScriptStatus s) const {return status == s;}
	int			GetId() const {return id;}
	ScriptStatus	GetStatus() const {return status;}
	ScriptLoader&	GetLoader() {return parent.GetLoader();}
	String		GetErrorString() const {return err_str;}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<ScriptLoopLoader*>& v) = 0;
	virtual void		ForwardLoops() = 0;
	virtual void		LoopStatus() = 0;
	virtual void		SetRetryDeep() = 0;
	
};

class ScriptLoopLoader : public ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader> {
public:
	using Base = ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader>;
	RTTI_DECL1(ScriptLoopLoader, Base)
	
	
protected:
	friend class ScriptLoader;
	
	
	Script::APlanNode				start_node;
	Script::APlanNode				goal_node;
	Script::WorldState				start;
	Script::WorldState				goal;
	
	Array<ScriptLoopSegment>		segments;
	Script::ActionPlanner			planner;
	const Script::APlanNode*		accepted_side_node = 0;
	
	Array<AtomBaseRef>		atoms;
	
	
	void SetupSegment(ScriptLoopSegment& s);
	bool SetWorldState(Script::WorldState& ws, const Script::Statement& stmt);
	
public:
	ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def);
	
	
	void		Forward();
	void		InitSegments();
	void		ForwardTopSegment();
	
	
	bool		Parse();
	bool		Load();
	SideStatus	AcceptOutput(ScriptLoopLoader& out, Script::ActionPlanner::State*& accepted_in, Script::ActionPlanner::State*& accepted_out);
	void		AddSideConnectionSegment(Script::ActionPlanner::State* n, ScriptLoopLoader* c, Script::ActionPlanner::State* side_state);
	
	ScriptLoopSegment& GetCurrentSegment() {return segments.Top();}
	
	void		Visit(RuntimeVisitor& vis) override {vis && atoms;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
};


class ScriptChainLoader : public ScriptLoaderBase<Script::ChainDefinition, ScriptTopChainLoader> {
	
	
public:
	using Base = ScriptLoaderBase<Script::ChainDefinition, ScriptTopChainLoader>;
	RTTI_DECL1(ScriptChainLoader, Base)
	
public:
	Array<ScriptLoopLoader>		loops;
	
	
	ScriptChainLoader(ScriptTopChainLoader& parent, int id, Script::ChainDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | loops;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class ScriptTopChainLoader : public ScriptLoaderBase<Script::ChainDefinition, ScriptMachineLoader> {
public:
	using Base = ScriptLoaderBase<Script::ChainDefinition, ScriptMachineLoader>;
	RTTI_DECL1(ScriptTopChainLoader, Base)
	
public:
	enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<ScriptChainLoader>		chains;
	Array<ScriptTopChainLoader>	subchains;
	ScriptTopChainLoader*			chain_parent;
	bool						use_subchains = false;
	
	
	ScriptTopChainLoader(int mode, ScriptMachineLoader& parent, ScriptTopChainLoader* chain_parent, int id, Script::ChainDefinition& def);
	void		ForwardSubchainLoops();
	void		ForwardChainLoops();
	
	void		Visit(RuntimeVisitor& vis) override {vis | subchains | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class ScriptMachineLoader : public ScriptLoaderBase<Script::MachineDefinition, ScriptSystemLoader> {
public:
	using Base = ScriptLoaderBase<Script::MachineDefinition, ScriptSystemLoader>;
	RTTI_DECL1(ScriptMachineLoader, Base)
	
public:
	Array<ScriptTopChainLoader>	chains;
	
	
	ScriptMachineLoader(ScriptSystemLoader& parent, int id, Script::MachineDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};

class ScriptSystemLoader : public ScriptLoaderBase<Script::GlobalScope, ScriptLoader> {
public:
	using Base = ScriptLoaderBase<Script::GlobalScope, ScriptLoader>;
	RTTI_DECL1(ScriptSystemLoader, Base)
	
public:
	Array<ScriptMachineLoader>		machs;
	
	
	ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& glob);
	
	void		Visit(RuntimeVisitor& vis) override {vis | machs;}
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	String		GetTreeString(int indent=0) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
	void		Dump() {LOG(GetTreeString());}
	
};

bool TestParseScriptCode(String code);

class ScriptLoader :
	public System<ScriptLoader>
{
protected:
	friend class ScriptLoopLoader;
	friend class ScriptChainLoader;
	friend class ScriptTopChainLoader;
	friend class ScriptMachineLoader;
	static int loop_counter;
	
	//LinkedList<ScriptScope> scopes;
	Vector<Script::GlobalScope*> scopes;
	One<ScriptSystemLoader> loader;
	
	Script::WorldState def_ws;
	Script::ActionPlanner def_planner;
	int tmp_side_id_counter = 0;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	Script::AtomilationUnit root;
	LoopStoreRef es;
	
	Vector<ScriptError> errs;
	bool collect_errors = false;
	
	
	void AddError(String msg);
	void AddError(ScriptLoopLoader* ll, String msg);
	void ReleaseErrorBuffer();
	void ClearErrorBuffer();
	void CollectErrorBuffer(bool b) {collect_errors = b;}
	//void EnterScope();
	//bool LeaveScope();
	
public:
	SYS_RTTI(ScriptLoader)
	SYS_CTOR(ScriptLoader);
	SYS_DEF_VISIT_((vis & es); if (!loader.IsEmpty()) vis % *loader;)
	
	void PostLoadFile(String path) {post_load_file << path;}
	void PostLoadString(String s) {post_load_string << s;}
	
	ScriptLoader&	GetLoader() {return *this;}
	int&		GetSideIdCounter() {return tmp_side_id_counter;}
	
	
protected:
	
    bool		Initialize() override;
    void		Start() override;
    void		Update(double dt) override;
    void		Stop() override;
    void		Uninitialize() override;
    
    void		Cleanup();
    void		DumpErrors();
    bool		DoPostLoad();
	bool		LoadFile(String path);
	bool		Load(String content, String filepath="temp");
	bool		LoadAtomilationUnit(Script::AtomilationUnit& cunit);
	bool		LoadGlobalScope(Script::GlobalScope& list);
	LoopRef	ResolveLoop(Script::Id& id);
	bool		ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1);
	bool		ImplementScript();
	
	Script::State*	FindState(const Script::Id& id);
	
	
	
};

using ScriptLoaderRef = Ref<ScriptLoader, RefParent1<Machine>>;



class ScriptConnectionSolver {
	Vector<ScriptLoopLoader*>		loops;
	String						err_str;
	int&						tmp_side_id_counter;
	bool						is_missing_input = false;
	bool						is_missing_output = false;
	
	void SetError(String s) {err_str = s;}
	bool Process();
public:
	
	ScriptConnectionSolver(int& side_id_counter) : tmp_side_id_counter(side_id_counter) {}
	
	template <class T>
	bool Solve(T* o) {
		loops.SetCount(0);
		o->GetLoops(loops);
		if (loops.IsEmpty()) {
			SetError("Internal error: no loops");
			return false;
		}
		
		return Process();
	}
	
	String	GetError() const {return err_str;}
	bool	IsMissingInput() const {return is_missing_input;}
	bool	IsMissingOutput() const {return is_missing_output;}
	
};

NAMESPACE_SERIAL_END

NAMESPACE_TOPSIDE_BEGIN


template <>	inline bool TerminalTest<Serial::Script::ActionNode>(Node<Serial::Script::ActionNode>& n) {
	/*if (&n == (void*)0x806A107A0) {
		LOG("");
	}*/
	
	using namespace Serial;
	int est = n.GetEstimate();
	if (est <= 0)
		return true;
	Script::ActionNode& goal = n.GetGoal();
	Script::WorldState& goal_ws = goal.GetWorldState();
	if (n.Contains(goal))
		return true;
	if (goal.Conflicts(n))
		return false;
	Script::WorldState& ws = n.GetWorldState();
	Script::ActionPlanner& ap = n.GetActionPlanner();
	ScriptLoopLoader& ll = ap.GetLoopLoader();
	ScriptLoopSegment& seg = ll.GetCurrentSegment();
	
	/*if (est == 1) {
		LOG(ws.ToString());
	}*/
	
	AtomTypeCls atom = ws.GetAtom();
	if (ws.IsAddAtom() && n.GetLinkedCount() && atom.iface.src.val == ValCls::ORDER)
		return false;
	
	if (ws.IsAddAtom()) {
		if (n.GetLinkedCount() > 0) {
			AtomTypeCls a = ws.GetAtom();
			if (a.iface.side.IsValid()) {
				ASSERT(a.IsRoleSide());
				if (!a.IsRoleSideSource()) {
					ap.AddSideInput(seg.as, n);
					return false;
				}
				else {
					POPO(Pol::Serial::Script::Loop::SideInIsBeforeSideOutAlways)
					if (goal_ws	.IsTrue	("has.side.in") &&
						ws		.IsFalse("has.side.in"))
						return false;
					
					ap.AddSideOutput(seg.as, n);
					return false;
				}
			}
			/*else {
				const Script::APlanNode* accepted = ll.GetAcceptedSideNode();
				ASSERT(accepted);
				//if (n.GetWorldState() != accepted->GetWorldState())
				//	return false;
				if (&n != accepted) {
					LOG("Skipped terminal: " << IntStr64(n.GetWorldState().GetHashValue()) << ": " << n.GetWorldState().ToString());
					return false;
				}
				LOG("Found side-ch path: " << accepted->GetWorldState().ToString());
				
			}*/
		}
	}
	else {
		LOG("Unexpected action");
		return false;
	}
	
	Array<Serial::Script::WorldState*> to;
	Vector<double> action_costs;
	ap.GetPossibleStateTransition(n, to, action_costs);
	
	LOG("TerminalTest: " << HexStr(&n) << " -> " << to.GetCount() << " (estimate " << n.GetEstimate() << ")");
	for(int i = 0; i < to.GetCount(); i++) {
		Serial::Script::WorldState& ws_to = *to[i];
		
		hash_t hash = ws_to.GetHashValue();
		int j = ap.tmp_sub.Find(hash);
		Serial::Script::APlanNode* an = 0;
		if (j == -1) {
			Serial::Script::APlanNode& sub = ap.tmp_sub.Add(hash);// n.Add();
			sub.IncLinked();
			sub.SetActionPlanner(n.GetActionPlanner());
			sub.SetGoal(n.GetGoal());
			sub.SetWorldState(ws_to);
			sub.SetCost(action_costs[i]);
			n.AddLink(sub);
			an = &sub;
		} else {
			an = &ap.tmp_sub[j];
			an->IncLinked();
			n.AddLink(*an);
		}
		LOG("\t" << n.GetEstimate() << ": " << HexStr(an) << " -> " << ws_to.ToString());
		
		/*if (ws_to.IsAddAtom()) {
			AtomTypeCls t = ws_to.GetAtom();
			if (t.sub == SubAtomCls::SIDE_INPUT) {
				ap.AddSideInput(*an);
			}
			else if (t.sub == SubAtomCls::SIDE_OUTPUT) {
				ap.AddSideOutput(*an);
			}
		}*/
	}
	//if (n.GetTotalCount())
	//	return false;
	
	return false;
}

NAMESPACE_TOPSIDE_END

#include "LoaderBase.inl"

#endif

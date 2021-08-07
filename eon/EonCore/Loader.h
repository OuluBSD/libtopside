#ifndef _EonCore_Loader_h_
#define _EonCore_Loader_h_


NAMESPACE_EON_BEGIN




class Loader;



struct Error : Moveable<Error> {
	LoopLoader* ll = 0;
	String msg;
	int status = -1;
	
};









class LoopSegment {
public:
	AStar<ActionNode>		as;
	Plan					ep;
	APlanNode*				start_node = 0;
	const ActionNode*		stop_node = 0;
	LoopLoader*				side_conn = 0;
	
	
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
} Status;

inline const char* GetStatusString(Status status) {
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

String GetStatusLine(int indent, Status status, String extra_str=String());

class SystemLoader;
class MachineLoader;
class ChainLoader;
class TopChainLoader;
class Loader;

template <class ParserDef, class LoaderParent>
class LoaderBase : RTTIBase {
	
	
protected:
	void ResetFlags() {any_waiting = false; any_retrying = false; all_ready = true; any_failed = false;}
	void CheckFlags(bool allow_internal);
	void CheckStatus(Status s);
	
public:
	RTTI_DECL0(LoaderBase)
	virtual ~LoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	Status					status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	bool						any_waiting = false;
	bool						any_retrying = false;
	bool						all_ready = false;
	bool						any_failed = false;
	
	
	LoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	void		Forward();
	void		SolveInternal();
	
	void		SetStatus(int s) {status = (Status)s;}
	void		SetStatusRetry() {status = RETRY;}
	void		SetError(String s) {err_str = s; status = FAILED;}
	
	bool		IsFailed() const {return status == FAILED;}
	bool		IsReady() const {return status == READY;}
	bool		IsStatus(Status s) const {return status == s;}
	int			GetId() const {return id;}
	Status	GetStatus() const {return status;}
	Loader&	GetLoader() {return parent.GetLoader();}
	String		GetErrorString() const {return err_str;}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<LoopLoader*>& v) = 0;
	virtual void		ForwardLoops() = 0;
	virtual void		LoopStatus() = 0;
	virtual void		SetRetryDeep() = 0;
	
};

class LoopLoader : public LoaderBase<LoopDefinition, ChainLoader> {
public:
	using Base = LoaderBase<LoopDefinition, ChainLoader>;
	RTTI_DECL1(LoopLoader, Base)
	
	
protected:
	friend class Loader;
	
	
	APlanNode				start_node;
	APlanNode				goal_node;
	WorldState				start;
	WorldState				goal;
	
	Array<LoopSegment>		segments;
	ActionPlanner			planner;
	const APlanNode*		accepted_side_node = 0;
	
	Array<ComponentBaseRef>		comps;
	
	
	void SetupSegment(LoopSegment& s);
	bool SetWorldState(WorldState& ws, const Statement& stmt);
	
public:
	LoopLoader(ChainLoader& parent, int id, LoopDefinition& def);
	
	
	void		Forward();
	void		InitSegments();
	void		ForwardTopSegment();
	
	
	bool		Parse();
	bool		Load();
	SideStatus	AcceptOutput(LoopLoader& out, ActionPlanner::State*& accepted_in, ActionPlanner::State*& accepted_out);
	void		AddSideConnectionSegment(ActionPlanner::State* n, LoopLoader* c, ActionPlanner::State* side_state);
	
	LoopSegment& GetCurrentSegment() {return segments.Top();}
	
	void		Visit(RuntimeVisitor& vis) override {vis && comps;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<LoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
};


class ChainLoader : public LoaderBase<ChainDefinition, TopChainLoader> {
	
	
public:
	using Base = LoaderBase<ChainDefinition, TopChainLoader>;
	RTTI_DECL1(ChainLoader, Base)
	
public:
	Array<LoopLoader>		loops;
	
	
	ChainLoader(TopChainLoader& parent, int id, ChainDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | loops;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<LoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class TopChainLoader : public LoaderBase<ChainDefinition, MachineLoader> {
public:
	using Base = LoaderBase<ChainDefinition, MachineLoader>;
	RTTI_DECL1(TopChainLoader, Base)
	
public:
	enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<ChainLoader>		chains;
	Array<TopChainLoader>	subchains;
	TopChainLoader*			chain_parent;
	bool						use_subchains = false;
	
	
	TopChainLoader(int mode, MachineLoader& parent, TopChainLoader* chain_parent, int id, ChainDefinition& def);
	void		ForwardSubchainLoops();
	void		ForwardChainLoops();
	
	void		Visit(RuntimeVisitor& vis) override {vis | subchains | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<LoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class MachineLoader : public LoaderBase<MachineDefinition, SystemLoader> {
public:
	using Base = LoaderBase<MachineDefinition, SystemLoader>;
	RTTI_DECL1(MachineLoader, Base)
	
public:
	Array<TopChainLoader>	chains;
	
	
	MachineLoader(SystemLoader& parent, int id, MachineDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<LoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};

class SystemLoader : public LoaderBase<GlobalScope, Loader> {
public:
	using Base = LoaderBase<GlobalScope, Loader>;
	RTTI_DECL1(SystemLoader, Base)
	
public:
	Array<MachineLoader>		machs;
	
	
	SystemLoader(Loader& parent, int id, GlobalScope& glob);
	
	void		Visit(RuntimeVisitor& vis) override {vis | machs;}
	void		GetLoops(Vector<LoopLoader*>& v) override;
	String		GetTreeString(int indent=0) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
	void		Dump() {LOG(GetTreeString());}
	
};

bool TestParseEonCode(String code);

class Loader :
	public System<Loader>
{
protected:
	friend class LoopLoader;
	friend class ChainLoader;
	friend class TopChainLoader;
	friend class MachineLoader;
	static int loop_counter;
	
	//LinkedList<EonScope> scopes;
	Vector<GlobalScope*> scopes;
	One<SystemLoader> loader;
	
	WorldState def_ws;
	ActionPlanner def_planner;
	int tmp_side_id_counter = 0;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	CompilationUnit root;
	EntityStoreRef es;
	
	Vector<Error> errs;
	bool collect_errors = false;
	
	
	void AddError(String msg);
	void AddError(LoopLoader* ll, String msg);
	void ReleaseErrorBuffer();
	void ClearErrorBuffer();
	void CollectErrorBuffer(bool b) {collect_errors = b;}
	//void EnterScope();
	//bool LeaveScope();
	
public:
	SYS_RTTI(Loader)
	SYS_CTOR(Loader);
	SYS_DEF_VISIT_((vis & es); if (!loader.IsEmpty()) vis % *loader;)
	
	void PostLoadFile(String path) {post_load_file << path;}
	void PostLoadString(String s) {post_load_string << s;}
	
	Loader&	GetLoader() {return *this;}
	int&		GetSideIdCounter() {return tmp_side_id_counter;}
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::SYS_EON;}
	
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
	bool		LoadCompilationUnit(CompilationUnit& cunit);
	bool		LoadGlobalScope(GlobalScope& list);
	EntityRef	ResolveEntity(IdPath& id);
	bool		ConnectSides(LoopLoader& loop0, LoopLoader& loop1);
	bool		ImplementPlan();
	
	State*	FindState(const IdPath& id);
	
	
	
};

using LoaderRef = Ref<Loader, RefParent1<Machine>>;



class ConnectionSolver {
	Vector<LoopLoader*>		loops;
	String						err_str;
	int&						tmp_side_id_counter;
	bool						is_missing_input = false;
	bool						is_missing_output = false;
	
	void SetError(String s) {err_str = s;}
	bool Process();
public:
	
	ConnectionSolver(int& side_id_counter) : tmp_side_id_counter(side_id_counter) {}
	
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

NAMESPACE_ECS_END

NAMESPACE_TOPSIDE_BEGIN


template <>	inline bool TerminalTest<Eon::ActionNode>(Node<Eon::ActionNode>& n) {
	if (&n == (void*)0x8026C63C0) {
		LOG("");
	}
	
	using namespace Ecs;
	int est = n.GetEstimate();
	if (est <= 0)
		return true;
	ActionNode& goal = n.GetGoal();
	WorldState& goal_ws = goal.GetWorldState();
	if (n.Contains(goal))
		return true;
	if (goal.Conflicts(n))
		return false;
	WorldState& ws = n.GetWorldState();
	ActionPlanner& ap = n.GetActionPlanner();
	LoopLoader& ll = ap.GetLoopLoader();
	LoopSegment& seg = ll.GetCurrentSegment();
	
	TypeCompCls comp = ws.GetComponent();
	if (ws.IsAddComponent() && n.GetLinkedCount() && comp.side.vd.val == ValCls::ORDER)
		return false;
	
	bool req_ext = false;
	if (ws.IsAddComponent()) {
		if (comp.sub == SubCompCls::SIDE_INPUT || comp.sub == SubCompCls::SIDE_OUTPUT)
			req_ext = true;
	}
	
	
	if (ws.IsAddExtension()) {
		if (n.GetLinkedCount() > 0) {
			TypeExtCls ext = ws.GetExtension();
			//if (!seg.side_conn) {
			if (ext.sub == SubCompCls::SIDE_INPUT) {
				ap.AddSideInput(seg.as, n);
				return false;
			}
			else if (ext.sub == SubCompCls::SIDE_OUTPUT) {
				POPO(Pol::Eon::Loop::SideInIsBeforeSideOutAlways)
				if (goal_ws	.IsTrue	("has.side.in") &&
					ws		.IsFalse("has.side.in"))
					return false;
				
				ap.AddSideOutput(seg.as, n);
				return false;
			}
			/*}
			else {
				const APlanNode* accepted = ll.GetAcceptedSideNode();
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
	
	Array<Eon::WorldState*> to;
	Vector<double> action_costs;
	ap.GetPossibleStateTransition(n, to, action_costs);
	
	//LOG("TerminalTest: " << HexStr(&n) << " -> " << to.GetCount() << " (estimate " << n.GetEstimate() << ")");
	for(int i = 0; i < to.GetCount(); i++) {
		Eon::WorldState& ws_to = *to[i];
		if (req_ext && ws_to.IsAddComponent())
			continue;
		/*if (req_ext) {
			TypeCompCls to_comp = ws_to.GetComponent();
			ASSERT(to_comp.sink.val != ValCls::RECEIPT);
		}*/
		hash_t hash = ws_to.GetHashValue();
		int j = ap.tmp_sub.Find(hash);
		Eon::APlanNode* an = 0;
		if (j == -1) {
			Eon::APlanNode& sub = ap.tmp_sub.Add(hash);// n.Add();
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
		//LOG("\t" << n.GetEstimate() << ": " << HexStr(an) << " -> " << ws_to.ToString());
		
		/*if (ws_to.IsAddComponent()) {
			TypeCompCls t = ws_to.GetComponent();
			if (t.sub == SubCompCls::SIDE_INPUT) {
				ap.AddSideInput(*an);
			}
			else if (t.sub == SubCompCls::SIDE_OUTPUT) {
				ap.AddSideOutput(*an);
			}
		}*/
	}
	//if (n.GetTotalCount())
	//	return false;
	
	return false;
}


NAMESPACE_EON_END

#endif

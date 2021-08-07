#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_ECS_BEGIN


class EonLoader;



struct EonError : Moveable<EonError> {
	EonLoopLoader* ll = 0;
	String msg;
	int status = -1;
	
};






/*class EonScope {
protected:
	friend class EonLoader;
	friend class EonLoopLoader;
	
	Eon::WorldState			current_state;
	Eon::LoopDefinition*	loop = 0;
	Eon::ChainDefinition*	chain = 0;
	Eon::Machine*			mach = 0;
	Eon::GlobalScope*		glob = 0;
public:
	EonScope() {}
	
	void SetCurrentState(const Eon::WorldState& s) {current_state = s;}
	
	
};*/



class EonLoopSegment {
public:
	AStar<Eon::ActionNode>		as;
	Eon::Plan					ep;
	Eon::APlanNode*				start_node = 0;
	const Eon::ActionNode*		stop_node = 0;
	EonLoopLoader*				side_conn = 0;
	
	
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
} EonStatus;

inline const char* GetEonStatusString(EonStatus status) {
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

String GetEonStatusLine(int indent, EonStatus status, String extra_str=String());

class EonSystemLoader;
class EonMachineLoader;
class EonChainLoader;
class EonTopChainLoader;
class EonLoader;

template <class ParserDef, class LoaderParent>
class EonLoaderBase : RTTIBase {
	
	
protected:
	void ResetFlags() {any_waiting = false; any_retrying = false; all_ready = true; any_failed = false;}
	void CheckFlags(bool allow_internal);
	void CheckStatus(EonStatus s);
	
public:
	RTTI_DECL0(EonLoaderBase)
	virtual ~EonLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	EonStatus					status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	bool						any_waiting = false;
	bool						any_retrying = false;
	bool						all_ready = false;
	bool						any_failed = false;
	
	
	EonLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	void		Forward();
	void		SolveInternal();
	
	void		SetStatus(int s) {status = (EonStatus)s;}
	void		SetStatusRetry() {status = RETRY;}
	void		SetError(String s) {err_str = s; status = FAILED;}
	
	bool		IsFailed() const {return status == FAILED;}
	bool		IsReady() const {return status == READY;}
	bool		IsStatus(EonStatus s) const {return status == s;}
	int			GetId() const {return id;}
	EonStatus	GetStatus() const {return status;}
	EonLoader&	GetLoader() {return parent.GetLoader();}
	String		GetErrorString() const {return err_str;}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<EonLoopLoader*>& v) = 0;
	virtual void		ForwardLoops() = 0;
	virtual void		LoopStatus() = 0;
	virtual void		SetRetryDeep() = 0;
	
};

class EonLoopLoader : public EonLoaderBase<Eon::LoopDefinition, EonChainLoader> {
public:
	using Base = EonLoaderBase<Eon::LoopDefinition, EonChainLoader>;
	RTTI_DECL1(EonLoopLoader, Base)
	
	
protected:
	friend class EonLoader;
	
	
	Eon::APlanNode				start_node;
	Eon::APlanNode				goal_node;
	Eon::WorldState				start;
	Eon::WorldState				goal;
	
	Array<EonLoopSegment>		segments;
	Eon::ActionPlanner			planner;
	const Eon::APlanNode*		accepted_side_node = 0;
	
	Array<ComponentBaseRef>		comps;
	
	
	void SetupSegment(EonLoopSegment& s);
	bool SetWorldState(Eon::WorldState& ws, const Eon::Statement& stmt);
	
public:
	EonLoopLoader(EonChainLoader& parent, int id, Eon::LoopDefinition& def);
	
	
	void		Forward();
	void		InitSegments();
	void		ForwardTopSegment();
	
	
	bool		Parse();
	bool		Load();
	SideStatus	AcceptOutput(EonLoopLoader& out, Eon::ActionPlanner::State*& accepted_in, Eon::ActionPlanner::State*& accepted_out);
	void		AddSideConnectionSegment(Eon::ActionPlanner::State* n, EonLoopLoader* c, Eon::ActionPlanner::State* side_state);
	
	EonLoopSegment& GetCurrentSegment() {return segments.Top();}
	
	void		Visit(RuntimeVisitor& vis) override {vis && comps;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<EonLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
};


class EonChainLoader : public EonLoaderBase<Eon::ChainDefinition, EonTopChainLoader> {
	
	
public:
	using Base = EonLoaderBase<Eon::ChainDefinition, EonTopChainLoader>;
	RTTI_DECL1(EonChainLoader, Base)
	
public:
	Array<EonLoopLoader>		loops;
	
	
	EonChainLoader(EonTopChainLoader& parent, int id, Eon::ChainDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | loops;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<EonLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class EonTopChainLoader : public EonLoaderBase<Eon::ChainDefinition, EonMachineLoader> {
public:
	using Base = EonLoaderBase<Eon::ChainDefinition, EonMachineLoader>;
	RTTI_DECL1(EonTopChainLoader, Base)
	
public:
	enum {NORMAL, SPLITTED_CHAIN, SPLITTED_LOOPS};
	
	Array<EonChainLoader>		chains;
	Array<EonTopChainLoader>	subchains;
	EonTopChainLoader*			chain_parent;
	bool						use_subchains = false;
	
	
	EonTopChainLoader(int mode, EonMachineLoader& parent, EonTopChainLoader* chain_parent, int id, Eon::ChainDefinition& def);
	void		ForwardSubchainLoops();
	void		ForwardChainLoops();
	
	void		Visit(RuntimeVisitor& vis) override {vis | subchains | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<EonLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};


class EonMachineLoader : public EonLoaderBase<Eon::MachineDefinition, EonSystemLoader> {
public:
	using Base = EonLoaderBase<Eon::MachineDefinition, EonSystemLoader>;
	RTTI_DECL1(EonMachineLoader, Base)
	
public:
	Array<EonTopChainLoader>	chains;
	
	
	EonMachineLoader(EonSystemLoader& parent, int id, Eon::MachineDefinition& def);
	void		Visit(RuntimeVisitor& vis) override {vis | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<EonLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
};

class EonSystemLoader : public EonLoaderBase<Eon::GlobalScope, EonLoader> {
public:
	using Base = EonLoaderBase<Eon::GlobalScope, EonLoader>;
	RTTI_DECL1(EonSystemLoader, Base)
	
public:
	Array<EonMachineLoader>		machs;
	
	
	EonSystemLoader(EonLoader& parent, int id, Eon::GlobalScope& glob);
	
	void		Visit(RuntimeVisitor& vis) override {vis | machs;}
	void		GetLoops(Vector<EonLoopLoader*>& v) override;
	String		GetTreeString(int indent=0) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		SetRetryDeep() override;
	
	void		Dump() {LOG(GetTreeString());}
	
};

bool TestParseEonCode(String code);

class EonLoader :
	public System<EonLoader>
{
protected:
	friend class EonLoopLoader;
	friend class EonChainLoader;
	friend class EonTopChainLoader;
	friend class EonMachineLoader;
	static int loop_counter;
	
	//LinkedList<EonScope> scopes;
	Vector<Eon::GlobalScope*> scopes;
	One<EonSystemLoader> loader;
	
	Eon::WorldState def_ws;
	Eon::ActionPlanner def_planner;
	int tmp_side_id_counter = 0;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	Eon::CompilationUnit root;
	EntityStoreRef es;
	
	Vector<EonError> errs;
	bool collect_errors = false;
	
	
	void AddError(String msg);
	void AddError(EonLoopLoader* ll, String msg);
	void ReleaseErrorBuffer();
	void ClearErrorBuffer();
	void CollectErrorBuffer(bool b) {collect_errors = b;}
	//void EnterScope();
	//bool LeaveScope();
	
public:
	SYS_RTTI(EonLoader)
	SYS_CTOR(EonLoader);
	SYS_DEF_VISIT_((vis & es); if (!loader.IsEmpty()) vis % *loader;)
	
	void PostLoadFile(String path) {post_load_file << path;}
	void PostLoadString(String s) {post_load_string << s;}
	
	EonLoader&	GetLoader() {return *this;}
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
	bool		LoadCompilationUnit(Eon::CompilationUnit& cunit);
	bool		LoadGlobalScope(Eon::GlobalScope& list);
	EntityRef	ResolveEntity(Eon::Id& id);
	bool		ConnectSides(EonLoopLoader& loop0, EonLoopLoader& loop1);
	bool		ImplementPlan();
	
	Eon::State*	FindState(const Eon::Id& id);
	
	
	
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



class EonConnectionSolver {
	Vector<EonLoopLoader*>		loops;
	String						err_str;
	int&						tmp_side_id_counter;
	bool						is_missing_input = false;
	bool						is_missing_output = false;
	
	void SetError(String s) {err_str = s;}
	bool Process();
public:
	
	EonConnectionSolver(int& side_id_counter) : tmp_side_id_counter(side_id_counter) {}
	
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


template <>	inline bool TerminalTest<Ecs::Eon::ActionNode>(Node<Ecs::Eon::ActionNode>& n) {
	if (&n == (void*)0x8026C63C0) {
		LOG("");
	}
	
	using namespace Ecs;
	int est = n.GetEstimate();
	if (est <= 0)
		return true;
	Eon::ActionNode& goal = n.GetGoal();
	Eon::WorldState& goal_ws = goal.GetWorldState();
	if (n.Contains(goal))
		return true;
	if (goal.Conflicts(n))
		return false;
	Eon::WorldState& ws = n.GetWorldState();
	Eon::ActionPlanner& ap = n.GetActionPlanner();
	EonLoopLoader& ll = ap.GetLoopLoader();
	EonLoopSegment& seg = ll.GetCurrentSegment();
	
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
				POPO(Pol::Ecs::Eon::Loop::SideInIsBeforeSideOutAlways)
				if (goal_ws	.IsTrue	("has.side.in") &&
					ws		.IsFalse("has.side.in"))
					return false;
				
				ap.AddSideOutput(seg.as, n);
				return false;
			}
			/*}
			else {
				const Eon::APlanNode* accepted = ll.GetAcceptedSideNode();
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
	
	Array<Ecs::Eon::WorldState*> to;
	Vector<double> action_costs;
	ap.GetPossibleStateTransition(n, to, action_costs);
	
	//LOG("TerminalTest: " << HexStr(&n) << " -> " << to.GetCount() << " (estimate " << n.GetEstimate() << ")");
	for(int i = 0; i < to.GetCount(); i++) {
		Ecs::Eon::WorldState& ws_to = *to[i];
		if (req_ext && ws_to.IsAddComponent())
			continue;
		/*if (req_ext) {
			TypeCompCls to_comp = ws_to.GetComponent();
			ASSERT(to_comp.sink.val != ValCls::RECEIPT);
		}*/
		hash_t hash = ws_to.GetHashValue();
		int j = ap.tmp_sub.Find(hash);
		Ecs::Eon::APlanNode* an = 0;
		if (j == -1) {
			Ecs::Eon::APlanNode& sub = ap.tmp_sub.Add(hash);// n.Add();
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

NAMESPACE_TOPSIDE_END

#include "EonLoaderBase.inl"

#endif

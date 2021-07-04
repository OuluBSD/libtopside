#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_ECS_BEGIN


class EonLoader;










class EonScope {
protected:
	friend class EonLoader;
	friend class EonLoopLoader;
	
	Eon::WorldState current_state;
	Eon::SidechainDefinition* def = 0;
	
public:
	EonScope() {}
	
	void SetCurrentState(const Eon::WorldState& s) {current_state = s;}
	
	
};



class EonLoopSegment {
public:
	AStar<Eon::ActionNode>		as;
	Eon::Plan					ep;
	Eon::APlanNode*				start_node = 0;
	const Eon::ActionNode*		stop_node = 0;
	EonLoopLoader*				side_conn = 0;
	
	
};

class EonLoopLoader {
public:
	typedef enum {
		NOT_READY,
		WAITING_SIDE_INPUT,
		WAITING_SIDE_OUTPUT,
		READY,
		FAILED,
	} Status;
	
protected:
	friend class EonLoader;
	
	EonLoader&					loader;
	Eon::LoopDefinition&		def;
	
	Eon::APlanNode				start_node;
	Eon::APlanNode				goal_node;
	Eon::WorldState				start;
	Eon::WorldState				goal;
	
	Array<EonLoopSegment>		segments;
	Eon::ActionPlanner			planner;
	Status						status = NOT_READY;
	const Eon::APlanNode*		accepted_side_node = 0;
	
	Array<ComponentBaseRef>		comps;
	
	
	void SetupSegment(EonLoopSegment& s);
	
public:
	EonLoopLoader(EonLoader* loader, Eon::LoopDefinition& def);
	
	
	bool Parse();
	bool Forward();
	bool Load();
	bool AcceptOutput(EonLoopLoader& out, Eon::ActionPlanner::State*& accepted_in, Eon::ActionPlanner::State*& accepted_out);
	void AddError(String msg);
	void AddSideConnectionSegment(Eon::ActionPlanner::State* n, EonLoopLoader* c);
	
	bool IsFailed() const {return status == FAILED;}
	bool IsReady() const {return status == READY;}
	bool IsWaitingSideInput() const {return status == WAITING_SIDE_INPUT;}
	bool IsWaitingSideOutput() const {return status == WAITING_SIDE_OUTPUT;}
	EonLoopSegment& GetCurrentSegment() {return segments.Top();}
	
};



bool TestParseEonCode(String code);

class EonLoader :
	public System<EonLoader>
{
protected:
	friend class EonLoopLoader;
	
	LinkedList<EonScope> scopes;
	Array<EonLoopLoader> loops;
	
	Eon::WorldState def_ws;
	Eon::ActionPlanner def_planner;
	int tmp_side_id_counter = 0;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	Eon::CompilationUnit root;
	EntityStoreRef es;
	
	
	void AddError(String msg);
	
public:
	SYS_RTTI(EonLoader)
	SYS_CTOR(EonLoader);
	SYS_DEF_VISIT_(vis & es)
	
	void PostLoadFile(String path) {post_load_file << path;}
	void PostLoadString(String s) {post_load_string << s;}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::SYS_EON;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    bool DoPostLoad();
	bool LoadFile(String path);
	bool Load(String content, String filepath="temp");
	bool LoadCompilationUnit(Eon::CompilationUnit& cunit);
	bool LoadSidechainDefinition(Eon::SidechainDefinition& def);
	EntityRef ResolveEntity(Eon::Id& id);
	bool SolveLoops(Eon::SidechainDefinition& def);
	bool ConnectSides(EonLoopLoader& loop0, EonLoopLoader& loop1);
	
	
	
	
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



NAMESPACE_ECS_END

NAMESPACE_TOPSIDE_BEGIN


template <>	inline bool TerminalTest<Ecs::Eon::ActionNode>(Node<Ecs::Eon::ActionNode>& n) {
	using namespace Ecs;
	int est = n.GetEstimate();
	if (est <= 0)
		return true;
	Eon::ActionNode& goal = n.GetGoal();
	if (n.Contains(goal))
		return true;
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
		int64 hash = ws_to.GetHashValue();
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

#endif

#ifndef _SerialLib_Script_h_
#define _SerialLib_Script_h_

NAMESPACE_SERIAL_BEGIN


class ScriptLoader;



struct ScriptError : Moveable<ScriptError> {
	ScriptLoopLoader* ll = 0;
	String msg;
	int status = -1;
	
};



class ScriptLoopSegment {
public:
	AStar<Script::ActionNode>		as;
	Script::Plan					ep;
	Script::APlanNode*				start_node = 0;
	const Script::ActionNode*		stop_node = 0;
	//ScriptLoopLoader*				side_conn = 0;
	
	
	String GetTreeString(int id, int indent);
	
};

typedef enum {
	UNASSIGNED,
	
	IN_BEGINNING,
	WAITING_CHILDREN,
	
	SEARCH_SEGMENT,
	PRUNE_SEGMENT_GOALS,
	WAITING_PARENT_SIDE_LINKS,
	WAITING_OTHER_LOOPS,
	
	MAKE_OPTION_LINK_VECTOR,
	PRUNE_OPTION_LINKS,
	LINK_PLANNER,
	LINKER,
	
	READY,
	FAILED,
} ScriptStatus;

inline const char* GetScriptStatusString(ScriptStatus status) {
	const char* t = "<invalid status>";
	switch (status) {
		case IN_BEGINNING:					t = "In beginning"; break;
		case WAITING_PARENT_SIDE_LINKS:		t = "Waiting parent side links"; break;
		case WAITING_OTHER_LOOPS:				t = "Waiting other loops"; break;
		case WAITING_CHILDREN:				t = "Waiting children"; break;
		case SEARCH_SEGMENT:				t = "Search segment"; break;
		case PRUNE_SEGMENT_GOALS:			t = "Prune segment goals"; break;
		case MAKE_OPTION_LINK_VECTOR:		t = "Make option link vector"; break;
		case PRUNE_OPTION_LINKS:			t = "Prune option links"; break;
		case LINK_PLANNER:					t = "Link planner"; break;
		case LINKER:						t = "Linker"; break;
		case READY:							t = "Ready"; break;
		case FAILED:						t = "Failed"; break;
		case UNASSIGNED:					t = "Unassigned"; break;
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


int GetTotalSegmentCount(Vector<ScriptLoopLoader*>& v);


template <class ParserDef, class LoaderParent>
class ScriptLoaderBase : RTTIBase {
	
	
protected:
	void ResetFlags() {any_waiting_parent = false; any_waiting_children = false; any_linking = false; any_routing = false; all_ready = true; any_failed = false;}
	void CheckFlags();
	void CheckStatus(ScriptStatus s);
	
	int							iter = 0;
	
	
public:
	RTTI_DECL0(ScriptLoaderBase)
	virtual ~ScriptLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	ScriptStatus				status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	bool						any_waiting_parent = false;
	bool						any_waiting_children = false;
	bool						any_linking = false;
	bool						any_routing = false;
	bool						all_ready = false;
	bool						any_failed = false;
	int							prev_segment_count = 0;
	
	ScriptLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	void				Forward();
	
	//void				SetStatusRetry() {SetStatus(RETRY);}
	void				SetError(String s) {err_str = s; SetStatus(FAILED); LOG("ScriptLoaderBase::SetError: this=" << HexStr(this) << ": " << s); }
	
	bool				IsFailed() const {return status == FAILED;}
	bool				IsReady() const {return status == READY;}
	bool				IsStatus(ScriptStatus s) const {return status == s;}
	int					GetId() const {return id;}
	ScriptStatus		GetStatus() const {return status;}
	ScriptLoader&		GetLoader() {return parent.GetLoader();}
	String				GetErrorString() const {return err_str;}
	
	virtual Script::Id	GetDeepId() const {Script::Id id = parent.GetDeepId(); id.Append(def.id); return id;}
	virtual void		SetStatus(ScriptStatus s) {status = s;}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<ScriptLoopLoader*>& v) = 0;
	virtual void		ForwardLoops() = 0;
	virtual void		LoopStatus() = 0;
	virtual void		CheckStatusDeep() = 0;
	virtual void		GetDrivers(Vector<ScriptDriverLoader*>& v) {Panic("not implemented");}
	virtual void		GetStates(Vector<ScriptStateLoader*>& v) {Panic("not implemented");}
	
};

class ScriptLoopLoader : public ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader> {
	
protected:
	
	// Implement found loop
	struct AddedAtom {
		AtomBaseRef		r;
		LinkBaseRef		l;
		int				plan_i;
		int				seg_i;
		IfaceConnTuple	iface;
	};
	
	Array<AddedAtom>		added_atoms;
	
public:
	using Base = ScriptLoaderBase<Script::LoopDefinition, ScriptChainLoader>;
	RTTI_DECL1(ScriptLoopLoader, Base)
	
	
protected:
	friend class ScriptLoader;
	friend class ScriptConnectionSolver;
	friend class ScriptChainLoader;
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
	
	Script::APlanNode				start_node;
	Script::APlanNode				goal_node;
	Script::WorldState				start;
	Script::WorldState				goal;
	
	Array<ScriptLoopSegment>		segments;
	Script::ActionPlanner			planner;
	const Script::APlanNode*		accepted_side_node = 0;
	
	Array<AtomBaseRef>				atoms;
	Vector<AtomSideLinks>			atom_links;
	
	
	void SetSideSourceConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& sink);
	void SetSideSinkConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& src);
	bool IsAllSidesConnected() const;
	bool IsTopSidesConnected() const;
	void SetupSegment(ScriptLoopSegment& s);
	bool SetWorldState(Script::WorldState& ws, const Script::Statement& stmt);
	
	
public:
	ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def);
	
	
	void		Forward();
	void		InitSegments();
	void		SearchNewSegment();
	void		PruneSegmentGoals();
	void		DumpLoop();
	bool		PassSideConditionals(const Script::Statement& side_stmt);
	
	
	bool		Parse();
	bool		Load();
	bool		PostInitialize();
	bool		Start();
	void		AddSideConnectionSegment(Script::ActionPlanner::State& n);
	void		UpdateLoopLimits();
	void		RealizeConnections(const Script::ActionPlanner::State& last_state);
	int			GetAtomLinkCount() const {return atom_links.GetCount();}
	int			GetSegmentCount() const {return segments.GetCount();}
	
	ScriptLoopSegment& GetCurrentSegment() {return segments.Top();}
	
	void		Visit(RuntimeVisitor& vis) override {vis && atoms;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	void		SetStatus(ScriptStatus status) override;
};




struct ScriptIfaceReservation {
	ScriptLoopLoader*	loop = 0;
	int					ch_id = 0;
	bool				is_src = false;
	AtomTypeCls			type;
	
	bool Conflicts(const ScriptIfaceReservation& o) const {
		if (loop == o.loop) {
			// This is not an issue, don't enable
			#if 0
			if (is_src != o.is_src) // can't connect same loop's source to it's own sink
				return true;
			else
			#endif
			
			if (type == o.type)
				return ch_id == o.ch_id; // with the same type just don't use same channel
			else
				return true; // these are completely different nodes, which compete which each others about the same next atom's position
		}
		else return false; // different loops does not conflict
	}
};

struct ScriptIfaceOption {
	double							pre_node_dist = 0;
	double							post_node_dist = 0;
	double							total_distance = 0;
	bool							is_src = false;
	Script::ActionPlanner::State	state;
	const Script::Statement*		stmt = 0;
	int								id = -1;
	
	bool IsSource() const {return is_src;}
	bool IsSink() const {return !is_src;}
	String ToString() const;
	
	bool operator()(const ScriptIfaceOption& a, const ScriptIfaceOption& b) const {
		return a.total_distance < b.total_distance;
	}
};

struct ScriptLoopOptions {
	Array<ScriptIfaceOption>	link_opts;
	ScriptLoopLoader*			ll = 0;
	int							id = -1;
	
	int GetCount() const {return link_opts.GetCount();}
	const ScriptIfaceOption& operator[](int i) const {return link_opts[i];}
	String ToString() const;
};

struct ScriptLinkOption : Moveable<ScriptLinkOption> {
	ScriptLoopOptions*			src_loop = 0;
	ScriptLoopOptions*			sink_loop = 0;
	ScriptIfaceOption*			src = 0;
	ScriptIfaceOption*			sink = 0;
	double						src_total_distance;
	double						sink_total_distance;
	double						total_distance;
	
	bool operator()(const ScriptLinkOption& a, const ScriptLinkOption& b) const {
		return a.total_distance < b.total_distance;
	}
	
	String ToString() const;
};

class ScriptConnectionSolver {
	Array<ScriptLinkOption>		links;
	String						err_str;
	
	void SetError(String s) {err_str = s;}
	void InitializeLoops(const Vector<ScriptLoopLoader*>& loops);
public:
	
	
	template <class T>
	bool Initialize(T* o) {
		Vector<ScriptLoopLoader*> loops;
		o->GetLoops(loops);
		if (loops.IsEmpty()) {
			SetError("Internal error: no loops");
			return false;
		}
		InitializeLoops(loops);
		return true;
	}
	
	bool		MakeOptionLinkVector();
	bool		FindAcceptedLinks();
	bool		LinkPlanner();
	
	String		GetError() const {return err_str;}
	
	
	
	
	Array<ScriptLoopOptions>	loops;
	Vector<ScriptLinkOption*>	result;
	
};


class ScriptChainLoader : public ScriptLoaderBase<Script::ChainDefinition, ScriptTopChainLoader> {
	One<ScriptConnectionSolver>	solver;
	
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
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	Script::Id	GetDeepId() const override;
	
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
	void		ForwardSubchainLoops();
	void		ForwardChainLoops();
	
	void		Visit(RuntimeVisitor& vis) override {vis | subchains | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	
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
	void		ForwardLoops() override {}
	void		LoopStatus() override {}
	void		CheckStatusDeep() override {}
	String		GetTreeString(int indent) override;
	void		Forward() {}
	bool		Load();
	bool		PostInitialize();
	
};

class ScriptDriverLoader : public ScriptLoaderBase<Script::DriverDefinition, ScriptMachineLoader> {
	
protected:
	
	// Implement found loop
	struct AddedAtom {
		AtomBaseRef		a;
		LinkBaseRef		l;
	};
	
	Array<AddedAtom>		added_atoms;
	
protected:
	Vector<Script::WorldState>	atoms;
	Script::ActionPlanner		planner;  // required for Script::Action -> Script:WorldState -> key-index
	
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
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	void		Forward();
	bool		Load();
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
	void		Visit(RuntimeVisitor& vis) override {vis | chains;}
	String		GetTreeString(int indent) override;
	void		GetLoops(Vector<ScriptLoopLoader*>& v) override;
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	
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
	void		GetDrivers(Vector<ScriptDriverLoader*>& v) override;
	void		GetStates(Vector<ScriptStateLoader*>& v) override;
	String		GetTreeString(int indent=0) override;
	void		ForwardLoops() override;
	void		LoopStatus() override;
	void		CheckStatusDeep() override;
	
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
	One<Script::CompilationUnit> root;
	LoopStoreRef es;
	SpaceStoreRef ss;
	
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
	SYS_DEF_VISIT_(((vis & es) & ss); if (!loader.IsEmpty()) vis % *loader;)
	
	void PostLoadFile(const String& path) {post_load_file << path;}
	void PostLoadString(const String& s) {post_load_string << s;}
	
	ScriptLoader&	GetLoader() {return *this;}
	int&			GetSideIdCounter() {return tmp_side_id_counter;}
	
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::SCRIPT_LOADER_SYSTEM;}
	
protected:
	
	~ScriptLoader();
    bool		Initialize() override;
    void		Start() override;
    void		Update(double dt) override;
    void		Stop() override;
    void		Uninitialize() override;
    
    void		Cleanup();
    void		DumpErrors();
    bool		DoPostLoad();
	bool		LoadFile(String path);
	bool		Load(const String& content, const String& filepath="temp");
	bool		LoadCompilationUnit(Script::CompilationUnit& cunit);
	bool		LoadGlobalScope(Script::GlobalScope& list);
	bool		ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1);
	bool		ImplementScript();
	
	Script::State*	FindState(const Script::Id& id);
	
	
	
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



NAMESPACE_SERIAL_END

NAMESPACE_TOPSIDE_BEGIN


template <>	inline bool TerminalTest<Serial::Script::ActionNode>(
	Node<Serial::Script::ActionNode>& n,
	Node<Serial::Script::ActionNode>** prev)
{
	/*if (&n == (void*)0x806A117C0) {
		LOG("");
	}*/
	MACHVER_ENTER(TerminalTest)
	
	using namespace Serial;
	double est = n.GetEstimate();
	if (est <= 0) {
		MACHVER_LEAVE(TerminalTest)
		return true;
	}
	Script::ActionNode& goal = n.GetGoal();
	Script::WorldState& goal_ws = goal.GetWorldState();
	if (n.Contains(goal)) {
		MACHVER_LEAVE(TerminalTest)
		return true;
	}
	if (goal.Conflicts(n)) {
		MACHVER_LEAVE(TerminalTest)
		return false;
	}
	Script::WorldState& ws = n.GetWorldState();
	Script::ActionPlanner& ap = n.GetActionPlanner();
	ScriptLoopLoader& ll = ap.GetLoopLoader();
	ScriptLoopSegment& seg = ll.GetCurrentSegment();
	
	/*if (est == 1) {
		LOG(ws.ToString());
	}*/
	
	AtomTypeCls atom = ws.GetAtom();
	
	//TODO check for conflicting loop
	
	if (ws.IsAddAtom() && n.GetLinkedCount() && atom.iface.src().val == ValCls::ORDER) {
		MACHVER_LEAVE(TerminalTest)
		return false;
	}
	
	if (ws.IsAddAtom()) {
		if (n.GetLinkedCount() > 0) {
			AtomTypeCls a = ws.GetAtom();
			
			if (a.iface.sink.GetCount() >= 2 || a.iface.src.GetCount() >= 2) {
				for(int i = 1; i < a.iface.sink.GetCount(); i++) {
					ap.AddSideSink(i, seg.as, n, prev);
				}
				for(int i = 1; i < a.iface.src.GetCount(); i++) {
					ap.AddSideSource(i, seg.as, n, prev);
				}
				MACHVER_LEAVE(TerminalTest)
				return false;
			}
			
			#if 0
			if (a.iface.sink.GetCount() >= 2) {
				ASSERT(a.HasSideChannels());
				ap.AddSideSink(seg.as, n, prev);
				MACHVER_LEAVE(TerminalTest)
				return false;
			}
			if (a.iface.src.GetCount() >= 2) {
				ASSERT(a.HasSideChannels());
				POPO(Pol::Serial::Script::Loop::SideSinkIsBeforeSideSourceAlways)
				if (goal_ws	.IsTrue	("has.side.sink") &&
					ws		.IsFalse("has.side.sink")) {
					MACHVER_LEAVE(TerminalTest)
					return false;
				}
				
				ap.AddSideSource(seg.as, n, prev);
				
				MACHVER_LEAVE(TerminalTest)
				return false;
			}
			#endif
		}
	}
	else {
		LOG("Unexpected action");
		MACHVER_LEAVE(TerminalTest)
		return false;
	}
	
	Array<Serial::Script::WorldState*> to;
	Vector<double> action_costs;
	ap.GetPossibleStateTransition(n, to, action_costs);
	
	RTLOG("TerminalTest: " << HexStr(&n) << " -> " << to.GetCount() << " (estimate " << n.GetEstimate() << ")");
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
		
		RTLOG("   " << n.GetEstimate() << ": " << HexStr(an) << " -> " << ws_to.ToString());
	}
	
	MACHVER_LEAVE(TerminalTest)
	return false;
}

NAMESPACE_TOPSIDE_END

#include "LoaderBase.inl"

#endif

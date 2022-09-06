#ifndef _SerialScript_Planner_h_
#define _SerialScript_Planner_h_

NAMESPACE_SERIAL_BEGIN


namespace Script {
class WorldState;
class Action;
}

class ScriptLoader;
class ScriptLoopLoader;
class ScriptDriverLoader;
class ScriptStateLoader;

void GetAtomActions(const Script::WorldState& src, Vector<Script::Action>& acts);


namespace Script {

class ActionPlanner;
class ActionNode;

class WorldState : public Moveable<WorldState> {

public:
	typedef enum : byte {
		INVALID,
		ADD_COMP,
	} Type;
	
protected:
	friend class ActionPlanner;
	friend class ActionPlannerWrapper;
	friend class ActionNode;
	friend class ::TS::Serial::ScriptLoader;
	friend class ::TS::Serial::ScriptLoopLoader;
	friend class ::TS::Serial::ScriptDriverLoader;
	
	static const bool use_debugging_order = true;
	
	Vector<String>				values;
	Vector<bool>				using_act;
	Index<short>				dbg_order;
	AtomTypeCls					cur_atom;
	ValDevCls					sink_vd;
	ValDevCls					side_vd;
	Type						type = INVALID;
	ActionPlanner*				ap = 0;
	
public:
	
	WorldState();
	void Clear();
	
	const        Script::Statement* FindStatement(const WorldState* ws, LinkedList<Statement>& stmts, bool dbg_print=false) const;
	static const Script::Statement* FindStatement(const String& find_key, LinkedList<Statement>& stmts, bool dbg_print=false);
	
	bool Append(const WorldState& ws, LinkedList<Statement>& ret_list);
	void SetActionPlanner(ActionPlanner& ap) {this->ap = &ap;}
	bool Set(int index, bool value);
	bool Set(int index, String value);
	bool Set(const String& key, bool value);
	bool Set(const String& key, String value);
	void SetTrue(const String& key) {Set(key, true);}
	void SetFalse(const String& key) {Set(key, false);}
	void SetAs_AddAtom(AtomTypeCls atom) {type = ADD_COMP; cur_atom = atom;}
	void SetSideCls(ValDevCls vd) {side_vd = vd;}
	void SetSinkCls(ValDevCls vd) {sink_vd = vd;}
	
	ActionPlanner& GetActionPlanner() const {return *ap;}
	bool IsAddAtom() const {return type == ADD_COMP;}
	bool IsTrue(const String& key) const;
	bool IsFalse(const String& key) const;
	bool IsFalse(int idx) const;
	bool IsUndefined(const String& key) const;
	bool IsUndefined(int idx) const;
	bool IsEmpty() const {return values.IsEmpty();}
	String Get(const String& key) const;
	String Get(int idx) const;
	hash_t GetHashValue() const;
	AtomTypeCls GetAtom() const {return cur_atom;}
	ValDevCls GetCommonSink() const {return sink_vd;}
	ValDevTuple GetInterfaceSink() const {ASSERT(cur_atom.IsValid()); return cur_atom.iface.sink;}
	ValDevTuple GetInterfaceSource() const {ASSERT(cur_atom.IsValid()); return cur_atom.iface.src;}
	const ValDevCls& GetSideCls() const {return side_vd;}
	const ValDevCls& GetSinkCls() const {return sink_vd;}
	String ToString() const;
	String GetFullString() const;
	bool Contains(const WorldState& ws) const;
	bool Conflicts(const WorldState& ws) const;
	int Compare(int idx, const WorldState& ws) const;
	
	WorldState& operator=(const WorldState& src);
	
	bool operator==(const WorldState& ws) const {return GetHashValue() == ws.GetHashValue();}
	bool operator!=(const WorldState& ws) const {return GetHashValue() != ws.GetHashValue();}
	
};


class Action : public Moveable<Action> {
	
protected:
	friend class ActionPlanner;
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	friend class Factory;
	
	WorldState				precond;
	WorldState				postcond;
	double					cost;
	
public:

	Action();
	Action(const WorldState& cond) : precond(cond), postcond(cond), cost(0) {}
	
	const WorldState& Pre() const {return precond;}
	const WorldState& Post() const {return postcond;}
	WorldState& Pre() {return precond;}
	WorldState& Post() {return postcond;}
	
	bool IsAddAtom() const {return postcond.IsAddAtom();}
	
};

class ActionNode : RTTIBase {
	WorldState*			ws;
	double				cost;
	int					linked_count = 0;
	
	ActionPlanner*		ap;
	ActionNode*			goal;
	IfaceConnTuple		iface;
	
	
public:
	RTTI_DECL0(ActionNode)
	
	
	ActionNode();
	
	
	void SetActionPlanner(ActionPlanner& ap_) {ap = &ap_;}
	void SetGoal(ActionNode& ws) {goal = &ws;}
	void SetWorldState(WorldState& ws) {this->ws = &ws;}
	void SetCost(double d) {cost = d;}
	void IncLinked() {linked_count++;}
	void ResetLinked() {linked_count=0;}
	
	ActionPlanner& GetActionPlanner() {return *ap;}
	WorldState& GetWorldState() {return *ws;}
	const WorldState& GetWorldState() const {return *ws;}
	ActionNode& GetGoal() {return *goal;}
	double GetDistance(const ActionNode& to);
	double GetEstimate();
	double GetCost() const {return cost;}
	int GetLinkedCount() const {return linked_count;}
	IfaceConnTuple&			GetInterface() {return iface;}
	const IfaceConnTuple&	GetInterface() const {return iface;}
	bool Contains(const ActionNode& n) const;
	bool Conflicts(const ActionNode& n) const;
	
};

typedef Node<ActionNode> APlanNode;


class Plan : Moveable<Plan> {
public:
	Vector<Script::ActionNode*> plan;
	
	Plan() {}
	Plan(const Plan& ep) {*this = ep;}
	void operator=(const Plan& ep) {
		plan <<= ep.plan;
	}
};


class ActionPlannerWrapper;

class ActionPlanner {
	
public:
	using ANode = Node<Script::ActionNode>;
	using Searcher = AStar<Script::ActionNode>;
	
	struct State : Moveable<State> {
		static const int MAX_PREV = 5;
		ANode*					previous[MAX_PREV];
		ANode*					last = 0;
		Searcher				as;
		int						ch_i;
		
		
		String ToString() const;
	};
	
protected:
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	friend class ::TS::Serial::ScriptLoader;
	friend class ::TS::Serial::ScriptLoopLoader;
	friend class ::TS::Serial::ScriptDriverLoader;
	
	
	struct Atom : Moveable<Atom> {
		Vector<String> id;
		
		String ToString() const {return Join(id, ".");}
	};
	
	VectorMap<String, Atom>		atoms;
	Vector<Action>				acts;
	ActionPlannerWrapper*		wrapper = 0;
	ScriptLoopLoader*			loop_loader = 0;
	Array<WorldState>			search_cache;
	Vector<State>				side_sinks, side_srcs;
	double						side_sink_max_est, side_src_max_est;
	
public:
	ArrayMap<hash_t, Node<ActionNode> > tmp_sub;
	
public:
	ActionPlanner();
	
	
	void Clear();
	void ClearForward();
	
	int GetActionCount() const {return acts.GetCount();}
	int GetAtomCount() const {return atoms.GetCount();}
	int GetAddAtom(String id);
	int GetAddAtom(const Id& id);
	const Atom& GetAtom(int i) const {return atoms[i];}
	bool IsSideSink() const {return side_sink_max_est <= side_src_max_est;}
	Vector<State>& GetSideSinks() {return side_sinks;}
	Vector<State>& GetSideSources() {return side_srcs;}
	
	bool SetPreCondition(int action_id, int atom_id, bool value);
	bool SetPostCondition(int action_id, int atom_id, bool value);
	bool SetCost(int action_id, int cost );
	void SetLoopLoader(ScriptLoopLoader* l) {loop_loader = l;}
	void AddSideSink(int ch_i, const Searcher& as, ANode& n, ANode** prev);
	void AddSideSource(int ch_i, const Searcher& as, ANode& n, ANode** prev);
	
	void GetPossibleStateTransition(Node<Script::ActionNode>& n, Array<WorldState*>& dest, Vector<double>& action_costs);
	ScriptLoopLoader& GetLoopLoader() const {return *loop_loader;}
	
};

class ActionPlannerWrapper {
	ActionPlanner& ap;
	Vector<String> atoms, acts;
	
protected:
	friend class ActionPlanner;
	
	void OnResize();
	
public:
	ActionPlannerWrapper(ActionPlanner& planner);
	
	int GetAtomIndex(String atom_name);
	int GetActionIndex(String action_name);
	String GetAtomName(int i) {return atoms[i];}
	String GetActionName(int i) {return acts[i];}
	String GetWorldstateDescription( const WorldState& ws );
	String GetDescription();
	
	void SetAction(int act_i, String s) {acts[act_i] = s;}
	void SetAtom(int atom_i, String s) {atoms[atom_i] = s;}
	bool SetPreCondition(String action_name, String atom_name, bool value);
	bool SetPostCondition(String action_name, String atom_name, bool value);
	bool SetCost(String action_name, int cost );
	
};


}

NAMESPACE_SERIAL_END

#endif

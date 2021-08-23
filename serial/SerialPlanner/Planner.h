#ifndef _SerialPlanner_Planner_h_
#define _SerialPlanner_Planner_h_

NAMESPACE_SERIAL_BEGIN


namespace Script {
class WorldState;
class Action;
}

class ScriptLoader;
class ScriptLoopLoader;

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
	
	static const bool use_debugging_order = true;
	
	Vector<String>				values;
	Vector<bool>				using_act;
	Index<short>				dbg_order;
	AtomTypeCls					cur_atom;
	ValDevCls					side_vd;
	Type						type = INVALID;
	ActionPlanner*				ap = 0;
public:
	
	WorldState();
	void Clear();
	
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
	
	ActionPlanner& GetActionPlanner() const {return *ap;}
	bool IsAddAtom() const {return type == ADD_COMP;}
	bool IsTrue(const String& key) const;
	bool IsFalse(const String& key) const;
	bool IsFalse(int idx) const;
	bool IsUndefined(const String& key) const;
	bool IsUndefined(int idx) const;
	String Get(const String& key) const;
	String Get(int idx) const;
	hash_t GetHashValue() const;
	AtomTypeCls GetAtom() const {return cur_atom;}
	ValDevCls GetInterface() const {ASSERT(cur_atom.IsValid()); return cur_atom.iface.side;}
	const ValDevCls& GetSideCls() const {return side_vd;}
	String ToString() const;
	String GetFullString() const;
	bool Contains(const WorldState& ws) const;
	bool Conflicts(const WorldState& ws) const;
	int Atomare(int idx, const WorldState& ws) const;
	
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
	int					side_in = -1;
	int					side_out = -1;
	
public:
	RTTI_DECL0(ActionNode)
	
	
	ActionNode();
	
	
	void SetActionPlanner(ActionPlanner& ap_) {ap = &ap_;}
	void SetGoal(ActionNode& ws) {goal = &ws;}
	void SetWorldState(WorldState& ws) {this->ws = &ws;}
	void SetCost(double d) {cost = d;}
	void SetSideInId(int i) {side_in = i;}
	void SetSideOutId(int i) {side_out = i;}
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
	int GetSideInId() const {return side_in;}
	int GetSideOutId() const {return side_out;}
	
	bool Contains(const ActionNode& n) const;
	bool Conflicts(const ActionNode& n) const;
	
};

typedef Node<ActionNode> APlanNode;


struct Plan : Moveable<Plan> {
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
		ANode*					last;
		Searcher				as;
	};
	
protected:
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	friend class ::TS::Serial::ScriptLoader;
	friend class ::TS::Serial::ScriptLoopLoader;
	
	
	struct Atom : Moveable<Atom> {
		Vector<String> id;
		
		String ToString() const {return Join(id, ".");}
	};
	
	VectorMap<String, Atom>		atoms;
	Vector<Action>				acts;
	ActionPlannerWrapper*		wrapper = 0;
	ScriptLoopLoader*				loop_loader = 0;
	Array<WorldState>			search_cache;
	Vector<State>				side_inputs, side_outputs;
	int							side_in_max_est, side_out_max_est;
	
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
	bool IsSideInput() const {return side_in_max_est <= side_out_max_est;}
	Vector<State>& GetSideInputs() {return side_inputs;}
	Vector<State>& GetSideOutputs() {return side_outputs;}
	
	bool SetPreCondition(int action_id, int atom_id, bool value);
	bool SetPostCondition(int action_id, int atom_id, bool value);
	bool SetCost(int action_id, int cost );
	void SetLoopLoader(ScriptLoopLoader* l) {loop_loader = l;}
	void AddSideInput(const Searcher& as, ANode& n);
	void AddSideOutput(const Searcher& as, ANode& n);
	
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

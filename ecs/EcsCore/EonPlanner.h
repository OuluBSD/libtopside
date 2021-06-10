#ifndef _EcsLib_EonPlanner_h_
#define _EcsLib_EonPlanner_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Eon {

class ActionPlanner;
class ActionNode;

class WorldState : public Moveable<WorldState> {

protected:
	friend class ActionPlanner;
	friend class ActionPlannerWrapper;
	friend class ActionNode;
	
	Vector<String>		values;
	Vector<bool>		using_act;
	TypeCls				cur_comp;
public:
	
	WorldState();
	void Clear();
	
	void SetComponent(TypeCls t) {cur_comp = t;}
	bool Set(int index, bool value);
	bool Set(int index, String value);
	
	WorldState& operator = (const WorldState& src);
	
	int64 GetHashValue();
	TypeCls GetComponent() const {return cur_comp;}
	
};


class Action : public Moveable<Action> {
	
protected:
	friend class ActionPlanner;
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	
	WorldState precond, postcond;
	double cost;
	
public:

	Action();
};


class ActionPlannerWrapper;

class ActionPlanner {
	
protected:
	friend class ActionNode;
	friend class ActionPlannerWrapper;
	
	struct Atom : Moveable<Atom> {
		Vector<String> id;
	};
	
	VectorMap<String, Atom> atoms;
	Vector<Action> acts;
	ActionPlannerWrapper* wrapper = 0;
	
	Array<WorldState> search_cache;
	
	
public:
	ActionPlanner();
	
	
	void Clear();
	
	int GetActionCount() const {return acts.GetCount();}
	int GetAtomCount() const {return atoms.GetCount();}
	
	int GetAddAtom(String id);
	int GetAddAtom(const Id& id);
	
	bool SetPreCondition(int action_id, int atom_id, bool value);
	bool SetPostCondition(int action_id, int atom_id, bool value);
	bool SetCost(int action_id, int cost );
	
	
	void DoAction( TypeCls dst_comp, int action_id, const WorldState& src, WorldState& dest);
	void GetPossibleStateTransition(Node<Eon::ActionNode>& n, const WorldState& src, Array<WorldState*>& dest, Vector<int>& act_ids, Vector<double>& action_costs);
	
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

class ActionNode : RTTIBase {
	WorldState* ws;
	double cost;
	int act_id;
	
	static ActionPlanner* ap;
	static ActionNode* goal;
	
public:
	RTTI_DECL0(ActionNode)
	
	static ArrayMap<hash_t, Node<ActionNode> > tmp_sub;
	
	
	ActionNode();
	
	static ActionPlanner& GetActionPlanner() {return *ap;}
	WorldState& GetWorldState() {return *ws;}
	
	void SetActionPlanner(ActionPlanner& ap_) {ap = &ap_;}
	void SetGoal(ActionNode& ws) {goal = &ws;}
	
	void SetWorldState(WorldState& ws) {this->ws = &ws;}
	inline void SetCost(double d) {cost = d;}
	inline void SetActionId(int i) {act_id = i;}
	
	double GetDistance(const ActionNode& to);
	double GetEstimate();
	inline double GetCost() const {return cost;}
	inline int GetActionId() const {return act_id;}
};

typedef Node<ActionNode> APlanNode;


}


template <>	inline bool TerminalTest<Eon::ActionNode>(Node<Eon::ActionNode>& n) {
	if (n.GetEstimate() <= 0)
		return true;
	Eon::WorldState& ws = n.GetWorldState();
	Eon::ActionPlanner& ap = Eon::APlanNode::GetActionPlanner();
	Array<Eon::WorldState*> to;
	Vector<int> act_ids;
	Vector<double> action_costs;
	ap.GetPossibleStateTransition(n, ws, to, act_ids, action_costs);
	for(int i = 0; i < to.GetCount(); i++) {
		Eon::WorldState& ws_to = *to[i];
		int64 hash = ws_to.GetHashValue();
		int j = Eon::ActionNode::tmp_sub.Find(hash);
		if (j == -1) {
			Eon::APlanNode& sub = Eon::ActionNode::tmp_sub.Add(hash);// n.Add();
			sub.SetWorldState(ws_to);
			sub.SetCost(action_costs[i]);
			sub.SetActionId(act_ids[i]);
			n.AddLink(sub);
		} else {
			n.AddLink(Eon::ActionNode::tmp_sub[j]);
		}
	}
	return !n.GetTotalCount();
}

NAMESPACE_TOPSIDE_END

#endif

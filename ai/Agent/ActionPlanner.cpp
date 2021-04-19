#include "Agent.h"


NAMESPACE_OULU_BEGIN

WorldState::WorldState() {
	
	Clear();
}

void WorldState::Clear() {
	values.Clear();
	using_act.Clear();
}

bool WorldState::Set(int index, bool value) {
	if (index < 0) return false;
	if (using_act.GetCount() <= index) {
		using_act.SetCount(index+1, false);
		values.SetCount(index+1, false);
	}
	using_act[index] = true;
	values[index] = value;
	return true;
}

WorldState& WorldState::operator = (const WorldState& src) {
	values <<= src.values;
	using_act <<= src.using_act;
	return *this;
}


int64 WorldState::GetHashValue() {
	CombineHash c;
	for(int i = 0; i < values.GetCount(); i++) {
		c.Do(using_act[i]);
		c.Do(values[i]);
	}
	return c;
}

Action::Action() : cost(1.0) {
	
}






ActionPlanner::ActionPlanner() {
	
}


void ActionPlanner::Clear() {
	atom_count = 0;
	acts.Clear();
	search_cache.Clear();
}


void ActionPlanner::DoAction( int action_id, const WorldState& src, WorldState& dest) {
	const WorldState& post = acts[action_id].postcond;
	
	dest = src;
	
	for(int i = 0; i < post.using_act.GetCount(); i++) {
		if (post.using_act[i]) {
			dest.Set(i, post.values[i]);
		}
	}
}


void ActionPlanner::GetPossibleStateTransition(const WorldState& src, Array<WorldState*>& dest, Vector<int>& act_ids, Vector<double>& action_costs)
{
	for ( int i=0; i < acts.GetCount(); ++i )
	{
		// Check precondition
		Action& act = acts[i];
		const WorldState& pre = act.precond;
		
		// Check that precondition is not using something outside of src values
		int count = Upp::min(pre.using_act.GetCount(), src.using_act.GetCount());
		bool fail = false;
		for(int j = count; j < pre.using_act.GetCount(); j++)
			if (pre.using_act[j] && pre.values[j]) {fail = true; break;}
		if (fail) continue;
		
		bool met = true;
		for(int j = 0; j < count; j++) {
			int a = pre.using_act[j];
			if (a && src.values[j] != pre.values[j]) {met = false; break;}
		}
		
		if (met) {
			act_ids.Add(i);
			action_costs.Add(act.cost);
			WorldState& tmp = search_cache.Add();
			DoAction( i, src, tmp );
			dest.Add(&tmp);
		}
	}
}

bool ActionPlanner::SetPreCondition(int act_idx, int atm_idx, bool value)
{
	if ( act_idx == -1 || atm_idx == -1 ) return false;
	acts[act_idx].precond.Set(atm_idx, value);
	return true;
}


bool ActionPlanner::SetPostCondition(int act_idx, int atm_idx, bool value)
{
	if ( act_idx == -1 || atm_idx == -1 ) return false;
	acts[act_idx].postcond.Set(atm_idx, value);
	return true;
}


bool ActionPlanner::SetCost(int act_idx, int cost )
{
	if ( act_idx == -1 ) return false;
	acts[ act_idx ].cost = cost;
	return true;
}








ActionPlannerWrapper::ActionPlannerWrapper(ActionPlanner& planner) : ap(planner) {
	
}

void ActionPlannerWrapper::Init() {
	ASSERT(ap.GetActionCount());
	ASSERT(ap.GetAtomCount());
	acts.SetCount(ap.GetActionCount());
	atoms.SetCount(ap.GetAtomCount());
	
	
}

String ActionPlannerWrapper::GetWorldstateDescription( const WorldState& ws )
{
	String str;
	//str += ws.GetName() + ": ";
	for(int i = 0; i < atoms.GetCount(); i++) {
		if (ws.using_act.GetCount() <= i) break;
		if (ws.using_act[i]) {
			bool set = ws.values[i];
			if (set)
				str += ToUpper(atoms[i]) + ",";
			else
				str += atoms[i] + ",";
		}
	}
	return str;
}


String ActionPlannerWrapper::GetDescription()
{
	String str;
	for(int j = 0; j < ap.acts.GetCount(); j++) {
		Action& act = ap.acts[j];
		str += acts[j] + ":\n";
		
		WorldState& pre  = act.precond;
		WorldState& post = act.postcond;
		
		int count = Upp::min(atoms.GetCount(), pre.values.GetCount());
		for(int i = 0; i < count; i++) {
			bool v = pre.values[i];
			str += " " + atoms[i] + "==" + IntStr(v) + "\n";
		}
		
		count = Upp::min(atoms.GetCount(), post.values.GetCount());
		for(int i = 0; i < count; i++) {
			bool v = post.values[i];
			str += " " + atoms[i] + "==" + IntStr(v) + "\n";
		}
	}
	return str;
}


int ActionPlannerWrapper::GetAtomIndex(String atom_name) {
	int i = VectorFind(atoms, atom_name);
	if (i != -1)
		return i;
	atoms.Add(atom_name);
	return atoms.GetCount()-1;
}


int ActionPlannerWrapper::GetActionIndex(String action_name) {
	int i = VectorFind(acts, action_name);
	if (i != -1)
		return i;
	acts.Add(action_name);
	return acts.GetCount()-1;
}


bool ActionPlannerWrapper::SetPreCondition(String action_name, String atom_name, bool value)
{
	int act_idx = GetActionIndex( action_name );
	int atm_idx = GetAtomIndex( atom_name );
	if ( act_idx == -1 || atm_idx == -1 ) return false;
	ap.acts[act_idx].precond.Set(atm_idx, value);
	return true;
}


bool ActionPlannerWrapper::SetPostCondition(String action_name, String atom_name, bool value)
{
	int act_idx = GetActionIndex( action_name );
	int atm_idx = GetAtomIndex( atom_name );
	if ( act_idx == -1 || atm_idx == -1 ) return false;
	ap.acts[act_idx].postcond.Set(atm_idx, value);
	return true;
}


bool ActionPlannerWrapper::SetCost(String action_name, int cost )
{
	int act_idx = GetActionIndex( action_name );
	if ( act_idx == -1 ) return false;
	ap.acts[ act_idx ].cost = cost;
	return true;
}










ActionPlanner* ActionNode::ap;
ActionNode* ActionNode::goal;
ArrayMap<int64, Node<ActionNode> > ActionNode::tmp_sub;

ActionNode::ActionNode() {
	cost = 0;
	act_id = -1;
}

double ActionNode::GetDistance(const ActionNode& to) {
	double dist = 0;
	
	Vector<bool>& values = ws->values;
	const Vector<bool>& to_values = to.ws->values;
	
	Vector<bool>& using_act = ws->using_act;
	const Vector<bool>& to_using_act = to.ws->using_act;
	
	int count = Upp::min(values.GetCount(), to_values.GetCount());
	
	for(int j = count; j < to_using_act.GetCount(); j++)
		if (to_using_act[j] && to_values[j])
			dist += 1;
	
	for(int j = 0; j < count; j++) {
		int b = to_using_act[j];
		if (b &&  values[j] != to_values[j]) {
			dist += 1; continue;}
	}
	return dist;
}

double ActionNode::GetEstimate() {
	return GetDistance(*goal);
}

NAMESPACE_OULU_END

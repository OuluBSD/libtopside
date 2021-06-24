#include "EcsCore.h"
//#include <EcsLib/EcsLib.h>

NAMESPACE_ECS_BEGIN
namespace Eon {

WorldState::WorldState() {
	
	Clear();
}

void WorldState::Clear() {
	values.Clear();
	using_act.Clear();
	cur_comp = Null;
	iface = Null;
	add_ext = Null;
	type = INVALID;
}

bool WorldState::Set(int index, bool value) {
	if (index < 0) return false;
	if (using_act.GetCount() <= index) {
		using_act.SetCount(index+1, false);
		values.SetCount(index+1);
	}
	using_act[index] = true;
	values[index] = value ? "true" : "false";
	return true;
}

bool WorldState::Set(int index, String value) {
	if (index < 0) return false;
	if (using_act.GetCount() <= index) {
		using_act.SetCount(index+1, false);
		values.SetCount(index+1);
	}
	using_act[index] = true;
	values[index] = value;
	return true;
}

WorldState& WorldState::operator=(const WorldState& src) {
	values		<<= src.values;
	using_act	<<= src.using_act;
	cur_comp	= src.cur_comp;
	add_ext		= src.add_ext;
	iface		= src.iface;
	type		= src.type;
	ap			= src.ap;
	return *this;
}


int64 WorldState::GetHashValue() {
	CombineHash c;
	c.Put((int)type);
	c.Put(cur_comp.GetHashValue());
	c.Put(add_ext.GetHashValue());
	c.Put(iface.GetHashValue());
	for(int i = 0; i < values.GetCount(); i++) {
		c.Put(using_act[i]);
		c.Put(values[i].GetHashValue());
	}
	return c;
}

bool WorldState::Append(const WorldState& ws, LinkedList<Statement>& ret_list) {
	for (const Eon::Statement& ret : ret_list) {
		String atom = ret.id.ToString();
		if (!ret.value.IsEmpty()) {
			const Eon::Value& v = *ret.value;
			if (v.type == Eon::Value::VAL_STRING)
				Set(atom, v.str);
			else if (v.type == Eon::Value::VAL_BOOLEAN)
				Set(atom, v.b ? "true" : "false");
			else if (v.type == Eon::Value::VAL_ID)
				Set(atom, v.id.ToString());
			else
				return false;
		}
		else if (ws.IsFalse(atom))
			Set(atom, "false");
		else
			Set(atom, ws.Get(atom));
	}
	return true;
}

bool WorldState::Set(const String& key, bool value) {
	int idx = ap->GetAddAtom(key);
	return Set(idx, value);
}

bool WorldState::IsTrue(const String& key) const {
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount())
		return values[idx] == "true";
	return false;
}

bool WorldState::IsFalse(const String& key) const {
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount())
		return values[idx] == "false";
	return true;
}

String WorldState::Get(const String& key) const {
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount())
		return values[idx];
	return String();
}

String WorldState::ToString() const {
	String s;
	for(int i = 0; i < values.GetCount(); i++) {
		if (!using_act[i])
			continue;
		String v = values[i];
		if (v.IsEmpty()) v = "false";
		String k = ap->GetAtom(i).ToString();
		if (!s.IsEmpty())
			s << ",";
		s << k << "=" << v;
	}
	return s;
}

bool WorldState::Contains(const WorldState& ws) const {
	if (0) {
		LOG("WorldState::Contains: this " << ToString());
		LOG("                      vs   " << ws.ToString());
	}
	int a_count = using_act.GetCount();
	int b_count = ws.using_act.GetCount();
	int c_count = min(a_count, b_count);
	for(int i = c_count; i < b_count; i++)
		if (ws.using_act[i])
			return false;
	for(int i = 0; i < c_count; i++) {
		if (ws.using_act[i]) {
			if (!using_act[i])
				return false;
			if (ws.values[i] != values[i])
				return false;
		}
	}
	return true;
}









Action::Action() : cost(1.0) {
	
}






ActionPlanner::ActionPlanner() {
	
}

void ActionPlanner::Clear() {
	atoms.Clear();
	acts.Clear();
	search_cache.Clear();
}

int ActionPlanner::GetAddAtom(String id) {
	int i = atoms.Find(id);
	if (i < 0) {
		i = atoms.GetCount();
		Atom& a = atoms.GetAdd(id);
		a.id = Split(id, ".");
		return i;
	}
	else return i;
}

int ActionPlanner::GetAddAtom(const Id& id) {
	String key = id.ToString();
	int i = atoms.Find(key);
	if (i < 0) {
		i = atoms.GetCount();
		Atom& a = atoms.GetAdd(key);
		for(const String& s : id.parts)
			a.id.Add(s);
		return i;
	}
	else return i;
}

void ActionPlanner::GetPossibleStateTransition(Node<Eon::ActionNode>& n, Array<WorldState*>& dest, Vector<double>& action_costs)
{
	auto& src = n.GetWorldState();
	EcsTypeCls comp_type = src.GetComponent();
	
	/*bool dbg =
		src.IsTrue("customer.id.ABCD")
		&& src.IsTrue("center.audio.src")
		&& src.IsTrue("center.audio.sink")
		&& src.IsAddComponent()
		&& src.GetComponent() == AsTypeCls<AudioOutputComponent>()
		;
	if (dbg) {
		LOG("");
	}*/
	
	acts.SetCount(0);
	Ecs::Factory::GetComponentActions(src, acts);
	
	/*if (!(!dbg || acts.GetCount())) {
		LOG(n.GetWorldState().ToString());
		Ecs::Factory::GetComponentActions(src, acts);
	}
	ASSERT(!dbg || acts.GetCount());*/
	
	for (int i = 0; i < acts.GetCount(); ++i) {
		// Check precondition
		Action& act = acts[i];
		
		if (act.precond.GetComponent() != comp_type) {
			DUMP(act.precond.GetComponent());
			DUMP(comp_type);
		}
		ASSERT(act.precond.GetComponent() == comp_type);
		if      (act.IsAddComponent()) {
			if (act.postcond.GetComponent() == comp_type) {DUMP(comp_type);}
			ASSERT(act.postcond.GetComponent() != comp_type);
		}
		else if (act.IsAddExtension()) {ASSERT(act.postcond.GetComponent() == comp_type);}
		else Panic("Invalid type");
		
		const WorldState& pre = act.precond;
		
		// Check that precondition is not using something outside of src values
		int count = UPP::min(pre.using_act.GetCount(), src.using_act.GetCount());
		bool fail = false;
		for(int j = count; j < pre.using_act.GetCount(); j++)
			if (pre.using_act[j] && pre.values[j])
				{fail = true; break;}
		if (fail)
			continue;
		
		bool met = true;
		for(int j = 0; j < count; j++) {
			int a = pre.using_act[j];
			if (a && src.values[j] != pre.values[j]) {
				met = false;
				break;
			}
		}
		
		if (met) {
			action_costs.Add(act.cost);
			WorldState& tmp = search_cache.Add(act.postcond);
			dest.Add(&tmp);
			//if (dbg) {LOG("\tDEBUG: " << tmp.ToString());}
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
	ap.wrapper = this;
	OnResize();
}

void ActionPlannerWrapper::OnResize() {
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
		
		int count = UPP::min(atoms.GetCount(), pre.values.GetCount());
		for(int i = 0; i < count; i++) {
			bool v = pre.values[i];
			str += " " + atoms[i] + "==" + IntStr(v) + "\n";
		}
		
		count = UPP::min(atoms.GetCount(), post.values.GetCount());
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











ActionNode::ActionNode() {
	cost = 0;
	ap = 0;
	goal = 0;
	ws = 0;
}

double ActionNode::GetDistance(const ActionNode& to) {
	double dist = 0;
	
	Vector<String>& values = ws->values;
	const Vector<String>& to_values = to.ws->values;
	
	Vector<bool>& using_act = ws->using_act;
	const Vector<bool>& to_using_act = to.ws->using_act;
	
	int count = UPP::min(values.GetCount(), to_values.GetCount());
	
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
	ASSERT(goal);
	return GetDistance(*goal);
}

bool ActionNode::Contains(const ActionNode& n) const {
	if (ws == n.ws)
		return true;
	const WorldState& a = *ws;
	const WorldState& b = *n.ws;
	return a.Contains(b);
}


}
NAMESPACE_ECS_END

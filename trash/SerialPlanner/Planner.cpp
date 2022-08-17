#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN
using namespace Parallel;

namespace Script {





ActionPlanner::ActionPlanner() {
	Clear();
}

void ActionPlanner::Clear() {
	atoms.Clear();
	acts.Clear();
	search_cache.Clear();
	ClearForward();
}

void ActionPlanner::ClearForward() {
	side_sinks.Clear();
	side_srcs.Clear();
	side_sink_max_est = INT_MAX;
	side_src_max_est = INT_MAX;
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

void ActionPlanner::GetPossibleStateTransition(Node<Script::ActionNode>& n, Array<WorldState*>& dest, Vector<double>& action_costs)
{
	auto& src = n.GetWorldState();
	AtomTypeCls atom_type = src.GetAtom();
	
	/*bool dbg =
		src.IsTrue("center.audio.side.src")
		&& src.IsTrue("center.audio.src.dbg_generator")
		&& src.IsAddAtom()
		&& src.GetAtom() == AsTypeCls<AudioOutputAtom>()
		;
	if (dbg) {
		LOG("");
	}*/
	
	if (atom_type.role == AtomRole::CUSTOMER &&
		n.GetLinkedCount())
		return;
		
	acts.SetCount(0);
	Serial::GetAtomActions(src, acts);
	
	/*if (!(!dbg || acts.GetCount())) {
		LOG(n.GetWorldState().ToString());
		Serial::Factory::GetAtomActions(src, acts);
	}
	ASSERT(!dbg || acts.GetCount());*/
	
	for (int i = 0; i < acts.GetCount(); ++i) {
		// Check precondition
		Action& act = acts[i];
		
		if (act.precond.GetAtom() != atom_type) {
			DUMP(act.precond.GetAtom());
			DUMP(atom_type);
		}
		ASSERT(act.precond.GetAtom() == atom_type);
		if      (act.IsAddAtom()) {
			//if (act.postcond.GetAtom() == atom_type) {DUMP(atom_type);}
			//ASSERT(act.postcond.GetAtom() != atom_type);
		}
		//else if (act.IsAddExtension()) {ASSERT(act.postcond.GetAtom() == atom_type);}
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


void ActionPlanner::AddSideSink(int ch_i, const Searcher& as, ANode& n, ANode** prev) {
	double est = n.GetEstimate();
	if (est < side_sink_max_est) {
		side_sink_max_est = est;
		side_sinks.Clear();
	}
	if (est <= side_sink_max_est) {
		/*for (State& s : side_sinks) {
			if (s.last == &n &&
				s.second_last == prev &&
				//s.as == as &&
				s.ch_i == ch_i)
				return;
		}*/
		State& s = side_sinks.Add();
		s.last = &n;
		s.as = as;
		s.ch_i = ch_i;
		
		int i = 0;
		if (prev) {
			for(; i < State::MAX_PREV-1; i++)
				if (prev[i])
					s.previous[i] = prev[i];
				else
					break;
		}
		for(; i < State::MAX_PREV; i++)
			s.previous[i] = 0;
	}
}

void ActionPlanner::AddSideSource(int ch_i, const Searcher& as, ANode& n, ANode** prev) {
	double est = n.GetEstimate();
	//if (est > 1) return; // this is wrong, because some "false" constraints give longer estimate
	if (est < side_src_max_est) {
		side_src_max_est = est;
		side_srcs.Clear();
	}
	if (est <= side_src_max_est) {
		/*for (State& s : side_sinks) {
			if (s.last == &n &&
				s.second_last == prev &&
				//s.as == as &&
				s.ch_i == ch_i)
				return;
		}*/
		/*hash_t h = n.GetWorldState().GetHashValue();
		for (State& s : side_srcs)
			if (s.last->GetWorldState().GetHashValue() == h)
				return;*/
		State& s = side_srcs.Add();
		s.last = &n;
		s.as = as;
		s.ch_i = ch_i;
		
		int i = 0;
		if (prev) {
			for(; i < State::MAX_PREV-1; i++)
				if (prev[i])
					s.previous[i] = prev[i];
				else
					break;
		}
		for(; i < State::MAX_PREV; i++)
			s.previous[i] = 0;
	}
}

String ActionPlanner::State::ToString() const {
	String s;
	s << "ch_i(" << ch_i << ")";
	s << ", last(" << HexStr(last) << ")";
	for(int i = 0; i < MAX_PREV; i++) {
		if (!previous[i])
			break;
		s << ", prev" << i << "(" << HexStr(previous[i]) << ")";
	}
	return s;
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

bool ActionNode::Conflicts(const ActionNode& n) const {
	const WorldState& a = *ws;
	const WorldState& b = *n.ws;
	return a.Conflicts(b);
}




}



void GetAtomActions(const Script::WorldState& src, Array<Script::Action>& acts) {
	auto& m = Parallel::Factory::AtomDataMap();
	
	AtomTypeCls atom = src.GetAtom();
	int i = m.Find(atom);
	if (i < 0) {
		LOG("GetAtomActions: error: atom not found: " << atom.ToString());
		return;
	}
	
	Parallel::Factory::AtomData& d = m[i];
	Parallel::Factory::RefreshLinks(d);
	
	One<Script::Action> a;
	a.Create();
	a->Pre() = src;
	
	
	/*if (src.IsAddAtom()) {
		for (const Factory::IfaceData& e : d.ext.GetValues()) {
			a.Post() = src;
			a.Post().SetAs_AddAtom(atom, e.cls);
			a.Post().SetSideCls(e.side_vd);
			if (e.action_fn(e.cls, a)) {
				MemSwap(acts.Add(), a);
				a.Pre() = src;
			}
		}
	}*/
	
	for (const Parallel::Factory::Link& link : d.sink_links) {
		AtomTypeCls dst = link.dst_atom;
		ASSERT(dst.IsValid());
		const Parallel::Factory::AtomData& dst_cd = m.Get(dst);
		
		/*if (dst.sub == SubAtomCls::CONVERTER && dst.side.vd == VD(OGL,AUDIO)) {
			LOG(dst.ToString());
		}*/
		/*FAIL if (atom.role != AtomRole::CUSTOMER &&
			//dst.sub != SubAtomCls::CONVERTER &&
			dst.iface.side.val != atom.iface.side.val &&
			dst.iface.sink.val != ValCls::RECEIPT)
			continue;*/
			
		/*FAIL if ((atom.role == AtomRole::SIDE_SOURCE || atom.role == AtomRole::SIDE_SINK) &&
			dst.iface.side.val != atom.iface.side.val &&
			dst.iface.sink.val != ValCls::RECEIPT)
			continue;*/
		
		//ASSERT(src.GetAtom() != link.dst_atom);
		
		auto& post = a->Post();
		post = src;
		post.SetAs_AddAtom(dst);
		post.SetSinkCls(link.common_vd);
		ASSERT(post.GetSinkCls().IsValid());
		if (dst_cd.action_fn(dst_cd.cls, *a)) {
			acts.Add(a.Detach());
			a.Create();
			a->Pre() = src;
		}
	}
	
}


NAMESPACE_SERIAL_END


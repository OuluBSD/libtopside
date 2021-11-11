#include "Internal.h"


NAMESPACE_SERIAL_BEGIN
namespace Script {

WorldState::WorldState() {
	
	Clear();
}

void WorldState::Clear() {
	values.Clear();
	using_act.Clear();
	cur_atom = Null;
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
	if (use_debugging_order)
		dbg_order.FindAdd(index);
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
	if (use_debugging_order)
		dbg_order.FindAdd(index);
	return true;
}

WorldState& WorldState::operator=(const WorldState& src) {
	values		<<= src.values;
	using_act	<<= src.using_act;
	dbg_order	<<= src.dbg_order;
	cur_atom	= src.cur_atom;
	type		= src.type;
	ap			= src.ap;
	return *this;
}


hash_t WorldState::GetHashValue() const {
	CombineHash c;
	c.Put((int)type);
	c.Put(cur_atom.GetHashValue());
	c.Put(side_vd.GetHashValue());
	bool begun = false;
	for(int i = values.GetCount()-1; i >= 0; i--) {
		bool b = using_act[i];
		if (begun) {
			c.Put(b);
			if (b) {
				c.Put(values[i].GetHashValue());
			}
		}
		else {
			if (b) {
				c.Put(b);
				begun = true;
				c.Put(values[i].GetHashValue());
			}
		}
	}
	return c;
}

const Script::Statement* WorldState::FindStatement(const String& find_key, LinkedList<Statement>& stmts, bool dbg_print) {
	for (const Statement& stmt : stmts) {
		String key = stmt.id.ToString();
		if (key == find_key) {
			if (dbg_print) RTLOG("WorldState::FindStatement: cmp '" << key << "' == '" << find_key << "': true");
			return &stmt;
		}
		else {
			if (dbg_print) RTLOG("WorldState::FindStatement: cmp '" << key << "' == '" << find_key << "': false");
		}
	}
	return 0;
}

const Script::Statement* WorldState::FindStatement(const WorldState* ws, LinkedList<Statement>& stmts, bool dbg_print) const {
	if (!ws) {
		static thread_local Index<String> cur_ws_keys;
		cur_ws_keys.Clear();
		int i = 0;
		for(const String& s : values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				cur_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(cur_ws_keys);
		
		for (const String& cur : cur_ws_keys) {
			if (dbg_print) RTLOG("WorldState::FindStatement: searching key '" << cur << "' in statements");
			const Script::Statement* s = FindStatement(cur, stmts, dbg_print);
			if (s) {
				if (dbg_print) RTLOG("WorldState::FindStatement: found statement: " << s->ToString());
				return s;
			}
		}
	}
	else {
		static thread_local Index<String> prev_ws_keys;
		prev_ws_keys.Clear();
		int i = 0;
		for(const String& s : ws->values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				prev_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(prev_ws_keys);
		
		static thread_local Index<String> cur_ws_keys;
		cur_ws_keys.Clear();
		i = 0;
		for(const String& s : values) {
			if (s.GetCount()) {
				String key = ap->GetAtom(i).ToString();
				cur_ws_keys.Add(key);
			}
			i++;
		}
		if (dbg_print) DUMPC(cur_ws_keys);
		
		static thread_local Index<String> new_ws_keys;
		new_ws_keys.Clear();
		for (const String& cur : cur_ws_keys) {
			bool is_new = prev_ws_keys.Find(cur) < 0;
			if (is_new)
				new_ws_keys.Add(cur);
		}
		if (dbg_print) DUMPC(new_ws_keys);
		
		for (const String& new_ : new_ws_keys) {
			if (dbg_print) RTLOG("WorldState::FindStatement: searching key '" << new_ << "' in statements");
			const Script::Statement* s = FindStatement(new_, stmts, dbg_print);
			if (s) {
				if (dbg_print) RTLOG("WorldState::FindStatement: found statement: " << s->ToString());
				return s;
			}
		}
	}
	return 0;
}

bool WorldState::Append(const WorldState& ws, LinkedList<Statement>& ret_list) {
	for (const Script::Statement& ret : ret_list) {
		String atom = ret.id.ToString();
		if (!ret.value.IsEmpty()) {
			const Script::Value& v = *ret.value;
			if (v.type == Script::Value::VAL_STRING)
				Set(atom, v.str);
			else if (v.type == Script::Value::VAL_BOOLEAN)
				Set(atom, v.b ? "true" : "false");
			else if (v.type == Script::Value::VAL_ID)
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
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Set(idx, value);
}

bool WorldState::Set(const String& key, String value) {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Set(idx, value);
}

bool WorldState::IsTrue(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount())
		return values[idx] == "true";
	return false;
}

bool WorldState::IsFalse(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	if (idx < values.GetCount()) {
		const auto& s = values[idx];
		return s.IsEmpty() || s == "false";
	}
	return true;
}

bool WorldState::IsFalse(int idx) const {
	ASSERT(ap);
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount()) {
		const auto& s = values[idx];
		return s.IsEmpty() || s == "false";
	}
	return true;
}

bool WorldState::IsUndefined(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return IsUndefined(idx);
}

bool WorldState::IsUndefined(int idx) const {
	ASSERT(ap);
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount()) {
		return !using_act[idx];
	}
	return true;
}

String WorldState::Get(const String& key) const {
	ASSERT(ap);
	int idx = ap->GetAddAtom(key);
	return Get(idx);
}

String WorldState::Get(int idx) const {
	ASSERT(idx >= 0);
	if (idx >= 0 && idx < values.GetCount())
		return values[idx];
	return String();
}

String WorldState::ToString() const {
	ASSERT(ap);
	String s;
	if (use_debugging_order && dbg_order.GetCount()) {
		for(int i = 0; i < dbg_order.GetCount(); i++) {
			int idx = dbg_order[i];
			if (!using_act[idx])
				continue;
			String v = values[idx];
			if (v.IsEmpty()) v = "false";
			String k = ap->GetAtom(idx).ToString();
			if (!s.IsEmpty())
				s << ",";
			s << k << "=" << v;
		}
	}
	else {
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
	}
	return s;
}

String WorldState::GetFullString() const {
	String s;
	if (IsAddAtom())
		s << "add-atom " << cur_atom.ToString() << " ";
	if (side_vd.IsValid())
		s << "side-vd=" << side_vd.ToString() << " ";
	s << ToString();
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
		if (ws.using_act[i] && !ws.IsFalse(i))
			return false;
	for(int i = 0; i < c_count; i++) {
		if (ws.using_act[i]) {
			if (Compare(i, ws) != 0)
				return false;
		}
	}
	return true;
}

bool WorldState::Conflicts(const WorldState& ws) const {
	int a_count = using_act.GetCount();
	int b_count = ws.using_act.GetCount();
	int c_count = min(a_count, b_count);
	for(int i = 0; i < c_count; i++) {
		if (using_act[i] && ws.using_act[i]) {
			if (Compare(i, ws) != 0)
				return true;
		}
	}
	return false;
}


int WorldState::Compare(int idx, const WorldState& ws) const {
	const String& a = values[idx];
	const String& b = ws.values[idx];
	// Compare false
	if (a.IsEmpty() || a == "false") {
		if (b.IsEmpty() || b == "false")
			return 0;
		return 1;
	}
	else {
		if (b.IsEmpty() || b == "false")
			return -1;
		return a == b ? 0 : -2;
	}
}








Action::Action() : cost(1.0) {
	
}






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



void GetAtomActions(const Script::WorldState& src, Vector<Script::Action>& acts) {
	auto& m = Factory::AtomDataMap();
	
	AtomTypeCls atom = src.GetAtom();
	Factory::AtomData& d = m.Get(atom);
	Factory::RefreshLinks(d);
	
	Script::Action a;
	a.Pre() = src;
	
	
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
	
	for (const Factory::Link& link : d.sink_links) {
		AtomTypeCls dst = link.dst_atom;
		ASSERT(dst.IsValid());
		const Factory::AtomData& dst_cd = m.Get(dst);
		
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
		
		auto& post = a.Post();
		post = src;
		post.SetAs_AddAtom(dst);
		post.SetSinkCls(link.common_vd);
		ASSERT(post.GetSinkCls().IsValid());
		if (dst_cd.action_fn(dst_cd.cls, a)) {
			MemSwap(acts.Add(), a);
			a.Pre() = src;
		}
	}
	
}


NAMESPACE_SERIAL_END

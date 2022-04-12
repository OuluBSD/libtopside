#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN


ScriptLoopLoader::ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def) :
	Base(parent, id, def)
{
	planner.SetLoopLoader(this);
}

void ScriptLoopLoader::LoopStatus() {
	Panic("internal error");
}

void ScriptLoopLoader::ForwardLoops() {
	Panic("internal error");
}

void ScriptLoopLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	Panic("internal error");
}

void ScriptLoopLoader::CheckStatusDeep() {
	// pass
}

void ScriptLoopLoader::SetStatus(ScriptStatus status) {
	MACHVER_STATUS(LoopLoader_Status, this)
	Base::SetStatus(status);
};

String ScriptLoopLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Loop " << id;
	s.Cat('\n');
	
	int id = 0;
	for (ScriptLoopSegment& seg : segments) {
		s << seg.GetTreeString(id++, indent+1);
	}
	
	String extra;
	if (status == ScriptStatus::FAILED)
		extra = err_str;
	
	s << GetScriptStatusLine(indent+1, status, extra);
	
	return s;
}

void ScriptLoopLoader::RealizeConnections(const Script::ActionPlanner::State& last_state) {
	static const bool print = true;
	if (print) RTLOG("ScriptLoopLoader::RealizeConnections: begin");
	ASSERT(segments.GetCount());
	
	ScriptLoopSegment& top_seg = segments.Top();
	if (top_seg.ep.plan.IsEmpty()) {
		top_seg.ep.plan = top_seg.as.ReconstructPath(*last_state.last);
		ASSERT(!top_seg.ep.plan.IsEmpty());
	}
	
	int atom_i = 0;
	int added = 0;
	int dbg_i = -1;
	const Script::WorldState* prev_ws0 = 0;
	const Script::WorldState* prev_ws1 = 0;
	//for (ScriptLoopSegment& seg : segments) {
	{
		ScriptLoopSegment& seg = top_seg;
		dbg_i++;
		ASSERT(!seg.ep.plan.IsEmpty());
		
		bool skip_first = atom_i > 0;
		int dbg_j = -1;
		for (Script::ActionNode* an : seg.ep.plan) {
			dbg_j++;
			
			Script::WorldState& ws = an->GetWorldState();
			ASSERT(ws.IsAddAtom());
			
			if (skip_first) {
				skip_first = false;
				continue;
			}
			else if (atom_i < atom_links.GetCount()) {
				if (1) {
					AtomSideLinks& atom = atom_links[atom_i];
					if (print) RTLOG("ScriptLoopLoader::RealizeConnections: atom #" << atom_i << " " << atom.type.ToString());
				}
			}
			else {
				AtomTypeCls type = ws.GetAtom();
				
				atom_links.SetCount(atom_i+1);
				
				const Script::Statement* stmt = ws.FindStatement(prev_ws0, def.stmts);
				if (!stmt) stmt = ws.FindStatement(prev_ws1, def.stmts);
				bool skip_all_src_conds = stmt && stmt->src_side_conds.IsEmpty();
				bool skip_all_sink_conds = stmt && stmt->sink_side_conds.IsEmpty();
				
				if (print) RTLOG("ScriptLoopLoader::RealizeConnections: atom #" << atom_i << ", " << (stmt ? "has stmt" : "NO stmt") << ", skip_all_src_conds: " << (int)skip_all_src_conds << ", skip_all_sink_conds: " << (int)skip_all_sink_conds);
				if (!stmt && prev_ws0) {
					DUMP(ws.ToString());
					DUMP(prev_ws0->ToString());
					if (prev_ws1) DUMP(prev_ws1->ToString());
					DUMPI(def.stmts);
				}
				ASSERT(stmt || type.IsRoleCustomer());
				
				AtomSideLinks& atom = atom_links[atom_i];
				atom.type = type;
				ASSERT(type.IsValid());
				
				atom.src_side_conns.SetCount(type.iface.src.count - 1);
				atom.sink_side_conns.SetCount(type.iface.sink.count - 1);
				
				#ifdef flagDEBUG
				static int dbg_counter = 0;
				if (dbg_counter == 3) {
					int i = 0; // line breakpoint placeholder
				}
				#endif
				
				int required_srcs = 0;
				int req_src_sides = type.iface.src.count - type.user_src_count - 1; // -1 bc of primary src
				for(int i = 0; i < atom.src_side_conns.GetCount(); i++) {
					SideLink& link = atom.src_side_conns[i];
					link.vd = type.iface.src[1 + i];
					link.is_user_conditional = i >= req_src_sides;
					link.is_user_stmt =		stmt &&
											i < stmt->src_side_conds.GetCount() &&
											!stmt->src_side_conds[i].id.IsEmpty();
					link.is_required = !skip_all_src_conds && (!link.is_user_conditional || link.is_user_stmt);
					ASSERT((link.is_required && skip_all_src_conds) == false);
					if (link.is_required)
						required_srcs++;
				}
				
				int required_sinks = 0;
				int req_sink_sides = type.iface.sink.count - type.user_sink_count - 1; // -1 bc of primary sink
				for(int i = 0; i < atom.sink_side_conns.GetCount(); i++) {
					SideLink& link = atom.sink_side_conns[i];
					link.vd = type.iface.sink[1 + i];
					link.is_user_conditional = i >= req_sink_sides;
					link.is_user_stmt =		stmt &&
											i < stmt->sink_side_conds.GetCount() &&
											!stmt->sink_side_conds[i].id.IsEmpty();
					link.is_required = !skip_all_sink_conds && (!link.is_user_conditional || link.is_user_stmt);
					ASSERT((link.is_required && skip_all_sink_conds) == false);
					if (link.is_required)
						required_sinks++;
				}
				
				added++;
				
				#ifdef flagDEBUG
				if (print) RTLOG("ScriptLoopLoader::RealizeConnections: chkpt #" << dbg_counter << " realized atom #" << atom_i << ", required_srcs: " << required_srcs << ", required_sinks: " << required_sinks << ", placeholder: " << atom.type.ToString());
				dbg_counter++;
				#endif
			}
			
			atom_i++;
			prev_ws1 = prev_ws0;
			prev_ws0 = &ws;
		}
	}
	
	if (print) RTLOG("ScriptLoopLoader::RealizeConnections: end count=" << atom_i << ", added=" << added);
	ASSERT(atom_i > 0);
	
	MACHVER_STATUS(LoopLoader_RealizeAtoms, this);
}

void ScriptLoopLoader::SetSideSourceConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& sink) {
	ASSERT(type.IsValid());
	ASSERT(ch_i > 0);
	ASSERT(type.iface.src.count > 1 && ch_i < type.iface.src.count);
	int side_ch_i = ch_i - 1;
	
	#if 0
	if (src_side_conns.IsEmpty()) {
		int side_conn_count = type.iface.src.count - 1 - type.user_src_count;
		src_side_conns.SetCount(side_conn_count, 0);
	}
	if (side_ch_i >= src_side_conns.GetCount()) {
		if (side_ch_i < type.iface.src.count - 1)
			src_side_conns.SetCount(side_ch_i + 1);
		else {
			ASSERT_(0, "invalid side channel");
			return;
		}
	}
	#endif
	
	AtomSideLinks& atom = atom_links.Top();
	
	RTLOG("ScriptLoopLoader::SetSideSourceConnected: loop " << HexStr(this) << " src ch #" << ch_i << " set " << HexStr(&sink));
	ASSERT(side_ch_i >= 0 && side_ch_i < atom.src_side_conns.GetCount());
	SideLink& l = atom.src_side_conns[side_ch_i];
	ASSERT(!l.link);
	l.link = &sink;
	
	MACHVER_STATUS(LoopLoader_AtomLinked, this);
}

void ScriptLoopLoader::SetSideSinkConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& src) {
	ASSERT(type.IsValid());
	ASSERT(ch_i > 0);
	ASSERT(type.iface.sink.count > 1 && ch_i < type.iface.sink.count);
	int side_ch_i = ch_i - 1;
	
	#if 0
	if (sink_side_conns.IsEmpty()) {
		int side_conn_count = type.iface.sink.count - 1 - type.user_sink_count;
		sink_side_conns.SetCount(side_conn_count, 0);
	}
	if (side_ch_i >= sink_side_conns.GetCount()) {
		if (side_ch_i < type.iface.sink.count - 1)
			sink_side_conns.SetCount(side_ch_i + 1);
		else {
			ASSERT_(0, "invalid side channel");
			return;
		}
	}
	#endif
	
	AtomSideLinks& atom = atom_links.Top();
	
	RTLOG("ScriptLoopLoader::SetSideSourceConnected: loop " << HexStr(this) << " sink ch #" << ch_i << " set " << HexStr(&src));
	ASSERT(side_ch_i >= 0 && side_ch_i < atom.sink_side_conns.GetCount());
	SideLink& l = atom.sink_side_conns[side_ch_i];
	ASSERT(!l.link);
	l.link = &src;
	
	MACHVER_STATUS(LoopLoader_AtomLinked, this);
}

bool ScriptLoopLoader::IsAllSidesConnected() const {
	ASSERT(atom_links.GetCount());
	for (const auto& atom : atom_links) {
		for (const SideLink& l : atom.src_side_conns)
			if (l.is_required && !l.link)
				return false;
		for (const SideLink& l : atom.sink_side_conns)
			if (l.is_required && !l.link)
				return false;
	}
	return true;
}

bool ScriptLoopLoader::IsTopSidesConnected() const {
	ASSERT(atom_links.GetCount());
	const auto& atom = atom_links.Top();
	int dbg_i = 0;
	for (const SideLink& l : atom.src_side_conns) {
		if (l.is_required && !l.link) {
			//ASSERT(!l.is_user_stmt);
			return false;
		}
		dbg_i++;
	}
	dbg_i = 0;
	for (const SideLink& l : atom.sink_side_conns) {
		if (l.is_required && !l.link) {
			//ASSERT(!l.is_user_stmt);
			return false;
		}
		dbg_i++;
	}
	return true;
}

String ScriptLoopSegment::GetTreeString(int id, int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Segment " << id;
	s.Cat('\n');
	if (!ep.plan.IsEmpty()) {
		bool started = false;
		for (Script::ActionNode* n : ep.plan) {
			started = started || n == start_node;
			if (!started) continue;
			String state_str = n->GetWorldState().ToString();
			if (state_str.GetCount()) {
				s.Cat('\t', indent+1);
				s << state_str << "\n";
			}
		}
	}
	else {
		s.Cat('\t', indent+1);
		s << "empty\n";
	}
	return s;
}

void ScriptLoopLoader::SetupSegment(ScriptLoopSegment& s) {
	
	
	// Do the action plan searching
	s.as.SetLimit(10000);
	
}

void ScriptLoopLoader::Forward() {
	if (IsReady())
		return;
	
	ASSERT(!IsFailed());
	ScriptStatus prev_status = status;
	
	
	if (status == ScriptStatus::IN_BEGINNING) {
		if (!InitSegments())
			return;
		
		SetStatus(WAITING_CHILDREN);
	}
	
	if (status == ScriptStatus::WAITING_CHILDREN) {
		SetStatus(SEARCH_SEGMENT);
	}
	
	if (status == ScriptStatus::SEARCH_SEGMENT) {
		MACHVER_ENTER(ScriptLoopLoaderForwardBeginning)
		
		if (def.stmts.IsEmpty() && def.req.IsEmpty()) {
			String id = def.id.ToString();
			SetError("Loop " + IntStr(GetId()) + " '" + id + "' has no statements");
			MACHVER_LEAVE(ScriptLoopLoaderForwardBeginning)
			return;
		}
		
		SearchNewSegment();
		
		MACHVER_LEAVE(ScriptLoopLoaderForwardBeginning)
	}
	else if (status == ScriptStatus::PRUNE_SEGMENT_GOALS) {
		PruneSegmentGoals();
	}
	else  if (status == ScriptStatus::WAITING_OTHER_LOOPS) {
		int si = planner.GetSideSinks().GetCount();
		int sr = planner.GetSideSources().GetCount();
		ASSERT_(si || sr, "planner side links have been cleared for retry");
		RTLOG("ScriptLoopLoader::Forward: WAITING_OTHER_LOOPS -> WAITING_PARENT_SIDE_LINKS: " << def.id.ToString() << " sinks=" << si << " srcs=" << sr);
		SetStatus(WAITING_PARENT_SIDE_LINKS);
	}
	else  if (status == ScriptStatus::WAITING_PARENT_SIDE_LINKS) {
		// pass
		return;
	}
	else {
		
		TODO
		
	}
	
	ASSERT(prev_status != status);
}

bool ScriptLoopLoader::InitSegments() {
	ASSERT(segments.IsEmpty());
	
	DevCls dev = DevCls::Get(def.id.parts.First());
	if (!dev.IsValid())
		dev = DevCls::CENTER;
	
	AtomTypeCls consumer;
	
	if (dev == DevCls::CENTER)
		consumer = AsAtomTypeCls<CenterCustomer>();
	else if (dev == DevCls::OGL) {
		#ifdef flagSCREEN
		consumer = AsAtomTypeCls<OglCustomer>();
		#else
		SetError("OGL device not supported without this program compiled with GUI compilation flag");
		return false;
		#endif
	}
	else {
		SetError("Unsupported device class: " + dev.GetName());
		return false;
	}
	
	// Prepare action planner and world states
	int CONNECTED = planner.GetAddAtom("loop.connected");
	AtomCls customer;
	customer.sink = ValDevCls(dev, ValCls::RECEIPT);
	customer.side = ValDevCls(dev, ValCls::ORDER);
	customer.src  = ValDevCls(dev, ValCls::ORDER);
	
	//start = scope.current_state;
	start.SetActionPlanner(planner);
	
	
	start.SetAs_AddAtom(consumer);
	//int HAS_DEV = planner.GetAddAtom("has." + dev.GetActionName());
	//start.Set(HAS_DEV, true);
	
	goal.SetActionPlanner(planner);
	goal.SetAs_AddAtom(consumer);
	goal.Set(CONNECTED, true);
	
	for (Script::Id& req : def.req) {
		Script::State* s = GetLoader().FindState(req);
		if (!s) {
			SetError("Could not find required state '" + req.ToString() + "'");
			return false;
		}
		for (Script::Statement& stmt : s->stmts)
			if (!SetWorldState(goal, stmt))
				return false;
	}
	
	for (Script::Statement& stmt : def.stmts)
		if (stmt.IsRouting() && !SetWorldState(goal, stmt))
			return false;
	
	goal_node.SetWorldState(goal);
	goal_node.SetGoal(goal_node);
	
	start_node.SetActionPlanner(planner);
	start_node.SetGoal(goal_node);
	start_node.SetWorldState(start);
	
	
	ScriptLoopSegment& seg = segments.Add();
	seg.start_node = &start_node;
	
	return true;
}

void ScriptLoopLoader::SearchNewSegment() {
	MACHVER_ENTER(SearchNewSegment)
	MACHVER_STATUS(LoopLoader_SearchNewSegment, this);
	
	ScriptLoopSegment& seg = segments.Top();
	ASSERT(seg.start_node);
	SetupSegment(seg);
	
	LOG("goal: " << goal.ToString());
	LOG("start-node: " << seg.start_node->GetWorldState().GetAtom().ToString());
	seg.start_node->ResetLinked();
	if (segments.GetCount() == 1)
		seg.ep.plan = seg.as.Search(*seg.start_node);
	else
		seg.ep.plan = seg.as.ContinueSearch(*seg.start_node);
	
	if (!seg.ep.plan.IsEmpty()) {
		// Set last node
		seg.stop_node = seg.ep.plan.Top();
		
		if (1)
			DumpLoop();
		
		SetStatus(READY);
	}
	else {
		SetStatus(PRUNE_SEGMENT_GOALS);
	}
	
	MACHVER_LEAVE(SearchNewSegment)
}

void ScriptLoopLoader::DumpLoop() {
	int pos = 0;
	ScriptLoopSegment& seg = segments.Top();
	for (Script::ActionNode* n : seg.ep.plan) {
		const Script::WorldState& ws = n->GetWorldState();
		AtomTypeCls atom = ws.GetAtom();
		const auto& d = Parallel::Factory::AtomDataMap().Get(atom);
		if (ws.IsAddAtom()) {
			LOG(pos++ << ": add atom: " << d.name);
		}
		LOG("\t" << ws.ToString());
	}
}

void ScriptLoopLoader::PruneSegmentGoals() {
	ScriptLoopSegment& seg = segments.Top();
	ASSERT(seg.ep.plan.IsEmpty());
	
	Vector<Script::ActionPlanner::State>& sinks = planner.GetSideSinks();
	Vector<Script::ActionPlanner::State>& sources = planner.GetSideSources();
	bool is_sink = planner.IsSideSink();
	
	DUMPC(sinks);
	DUMPC(sources);
	DUMP(is_sink);
	
	int removed_count = 0;
	
	for(int i = 0; i < sources.GetCount(); i++) {
		const Script::ActionPlanner::State& state = sources[i];
		const Script::WorldState& ws = state.last->GetWorldState();
		const Script::WorldState* prev_ws = state.previous[0] ? &state.previous[0]->GetWorldState() : 0;
		const Script::Statement* stmt = ws.FindStatement(prev_ws, def.stmts);
		int ch_i = state.ch_i;
		
		if (!stmt) continue;
		
		AtomTypeCls type = ws.GetAtom();
		ASSERT(type.IsValid());
		int user_defined_count = stmt->src_side_conds.GetCount();
		int required_count = type.iface.src.count - type.user_src_count;
		bool remove = false;
		if (user_defined_count == 0 && required_count == 1) {
			// no given user conditionals here means that skip all source interfaces
			remove = true;
		}
		else if (user_defined_count == 0 && ch_i > 0 && ch_i < required_count) {
			// required side-connections does not require user conditionals
		}
		else if (ch_i > 0) {
			ASSERT(user_defined_count > 0);
			ASSERT(ch_i >= required_count);
			int side_ch = ch_i - 1;
			if (type.user_src_count != user_defined_count) {
				SetError("user conditional count differs to atom requirements: user gives " + IntStr(user_defined_count) + ", atom requires " + IntStr(type.user_src_count));
				return;
			}
			if (side_ch < user_defined_count) {
				const Script::Statement& src_stmt = stmt->src_side_conds[side_ch];
				if (src_stmt.value.IsEmpty())
					remove = true; // user did not give conditional statement, which is required
			}
		}
		
		if (remove) {
			removed_count++;
			sources.Remove(i--);
		}
	}
	
	for(int i = 0; i < sinks.GetCount(); i++) {
		const Script::ActionPlanner::State& state = sinks[i];
		const Script::WorldState& ws = state.last->GetWorldState();
		const Script::WorldState* prev_ws = state.previous[0] ? &state.previous[0]->GetWorldState() : 0;
		const Script::Statement* stmt = ws.FindStatement(prev_ws, def.stmts);
		int ch_i = state.ch_i;
		
		if (!stmt) continue;
		
		AtomTypeCls type = ws.GetAtom();
		ASSERT(type.IsValid());
		int user_defined_count = stmt->sink_side_conds.GetCount();
		int required_count = type.iface.sink.count - type.user_sink_count;
		bool remove = false;
		if (user_defined_count == 0 && required_count == 1) {
			// no given user conditionals here means that skip all sink interfaces
			remove = true;
		}
		else if (user_defined_count == 0 && ch_i > 0 && ch_i < required_count) {
			// required side-connections does not require user conditionals
		}
		else if (ch_i > 0) {
			ASSERT(user_defined_count > 0);
			ASSERT(ch_i >= required_count);
			int side_ch = ch_i - 1;
			if (type.user_sink_count != user_defined_count) {
				SetError("user conditional count differs to atom requirements: user gives " + IntStr(user_defined_count) + ", atom requires " + IntStr(type.user_sink_count));
				return;
			}
			if (side_ch < user_defined_count) {
				const Script::Statement& sink_stmt = stmt->sink_side_conds[side_ch];
				if (sink_stmt.value.IsEmpty())
					remove = true; // user did not give conditional statement, which is required
			}
		}
		
		if (remove) {
			removed_count++;
			sinks.Remove(i--);
		}
	}
	
	RTLOG("ScriptLoopLoader::PruneSegmentGoals: pruned " << removed_count << " from potential goals");
	
	if (sinks.IsEmpty() && sources.IsEmpty()) {
		SetError("no sinks nor sources left after pruning");
		SetStatus(FAILED);
	}
	else {
		SetStatus(ScriptStatus::WAITING_PARENT_SIDE_LINKS);
	}
}

bool ScriptLoopLoader::SetWorldState(Script::WorldState& ws, const Script::Statement& stmt) {
	if (!stmt.value || stmt.value->type == Script::Value::VAL_CUSTOMER)
		return true;;
	
	int atom = planner.GetAddAtom(stmt.id);
	
	String old_value = goal.Get(atom);
	String new_value;
	
	if (stmt.value->type == Script::Value::VAL_BOOLEAN)
		new_value = stmt.value->b ? "true" : "false";
	else if (stmt.value->type == Script::Value::VAL_ID)
		new_value = stmt.value->id.ToString();
	else if (stmt.value->type == Script::Value::VAL_STRING)
		new_value = stmt.value->str;
	else if (stmt.value->type == Script::Value::VAL_INT)
		new_value = IntStr(stmt.value->i);
	else if (stmt.value->type == Script::Value::VAL_DOUBLE)
		new_value = DblStr(stmt.value->f);
	else {
		SetError("internal error");
		return false;
	}
	
	if (old_value != new_value && !old_value.IsEmpty()) {
		SetError("Earlier value mismatch newer value for id '" + stmt.id.ToString() + "' (" +
			old_value + " != " + new_value + ")");
		return false;
	}
	
	ws.Set(atom, new_value);
	return true;
}


bool ScriptLoopLoader::Load() {
	RTLOG("ScriptLoopLoader::Load: " << def.id.ToString());
	ScriptLoader& loader = GetLoader();
	
	// Target entity for atoms
	Script::Id deep_id = GetDeepId();
	//DUMP(deep_id);
	LoopRef l = loader.ResolveLoop(deep_id);
	if (!l) {
		SetError("Could not resolve entity with deep id: " + deep_id.ToString());
		return false;
	}
	
	
	added_atoms.Clear();
	
	int seg_i = segments.GetCount()-1;
	ScriptLoopSegment& seg = segments.Top();
	int plan_i = 0;
	const Script::WorldState* prev_ws0 = 0;
	const Script::WorldState* prev_ws1 = 0;
	LinkBaseRef first_lb;
	AtomBaseRef first_ab;
	bool is_first = true;
	for (Script::ActionNode* n : seg.ep.plan) {
		RTLOG("Loading plan node " << plan_i);
		Script::WorldState& ws = n->GetWorldState();
		if (ws.IsAddAtom()) {
			bool is_last = plan_i == seg.ep.plan.GetCount()-1;
			AtomTypeCls atom = ws.GetAtom();
			LinkTypeCls link = Parallel::Factory::GetAtomLinkType(atom);
			LinkBaseRef lb;
			AtomBaseRef ab;
			
			if (is_last) {
				ab = first_ab;
				lb = first_lb;
			}
			else {
				ab = l->GetSpace()->AddTypeCls(atom);
				lb = l->AddTypeCls(link);
			}
			
			if (is_first) {
				first_ab = ab;
				first_lb = lb;
				is_first = false;
			}
			
			if (!ab) {
				String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
				SetError("Could not create atom '" + atom_name + "' at '" + def.id.ToString() + "'");
				DUMP(atom);
				ASSERT(0);
				return false;
			}
			
			if (!lb) {
				String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
				SetError("Could not create link for atom '" + atom_name + "' at '" + def.id.ToString() + "'");
				DUMP(atom);
				ASSERT(0);
				return false;
			}
			
			ab->SetId(id);
			lb->SetId(id);
			
			ab->link = &*lb;
			lb->atom = &*ab;
			
			auto& c = added_atoms.Add();
			c.r					= ab;
			c.l					= lb;
			c.plan_i			= plan_i;
			c.seg_i				= seg_i;
			c.iface				= n->GetInterface();
			ASSERT(/*!c.iface.type.IsValid() ||*/ c.iface.IsComplete());
			
			AtomTypeCls type = ws.GetAtom();
			ASSERT(!c.iface.type.IsValid() || type == c.iface.type);
			ASSERT((type.iface.src.count == 1 && type.iface.sink.count == 1) || c.iface.type.IsValid());
			
			// Add arguments to ws
			const Script::Statement* stmt = ws.FindStatement(prev_ws0, def.stmts);
			if (!stmt) stmt = ws.FindStatement(prev_ws1, def.stmts);
			if (stmt) {
				RTLOG("ScriptLoopLoader::Load: stmt found: " << stmt->ToString());
				for (const Script::Statement& arg : stmt->args) {
					//LOG("\t" << arg.id.ToString());
					String k = arg.id.ToString();
					String v = arg.value ? arg.value->GetValue() : String();
					ws.Set("." + k, v);
					LOG("ScriptLoopLoader::Load: set argument: " << k << " = " << v);
				}
			}
			else {
				RTLOG("ScriptLoopLoader::Load: stmt not found:       ws: " << ws.ToString());
				if (prev_ws0)
					RTLOG("                                        prev_ws0: " << prev_ws0->ToString());
				if (prev_ws0)
					RTLOG("                                        prev_ws1: " << prev_ws1->ToString());
				DUMPI(def.stmts);
				if (!ws.IsEmpty())
					stmt = ws.FindStatement(prev_ws0, def.stmts, true);
			}
			
			if (!ab->InitializeAtom(ws) || !ab->Initialize(ws)) {
				const auto& a = Parallel::Factory::AtomDataMap().Get(type);
				SetError("Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			
			if (!lb->Initialize(ws)) {
				const auto& a = Parallel::Factory::AtomDataMap().Get(type);
				SetError("Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			
			ab->SetRunning();
		}
		else {
			Panic("Invalid world state type");
		}
		
		prev_ws1 = prev_ws0;
		prev_ws0 = &ws;
		++plan_i;
	}
	
	
	for(int i = 0; i < added_atoms.GetCount()-1; i++) {
		AddedAtom& src_info = added_atoms[i];
		AtomBaseRef src = src_info.r;
		
		AddedAtom& sink_info = added_atoms[i+1];
		AtomBaseRef sink = sink_info.r;
		ScriptLoopSegment& sink_seg = segments[sink_info.seg_i];
		Script::ActionNode& sink_an = *sink_seg.ep.plan[sink_info.plan_i];
		const Script::WorldState& sink_ws = sink_an.GetWorldState();
		
		ValDevCls common_vd = sink_ws.GetCommonSink();
		ASSERT(common_vd.IsValid());
		
		if (!l->MakeLink(src, sink, common_vd)) {
			AtomTypeCls atom = sink_ws.GetAtom();
			String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
			String src_sink_name = Parallel::Factory::IfaceLinkDataMap().Get(common_vd).name;
			SetError("Could not link atom '" + atom_name + "' source '" + src_sink_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		
		src->SetInterface(src_info.iface);
		
		atoms.Add(src);
	}
	
	
	UpdateLoopLimits();
	
	
	AddedAtom& first = added_atoms[0];
	AddedAtom& last  = added_atoms.Top();
	ScriptLoopSegment& first_seg = segments[first.seg_i];
	ScriptLoopSegment& last_seg  = segments[last.seg_i];
	
	
	// Process sub-loops
	for (Script::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Script::Value::VAL_CUSTOMER)
			continue;
		//LoadLoopDefinition(stmt.value->customer);
		SetError("Sub-loops not supported yet");
		return false;
	}
	
	
	// Add changes to parent state
	/*const Script::WorldState& ret_ws = last_seg.ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		SetError("Invalid type in return value");
		return false;
	}*/
	
	
	return true;
}

void ScriptLoopLoader::UpdateLoopLimits() {
	
	// as in AtomBase::LinkSideSink
	
	bool changes = false;
	int c = added_atoms.GetCount()-1;
	int total_max = 1000000;
	int total_min = 0;
	
	for(int i = 0; i < c; i++) {
		AddedAtom& info = added_atoms[i];
		InterfaceSourceRef src = info.r->GetSource();
		int src_c = src->GetSourceCount();
		for(int j = 0; j < src_c; j++) {
			int src_min_packets = src->GetSourceValue(j).GetMinPackets();
			int src_max_packets = src->GetSourceValue(j).GetMaxPackets();
			total_min = max(total_min, src_min_packets);
			total_max = min(total_max, src_max_packets);
		}
		
		InterfaceSinkRef sink = info.r->GetSink();
		int sink_c = sink->GetSinkCount();
		for(int j = 0; j < sink_c; j++) {
			int sink_min_packets = sink->GetValue(j).GetMinPackets();
			int sink_max_packets = sink->GetValue(j).GetMaxPackets();
			total_min = max(total_min, sink_min_packets);
			total_max = min(total_max, sink_max_packets);
		}
	}
	
	if (total_min > total_max) {
		total_max = total_min;
	}
	
	LOG("ScriptLoopLoader::UpdateLoopLimits: set loop limits: min=" << total_min << ", max=" << total_max);
	
	for(int i = 0; i < c; i++) {
		AddedAtom& info = added_atoms[i];
		
		InterfaceSourceRef src = info.r->GetSource();
		InterfaceSinkRef sink = info.r->GetSink();
		
		int sink_c = sink->GetSinkCount();
		for(int k = 0; k < sink_c; k++) {
			Value& v = sink->GetValue(k);
			v.SetMinQueueSize(total_min);
			v.SetMaxQueueSize(total_max);
		}
		
		int src_c = src->GetSourceCount();
		for(int k = 0; k < src_c; k++) {
			Value& v = src->GetSourceValue(k);
			v.SetMinQueueSize(total_min);
			v.SetMaxQueueSize(total_max);
		}
			
		/*
		//DUMP(min_packets);
		//DUMP(sink_min_packets);
		//DUMP(src_min_packets);
		*/
	}
}


bool ScriptLoopLoader::PostInitialize() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.r->PostInitialize())
			return false;
		if (!a.l->PostInitialize())
			return false;
	}
	return true;
}

bool ScriptLoopLoader::Start() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.r->Start())
			return false;
		if (!a.l->Start())
			return false;
	}
	return true;
}

#if 0
SideStatus ScriptLoopLoader::AcceptSink(ScriptLoopLoader& sink_loader, Script::ActionPlanner::State*& accepted_src, Script::ActionPlanner::State*& accepted_sink) {
	
	TODO
	
	
	if (&sink_loader == this)
		return SIDE_NOT_ACCEPTED;
	
	ASSERT(status == SOURCE_IS_WAITING);
	ASSERT(sink_loader.status == SINK_IS_WAITING);
	Vector<Script::ActionPlanner::State>& sources = planner.GetSideSources();
	Vector<Script::ActionPlanner::State>& sinks = sink_loader.planner.GetSideSinks();
	ASSERT(!sources.IsEmpty() && !sinks.IsEmpty());
	
	SideStatus ret = SIDE_NOT_ACCEPTED;
	int accepted_count = 0;
	hash_t accepted_hash = 0;
	
	// Don't clear, just overwrite:
	//accepted_src = 0;
	//accepted_sink = 0;
	
	//int src_side_id = src_side_conns.GetCount();
	//int sink_side_id = sink_loader.sink_side_conns.GetCount();
	
	/*if (def.id.ToString() == "source" && sink_loader.def.id.ToString() == "sink1") {
		LOG("");
	}*/
	
	for (Script::ActionPlanner::State& src_state : sources) {
		Script::APlanNode* src = src_state.last;
		Script::WorldState& src_ws = src->GetWorldState();
		Script::WorldState* src_prev_ws = src_state.second_last ? &src_state.second_last->GetWorldState() : 0;
		int src_side_id = src_state.ch_i - 1;
		ASSERT(src_ws.IsAddAtom());
		AtomTypeCls src_atom = src_ws.GetAtom();
		auto& src_d = Serial::Factory::AtomDataMap().Get(src_atom);
		
		
		const Script::Statement* src_stmt = src_ws.FindStatement(src_prev_ws, def.stmts);
		ASSERT(src_stmt);
		if (src_stmt && src_stmt->src_side_conds.GetCount()) {
			if (src_side_id >= src_stmt->src_side_conds.GetCount()) {
				//SetError("side connection id-number is higher than the count of given side-connection conditionals");
				RTLOG("ScriptLoopLoader::AcceptSink: side connection id-number is higher than the count of given side-connection conditionals");
			}
			else {
				RTLOG("ScriptLoopLoader::AcceptSink: testing source conditionals in sink");
				const Script::Statement& cond_stmt = src_stmt->src_side_conds[src_side_id];
				if (cond_stmt.value.IsEmpty()) {
					RTLOG("ScriptLoopLoader::AcceptSink: skipping src state with empty user conditional");
					continue;
				}
				else if (!sink_loader.PassSideConditionals(cond_stmt)) {
					RTLOG("ScriptLoopLoader::AcceptSink: source side conditionals did not pass");
					continue;
				}
			}
		}
		
		
		for (Script::ActionPlanner::State& sink_state : sinks) {
			Script::APlanNode* sink = sink_state.last;
			Script::WorldState& sink_ws = sink->GetWorldState();
			Script::WorldState* sink_prev_ws = sink_state.second_last ? &sink_state.second_last->GetWorldState() : 0;
			int sink_side_id = sink_state.ch_i - 1;
			ASSERT(sink_ws.IsAddAtom());
			AtomTypeCls sink_atom = sink_ws.GetAtom();
			auto& sink_d = Serial::Factory::AtomDataMap().Get(sink_atom);
			
			RTLOG("ScriptLoopLoader::AcceptSink: src loop '" << def.id.ToString() << "' (" << HexStr(&src_state) << ") ch #" << src_side_id << " against sink '" << sink_loader.def.id.ToString() << "'(" << HexStr(&sink_state) << ") ch #" << sink_side_id << ": " << src_side_id << " --> " << sink_side_id);
			
			
			const Script::Statement* sink_stmt = sink_ws.FindStatement(sink_prev_ws, sink_loader.def.stmts);
			ASSERT(sink_stmt);
			if (!sink_stmt) {
				RTLOG("ScriptLoopLoader::AcceptSink: did not find sink statement");
			}
			else if (sink_stmt->sink_side_conds.IsEmpty()) {
				RTLOG("ScriptLoopLoader::AcceptSink: no user side-sink conditionals given");
			}
			else {
				if (sink_side_id >= sink_stmt->sink_side_conds.GetCount()) {
					//SetError("side connection id-number is higher than the count of given side-connection conditionals");
					RTLOG("ScriptLoopLoader::AcceptSink: side connection id-number is higher than the count of given side-connection conditionals");
				}
				else {
					RTLOG("ScriptLoopLoader::AcceptSink: testing sink conditionals in source");
					const Script::Statement& cond_stmt = sink_stmt->sink_side_conds[sink_side_id];
					if (cond_stmt.value.IsEmpty()) {
						RTLOG("ScriptLoopLoader::AcceptSink: skipping sink state with empty user conditional");
						continue;
					}
					else if (!PassSideConditionals(cond_stmt)) {
						RTLOG("ScriptLoopLoader::AcceptSink: sink side conditionals did not pass");
						continue;
					}
				}
			}
			
			
			SideStatus a, b;
			if ((a = src_d.side_fn(src_atom, src_ws, sink_atom, sink_ws)) != SIDE_NOT_ACCEPTED) {
				if ((b = sink_d.side_fn(src_atom, src_ws, sink_atom, sink_ws)) != SIDE_NOT_ACCEPTED) {
					
					CombineHash ch;
					
					
					ch.Put(def.id.ToString().GetHashValue());
					ch.Put(sink_loader.def.id.ToString().GetHashValue());
					ch.Put(src_side_id);
					ch.Put(sink_side_id);
					hash_t hash = ch;
					if (accepted_hash != 0 && accepted_hash == hash) {
						RTLOG("ScriptLoopLoader::AcceptSink: warning: HOTFIX skipping duplicate(?) link.... oh why this happens? whyyyyyyyyyy");
						continue;
					}
					
					RTLOG("ScriptLoopLoader::AcceptSink: pass");
					accepted_hash = hash;
					accepted_src = &src_state;
					accepted_sink = &sink_state;
					accepted_count++;
					
					if (a == SIDE_ACCEPTED_MULTI || b == SIDE_ACCEPTED_MULTI)
						ret = SIDE_ACCEPTED_MULTI;
					else
						ret = SIDE_ACCEPTED;
				}
				else {
					RTLOG("ScriptLoopLoader::AcceptSink: sink side function did not pass");
				}
			}
			else {
				RTLOG("ScriptLoopLoader::AcceptSink: source side function did not pass");
			}
		}
	}
	
	if (accepted_count == 0) {
		// not error here, but in caller: SetError("No sources accepts any sinks");
		ret = SIDE_NOT_ACCEPTED;
	}
	else if (accepted_count > 1) {
		RTLOG("ScriptLoopLoader::AcceptSink: error: too many accepting source/sink combinations");
		SetError("Too many accepting source/sink combinations");
		ret = SIDE_NOT_ACCEPTED;
	}
	
	return ret;
}
#endif

void ScriptLoopLoader::AddSideConnectionSegment(Script::ActionPlanner::State& state) {
	ScriptLoopSegment& prev = segments.Top();
	prev.stop_node = state.last;
	prev.ep.plan = prev.as.ReconstructPath(*state.last);
	ASSERT(prev.ep.plan.GetCount());
	ScriptLoopSegment& seg = segments.Add();
	seg.start_node = state.last;
	seg.as = state.as;
}

bool ScriptLoopLoader::PassSideConditionals(const Script::Statement& src_side_stmt) {
	if (src_side_stmt.value.IsEmpty()) {
		SetError("statement '" + src_side_stmt.id.ToString() + "' has no value");
		return false;
	}
	
	static const bool print = false;
	
	// 'loop' keyword compares loops name
	if (src_side_stmt.id.parts.GetCount() == 1 && src_side_stmt.id.parts.First() == "loop") {
		if (src_side_stmt.value) {
			bool b;
			if (src_side_stmt.value->IsId()) {
				b = src_side_stmt.value->id == this->def.id;
			}
			else if (src_side_stmt.value->IsString()) {
				b = src_side_stmt.value->str == this->def.id.ToString();
			}
			else {
				if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: invalid loop id value in stmt: " << src_side_stmt.id.ToString());
				return false;
			}
			if (print &&  b) RTLOG("ScriptLoopLoader::PassSideConditionals: conditional loop id '" << src_side_stmt.id.ToString() << "': matching");
			if (print && !b) RTLOG("ScriptLoopLoader::PassSideConditionals: conditional loop id '" << src_side_stmt.id.ToString() << "': no match");
			return b;
		}
		if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: empty loop id value in stmt: " << src_side_stmt.id.ToString());
		return false;
	}

	for (const Script::Statement& stmt : def.stmts) {
		if (stmt.value.IsEmpty()) {
			if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: skip loop empty value stmt: " << stmt.id.ToString());
			continue;
		}
		if (stmt.value->IsBoolean()) {
			if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: skip loop boolean value stmt: " << stmt.id.ToString());
			continue;
		}
		
		if (stmt.id == src_side_stmt.id) {
			bool b = *stmt.value == *src_side_stmt.value;
			if (b) {
				if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: conditional '" << stmt.id.ToString() << "': matching '" << stmt.value->ToString() << "'");
			}
			else {
				if (print) RTLOG("ScriptLoopLoader::PassSideConditionals: conditional '" << stmt.id.ToString() << "': no match: '" << stmt.value->ToString() << "' vs '" << src_side_stmt.value->ToString() << "'");
			}
			return b;
		}
		else {
			if (print) LOG("ScriptLoopLoader::PassSideConditionals: no id match: " << stmt.id.ToString() << " != " << src_side_stmt.id.ToString());
		}
	}
	return false;
}




NAMESPACE_SERIAL_END

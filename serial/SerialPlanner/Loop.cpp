#include "Internal.h"


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

void ScriptLoopLoader::SetRetryDeep() {
	if (status == ScriptStatus::READY)
		return;
	status = ScriptStatus::RETRY;
}

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
	ASSERT(!IsReady() && !IsFailed());
	ScriptStatus prev_status = status;
	
	if (status == ScriptStatus::IN_BEGINNING) {
		if (def.stmts.IsEmpty() && def.req.IsEmpty()) {
			String id = def.id.ToString();
			SetError("Loop " + IntStr(GetId()) + " '" + id + "' has no statements");
			return;
		}
		
		InitSegments();
		ForwardTopSegment();
	}
	else if (status == ScriptStatus::RETRY) {
		ASSERT(segments.GetCount() >= 1);
		planner.ClearForward();
		
		ForwardTopSegment();
	}
	else {
		
		TODO
		
	}
	
	ASSERT(prev_status != status);
}

void ScriptLoopLoader::InitSegments() {
	DevCls dev = DevCls::Get(def.id.parts.First());
	if (!dev.IsValid())
		dev = DevCls::CENTER;
	
	AtomTypeCls consumer;
	if (dev == DevCls::CENTER)
		consumer = AsAtomTypeCls<CenterCustomer>();
	else if (dev == DevCls::ACCEL)
		consumer = AsAtomTypeCls<AccelCustomer>();
	else {
		TODO
		return;
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
			return;
		}
		for (Script::Statement& stmt : s->stmts)
			if (!SetWorldState(goal, stmt))
				return;
	}
	
	for (Script::Statement& stmt : def.stmts)
		if (!SetWorldState(goal, stmt))
			return;
	
	goal_node.SetWorldState(goal);
	goal_node.SetGoal(goal_node);
	
	start_node.SetActionPlanner(planner);
	start_node.SetGoal(goal_node);
	start_node.SetWorldState(start);
	
	
	ScriptLoopSegment& seg = segments.Add();
	seg.start_node = &start_node;
}

void ScriptLoopLoader::ForwardTopSegment() {
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
	
	if (seg.ep.plan.IsEmpty()) {
		if (accepted_side_node) {
			SetError("Script implementation searching failed after side-connection");
			return;
		}
		
		// Check side-channel connections
		const auto& inputs = planner.GetSideSinks();
		const auto& outputs = planner.GetSideSources();
		bool is_input = planner.IsSideSink();
		if (is_input && inputs.GetCount()) {
			LOG("Loop " << id << " side-inputs:");
			for(int i = 0; i < inputs.GetCount(); i++) {
				auto& state = inputs[i];
				const Script::WorldState& ws = state.last->GetWorldState();
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = INPUT_IS_WAITING;
			return;
		}
		else if (!is_input && outputs.GetCount()) {
			LOG("Loop " << id << " side-outputs:");
			for(int i = 0; i < outputs.GetCount(); i++) {
				auto& state = outputs[i];
				const Script::WorldState& ws = state.last->GetWorldState();
				//LOG(i << ": " << state.last->GetEstimate() << ": " << ws.GetFullString());
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = OUTPUT_IS_WAITING;
			return;
		}
		else {
			SetError("Script implementation searching failed");
			return;
		}
	}
	
	// Set last node
	seg.stop_node = seg.ep.plan.Top();
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		ScriptLoopSegment& seg = segments.Top();
		for (Script::ActionNode* n : seg.ep.plan) {
			const Script::WorldState& ws = n->GetWorldState();
			AtomTypeCls atom = ws.GetAtom();
			const auto& d = Serial::Factory::AtomDataMap().Get(atom);
			if (ws.IsAddAtom()) {
				LOG(pos++ << ": add atom: " << d.name);
			}
			LOG("\t" << ws.ToString());
		}
	}
	
	status = READY;
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
	ScriptLoader& loader = GetLoader();
	
	// Target entity for atoms
	LoopRef l = loader.ResolveLoop(def.id);
	if (!l) {
		SetError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	
	added_atoms.Clear();
	
	int seg_i = segments.GetCount()-1;
	ScriptLoopSegment& seg = segments.Top();
	int plan_i = 0;
	const Script::WorldState* prev_ws = 0;
	for (Script::ActionNode* n : seg.ep.plan) {
		RTLOG("Loading plan node " << plan_i);
		Script::WorldState& ws = n->GetWorldState();
		if (ws.IsAddAtom()) {
			bool is_last = plan_i == seg.ep.plan.GetCount()-1;
			AtomTypeCls atom = ws.GetAtom();
			AtomBaseRef ab =
				is_last ?
					l->FindTypeCls(atom) :
					l->GetAddTypeCls(atom);
			if (!ab) {
				String atom_name = Serial::Factory::AtomDataMap().Get(atom).name;
				SetError("Could not create atom '" + atom_name + "' at '" + def.id.ToString() + "'");
				DUMP(atom);
				ASSERT(0);
				return false;
			}
			auto& c = added_atoms.Add();
			c.r = ab;
			c.plan_i = plan_i;
			c.seg_i = seg_i;
			c.side_sink = n->GetSideSinkId();
			c.side_src = n->GetSideSrcId();
			
			
			AtomTypeCls type = ws.GetAtom();
			
			
			// Add arguments to ws
			const Script::Statement* stmt = ws.FindStatement(prev_ws, def.stmts);
			if (stmt) {
				for (const Script::Statement& arg : stmt->args) {
					//LOG("\t" << arg.id.ToString());
					String k = arg.id.ToString();
					String v = arg.value ? arg.value->GetValue() : String();
					ws.Set("." + k, v);
					LOG("ScriptLoopLoader::Load: set argument: " << k << " = " << v);
				}
			}
			
			
			if (!ab->InitializeAtom(ws) || !ab->AltInitialize(ws) || !ab->Initialize(ws)) {
				const auto& a = Serial::Factory::AtomDataMap().Get(type);
				SetError("Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			
		}
		else {
			Panic("Invalid world state type");
		}
				
		prev_ws = &ws;
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
		
		if (!l->Link(src, sink, common_vd)) {
			AtomTypeCls atom = sink_ws.GetAtom();
			String atom_name = Serial::Factory::AtomDataMap().Get(atom).name;
			String src_sink_name = Serial::Factory::IfaceLinkDataMap().Get(common_vd).name;
			SetError("Could not link atom '" + atom_name + "' source '" + src_sink_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		if (src_info.side_sink >= 0)
			src->AddSideSinkId(src_info.side_sink);
		if (src_info.side_src >= 0)
			src->AddSideSrcId(src_info.side_src);
		
		atoms.Add(src);
	}
	
	AddedAtom& first = added_atoms[0];
	AddedAtom& last  = added_atoms.Top();
	ScriptLoopSegment& first_seg = segments[first.seg_i];
	ScriptLoopSegment& last_seg  = segments[last.seg_i];
	AtomBaseRef atom = first.r;
	if (atom) {
		atom->AddPlan(first_seg.ep);
	}
	
	
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

bool ScriptLoopLoader::PostInitialize() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.r->PostInitialize())
			return false;
	}
	return true;
}

SideStatus ScriptLoopLoader::AcceptOutput(ScriptLoopLoader& out, Script::ActionPlanner::State*& accepted_in, Script::ActionPlanner::State*& accepted_out) {
	ASSERT(status == INPUT_IS_WAITING);
	ASSERT(out.status == OUTPUT_IS_WAITING);
	auto& inputs = planner.GetSideSinks();
	auto& outputs = out.planner.GetSideSources();
	ASSERT(!inputs.IsEmpty() && !outputs.IsEmpty());
	
	SideStatus ret = SIDE_NOT_ACCEPTED;
	int accepted_count = 0;
	accepted_in = 0;
	accepted_out = 0;
	
	for (auto& in_state : inputs) {
		Script::APlanNode* in = in_state.last;
		Script::WorldState& in_ws = in->GetWorldState();
		ASSERT(in_ws.IsAddAtom());
		AtomTypeCls in_atom = in_ws.GetAtom();
		auto& in_d = Serial::Factory::AtomDataMap().Get(in_atom);
		
		for (auto& out_state : outputs) {
			Script::APlanNode* out = out_state.last;
			Script::WorldState& out_ws = out->GetWorldState();
			ASSERT(out_ws.IsAddAtom());
			AtomTypeCls out_atom = out_ws.GetAtom();
			auto& out_d = Serial::Factory::AtomDataMap().Get(out_atom);
			
			SideStatus a, b;
			if ((a = in_d.side_fn(out_atom, out_ws, in_atom, in_ws)) != SIDE_NOT_ACCEPTED) {
				if ((b = out_d.side_fn(out_atom, out_ws, in_atom, in_ws)) != SIDE_NOT_ACCEPTED) {
					accepted_in = &in_state;
					accepted_out = &out_state;
					accepted_count++;
					if (a == SIDE_ACCEPTED_MULTI || b == SIDE_ACCEPTED_MULTI)
						ret = SIDE_ACCEPTED_MULTI;
					else
						ret = SIDE_ACCEPTED;
				}
			}
		}
	}
	
	if (accepted_count == 0) {
		SetError("No inputs accepts any outputs");
		return SIDE_NOT_ACCEPTED;
	}
	else if (accepted_count > 1) {
		SetError("Too many accepting input/output combinations");
		return SIDE_NOT_ACCEPTED;
	}
	
	
	return ret;
}

void ScriptLoopLoader::AddSideConnectionSegment(Script::ActionPlanner::State* state, ScriptLoopLoader* c, Script::ActionPlanner::State* side_state) {
	ScriptLoopSegment& prev = segments.Top();
	prev.stop_node = state->last;
	prev.ep.plan = prev.as.ReconstructPath(*state->last);
	ASSERT(prev.ep.plan.GetCount());
	ScriptLoopSegment& seg = segments.Add();
	seg.start_node = state->last;
	seg.side_conn = c;
	seg.as = state->as;
}


NAMESPACE_SERIAL_END

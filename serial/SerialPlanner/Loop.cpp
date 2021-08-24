#include "SerialPlanner.h"
#include <AtomLocal/Customer.h>

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
	
	// Prepare action planner and world states
	int CONNECTED = planner.GetAddAtom("loop.connected");
	AtomCls customer;
	customer.sink = ValDevCls(dev, ValCls::RECEIPT);
	customer.side = ValDevCls(dev, ValCls::ORDER);
	customer.src  = ValDevCls(dev, ValCls::ORDER);
	
	//start = scope.current_state;
	start.SetActionPlanner(planner);
	
	
	start.SetAs_AddAtom(AsAtomTypeCls<CustomerAtom>());
	//int HAS_DEV = planner.GetAddAtom("has." + dev.GetActionName());
	//start.Set(HAS_DEV, true);
	
	goal.SetActionPlanner(planner);
	goal.SetAs_AddAtom(AsAtomTypeCls<CustomerAtom>());
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
	LOG("goal: " << goal.ToString());
	
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
	
	LOG("start-node: " << seg.start_node->GetWorldState().ToString());
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
		const auto& inputs = planner.GetSideInputs();
		const auto& outputs = planner.GetSideOutputs();
		bool is_input = planner.IsSideInput();
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
	
	// Target entity for atomonents
	LoopRef l = loader.ResolveLoop(def.id);
	if (!l) {
		SetError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	//ScriptScope& scope = loader.scopes.Top();
	
	
	// Implement found loop
	struct AddedAtom {
		AtomBaseRef r;
		int plan_i;
		int seg_i;
		int side_in;
		int side_out;
	};
	Array<AddedAtom> added_atoms;
	
	int seg_i = segments.GetCount()-1;
	ScriptLoopSegment& seg = segments.Top();
	int plan_i = 0;
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
			ASSERT(ab);
			if (!ab) {
				String atom_name = Serial::Factory::AtomDataMap().Get(atom).name;
				SetError("Could not create atomonent '" + atom_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			auto& c = added_atoms.Add();
			c.r = ab;
			c.plan_i = plan_i;
			c.seg_i = seg_i;
			c.side_in = n->GetSideInId();
			c.side_out = n->GetSideOutId();
			
			
			AtomTypeCls type = ws.GetAtom();
			
			
			// Add arguments to ws
			for(int i = 0; i < ws.values.GetCount(); i++) {
				String key = planner.atoms.GetKey(i);
				for (const Script::Statement& stmt : def.stmts) {
					String stmt_key = stmt.id.ToString();
					if (stmt_key == key) {
						//LOG(i << " " << key << " " << stmt_key);
						for (const Script::Statement& arg : stmt.args) {
							//LOG("\t" << arg.id.ToString());
							if (arg.value) {
								String k = arg.id.ToString();
								String v = arg.value->GetValue();
								ws.Set("." + k, v);
								//LOG("ScriptLoader::LoadLoopDefinition: add argument: " << k << " = " << v);
							}
						}
					}
				}
			}
			
			
			if (!ab->Initialize(ws)) {
				const auto& a = Serial::Factory::AtomDataMap().Get(type);
				SetError("Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
				return false;
			}
		}
		else {
			Panic("Invalid world state type");
		}
		
		++plan_i;
	}
	
	
	for(int i = 0; i < added_atoms.GetCount()-1; i++) {
		AddedAtom& c0 = added_atoms[i];
		AddedAtom& c1 = added_atoms[i+1];
		AtomBaseRef src = c0.r;
		AtomBaseRef dst = c1.r;
		ScriptLoopSegment& seg = segments[c1.seg_i];
		Script::ActionNode& n = *seg.ep.plan[c1.plan_i];
		const Script::WorldState& ws = n.GetWorldState();
		ValDevCls iface = ws.GetInterface();
		if (!l->Link(src, dst, iface)) {
			AtomTypeCls atom = ws.GetAtom();
			String atom_name = Serial::Factory::AtomDataMap().Get(atom).name;
			String src_iface_name = Serial::Factory::SourceDataMap().Get(iface).name;
			SetError("Could not link atomonent '" + atom_name + "' source '" + src_iface_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		if (c0.side_in >= 0)
			src->SetSideIn(c0.side_in);
		if (c0.side_out >= 0)
			src->SetSideOut(c0.side_out);
		
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


SideStatus ScriptLoopLoader::AcceptOutput(ScriptLoopLoader& out, Script::ActionPlanner::State*& accepted_in, Script::ActionPlanner::State*& accepted_out) {
	ASSERT(status == INPUT_IS_WAITING);
	ASSERT(out.status == OUTPUT_IS_WAITING);
	auto& inputs = planner.GetSideInputs();
	auto& outputs = out.planner.GetSideOutputs();
	ASSERT(!inputs.IsEmpty() && !outputs.IsEmpty());
	
	SideStatus ret = SIDE_NOT_ACCEPTED;
	int accepted_count = 0;
	accepted_in = 0;
	accepted_out = 0;
	
	TODO
	#if 0
	for (auto& in_state : inputs) {
		Script::APlanNode* in = in_state.last;
		Script::WorldState& in_ws = in->GetWorldState();
		ASSERT(in_ws.IsAddExtension());
		AtomTypeCls in_atom = in_ws.GetAtom();
		AtomTypeCls in_type = in_ws.GetExtension();
		auto& in_d = Serial::Factory::AtomDataMap().Get(in_atom);
		auto& in_e = in_d.ext.Get(in_type);
		
		for (auto& out_state : outputs) {
			Script::APlanNode* out = out_state.last;
			Script::WorldState& out_ws = out->GetWorldState();
			ASSERT(out_ws.IsAddExtension());
			AtomTypeCls out_atom = out_ws.GetAtom();
			AtomTypeCls out_type = out_ws.GetExtension();
			auto& out_d = Serial::Factory::AtomDataMap().Get(out_atom);
			auto& out_e = out_d.ext.Get(out_type);
			
			SideStatus a, b;
			if ((a = in_e.side_fn(out_type, out_ws, in_type, in_ws)) != SIDE_NOT_ACCEPTED) {
				if ((b = out_e.side_fn(out_type, out_ws, in_type, in_ws)) != SIDE_NOT_ACCEPTED) {
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
	
	#endif
	
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

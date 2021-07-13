#include "EonCore.h"

NAMESPACE_EON_BEGIN



LoopLoader::LoopLoader(ChainLoader& parent, int id, LoopDefinition& def) :
	Base(parent, id, def)
{
	planner.SetLoopLoader(this);
}

void LoopLoader::LoopStatus() {
	Panic("internal error");
}

void LoopLoader::ForwardLoops() {
	Panic("internal error");
}

void LoopLoader::GetLoops(Vector<LoopLoader*>& v) {
	Panic("internal error");
}

void LoopLoader::SetRetryDeep() {
	if (status == Status::READY)
		return;
	status = Status::RETRY;
}

String LoopLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Loop " << id;
	s.Cat('\n');
	
	int id = 0;
	for (LoopSegment& seg : segments) {
		s << seg.GetTreeString(id++, indent+1);
	}
	
	String extra;
	if (status == Status::FAILED)
		extra = err_str;
	
	s << GetStatusLine(indent+1, status, extra);
	
	return s;
}

String LoopSegment::GetTreeString(int id, int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Segment " << id;
	s.Cat('\n');
	if (!ep.plan.IsEmpty()) {
		bool started = false;
		for (ActionNode* n : ep.plan) {
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

void LoopLoader::SetupSegment(LoopSegment& s) {
	
	
	// Do the action plan searching
	s.as.SetLimit(10000);
	
}

void LoopLoader::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	Status prev_status = status;
	
	if (status == Status::IN_BEGINNING) {
		if (def.stmts.IsEmpty() && def.req.IsEmpty()) {
			String id = def.id.ToString();
			SetError("Loop " + IntStr(GetId()) + " '" + id + "' has no statements");
			return;
		}
		
		InitSegments();
		ForwardTopSegment();
	}
	else if (status == Status::RETRY) {
		ASSERT(segments.GetCount() >= 1);
		planner.ClearForward();
		
		ForwardTopSegment();
	}
	else {
		
		TODO
		
	}
	
	ASSERT(prev_status != status);
}

void LoopLoader::InitSegments() {
	DevCls dev = DevCls::Get(def.id.parts.First());
	if (!dev.IsValid())
		dev = DevCls::CENTER;
	
	// Prepare action planner and world states
	int CONNECTED = planner.GetAddAtom("loop.connected");
	CompCls customer;
	customer.sink = ValDevCls(dev, ValCls::RECEIPT);
	customer.side = ValDevCls(dev, ValCls::ORDER);
	customer.src  = ValDevCls(dev, ValCls::ORDER);
	
	//start = scope.current_state;
	start.SetActionPlanner(planner);
	start.SetAs_AddComponent(AsTypeCompCls<ExtComponent>(SubCompCls::CUSTOMER, customer));
	//int HAS_DEV = planner.GetAddAtom("has." + dev.GetActionName());
	//start.Set(HAS_DEV, true);
	
	goal.SetActionPlanner(planner);
	goal.SetAs_AddComponent(AsTypeCompCls<ExtComponent>(SubCompCls::CUSTOMER, customer));
	goal.Set(CONNECTED, true);
	
	for (IdPath& req : def.req) {
		State* s = GetLoader().FindState(req);
		if (!s) {
			SetError("Could not find required state '" + req.ToString() + "'");
			return;
		}
		for (Statement& stmt : s->stmts)
			if (!SetWorldState(goal, stmt))
				return;
	}
	
	for (Statement& stmt : def.stmts)
		if (!SetWorldState(goal, stmt))
			return;
	LOG("goal: " << goal.ToString());
	
	goal_node.SetWorldState(goal);
	goal_node.SetGoal(goal_node);
	
	start_node.SetActionPlanner(planner);
	start_node.SetGoal(goal_node);
	start_node.SetWorldState(start);
	
	
	LoopSegment& seg = segments.Add();
	seg.start_node = &start_node;
}

void LoopLoader::ForwardTopSegment() {
	LoopSegment& seg = segments.Top();
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
			SetError("Plan implementation searching failed after side-connection");
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
				const WorldState& ws = state.last->GetWorldState();
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = INPUT_IS_WAITING;
			return;
		}
		else if (!is_input && outputs.GetCount()) {
			LOG("Loop " << id << " side-outputs:");
			for(int i = 0; i < outputs.GetCount(); i++) {
				auto& state = outputs[i];
				const WorldState& ws = state.last->GetWorldState();
				//LOG(i << ": " << state.last->GetEstimate() << ": " << ws.GetFullString());
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = OUTPUT_IS_WAITING;
			return;
		}
		else {
			SetError("Plan implementation searching failed");
			return;
		}
	}
	
	// Set last node
	seg.stop_node = seg.ep.plan.Top();
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		LoopSegment& seg = segments.Top();
		for (ActionNode* n : seg.ep.plan) {
			const WorldState& ws = n->GetWorldState();
			TypeCompCls comp = ws.GetComponent();
			const auto& d = Eon::Factory::CompDataMap().Get(comp);
			if (ws.IsAddComponent()) {
				LOG(pos++ << ": add comp: " << d.name);
			}
			if (ws.IsAddExtension()) {
				const auto& e = d.ext.Get(ws.GetExtension());
				LOG(pos++ << ": add ext: " << e.name << " (to " << d.name << ")");
			}
			LOG("\t" << ws.ToString());
		}
	}
	
	status = READY;
}

bool LoopLoader::SetWorldState(WorldState& ws, const Statement& stmt) {
	if (!stmt.value || stmt.value->type == Value::VAL_CUSTOMER)
		return true;;
	
	int atom = planner.GetAddAtom(stmt.id);
	
	String old_value = goal.Get(atom);
	String new_value;
	
	if (stmt.value->type == Value::VAL_BOOLEAN)
		new_value = stmt.value->b ? "true" : "false";
	else if (stmt.value->type == Value::VAL_ID)
		new_value = stmt.value->id.ToString();
	else if (stmt.value->type == Value::VAL_STRING)
		new_value = stmt.value->str;
	else if (stmt.value->type == Value::VAL_INT)
		new_value = IntStr(stmt.value->i);
	else if (stmt.value->type == Value::VAL_DOUBLE)
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


bool LoopLoader::Load() {
	Loader& loader = GetLoader();
	
	// Target entity for components
	EntityRef e = loader.ResolveEntity(def.id);
	if (!e) {
		SetError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	//EonScope& scope = loader.scopes.Top();
	
	
	// Implement found loop
	struct AddedComp {
		ComponentBaseRef r;
		int plan_i;
		int seg_i;
		int side_in;
		int side_out;
	};
	Array<AddedComp> added_comps;
	
	int seg_i = segments.GetCount()-1;
	LoopSegment& seg = segments.Top();
	int plan_i = 0;
	for (ActionNode* n : seg.ep.plan) {
		
		RTLOG("Loading plan node " << plan_i);
		WorldState& ws = n->GetWorldState();
		if (ws.IsAddComponent()) {
			bool is_last = plan_i == seg.ep.plan.GetCount()-1;
			TypeCompCls comp = ws.GetComponent();
			ComponentBaseRef cb =
				is_last ?
					e->FindTypeCls(comp) :
					e->GetAddTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = Eon::Factory::CompDataMap().Get(comp).name;
				SetError("Could not create component '" + comp_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			auto& c = added_comps.Add();
			c.r = cb;
			c.plan_i = plan_i;
			c.seg_i = seg_i;
			c.side_in  = -1;
			c.side_out = -1;
		}
		else if (ws.IsAddExtension()) {
			POPO(Pol::Eon::Loader::CorrespondingAddCompAndExt);
			auto& c = added_comps.Top();
			c.side_in = n->GetSideInId();
			c.side_out = n->GetSideOutId();
			
			
			TypeCompCls comp = ws.GetComponent();
			TypeExtCls ext = ws.GetExtension();
			ComponentBaseRef cb = e->GetTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = Eon::Factory::CompDataMap().Get(comp).name;
				SetError("Could not fwsind component '" + comp_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			{
				ComponentExtBaseRef existing_ext = cb->GetExtension();
				if (existing_ext) {
					const auto& c = Eon::Factory::CompDataMap().Get(comp);
					const auto& e = c.ext.Get(ext);
					SetError("Could not create extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "' because existing extension '" + existing_ext->GetDynamicName() + "'");
					return false;
				}
			}
			
			
			// Add arguments to ws
			for(int i = 0; i < ws.values.GetCount(); i++) {
				String key = planner.atoms.GetKey(i);
				for (const Statement& stmt : def.stmts) {
					String stmt_key = stmt.id.ToString();
					if (stmt_key == key) {
						//LOG(i << " " << key << " " << stmt_key);
						for (const Statement& arg : stmt.args) {
							//LOG("\t" << arg.id.ToString());
							if (arg.value) {
								String k = arg.id.ToString();
								String v = arg.value->GetValue();
								ws.Set("." + k, v);
								//LOG("Loader::LoadLoopDefinition: add argument: " << k << " = " << v);
							}
						}
					}
				}
			}
			
			
			ComponentExtBaseRef eb = cb->SetExtensionTypeCls(ext);
			ASSERT(eb);
			if (!eb || !eb->Initialize(ws)) {
				const auto& c = Eon::Factory::CompDataMap().Get(comp);
				const auto& e = c.ext.Get(ext);
				SetError("Could not " + String(!eb ? "create" : "initialize") + " extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "'");
				return false;
			}
		}
		else {
			Panic("Invalid world state type");
		}
		++plan_i;
	}
	
	
	PoolRef pool = e->GetPool();
	
	for(int i = 0; i < added_comps.GetCount()-1; i++) {
		AddedComp& c0 = added_comps[i];
		AddedComp& c1 = added_comps[i+1];
		ComponentBaseRef src = c0.r;
		ComponentBaseRef dst = c1.r;
		LoopSegment& seg = segments[c1.seg_i];
		ActionNode& n = *seg.ep.plan[c1.plan_i];
		const WorldState& ws = n.GetWorldState();
		ValDevCls iface = ws.GetInterface();
		if (!pool->Link(src, dst, iface)) {
			TypeCompCls comp = ws.GetComponent();
			String comp_name = Eon::Factory::CompDataMap().Get(comp).name;
			String src_iface_name = Eon::Factory::SourceDataMap().Get(iface).name;
			SetError("Could not link component '" + comp_name + "' source '" + src_iface_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		if (c0.side_in >= 0)
			src->SetSideIn(c0.side_in);
		if (c0.side_out >= 0)
			src->SetSideOut(c0.side_out);
		
		comps.Add(src);
	}
	
	AddedComp& first = added_comps[0];
	AddedComp& last  = added_comps.Top();
	LoopSegment& first_seg = segments[first.seg_i];
	LoopSegment& last_seg  = segments[last.seg_i];
	ExtComponentRef comp = first.r->AsRef<ExtComponent>();
	if (comp) {
		comp->AddPlan(first_seg.ep);
	}
	
	
	// Process sub-loops
	for (Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Value::VAL_CUSTOMER)
			continue;
		//LoadLoopDefinition(stmt.value->customer);
		SetError("Sub-loops not supported yet");
		return false;
	}
	
	
	// Add changes to parent state
	/*const WorldState& ret_ws = last_seg.ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		SetError("Invalid type in return value");
		return false;
	}*/
	
	
	return true;
}


SideStatus LoopLoader::AcceptOutput(LoopLoader& out, ActionPlanner::State*& accepted_in, ActionPlanner::State*& accepted_out) {
	ASSERT(status == INPUT_IS_WAITING);
	ASSERT(out.status == OUTPUT_IS_WAITING);
	auto& inputs = planner.GetSideInputs();
	auto& outputs = out.planner.GetSideOutputs();
	ASSERT(!inputs.IsEmpty() && !outputs.IsEmpty());
	
	SideStatus ret = SIDE_NOT_ACCEPTED;
	int accepted_count = 0;
	accepted_in = 0;
	accepted_out = 0;
	
	for (auto& in_state : inputs) {
		APlanNode* in = in_state.last;
		WorldState& in_ws = in->GetWorldState();
		ASSERT(in_ws.IsAddExtension());
		TypeCompCls in_comp = in_ws.GetComponent();
		TypeExtCls in_type = in_ws.GetExtension();
		auto& in_d = Eon::Factory::CompDataMap().Get(in_comp);
		auto& in_e = in_d.ext.Get(in_type);
		
		for (auto& out_state : outputs) {
			APlanNode* out = out_state.last;
			WorldState& out_ws = out->GetWorldState();
			ASSERT(out_ws.IsAddExtension());
			TypeCompCls out_comp = out_ws.GetComponent();
			TypeExtCls out_type = out_ws.GetExtension();
			auto& out_d = Eon::Factory::CompDataMap().Get(out_comp);
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
	
	return ret;
}

void LoopLoader::AddSideConnectionSegment(ActionPlanner::State* state, LoopLoader* c, ActionPlanner::State* side_state) {
	LoopSegment& prev = segments.Top();
	prev.stop_node = state->last;
	prev.ep.plan = prev.as.ReconstructPath(*state->last);
	ASSERT(prev.ep.plan.GetCount());
	LoopSegment& seg = segments.Add();
	seg.start_node = state->last;
	seg.side_conn = c;
	seg.as = state->as;
}



NAMESPACE_EON_END

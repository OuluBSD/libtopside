#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


EonLoopLoader::EonLoopLoader(EonChainLoader& parent, int id, Eon::LoopDefinition& def) :
	Base(parent, id, def)
{
	planner.SetLoopLoader(this);
}

void EonLoopLoader::LoopStatus() {
	Panic("internal error");
}

void EonLoopLoader::ForwardLoops() {
	Panic("internal error");
}

void EonLoopLoader::GetLoops(Vector<EonLoopLoader*>& v) {
	Panic("internal error");
}

void EonLoopLoader::SetRetryDeep() {
	if (status == EonStatus::READY)
		return;
	status = EonStatus::RETRY;
}

String EonLoopLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Loop " << id;
	s.Cat('\n');
	
	int id = 0;
	for (EonLoopSegment& seg : segments) {
		s << seg.GetTreeString(id++, indent+1);
	}
	
	s << GetEonStatusLine(indent+1, status);
	
	return s;
}

String EonLoopSegment::GetTreeString(int id, int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Segment " << id;
	s.Cat('\n');
	if (!ep.plan.IsEmpty()) {
		bool started = false;
		for (Eon::ActionNode* n : ep.plan) {
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

void EonLoopLoader::AddError(String msg) {
	//GetLoader().AddError(this, msg);
	status = FAILED;
}

void EonLoopLoader::SetupSegment(EonLoopSegment& s) {
	
	
	// Do the action plan searching
	s.as.SetLimit(10000);
	
}

void EonLoopLoader::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	EonStatus prev_status = status;
	
	if (status == EonStatus::IN_BEGINNING) {
		if (def.stmts.IsEmpty() && def.req.IsEmpty()) {
			String id = def.id.ToString();
			AddError("Loop " + IntStr(GetId()) + " '" + id + "' has no statements");
			return;
		}
		
		InitSegments();
		ForwardTopSegment();
	}
	else if (status == EonStatus::RETRY) {
		ASSERT(segments.GetCount() >= 1);
		planner.ClearForward();
		
		ForwardTopSegment();
	}
	else {
		
		TODO
		
	}
	
	ASSERT(prev_status != status);
}

void EonLoopLoader::InitSegments() {
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
	
	for (Eon::Id& req : def.req) {
		Eon::State* s = GetLoader().FindState(req);
		if (!s) {
			AddError("Could not find required state '" + req.ToString() + "'");
			return;
		}
		for (Eon::Statement& stmt : s->stmts)
			if (!SetWorldState(goal, stmt))
				return;
	}
	
	for (Eon::Statement& stmt : def.stmts)
		if (!SetWorldState(goal, stmt))
			return;
	LOG("goal: " << goal.ToString());
	
	goal_node.SetWorldState(goal);
	goal_node.SetGoal(goal_node);
	
	start_node.SetActionPlanner(planner);
	start_node.SetGoal(goal_node);
	start_node.SetWorldState(start);
	
	
	EonLoopSegment& seg = segments.Add();
	seg.start_node = &start_node;
}

void EonLoopLoader::ForwardTopSegment() {
	EonLoopSegment& seg = segments.Top();
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
			AddError("Plan implementation searching failed after side-connection");
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
				const Eon::WorldState& ws = state.last->GetWorldState();
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = INPUT_IS_WAITING;
			return;
		}
		else if (!is_input && outputs.GetCount()) {
			LOG("Loop " << id << " side-outputs:");
			for(int i = 0; i < outputs.GetCount(); i++) {
				auto& state = outputs[i];
				const Eon::WorldState& ws = state.last->GetWorldState();
				//LOG(i << ": " << state.last->GetEstimate() << ": " << ws.GetFullString());
				LOG(i << ": " << state.last->GetEstimate() << ": " << ws.ToString());
			}
			status = OUTPUT_IS_WAITING;
			return;
		}
		else {
			AddError("Plan implementation searching failed");
			return;
		}
	}
	
	// Set last node
	seg.stop_node = seg.ep.plan.Top();
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		EonLoopSegment& seg = segments.Top();
		for (Eon::ActionNode* n : seg.ep.plan) {
			const Eon::WorldState& ws = n->GetWorldState();
			TypeCompCls comp = ws.GetComponent();
			const auto& d = Ecs::Factory::CompDataMap().Get(comp);
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

bool EonLoopLoader::SetWorldState(Eon::WorldState& ws, const Eon::Statement& stmt) {
	if (!stmt.value || stmt.value->type == Eon::Value::VAL_CUSTOMER)
		return true;;
	
	int atom = planner.GetAddAtom(stmt.id);
	
	String old_value = goal.Get(atom);
	String new_value;
	
	if (stmt.value->type == Eon::Value::VAL_BOOLEAN)
		new_value = stmt.value->b ? "true" : "false";
	else if (stmt.value->type == Eon::Value::VAL_ID)
		new_value = stmt.value->id.ToString();
	else if (stmt.value->type == Eon::Value::VAL_STRING)
		new_value = stmt.value->str;
	else if (stmt.value->type == Eon::Value::VAL_INT)
		new_value = IntStr(stmt.value->i);
	else if (stmt.value->type == Eon::Value::VAL_DOUBLE)
		new_value = DblStr(stmt.value->f);
	else {
		AddError("internal error");
		return false;
	}
	
	if (old_value != new_value && !old_value.IsEmpty()) {
		AddError("Earlier value mismatch newer value for id '" + stmt.id.ToString() + "' (" +
			old_value + " != " + new_value + ")");
		return false;
	}
	
	ws.Set(atom, new_value);
	return true;
}


bool EonLoopLoader::Load() {
	EonLoader& loader = GetLoader();
	
	// Target entity for components
	EntityRef e = loader.ResolveEntity(def.id);
	if (!e) {
		AddError("Could not resolve entity with id: " + def.id.ToString());
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
	EonLoopSegment& seg = segments.Top();
	int plan_i = 0;
	for (Eon::ActionNode* n : seg.ep.plan) {
		
		RTLOG("Loading plan node " << plan_i);
		Eon::WorldState& ws = n->GetWorldState();
		if (ws.IsAddComponent()) {
			bool is_last = plan_i == seg.ep.plan.GetCount()-1;
			TypeCompCls comp = ws.GetComponent();
			ComponentBaseRef cb =
				is_last ?
					e->FindTypeCls(comp) :
					e->GetAddTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
				AddError("Could not create component '" + comp_name + "' at '" + def.id.ToString() + "'");
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
			POPO(Pol::Ecs::Eon::Loader::CorrespondingAddCompAndExt);
			auto& c = added_comps.Top();
			c.side_in = n->GetSideInId();
			c.side_out = n->GetSideOutId();
			
			
			TypeCompCls comp = ws.GetComponent();
			TypeExtCls ext = ws.GetExtension();
			ComponentBaseRef cb = e->GetTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
				AddError("Could not fwsind component '" + comp_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			{
				ComponentExtBaseRef existing_ext = cb->GetExtension();
				if (existing_ext) {
					const auto& c = Ecs::Factory::CompDataMap().Get(comp);
					const auto& e = c.ext.Get(ext);
					AddError("Could not create extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "' because existing extension '" + existing_ext->GetDynamicName() + "'");
					return false;
				}
			}
			
			
			// Add arguments to ws
			for(int i = 0; i < ws.values.GetCount(); i++) {
				String key = planner.atoms.GetKey(i);
				for (const Eon::Statement& stmt : def.stmts) {
					String stmt_key = stmt.id.ToString();
					if (stmt_key == key) {
						//LOG(i << " " << key << " " << stmt_key);
						for (const Eon::Statement& arg : stmt.args) {
							//LOG("\t" << arg.id.ToString());
							if (arg.value) {
								String k = arg.id.ToString();
								String v = arg.value->GetValue();
								ws.Set("." + k, v);
								//LOG("EonLoader::LoadLoopDefinition: add argument: " << k << " = " << v);
							}
						}
					}
				}
			}
			
			
			ComponentExtBaseRef eb = cb->SetExtensionTypeCls(ext);
			ASSERT(eb);
			if (!eb || !eb->Initialize(ws)) {
				const auto& c = Ecs::Factory::CompDataMap().Get(comp);
				const auto& e = c.ext.Get(ext);
				AddError("Could not " + String(!eb ? "create" : "initialize") + " extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "'");
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
		EonLoopSegment& seg = segments[c1.seg_i];
		Eon::ActionNode& n = *seg.ep.plan[c1.plan_i];
		const Eon::WorldState& ws = n.GetWorldState();
		ValDevCls iface = ws.GetInterface();
		if (!pool->Link(src, dst, iface)) {
			TypeCompCls comp = ws.GetComponent();
			String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
			String src_iface_name = Ecs::Factory::SourceDataMap().Get(iface).name;
			AddError("Could not link component '" + comp_name + "' source '" + src_iface_name + "' at '" + def.id.ToString() + "'");
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
	EonLoopSegment& first_seg = segments[first.seg_i];
	EonLoopSegment& last_seg  = segments[last.seg_i];
	ExtComponentRef comp = first.r->AsRef<ExtComponent>();
	if (comp) {
		comp->AddPlan(first_seg.ep);
	}
	
	
	// Process sub-loops
	for (Eon::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Eon::Value::VAL_CUSTOMER)
			continue;
		//LoadLoopDefinition(stmt.value->customer);
		AddError("Sub-loops not supported yet");
		return false;
	}
	
	
	// Add changes to parent state
	/*const Eon::WorldState& ret_ws = last_seg.ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		AddError("Invalid type in return value");
		return false;
	}*/
	
	
	return true;
}


SideStatus EonLoopLoader::AcceptOutput(EonLoopLoader& out, Eon::ActionPlanner::State*& accepted_in, Eon::ActionPlanner::State*& accepted_out) {
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
		Eon::APlanNode* in = in_state.last;
		Eon::WorldState& in_ws = in->GetWorldState();
		ASSERT(in_ws.IsAddExtension());
		TypeCompCls in_comp = in_ws.GetComponent();
		TypeExtCls in_type = in_ws.GetExtension();
		auto& in_d = Ecs::Factory::CompDataMap().Get(in_comp);
		auto& in_e = in_d.ext.Get(in_type);
		
		for (auto& out_state : outputs) {
			Eon::APlanNode* out = out_state.last;
			Eon::WorldState& out_ws = out->GetWorldState();
			ASSERT(out_ws.IsAddExtension());
			TypeCompCls out_comp = out_ws.GetComponent();
			TypeExtCls out_type = out_ws.GetExtension();
			auto& out_d = Ecs::Factory::CompDataMap().Get(out_comp);
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

void EonLoopLoader::AddSideConnectionSegment(Eon::ActionPlanner::State* state, EonLoopLoader* c, Eon::ActionPlanner::State* side_state) {
	EonLoopSegment& prev = segments.Top();
	prev.stop_node = state->last;
	prev.ep.plan = prev.as.ReconstructPath(*state->last);
	ASSERT(prev.ep.plan.GetCount());
	EonLoopSegment& seg = segments.Add();
	seg.start_node = state->last;
	seg.side_conn = c;
	seg.as = state->as;
}


NAMESPACE_ECS_END

#include "EcsLib.h"

NAMESPACE_ECS_BEGIN






bool EonLoader::Initialize() {
	es = GetMachine().TryGet<EntityStore>();
	if (!es) {
		LOG("EonLoader requires EntityStore present in machine");
		return false;
	}
	
	if (!DoPostLoad())
		return false;
	
	return true;
}

bool EonLoader::DoPostLoad() {
	for(String path : post_load_file) {
		if (!LoadFile(path))
			return false;
	}
	post_load_file.Clear();
	
	for(String s : post_load_string) {
		if (!Load(s, "input"))
			return false;
	}
	post_load_string.Clear();
	
	return true;
}

void EonLoader::Start() {
	
}

void EonLoader::Update(double dt) {
	
	DoPostLoad();
	
}

void EonLoader::Stop() {
	
}

void EonLoader::Uninitialize() {
	
}

bool EonLoader::LoadFile(String path) {
	if (!FileExists(path)) {
		LOG("Could not find EON file");
		return false;
	}
	String eon = TS::LoadFile(path);
	return Load(eon, path);
}

bool TestParseEonCode(String content) {
	Eon::Parser p;
	if (!p.Parse(content, "<file>")) {
		LOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	return true;
}

bool EonLoader::Load(String content, String filepath) {
	DLOG("EonLoader::Load: Loading \"" << filepath << "\"");
	
	Eon::Parser p;
	if (!p.Parse(content, filepath)) {
		LOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	MemSwap(p.GetResult(), root);
	
	return LoadCompilationUnit(root);
}

bool EonLoader::LoadCompilationUnit(Eon::CompilationUnit& cunit) {
	return LoadSidechainDefinition(cunit.main);
}

bool EonLoader::LoadSidechainDefinition(Eon::SidechainDefinition& def) {
	// Enter scope
	EonScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	EonScope& scope = scopes.Add();
	scope.def = &def;
	if (parent) {
		scope.current_state = parent->current_state;
	}
	
	
	for (Eon::SidechainDefinition& d : def.chains) {
		if (!LoadSidechainDefinition(d)) {
			scopes.RemoveLast();
			return false;
		}
	}
	
	for (Eon::LoopDefinition& d : def.loops) {
		if (!LoadLoopDefinition(d)) {
			scopes.RemoveLast();
			return false;
		}
	}
	
	if (scopes.GetCount() >= 2) {
		EonScope& par = scopes.At(scopes.GetCount()-2);
		const Eon::WorldState& src_ws = scope.current_state;
		Eon::WorldState& dst_ws = par.current_state;
		if (!dst_ws.Append(src_ws, par.def->ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
	}
	
	
	// Add changes to parent state
	if (parent) {
		if (!parent->current_state.Append(scope.current_state, def.ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
	}
	
	scopes.RemoveLast();
	return true;
}

bool EonLoader::LoadLoopDefinition(Eon::LoopDefinition& def) {
	
	// Target entity for components
	EntityRef e = ResolveEntity(def.id);
	if (!e) {
		AddError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	EonScope& scope = scopes.Top();
	
	
	// Prepare action planner and world states
	Eon::ActionPlanner planner;
	int CONNECTED = planner.GetAddAtom("loop.connected");
	ValDevCls ord_vd(DevCls::CENTER, ValCls::ORDER);
	ValDevCls rcp_vd(DevCls::CENTER, ValCls::RECEIPT);
	
	Eon::WorldState src;
	src = scope.current_state;
	src.SetActionPlanner(planner);
	src.SetAs_AddComponent(AsEcsTypeCls<CustomerComponent>(ord_vd), rcp_vd);
	src.Set(CONNECTED, false);
	
	Eon::WorldState goal;
	goal.SetActionPlanner(planner);
	goal.SetAs_AddComponent(AsEcsTypeCls<CustomerComponent>(ord_vd), rcp_vd);
	goal.Set(CONNECTED, true);
		
	
	for (Eon::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type == Eon::Value::VAL_CUSTOMER)
			continue;
		
		int atom = planner.GetAddAtom(stmt.id);
		if (stmt.value->type == Eon::Value::VAL_BOOLEAN)
			goal.Set(atom, stmt.value->b);
		else if (stmt.value->type == Eon::Value::VAL_ID)
			goal.Set(atom, stmt.value->id.ToString());
		else if (stmt.value->type == Eon::Value::VAL_STRING)
			goal.Set(atom, stmt.value->str);
		else
			Panic("internal error");
	}
	LOG("goal: " << goal.ToString());
	
	Eon::APlanNode goal_node;
	goal_node.SetWorldState(goal);
	goal_node.SetGoal(goal_node);
	
	Eon::APlanNode start_node;
	start_node.SetActionPlanner(planner);
	start_node.SetGoal(goal_node);
	start_node.SetWorldState(src);
	
	
	// Do the action plan searching
	AStar<Eon::ActionNode> as;
	Eon::Plan ep;
	ep.plan = as.Search(start_node);
	
	if (ep.plan.IsEmpty()) {
		AddError("Plan implementation searching failed");
		return false;
	}
	
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		for (Eon::ActionNode* n : ep.plan) {
			const Eon::WorldState& ws = n->GetWorldState();
			EcsTypeCls comp = ws.GetComponent();
			const auto& d = Ecs::Factory::CompDataMap().Get(comp);
			if (ws.IsAddComponent()) {LOG(pos++ << ": add comp: " << d.name);}
			if (ws.IsAddExtension()) {
				const auto& e = d.ext.Get(ws.GetExtension());
				LOG(pos++ << ": add ext: " << e.name << " (to " << d.name << ")");
			}
			LOG("\t" << ws.ToString());
		}
	}
	
	
	// Implement found loop
	struct AddedComp {
		ComponentBaseRef r;
		int plan_i;
	};
	Array<AddedComp> added_comps;
	
	int plan_i = 0;
	for (Eon::ActionNode* n : ep.plan) {
		const Eon::WorldState& ws = n->GetWorldState();
		if (ws.IsAddComponent()) {
			bool is_last = plan_i == ep.plan.GetCount()-1;
			EcsTypeCls comp = ws.GetComponent();
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
		}
		else if (ws.IsAddExtension()) {
			EcsTypeCls comp = ws.GetComponent();
			EcsTypeCls ext = ws.GetExtension();
			ComponentBaseRef cb = e->GetTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
				AddError("Could not find component '" + comp_name + "' at '" + def.id.ToString() + "'");
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
			ComponentExtBaseRef eb = cb->SetExtensionTypeCls(ext);
			ASSERT(eb);
			if (!eb) {
				const auto& c = Ecs::Factory::CompDataMap().Get(comp);
				const auto& e = c.ext.Get(ext);
				AddError("Could not create extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "'");
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
		Eon::ActionNode& n = *ep.plan[c1.plan_i];
		const Eon::WorldState& ws = n.GetWorldState();
		ValDevCls iface = ws.GetInterface();
		if (!pool->Link(src, dst, iface)) {
			EcsTypeCls comp = ws.GetComponent();
			String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
			String src_iface_name = Ecs::Factory::SourceDataMap().Get(iface).name;
			AddError("Could not link component '" + comp_name + "' source '" + src_iface_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
	}
	
	CustomerComponentRef customer = added_comps[0].r->AsRef<CustomerComponent>();
	if (customer) {
		customer->AddPlan(ep);
	}
	
	
	// Process sub-loops
	for (Eon::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Eon::Value::VAL_CUSTOMER)
			continue;
		LoadLoopDefinition(stmt.value->customer);
	}
	
	
	// Add changes to parent state
	const Eon::WorldState& ret_ws = ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		AddError("Invalid type in return value");
		return false;
	}
	
	
	return true;
}

EntityRef EonLoader::ResolveEntity(Eon::Id& id) {
	ASSERT(es);
	EntityRef e;
	PoolRef p = es->GetRoot();
	int i = 0, count = id.parts.GetCount();
	for (const String& part : id.parts) {
		if (i++ == count - 1) {
			e = p->GetAddEmpty(part);
		}
		else {
			p = p->GetAddPool(part);
		}
	}
	return e;
}

void EonLoader::AddError(String msg) {
	LOG("EonLoader: error: " + msg);
}



NAMESPACE_ECS_END

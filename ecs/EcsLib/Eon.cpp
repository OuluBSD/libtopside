#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN






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

bool EonLoader::Load(String content, String filepath) {
	DLOG("EonLoader::Load: Loading \"" << filepath << "\"");
	
	Eon::Parser p;
	if (!p.Parse(content, filepath)) {
		LOG(content);
		return false;
	}
	p.Dump();
	MemSwap(p.GetResult(), root);
	
	return LoadCompilationUnit(root);
}

bool EonLoader::LoadCompilationUnit(Eon::CompilationUnit& cunit) {
	
	for (Eon::CustomerDefinition& def : cunit.customers) {
		if (!LoadCustomerDefinition(def))
			return false;
	}
	
	return true;
}

bool EonLoader::LoadCustomerDefinition(Eon::CustomerDefinition& def) {
	
	// Target entity for components
	EntityRef e = ResolveEntity(def.id);
	if (!e) {
		AddError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	// Enter scope
	EonScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	EonScope& current = scopes.Add();
	
	
	// Prepare action planner and world states
	Eon::ActionPlanner planner;
	int CONNECTED = planner.GetAddAtom("loop.connected");
	
	Eon::WorldState src;
	src.SetActionPlanner(planner);
	src.SetAs_AddComponent(AsTypeCls<CustomerComponent>(), AsTypeCls<ReceiptSource>(), AsTypeCls<ReceiptSink>());
	src.Set(CONNECTED, false);
	
	Eon::WorldState goal;
	goal.SetActionPlanner(planner);
	goal.SetAs_AddComponent(AsTypeCls<CustomerComponent>(), AsTypeCls<ReceiptSource>(), AsTypeCls<ReceiptSink>());
	goal.Set(CONNECTED, true);
	
	
	if (parent)
		current.SetConstantState(parent->GetFinalState());
	
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
	EonPlan ep;
	ep.plan = as.Search(start_node);
	
	if (ep.plan.IsEmpty()) {
		AddError("Eon action planner failed");
		return false;
	}
	
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		for (Eon::ActionNode* n : ep.plan) {
			const Eon::WorldState& ws = n->GetWorldState();
			TypeCls comp = ws.GetComponent();
			const auto& d = EcsFactory::CompDataMap().Get(comp);
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
			TypeCls comp = ws.GetComponent();
			ComponentBaseRef cb = e->GetAddTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = EcsFactory::CompDataMap().Get(comp).name;
				AddError("Could not create component '" + comp_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			auto& c = added_comps.Add();
			c.r = cb;
			c.plan_i = plan_i;
		}
		else if (ws.IsAddExtension()) {
			TypeCls comp = ws.GetComponent();
			TypeCls ext = ws.GetExtension();
			ComponentBaseRef cb = e->GetTypeCls(comp);
			ASSERT(cb);
			if (!cb) {
				String comp_name = EcsFactory::CompDataMap().Get(comp).name;
				AddError("Could not find component '" + comp_name + "' at '" + def.id.ToString() + "'");
				return false;
			}
			ComponentExtBaseRef existing_ext = cb->GetExtension();
			if (existing_ext) {
				const auto& c = EcsFactory::CompDataMap().Get(comp);
				const auto& e = c.ext.Get(ext);
				AddError("Could not create extension '" + e.name + "' to '" + c.name + "' at '" + def.id.ToString() + "' because existing extension '" + existing_ext->GetDynamicName() + "'");
				return false;
			}
			ComponentExtBaseRef eb = cb->SetExtensionTypeCls(ext);
			ASSERT(eb);
			if (!eb) {
				const auto& c = EcsFactory::CompDataMap().Get(comp);
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
	ConnectManuallyInterfacesRef conn = e->GetPool().GetAdd<ConnectManuallyInterfaces>();
	
	for(int i = 0; i < added_comps.GetCount()-1; i++) {
		AddedComp& c0 = added_comps[i];
		AddedComp& c1 = added_comps[i+1];
		ComponentBaseRef src = c0.r;
		ComponentBaseRef dst = c1.r;
		Eon::ActionNode& n = *ep.plan[c1.plan_i];
		const Eon::WorldState& ws = n.GetWorldState();
		TypeCls src_iface = ws.GetSourceInterface();
		TypeCls sink_iface = ws.GetSinkInterface();
		if (!conn->LinkManually(src, dst, src_iface, sink_iface)) {
			TypeCls comp = ws.GetComponent();
			String comp_name = EcsFactory::CompDataMap().Get(comp).name;
			String src_iface_name = EcsFactory::SourceDataMap().Get(src_iface).name;
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
		LoadCustomerDefinition(stmt.value->customer);
	}
	
	
	// Exit scope
	scopes.RemoveLast();
	
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



NAMESPACE_TOPSIDE_END

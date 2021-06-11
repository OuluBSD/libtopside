#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN






bool EonLoader::Initialize() {
	es = GetMachine().TryGet<EntityStore>();
	if (!es) {
		LOG("EonLoader requires EntityStore present in machine");
		return false;
	}
	
	for(String path : post_load_file) {
		if (!LoadFile(path))
			return false;
	}
	
	return true;
}

void EonLoader::Start() {
	
}

void EonLoader::Update(double dt) {
	
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
	EntityRef e = ResolveEntity(def.id);
	if (!e) {
		AddError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	EonScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	EonScope& current = scopes.Add();
	
	
	
	Eon::ActionPlanner planner;
	int CONNECTED = planner.GetAddAtom("loop.connected");
	
	Eon::WorldState src;
	src.SetActionPlanner(planner);
	src.SetComponent(AsTypeCls<CustomerComponent>());
	src.Set(CONNECTED, false);
	
	Eon::WorldState goal;
	goal.SetActionPlanner(planner);
	goal.SetComponent(AsTypeCls<CustomerComponent>());
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
	
	AStar<Eon::ActionNode> as;
	Vector<Eon::ActionNode*> plan = as.Search(start_node);
	
	if (plan.IsEmpty()) {
		AddError("Eon action planner failed");
		return false;
	}
	
	if (1) {
		int pos = 0;
		for (Eon::ActionNode* n : plan) {
			const Eon::WorldState& ws = n->GetWorldState();
			TypeCls comp = ws.GetComponent();
			String comp_name = EcsFactory::CompDataMap().Get(comp).name;
			LOG(pos++ << ": " << comp_name);
			LOG("\t" << ws.ToString());
		}
	}
	
	
	
	
	for (Eon::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Eon::Value::VAL_CUSTOMER)
			continue;
		LoadCustomerDefinition(stmt.value->customer);
	}
	
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

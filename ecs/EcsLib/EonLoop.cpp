#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


void EonLoopLoader::AddError(String msg) {
	failed = true;
	loader.AddError(msg);
}

bool EonLoopLoader::Forward() {
	EonScope& scope = loader.scopes.Add();
	
	// Prepare action planner and world states
	int CONNECTED = planner.GetAddAtom("loop.connected");
	CompCls customer;
	customer.sink = VD(DevCls::CENTER, ValCls::RECEIPT);
	customer.side = VD(DevCls::CENTER, ValCls::ORDER);
	customer.src  = VD(DevCls::CENTER, ValCls::ORDER);
	
	Eon::WorldState src;
	src = scope.current_state;
	src.SetActionPlanner(planner);
	src.SetAs_AddComponent(AsTypeCompCls<ExtComponent>(SubCompCls::CUSTOMER, customer));
	src.Set(CONNECTED, false);
	
	Eon::WorldState goal;
	goal.SetActionPlanner(planner);
	goal.SetAs_AddComponent(AsTypeCompCls<ExtComponent>(SubCompCls::CUSTOMER, customer));
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
	as.SetLimit(1000);
	ep.plan = as.Search(start_node);
	
	if (ep.plan.IsEmpty()) {
		
		// Check side-channel connections
		TODO
		
		
		AddError("Plan implementation searching failed");
		return false;
	}
	
	
	// Debug print found loop
	if (1) {
		int pos = 0;
		for (Eon::ActionNode* n : ep.plan) {
			const Eon::WorldState& ws = n->GetWorldState();
			TypeCompCls comp = ws.GetComponent();
			const auto& d = Ecs::Factory::CompDataMap().Get(comp);
			if (ws.IsAddComponent()) {LOG(pos++ << ": add comp: " << d.name);}
			if (ws.IsAddExtension()) {
				const auto& e = d.ext.Get(ws.GetExtension());
				LOG(pos++ << ": add ext: " << e.name << " (to " << d.name << ")");
			}
			LOG("\t" << ws.ToString());
		}
	}
	
	return true;
}

bool EonLoopLoader::Load() {
	
	// Target entity for components
	EntityRef e = loader.ResolveEntity(def.id);
	if (!e) {
		AddError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	EonScope& scope = loader.scopes.Top();
	
	
	// Implement found loop
	struct AddedComp {
		ComponentBaseRef r;
		int plan_i;
	};
	Array<AddedComp> added_comps;
	
	int plan_i = 0;
	for (Eon::ActionNode* n : ep.plan) {
		RTLOG("Loading plan node " << plan_i);
		Eon::WorldState& ws = n->GetWorldState();
		if (ws.IsAddComponent()) {
			bool is_last = plan_i == ep.plan.GetCount()-1;
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
		}
		else if (ws.IsAddExtension()) {
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
		Eon::ActionNode& n = *ep.plan[c1.plan_i];
		const Eon::WorldState& ws = n.GetWorldState();
		ValDevCls iface = ws.GetInterface();
		if (!pool->Link(src, dst, iface)) {
			TypeCompCls comp = ws.GetComponent();
			String comp_name = Ecs::Factory::CompDataMap().Get(comp).name;
			String src_iface_name = Ecs::Factory::SourceDataMap().Get(iface).name;
			AddError("Could not link component '" + comp_name + "' source '" + src_iface_name + "' at '" + def.id.ToString() + "'");
			return false;
		}
	}
	
	ExtComponentRef comp = added_comps[0].r->AsRef<ExtComponent>();
	if (comp) {
		comp->AddPlan(ep);
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
	const Eon::WorldState& ret_ws = ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		AddError("Invalid type in return value");
		return false;
	}
	
	
	return true;
}


NAMESPACE_ECS_END

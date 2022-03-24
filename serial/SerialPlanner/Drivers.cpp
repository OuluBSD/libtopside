#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN
using namespace Parallel;


ScriptDriverLoader::ScriptDriverLoader(ScriptMachineLoader& parent, int id, Script::DriverDefinition& def) :
	Base(parent, id, def)
{
	
}

String ScriptDriverLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Driver " << id;
	s.Cat('\n');
	/*for (ScriptTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}*/
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptDriverLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	
}

void ScriptDriverLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	v.Add(this);
}

void ScriptDriverLoader::Forward() {
	if (IsReady())
		return;
	
	ASSERT(!IsFailed());
	ScriptStatus prev_status = status;
	
	ASSERT(status != ScriptStatus::READY);
	
	if (status == ScriptStatus::IN_BEGINNING) {
		if (def.stmts.IsEmpty()) {
			String id = def.id.ToString();
			SetError("Driver " + IntStr(GetId()) + " '" + id + "' has no statements");
			return;
		}
		
		FindAtoms();
	}
	else {
		SetStatus(ScriptStatus::FAILED);
	}
	
	ASSERT(prev_status != status);
}

bool ScriptDriverLoader::Load() {
	ScriptLoader& loader = GetLoader();
	
	// Target entity for atoms
	LoopRef l = loader.ResolveLoop(def.id);
	if (!l) {
		SetError("Could not resolve entity with id: " + def.id.ToString());
		return false;
	}
	
	for (Script::WorldState& ws : atoms) {
		AtomTypeCls type = ws.GetAtom();
		ASSERT(type.IsValid());
		
		RTLOG("Loading driver atom " << type.ToString());
		
		AtomBaseRef ab = l->FindTypeCls(type);
		if (ab) {
			SetError("loop '" + def.id.ToString() + "' already has atom: " + type.ToString());
			return false;
		}
		
		ab = l->GetAddTypeCls(type);
		
		if (!ab) {
			String atom_name = Serial::Factory::AtomDataMap().Get(type).name;
			SetError("Could not create atom '" + atom_name + "' at '" + def.id.ToString() + "'");
			DUMP(type);
			ASSERT(0);
			return false;
		}
		
		// Add arguments to ws
		const Script::Statement* stmt = ws.FindStatement(0, def.stmts);
		if (stmt) {
			for (const Script::Statement& arg : stmt->args) {
				//LOG("\t" << arg.id.ToString());
				String k = arg.id.ToString();
				String v = arg.value ? arg.value->GetValue() : String();
				ws.Set("." + k, v);
				LOG("ScriptDriverLoader::Load: add argument: " << k << " = " << v);
			}
		}
		
		TODO
		/*if (!ab->InitializeAtom(ws) || !ab->Initialize(ws)) {
			const auto& a = Serial::Factory::AtomDataMap().Get(type);
			SetError("Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
			return false;
		}*/
		
		added_atoms.Add(ab);
	}
	
	return true;
}

bool ScriptDriverLoader::PostInitialize() {
	TODO
	/*for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		if (!added_atoms[i]->PostInitialize())
			return false;
	}*/
	return true;
}

void ScriptDriverLoader::ForwardLoops() {
	Panic("internal error");
}

void ScriptDriverLoader::LoopStatus() {
	Panic("internal error");
}

void ScriptDriverLoader::CheckStatusDeep() {
	CheckFlags();
}

void ScriptDriverLoader::FindAtoms() {
	atoms.Clear();
	if (def.stmts.IsEmpty()) {
		SetError("no statements in driver");
		return;
	}
	
	
	for (const auto& atom : Parallel::Factory::AtomDataMap().GetValues()) {
		Script::Action act;
		Script::WorldState& pre		= act.Pre();
		Script::WorldState& post	= act.Post();
		pre		.SetActionPlanner(planner);
		post	.SetActionPlanner(planner);
		
		if (atom.action_fn(atom.cls, act)) {
			bool all_match = true;
			for (Script::Statement& stmt : def.stmts) {
				String id = stmt.id.ToString();
				String val = post.Get(id);
				String exp_val = stmt.value ? stmt.value->ToString() : "true";
				if (val != exp_val) {
					all_match = false;
					break;
				}
			}
			
			if (all_match) {
				Script::WorldState& ws = atoms.Add();
				ws = post;
				ws.SetAs_AddAtom(atom.cls);
				break;
			}
		}
	}
	
	if (atoms.IsEmpty()) {
		SetError("no atom found, which could satisfy driver statements");
		return;
	}
	
	SetStatus(ScriptStatus::READY);
}


NAMESPACE_SERIAL_END

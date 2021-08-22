#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN

String GetScriptStatusLine(int indent, ScriptStatus status, String extra_str) {
	String s;
	s.Cat('\t', indent);
	const char* t = GetScriptStatusString(status);
	s << "-> " << t;
	if (extra_str.GetCount())
		s << " (" << extra_str << ")";
	s.Cat('\n');
	return s;
}





int ScriptLoader::loop_counter = 0;




bool ScriptLoader::Initialize() {
	def_ws.SetActionPlanner(def_planner);
	
	es = GetMachine().TryGet<LoopStore>();
	if (!es) {
		LOG("ScriptLoader requires LoopStore present in machine");
		return false;
	}
	
	if (!DoPostLoad())
		return false;
	
	RTLOG("ScriptLoader::Initialize success!");
	return true;
}

bool ScriptLoader::DoPostLoad() {
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

void ScriptLoader::Start() {
	
}

void ScriptLoader::Update(double dt) {
	
	DoPostLoad();
	
}

void ScriptLoader::Stop() {
	
}

void ScriptLoader::Uninitialize() {
	
}

bool ScriptLoader::LoadFile(String path) {
	if (!FileExists(path)) {
		LOG("Could not find EON file");
		return false;
	}
	String eon = TS::LoadFile(path);
	return Load(eon, path);
}

bool TestParseScriptCode(String content) {
	Script::Parser p;
	if (!p.Parse(content, "<file>")) {
		LOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	return true;
}

bool ScriptLoader::Load(String content, String filepath) {
	RTLOG("ScriptLoader::Load: Loading \"" << filepath << "\"");
	
	Script::Parser p;
	if (!p.Parse(content, filepath)) {
		RTLOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	MemSwap(p.GetResult(), root);
	
	if (!LoadAtomilationUnit(root)) {
		LOG("error dump:"); loader->Dump();
		DumpErrors();
		
		Cleanup();
		return false;
	}
	
	if (!ImplementScript()) {
		DumpErrors();
		
		Cleanup();
		return false;
	}
	
	Cleanup();
	return true;
}

void ScriptLoader::Cleanup() {
	loader.Clear();
}

void ScriptLoader::DumpErrors() {
	Vector<ScriptLoopLoader*> loops;
	loader->GetLoops(loops);
	for (ScriptLoopLoader* ll : loops) {
		if (ll->GetStatus() == ScriptStatus::FAILED) {
			LOG("ScriptLoopLoader: error: " << ll->GetErrorString());
		}
	}
}

bool ScriptLoader::ImplementScript() {
	Vector<ScriptLoopLoader*> loops;
	loader->GetLoops(loops);
	for (ScriptLoopLoader* ll : loops) {
		if (!ll->Load())
			return false;
	}
	
	for (ScriptLoopLoader* loop0 : loops) {
		for (ScriptLoopLoader* loop1 : loops) {
			if (loop0 != loop1) {
				if (!ConnectSides(*loop0, *loop1)) {
					AddError("Side connecting failed");
					return false;
				}
			}
		}
	}
	
	return true;
}

bool ScriptLoader::LoadAtomilationUnit(Script::AtomilationUnit& cunit) {
	return LoadGlobalScope(cunit.list);
}
/*
void ScriptLoader::EnterScope() {
	ScriptScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	ScriptScope& scope = scopes.Add();
	
	scope.SetCurrentState(def_ws);
	
	if (parent) {
		scope.current_state = parent->current_state;
	}
}

bool ScriptLoader::LeaveScope() {
	ScriptScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	ScriptScope& scope = scopes.Top();
	
	if (scopes.GetCount() >= 2) {
		ScriptScope& par = scopes.At(scopes.GetCount()-2);
		const Script::WorldState& src_ws = scope.current_state;
		Script::WorldState& dst_ws = par.current_state;
		if (par.chain && !dst_ws.Append(src_ws, par.chain->ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
		if (par.loop && !dst_ws.Append(src_ws, par.loop->ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
	}
	
	
	// Add changes to parent state
	if (parent && scope.chain) {
		if (!parent->current_state.Append(scope.current_state, scope.chain->ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
	}
	if (parent && scope.loop) {
		if (!parent->current_state.Append(scope.current_state, scope.loop->ret_list)) {
			AddError("Invalid type in return value");
			return false;
		}
	}
	
	scopes.RemoveLast();
	return true;
}
*/
bool ScriptLoader::LoadGlobalScope(Script::GlobalScope& glob) {
	//EnterScope();
	//scopes.Top().glob = &glob;
	scopes.Add(&glob);
	
	loader = new ScriptSystemLoader(*this, 0, glob);
	
	int dbg_i = 0;
	while (!loader->IsFailed() && !loader->IsReady()) {
		DUMP(dbg_i);
		loader->Dump();
		
		loader->Forward();
		++dbg_i;
		
		ASSERT_(dbg_i < 100, "Something probably broke");
	}
	
	
	scopes.Remove(scopes.GetCount()-1);
	
	return loader->IsReady();
}

/*bool ScriptLoader::SolveLoops(Script::ChainDefinition& def) {
	loops.Clear();
	for (Script::LoopDefinition& loop_def : def.loops)
		loops.Add(new ScriptLoopLoader(loop_counter++, this, loop_def));
	if (loops.IsEmpty())
		return true;
	
	bool fail = false;
	enum {FORWARDING, CONNECTING_SIDECHANNEL};
	int mode = FORWARDING;
	int mode_count = 0;
	Vector<ScriptLoopLoader*> waiting_inputs, waiting_outputs;
	while(!fail) {
		if (mode == FORWARDING) {
			bool ready = true;
			bool keep_going = true;
			waiting_inputs.Clear();
			waiting_outputs.Clear();
			while (keep_going) {
				int dbg_i = 0;
				for (ScriptLoopLoader& loop : loops) {
					if (!loop.IsReady()) {
						keep_going = loop.Forward() && keep_going;
						fail = fail || loop.IsFailed();
						ready = ready && loop.IsReady();
					}
					if (loop.IsWaitingSideInput()) waiting_inputs.Add(&loop);
					if (loop.IsWaitingSideOutput()) waiting_outputs.Add(&loop);
					++dbg_i;
				}
			}
			if (ready)
				break;
		}
		else if (mode == CONNECTING_SIDECHANNEL) {
			
		}
		else Panic("Invalid mode");
		
		
		mode = (mode + 1) % 2;
		if (mode_count++ >= 10)
			break;
	}
	
	return !fail;
}*/

LoopRef ScriptLoader::ResolveLoop(Script::Id& id) {
	ASSERT(es);
	LoopRef e;
	LoopRef p = es->GetRoot();
	int i = 0, count = id.parts.GetCount();
	for (const String& part : id.parts) {
		if (i++ == count - 1) {
			e = p->GetAddEmpty(part);
		}
		else {
			p = p->GetAddLoop(part);
		}
	}
	return e;
}

void ScriptLoader::AddError(String msg) {
	if (!collect_errors) {
		LOG("ScriptLoader: error: " + msg);
	}
	else {
		ScriptError& e = errs.Add();
		e.msg = msg;
	}
}

void ScriptLoader::AddError(ScriptLoopLoader* ll, String msg) {
	if (!collect_errors) {
		LOG("ScriptLoader: error: " + msg);
	}
	else {
		ScriptError& e = errs.Add();
		e.ll = ll;
		e.status = ll->GetStatus();
		e.msg = msg;
	}
}

void ScriptLoader::ReleaseErrorBuffer() {
	if (errs.GetCount()) {
		ScriptError& e = errs.Top();
		LOG("ScriptLoader: error: " + e.msg);
		errs.Clear();
	}
}

void ScriptLoader::ClearErrorBuffer() {
	for (ScriptError& e : errs) {
		if (e.ll && e.ll->IsFailed() && e.status >= 0)
			e.ll->SetStatus(e.status);
	}
	errs.Clear();
}

bool ScriptLoader::ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1) {
	
	int dbg_i = 0;
	for (AtomBaseRef& in : loop0.atoms) {
		int in_conn = in->GetSideIn();
		if (in_conn < 0)
			continue;
		
		RTLOG("Trying to side-link id " << in_conn);
		bool found = false;
		for (AtomBaseRef& out : loop1.atoms) {
			int out_conn = out->GetSideOut();
			if (out_conn < 0)
				continue;
			
			if (in_conn == out_conn) {
				found = true;
				
				TODO
				#if 0
				if (!out->LinkSideIn(in)) {
					AddError("Side-output refused linking to side-input");
					return false;
				}
				if (!in->LinkSideOut(out)) {
					AddError("Side-input refused linking to side-output");
					return false;
				}
				#endif
				LOG(out->ToString() + "<> side-linked to " + in->ToString() + "<>");
				break;
			}
		}
		
		/*if (!found) {
			AddError("Could not link connection id " + IntStr(in_conn));
			return false;
		}*/
		
		dbg_i++;
	}
	
	
	return true;
}

Script::State* ScriptLoader::FindState(const Script::Id& id) {
	auto iter = scopes.rbegin();
	auto end = scopes.rend();
	for(; iter != end; --iter) {
		Script::GlobalScope& glob = **iter;
		for (Script::State& state : glob.states) {
			if (state.id == id) {
				return &state;
			}
		}
	}
	return NULL;
}

/*void ScriptLoader::SolveInsideLoops(Script::ChainDefinition& chain) {
	TODO
}

void ScriptLoader::SolveInsideChain(Script::ChainDefinition& chain) {
	TODO
}

void ScriptLoader::SolveBetweenChains(const Vector<Script::ChainDefinition*>& chains) {
	TODO
}

void ScriptLoader::SolveBetweenMachines(const Vector<Vector<Script::ChainDefinition*>>& machs) {
	TODO
}

bool ScriptLoader::IsNewConnections() const {
	TODO
}

void ScriptLoader::GetChainsDeepestFirst(Script::Machine& mach, Vector<Script::ChainDefinition*>& chains) {
	LinkedList<Script::ChainDefinition*> unvisited;
	
	for (Script::ChainDefinition& ch : mach.chains)
		unvisited.Add(&ch);
	
	while (unvisited.GetCount()) {
		Script::ChainDefinition* p = unvisited.First();
		unvisited.RemoveFirst();
		
		chains.Add(p);
		p->GetSubChainPointers(unvisited);
	}
	
	Reverse(chains);
}*/


bool ScriptConnectionSolver::Process() {
	Vector<ScriptLoopLoader*>	inputs;
	Vector<ScriptLoopLoader*>	outputs;
	
	is_missing_input = false;
	is_missing_output = false;
	
	for (ScriptLoopLoader* ll : loops) {
		if (ll->IsStatus(ScriptStatus::INPUT_IS_WAITING))
			inputs.Add(ll);
		if (ll->IsStatus(ScriptStatus::OUTPUT_IS_WAITING))
			outputs.Add(ll);
	}
	
	if (inputs.IsEmpty() && outputs.IsEmpty()) {
		SetError("Internal error. No any waiting sidechannel io exists.");
		return false;
	}
	
	if (inputs.IsEmpty()) {
		SetError("No input side-ports");
		is_missing_input = true;
		return false;
	}
	
	if (outputs.IsEmpty()) {
		SetError("No output side-ports");
		is_missing_output = true;
		return false;
	}
	
	Vector<ScriptLoopLoader*> retry_list;
	
	int accepted_count = 0;
	for (ScriptLoopLoader* in : inputs) {
		ScriptLoopLoader* accepted_out = 0;
		Script::ActionPlanner::State* accepted_in_node = 0;
		Script::ActionPlanner::State* accepted_out_node = 0;
		int accepted_out_count = 0;
		bool accepted_all_multi = true;
		for (ScriptLoopLoader* out : outputs) {
			if (!in->IsFailed() &&
				!out->IsFailed()) {
				SideStatus s = in->AcceptOutput(*out, accepted_in_node, accepted_out_node);
				if (s == SIDE_ACCEPTED || s == SIDE_ACCEPTED_MULTI) {
					accepted_out_count++;
					accepted_out = out;
					if (s != SIDE_ACCEPTED_MULTI)
						accepted_all_multi = false;
				}
			}
		}
		if (!accepted_all_multi && accepted_out_count > 1) {
			SetError("Input loop " + IntStr(in->GetId()) + " can accept multiple outputs");
			return false;
		}
		if (accepted_out_count == 0) {
			SetError("Input loop " + IntStr(in->GetId()) + " cannot accept any output");
			is_missing_output = true;
			continue;
		}
		
		int conn_id = tmp_side_id_counter++;
		accepted_in_node->last->SetSideInId(conn_id);
		accepted_out_node->last->SetSideOutId(conn_id);
		
		LOG("Loop " << in->GetId() << " accepted loop " << accepted_out->GetId() << " with id " << conn_id);
		
		in				->AddSideConnectionSegment(accepted_in_node,	accepted_out,	accepted_out_node);
		accepted_out	->AddSideConnectionSegment(accepted_out_node,	in,				accepted_in_node);
		
		retry_list.Add(in);
		retry_list.Add(accepted_out);
		
		++accepted_count;
	}
	
	for (ScriptLoopLoader* ll : retry_list)
		ll->SetStatusRetry();
	
	return accepted_count > 0;
}

NAMESPACE_SERIAL_END

#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


int EonLoader::loop_counter = 0;




bool EonLoader::Initialize() {
	def_ws.SetActionPlanner(def_planner);
	
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
	RTLOG("EonLoader::Load: Loading \"" << filepath << "\"");
	
	Eon::Parser p;
	if (!p.Parse(content, filepath)) {
		RTLOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	MemSwap(p.GetResult(), root);
	
	if (!LoadCompilationUnit(root))
		return false;
	
	return true;
}

bool EonLoader::LoadCompilationUnit(Eon::CompilationUnit& cunit) {
	return LoadGlobalScope(cunit.list);
}
/*
void EonLoader::EnterScope() {
	EonScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	EonScope& scope = scopes.Add();
	
	scope.SetCurrentState(def_ws);
	
	if (parent) {
		scope.current_state = parent->current_state;
	}
}

bool EonLoader::LeaveScope() {
	EonScope* parent = scopes.IsFilled() ? &scopes.Top() : 0;
	EonScope& scope = scopes.Top();
	
	if (scopes.GetCount() >= 2) {
		EonScope& par = scopes.At(scopes.GetCount()-2);
		const Eon::WorldState& src_ws = scope.current_state;
		Eon::WorldState& dst_ws = par.current_state;
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
bool EonLoader::LoadGlobalScope(Eon::GlobalScope& glob) {
	//EnterScope();
	//scopes.Top().glob = &glob;
	scopes.Add(&glob);
	
	loader = new EonSystemLoader(*this, 0, glob);
	
	int dbg_i = 0;
	while (!loader->IsFailed() && !loader->IsReady()) {
		DUMP(dbg_i);
		loader->Dump();
		
		loader->Forward();
		++dbg_i;
	}
	
	
	scopes.Remove(scopes.GetCount()-1);
	TODO // ret... chk err
	
	/*Vector<Vector<Eon::ChainDefinition*>> mach_chains;
	for (Eon::Machine& mach : glob.machs)
		GetChainsDeepestFirst(mach, mach_chains.Add());
	int iter = -1;
	while (1) {
		++iter;
		bool found_connection = false;
		
		// Check if all connections are satisfied and break
		if (iter > 0) {
			TODO
			
			// Clear potential errors
			TODO
			
			// Clear connection collection
			TODO
		}
		
		// Inside loops
		for (Vector<Eon::ChainDefinition*>& chains : mach_chains)
			for (Eon::ChainDefinition* chain : chains)
				SolveInsideLoops(*chain);
		if (IsNewConnections()) // start again, if this phase made new connections
			continue;
			
		// Inside chains
		for (Vector<Eon::ChainDefinition*>& chains : mach_chains)
			for (Eon::ChainDefinition* chain : chains)
			SolveInsideChain(*chain);
		if (IsNewConnections())
			continue;
		
		// Between chains
		for (Vector<Eon::ChainDefinition*>& chains : mach_chains)
			SolveBetweenChains(chains);
		if (IsNewConnections())
			continue;
		
		// Between machines
		SolveBetweenMachines(mach_chains);
		if (IsNewConnections())
			continue;
		
		// Check for potential errors, and break if not any
		TODO
	}
	
	
	for (EonLoopLoader& loop : loops) {
		if (!loop.Load()) {
			scopes.RemoveLast();
			return false;
		}
	}
	
	// Link side-connections
	for (EonLoopLoader& loop0 : loops) {
		for (EonLoopLoader& loop1 : loops) {
			if (&loop0 != &loop1) {
				if (!ConnectSides(loop0, loop1)) {
					AddError("Side connecting failed");
					return false;
				}
			}
		}
	}
	
	loops.Clear();*/
	
	//return LeaveScope();
}

/*bool EonLoader::SolveLoops(Eon::ChainDefinition& def) {
	loops.Clear();
	for (Eon::LoopDefinition& loop_def : def.loops)
		loops.Add(new EonLoopLoader(loop_counter++, this, loop_def));
	if (loops.IsEmpty())
		return true;
	
	bool fail = false;
	enum {FORWARDING, CONNECTING_SIDECHANNEL};
	int mode = FORWARDING;
	int mode_count = 0;
	Vector<EonLoopLoader*> waiting_inputs, waiting_outputs;
	while(!fail) {
		if (mode == FORWARDING) {
			bool ready = true;
			bool keep_going = true;
			waiting_inputs.Clear();
			waiting_outputs.Clear();
			while (keep_going) {
				int dbg_i = 0;
				for (EonLoopLoader& loop : loops) {
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
	if (!collect_errors) {
		LOG("EonLoader: error: " + msg);
	}
	else {
		EonError& e = errs.Add();
		e.msg = msg;
	}
}

void EonLoader::AddError(EonLoopLoader* ll, String msg) {
	if (!collect_errors) {
		LOG("EonLoader: error: " + msg);
	}
	else {
		EonError& e = errs.Add();
		e.ll = ll;
		e.status = ll->GetStatus();
		e.msg = msg;
	}
}

void EonLoader::ReleaseErrorBuffer() {
	if (errs.GetCount()) {
		EonError& e = errs.Top();
		LOG("EonLoader: error: " + e.msg);
		errs.Clear();
	}
}

void EonLoader::ClearErrorBuffer() {
	for (EonError& e : errs) {
		if (e.ll && e.ll->IsFailed() && e.status >= 0)
			e.ll->SetStatus(e.status);
	}
	errs.Clear();
}

bool EonLoader::ConnectSides(EonLoopLoader& loop0, EonLoopLoader& loop1) {
	
	int dbg_i = 0;
	for (ComponentBaseRef& in : loop0.comps) {
		int in_conn = in->GetSideIn();
		if (in_conn < 0)
			continue;
		
		RTLOG("Trying to side-link id " << in_conn);
		bool found = false;
		for (ComponentBaseRef& out : loop1.comps) {
			int out_conn = out->GetSideOut();
			if (out_conn < 0)
				continue;
			
			if (in_conn == out_conn) {
				found = true;
				
				if (!out->LinkSideIn(in)) {
					AddError("Side-output refused linking to side-input");
					return false;
				}
				if (!in->LinkSideOut(out)) {
					AddError("Side-input refused linking to side-output");
					return false;
				}
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

Eon::State* EonLoader::FindState(const Eon::Id& id) {
	auto iter = scopes.rbegin();
	auto end = scopes.rend();
	for(; iter != end; --iter) {
		Eon::GlobalScope& glob = **iter;
		for (Eon::State& state : glob.states) {
			if (state.id == id) {
				return &state;
			}
		}
	}
	return NULL;
}

/*void EonLoader::SolveInsideLoops(Eon::ChainDefinition& chain) {
	TODO
}

void EonLoader::SolveInsideChain(Eon::ChainDefinition& chain) {
	TODO
}

void EonLoader::SolveBetweenChains(const Vector<Eon::ChainDefinition*>& chains) {
	TODO
}

void EonLoader::SolveBetweenMachines(const Vector<Vector<Eon::ChainDefinition*>>& machs) {
	TODO
}

bool EonLoader::IsNewConnections() const {
	TODO
}

void EonLoader::GetChainsDeepestFirst(Eon::Machine& mach, Vector<Eon::ChainDefinition*>& chains) {
	LinkedList<Eon::ChainDefinition*> unvisited;
	
	for (Eon::ChainDefinition& ch : mach.chains)
		unvisited.Add(&ch);
	
	while (unvisited.GetCount()) {
		Eon::ChainDefinition* p = unvisited.First();
		unvisited.RemoveFirst();
		
		chains.Add(p);
		p->GetSubChainPointers(unvisited);
	}
	
	Reverse(chains);
}*/


bool EonConnectionSolver::Process() {
	Vector<EonLoopLoader*>	waiting_inputs;
	Vector<EonLoopLoader*>	waiting_outputs;
	
	is_missing_input = false;
	is_missing_output = false;
	
	for (EonLoopLoader* ll : loops) {
		if (ll->IsStatus(EonStatus::WAITING_SIDE_INPUT_LOOP))
			waiting_inputs.Add(ll);
		if (ll->IsStatus(EonStatus::WAITING_SIDE_OUTPUT_LOOP))
			waiting_outputs.Add(ll);
	}
	
	if (waiting_inputs.IsEmpty() && waiting_outputs.IsEmpty()) {
		SetError("Internal error. No waitin sidechannel io.");
		return false;
	}
	
	if (waiting_inputs.IsEmpty()) {
		SetError("No input side-ports");
		is_missing_input = true;
		return false;
	}
	
	if (waiting_outputs.IsEmpty()) {
		SetError("No output side-ports");
		is_missing_output = true;
		return false;
	}
	
	Vector<EonLoopLoader*> retry_list;
	
	int accepted_count = 0;
	for (EonLoopLoader* in : waiting_inputs) {
		EonLoopLoader* accepted_out = 0;
		Eon::ActionPlanner::State* accepted_in_node = 0;
		Eon::ActionPlanner::State* accepted_out_node = 0;
		int accepted_out_count = 0;
		bool accepted_all_multi = true;
		for (EonLoopLoader* out : waiting_outputs) {
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
			is_missing_input = true;
			return false;
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
	
	for (EonLoopLoader* ll : retry_list)
		ll->SetStatusRetry();
	
	ASSERT(accepted_count > 0);
	
	return true;
}

NAMESPACE_ECS_END

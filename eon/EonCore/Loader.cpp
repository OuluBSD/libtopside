#include "EonCore.h"


NAMESPACE_EON_BEGIN



String GetStatusLine(int indent, Status status, String extra_str) {
	String s;
	s.Cat('\t', indent);
	const char* t = GetStatusString(status);
	s << "-> " << t;
	if (extra_str.GetCount())
		s << " (" << extra_str << ")";
	s.Cat('\n');
	return s;
}





int Loader::loop_counter = 0;




bool Loader::Initialize() {
	def_ws.SetActionPlanner(def_planner);
	
	es = GetMachine().TryGet<EntityStore>();
	if (!es) {
		LOG("Loader requires EntityStore present in machine");
		return false;
	}
	
	if (!DoPostLoad())
		return false;
	
	RTLOG("Loader::Initialize success!");
	return true;
}

bool Loader::DoPostLoad() {
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

void Loader::Start() {
	
}

void Loader::Update(double dt) {
	
	DoPostLoad();
	
}

void Loader::Stop() {
	
}

void Loader::Uninitialize() {
	
}

bool Loader::LoadFile(String path) {
	if (!FileExists(path)) {
		LOG("Could not find EON file");
		return false;
	}
	String eon = TS::LoadFile(path);
	return Load(eon, path);
}

bool TestParseEonCode(String content) {
	Parser p;
	if (!p.Parse(content, "<file>")) {
		LOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	return true;
}

bool Loader::Load(String content, String filepath) {
	RTLOG("Loader::Load: Loading \"" << filepath << "\"");
	
	Parser p;
	if (!p.Parse(content, filepath)) {
		RTLOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	MemSwap(p.GetResult(), root);
	
	if (!LoadCompilationUnit(root)) {
		LOG("error dump:"); loader->Dump();
		DumpErrors();
		
		Cleanup();
		return false;
	}
	
	if (!ImplementPlan()) {
		DumpErrors();
		
		Cleanup();
		return false;
	}
	
	Cleanup();
	return true;
}

void Loader::Cleanup() {
	loader.Clear();
}

void Loader::DumpErrors() {
	Vector<LoopLoader*> loops;
	loader->GetLoops(loops);
	for (LoopLoader* ll : loops) {
		if (ll->GetStatus() == Status::FAILED) {
			LOG("LoopLoader: error: " << ll->GetErrorString());
		}
	}
}

bool Loader::ImplementPlan() {
	Vector<LoopLoader*> loops;
	loader->GetLoops(loops);
	for (LoopLoader* ll : loops) {
		if (!ll->Load())
			return false;
	}
	
	for (LoopLoader* loop0 : loops) {
		for (LoopLoader* loop1 : loops) {
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

bool Loader::LoadCompilationUnit(CompilationUnit& cunit) {
	return LoadGlobalScope(cunit.list);
}

bool Loader::LoadGlobalScope(GlobalScope& glob) {
	//EnterScope();
	//scopes.Top().glob = &glob;
	scopes.Add(&glob);
	
	loader = new SystemLoader(*this, 0, glob);
	
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

EntityRef Loader::ResolveEntity(IdPath& id) {
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

void Loader::AddError(String msg) {
	if (!collect_errors) {
		LOG("Loader: error: " + msg);
	}
	else {
		Error& e = errs.Add();
		e.msg = msg;
	}
}

void Loader::AddError(LoopLoader* ll, String msg) {
	if (!collect_errors) {
		LOG("Loader: error: " + msg);
	}
	else {
		Error& e = errs.Add();
		e.ll = ll;
		e.status = ll->GetStatus();
		e.msg = msg;
	}
}

void Loader::ReleaseErrorBuffer() {
	if (errs.GetCount()) {
		Error& e = errs.Top();
		LOG("Loader: error: " + e.msg);
		errs.Clear();
	}
}

void Loader::ClearErrorBuffer() {
	for (Error& e : errs) {
		if (e.ll && e.ll->IsFailed() && e.status >= 0)
			e.ll->SetStatus(e.status);
	}
	errs.Clear();
}

bool Loader::ConnectSides(LoopLoader& loop0, LoopLoader& loop1) {
	
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

State* Loader::FindState(const IdPath& id) {
	auto iter = scopes.rbegin();
	auto end = scopes.rend();
	for(; iter != end; --iter) {
		GlobalScope& glob = **iter;
		for (State& state : glob.states) {
			if (state.id == id) {
				return &state;
			}
		}
	}
	return NULL;
}

bool ConnectionSolver::Process() {
	Vector<LoopLoader*>	inputs;
	Vector<LoopLoader*>	outputs;
	
	is_missing_input = false;
	is_missing_output = false;
	
	for (LoopLoader* ll : loops) {
		if (ll->IsStatus(Status::INPUT_IS_WAITING))
			inputs.Add(ll);
		if (ll->IsStatus(Status::OUTPUT_IS_WAITING))
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
	
	Vector<LoopLoader*> retry_list;
	
	int accepted_count = 0;
	for (LoopLoader* in : inputs) {
		LoopLoader* accepted_out = 0;
		ActionPlanner::State* accepted_in_node = 0;
		ActionPlanner::State* accepted_out_node = 0;
		int accepted_out_count = 0;
		bool accepted_all_multi = true;
		for (LoopLoader* out : outputs) {
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
	
	for (LoopLoader* ll : retry_list)
		ll->SetStatusRetry();
	
	return accepted_count > 0;
}



NAMESPACE_EON_END

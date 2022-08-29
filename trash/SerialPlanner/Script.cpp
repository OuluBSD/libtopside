#include "SerialScript.h"


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

int GetTotalSegmentCount(Vector<ScriptLoopLoader*>& v) {
	int count = 0;
	for (ScriptLoopLoader* l : v)
		count += l->GetSegmentCount();
	return count;
}





int ScriptLoader::loop_counter = 0;



ScriptLoader::~ScriptLoader() {
	//LOG("~ScriptLoader");
}

bool ScriptLoader::Initialize() {
	Machine& mach = GetMachine();
	
	def_ws.SetActionPlanner(def_planner);
	
	es = mach.Find<LoopStore>();
	if (!es) {
		LOG("ScriptLoader requires LoopStore present in machine");
		return false;
	}
	
	ss = mach.Find<SpaceStore>();
	if (!ss) {
		LOG("ScriptLoader requires SpaceStore present in machine");
		return false;
	}
	
	if (!DoPostLoad())
		return false;
	
	RTLOG("ScriptLoader::Initialize success!");
	return true;
}

bool ScriptLoader::DoPostLoad() {
	bool success = true;
	
	while (!post_load_file.IsEmpty()) {
		String path = post_load_file[0];
		post_load_file.Remove(0);
		
		if (!LoadFile(path))
			success = false;
	}
	
	while (!post_load_string.IsEmpty()) {
		String s = post_load_string[0];
		post_load_string.Remove(0);
		
		if (!Load(s, "input"))
			success = false;
	}
	
	return success;
}

void ScriptLoader::Start() {
	
}

void ScriptLoader::Update(double dt) {
	
	if (!DoPostLoad()) {
		GetMachine().SetNotRunning();
	}
	
}

void ScriptLoader::Stop() {
	
}

void ScriptLoader::Uninitialize() {
	es.Clear();
	ss.Clear();
	loader.Clear();
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

bool ScriptLoader::Load(const String& content, const String& filepath) {
	RTLOG("ScriptLoader::Load: Loading \"" << filepath << "\"");
	
	if (HAVE_SCRIPTLOADER_MACHVER) {
		Machine& mach = GetMachine();
		MachineVerifier* mver = mach.GetMachineVerifier();
		if (mver)
			mver->Attach(*this);
	}
	
	WhenEnterScriptLoad(*this);
	
	Script::Parser p;
	if (!p.Parse(content, filepath)) {
		RTLOG(GetLineNumStr(content, 1));
		WhenLeaveScriptLoad();
		return false;
	}
	//p.Dump();
	root = p.DetachResult();
	
	if (!LoadCompilationUnit(*root)) {
		LOG("error dump:"); loader->Dump();
		DumpErrors();
		
		Cleanup();
		WhenLeaveScriptLoad();
		return false;
	}
	
	if (!ImplementScript()) {
		DumpErrors();
		
		Cleanup();
		WhenLeaveScriptLoad();
		return false;
	}
	
	Cleanup();
	WhenLeaveScriptLoad();
	
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
	
	RTLOG("ScriptLoader::ImplementScript: load drivers");
	Vector<ScriptDriverLoader*> drivers;
	loader->GetDrivers(drivers);
	for (ScriptDriverLoader* dl: drivers) {
		if (!dl->Load())
			return false;
	}
	
	RTLOG("ScriptLoader::ImplementScript: load states");
	Vector<ScriptStateLoader*> states;
	loader->GetStates(states);
	for (ScriptStateLoader* dl: states) {
		if (!dl->Load())
			return false;
	}
	
	RTLOG("ScriptLoader::ImplementScript: load loops");
	Vector<ScriptLoopLoader*> loops;
	loader->GetLoops(loops);
	for (ScriptLoopLoader* ll : loops) {
		if (!ll->Load())
			return false;
	}
	
	RTLOG("ScriptLoader::ImplementScript: connect sides");
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
	
	
	
	RTLOG("ScriptLoader::ImplementScript: driver post initialize");
	for (ScriptDriverLoader* dl: drivers) {
		if (!dl->PostInitialize())
			return false;
	}
	
	RTLOG("ScriptLoader::ImplementScript: loop post initialize");
	for (ScriptLoopLoader* ll : loops) {
		if (!ll->PostInitialize())
			return false;
	}
	
	
	
	RTLOG("ScriptLoader::ImplementScript: driver start");
	for (ScriptDriverLoader* dl: drivers) {
		if (!dl->Start())
			return false;
	}
	
	RTLOG("ScriptLoader::ImplementScript: loop start");
	for (ScriptLoopLoader* ll : loops) {
		if (!ll->Start())
			return false;
	}
	
	return true;
}

bool ScriptLoader::LoadCompilationUnit(Script::CompilationUnit& cunit) {
	return LoadGlobalScope(cunit.list);
}

bool ScriptLoader::LoadGlobalScope(Script::GlobalScope& glob) {
	//EnterScope();
	//scopes.Top().glob = &glob;
	scopes.Add(&glob);
	
	loader = new ScriptSystemLoader(*this, 0, glob);
	
	int dbg_i = 0;
	while (!loader->IsFailed() && !loader->IsReady()) {
		DUMP(dbg_i); loader->Dump();
		
		loader->Forward();
		++dbg_i;
		
		ASSERT_(dbg_i < 100, "Something probably broke");
	}
	
	scopes.Remove(scopes.GetCount()-1);
	
	if (loader->IsReady()) {
		if (!loader->LoadEcs()) {
			String e = "ecs loading failed: " + loader->GetErrorString();
			AddError(e);
			//loader->SetError(e);
			return false;
		}
	}
	
	return loader->IsReady();
}

LoopRef ScriptLoader::ResolveLoop(Script::Id& id) {
	ASSERT(es);
	LoopRef l0;
	LoopRef l1 = es->GetRoot();
	SpaceRef s0;
	SpaceRef s1 = ss->GetRoot();
	int i = 0, count = id.parts.GetCount();
	
	for (const String& part : id.parts) {
		if (i++ == count - 1) {
			l0 = l1->GetAddEmpty(part);
			s0 = s1->GetAddEmpty(part);
			l0->space = &*s0;
			s0->loop = &*l0;
		}
		else {
			l1 = l1->GetAddLoop(part);
			s1 = s1->GetAddSpace(part);
			l1->space = &*s1;
			s1->loop = &*l1;
		}
	}
	
	ASSERT(l0->GetSpace());
	return l0;
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
			e.ll->SetStatus((ScriptStatus)e.status);
	}
	errs.Clear();
}

bool ScriptLoader::ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1) {
	
	int dbg_i = 0;
	for (AtomBaseRef& sink : loop0.atoms) {
		LinkBaseRef sink_link = sink->GetLink()->AsRefT();
		const IfaceConnTuple& sink_iface = sink->GetInterface();
		for (int sink_ch = 1; sink_ch < sink_iface.type.iface.sink.count; sink_ch++) {
			const IfaceConnLink& sink_conn = sink_iface.sink[sink_ch];
			RTLOG("ScriptLoader::ConnectSides:	sink ch #" << sink_ch << " " << sink_conn.ToString());
			ASSERT(sink_conn.conn >= 0 || sink_iface.type.IsSinkChannelOptional(sink_ch));
			if (sink_conn.conn < 0 && sink_iface.type.IsSinkChannelOptional(sink_ch))
				continue;
			bool found = false;
			for (AtomBaseRef& src : loop1.atoms) {
				LinkBaseRef src_link = src->GetLink()->AsRefT();
				const IfaceConnTuple& src_iface = src->GetInterface();
				for (int src_ch = 1; src_ch < src_iface.type.iface.src.count; src_ch++) {
					const IfaceConnLink& src_conn = src_iface.src[src_ch];
					RTLOG("ScriptLoader::ConnectSides:		src ch #" << src_ch << " " << src_conn.ToString());
					ASSERT(src_conn.conn >= 0 || src_iface.type.IsSourceChannelOptional(src_ch));
					if (src_conn.conn < 0 && src_iface.type.IsSourceChannelOptional(src_ch))
						continue;
					if (sink_conn.conn == src_conn.conn) {
						RTLOG("ScriptLoader::ConnectSides:			linking side-link src ch #" << src_ch << " " << src_conn.ToString() << " to sink ch #" << sink_ch << " " << sink_conn.ToString());
						found = true;
						
						int src_ch_i = src_conn.local;
						int sink_ch_i = sink_conn.local;
						ASSERT(src_conn.other == sink_conn.local);
						ASSERT(sink_conn.other == src_conn.local);
						
						if (!src_link->LinkSideSink(sink_link, src_ch_i, sink_ch_i)) {
							AddError("Side-source refused linking to side-src");
							return false;
						}
						if (!sink_link->LinkSideSource(src_link, sink_ch_i, src_ch_i)) {
							AddError("Side-src refused linking to side-source");
							return false;
						}
						
						LOG(src->ToString() + "(" << src_ch_i << ") side-linked to " + sink->ToString() + "(" << sink_ch_i << ")");
						
						
						loop0.UpdateLoopLimits();
						loop1.UpdateLoopLimits();
						break;
					}
				}
			}
			
			/* Not error anymore:
			if (!found) {
				RTLOG("ScriptLoader::ConnectSides:		error: could not link side-link: " << sink_conn.ToString());
				AddError("Could not link connection id " + IntStr(in_conn));
				return false;
			}*/
			
			dbg_i++;
		}
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



#if 0
{
	Vector<ScriptLoopLoader*>	waiting_sources;
	Vector<ScriptLoopLoader*>	waiting_sinks;
	
	is_waiting_source = false;
	is_waiting_sink = false;
	
	for (ScriptLoopLoader* ll : loops) {
		if (ll->IsStatus(ScriptStatus::SOURCE_IS_WAITING))
			waiting_sources.Add(ll);
		if (ll->IsStatus(ScriptStatus::SINK_IS_WAITING))
			waiting_sinks.Add(ll);
	}
	
	if (waiting_sources.IsEmpty() && waiting_sinks.IsEmpty()) {
		SetError("Internal error. No any waiting sidechannel io exists.");
		return false;
	}
	
	if (waiting_sources.IsEmpty()) {
		SetError("No side-sources");
		is_waiting_sink = true; // because waiting_sinks.count > 0
		return false;
	}
	
	if (waiting_sinks.IsEmpty()) {
		SetError("No side-sinks");
		is_waiting_source = true; // because waiting_sources.count > 0
		return false;
	}
	
	Vector<ScriptLoopLoader*> retry_list;
	
	int accepted_count = 0;
	for (ScriptLoopLoader* src : waiting_sources) {
		ScriptLoopLoader* accepted_sink = 0;
		Script::ActionPlanner::State* accepted_src_node = 0;
		Script::ActionPlanner::State* accepted_sink_node = 0;
		int accepted_sink_count = 0;
		bool accepted_all_multi = true;
		int dbg_i = 0;
		for (ScriptLoopLoader* sink : waiting_sinks) {
			if (!src->IsFailed() &&
				!sink->IsFailed()) {
				RTLOG("ScriptConnectionSolver::Process: #" << dbg_i << " check fail state: src " << HexStr(src) << " against sink " << HexStr(sink) << ": passed");
				SideStatus s = src->AcceptSink(*sink, accepted_src_node, accepted_sink_node);
				if (s == SIDE_ACCEPTED || s == SIDE_ACCEPTED_MULTI) {
					ASSERT(accepted_src_node && accepted_sink_node);
					accepted_sink_count++;
					accepted_sink = sink;
					if (s != SIDE_ACCEPTED_MULTI)
						accepted_all_multi = false;
				}
			}
			else {
				RTLOG("ScriptConnectionSolver::Process: #" << dbg_i << " check fail state: src " << HexStr(src) << " against sink " << HexStr(sink) << ": failed");
			}
			dbg_i++;
		}
		if (!accepted_all_multi && accepted_sink_count > 1) {
			SetError("source loop " + IntStr(src->GetId()) + " cannot accept multiple sinks");
			return false;
		}
		if (accepted_sink_count == 0) {
			SetError("source loop " + IntStr(src->GetId()) + " cannot accept any sink");
			is_waiting_sink = true;
			continue;
		}
		
		src->RealizeConnections(accepted_src_node);
		accepted_sink->RealizeConnections(accepted_sink_node);
		
		ASSERT(accepted_sink);
		AtomTypeCls src_type = accepted_src_node->last->GetWorldState().GetAtom();
		AtomTypeCls sink_type = accepted_sink_node->last->GetWorldState().GetAtom();
		src->SetSideSourceConnected(src_type, accepted_src_node->ch_i, accepted_sink);
		accepted_sink->SetSideSinkConnected(sink_type, accepted_sink_node->ch_i, src);
		
		int conn_id = tmp_side_id_counter++;
		
		accepted_src_node->last->GetInterface().Realize(src_type);
		accepted_src_node->last->GetInterface().SetSource(conn_id,		accepted_src_node->ch_i,	accepted_sink_node->ch_i);
		
		accepted_sink_node->last->GetInterface().Realize(sink_type);
		accepted_sink_node->last->GetInterface().SetSink(conn_id,		accepted_sink_node->ch_i,	accepted_src_node->ch_i);
		
		LOG("Loop src " << src->GetId() << " ch " << accepted_src_node->ch_i << " accepted loop sink "
			<< accepted_sink->GetId() << " ch " << accepted_sink_node->ch_i << " with id " << conn_id);
		
		
		if (src->IsTopSidesConnected()) {
			LOG("Loop " << src->GetId() << " all sides connected");
			src->AddSideConnectionSegment(accepted_src_node, accepted_sink, accepted_sink_node);
			retry_list.Add(src);
		}
		
		if (accepted_sink->IsTopSidesConnected()) {
			LOG("Loop " << accepted_sink->GetId() << " all sides connected");
			accepted_sink->AddSideConnectionSegment(accepted_sink_node,	src, accepted_src_node);
			retry_list.Add(accepted_sink);
		}
		
		++accepted_count;
	}
	
	for (ScriptLoopLoader* ll : retry_list)
		ll->SetStatusRetry();
	
	return accepted_count > 0;
}
#endif


NAMESPACE_SERIAL_END


#include "Internal.h"

NAMESPACE_SERIAL_BEGIN

#if 0

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

#endif


namespace Script {


String Id::ToString() const {
	String s;
	for(String& part : parts) {
		if (!s.IsEmpty())
			s << ".";
		s << part;
	}
	return s;
}


}



int ScriptLoader::loop_counter = 0;


ScriptLoader::ScriptLoader(Machine& m) :
	SP(m),
	ErrorSource("ScriptLoader") {
	
}

ScriptLoader::~ScriptLoader() {
	//LOG("~ScriptLoader");
}

void ScriptLoader::LogMessage(ProcMsg msg) {
	LOG(msg.ToString());
}

bool ScriptLoader::Initialize() {
	Machine& mach = GetMachine();
	
	if (!WhenMessage)
		WhenMessage << THISBACK(LogMessage);
	
	//def_ws.SetActionPlanner(def_planner);
	
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

/*bool TestParseScriptCode(String content) {
	Script::Parser p;
	if (!p.Parse(content, "<file>")) {
		LOG(GetLineNumStr(content, 1));
		return false;
	}
	p.Dump();
	return true;
}*/

bool ScriptLoader::Load(const String& content, const String& filepath) {
	RTLOG("ScriptLoader::Load: Loading \"" << filepath << "\"");
	
	/*if (HAVE_SCRIPTLOADER_MACHVER) {
		Machine& mach = GetMachine();
		MachineVerifier* mver = mach.GetMachineVerifier();
		if (mver)
			mver->Attach(*this);
	}*/
	
	WhenEnterScriptLoad(*this);
	
	Compiler c;
	AstNode* root = c.CompileAst(content, filepath);
	if (!root) {
		RTLOG(GetLineNumStr(content, 1));
		WhenLeaveScriptLoad();
		return false;
	}
	//p.Dump();
	
	if (!LoadCompilationUnit(root)) {
		LOG("error dump:");
		if (loader) loader->Dump();
		//DumpErrors();
		
		Cleanup();
		WhenLeaveScriptLoad();
		return false;
	}
	
	if (!ImplementScript()) {
		//DumpErrors();
		
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

/*void ScriptLoader::DumpErrors() {
	Vector<ScriptLoopLoader*> loops;
	loader->GetLoops(loops);
	for (ScriptLoopLoader* ll : loops) {
		if (ll->GetStatus() == ScriptStatus::FAILED) {
			LOG("ScriptLoopLoader: error: " << ll->GetErrorString());
		}
	}
}*/

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
					AddError(loop0->def.loc, "Side connecting failed");
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

bool ScriptLoader::GetPathId(Script::Id& script_id, AstNode* from, AstNode* to) {
	Vector<AstNode*> path;
	
	AstNode* iter = to;
	while (iter && iter != from) {
		if (iter->src == SEMT_IDPART || iter == to) {
			path.Add(iter);
		}
		iter = iter->GetSubOwner();
	}
	if (path.IsEmpty()) {
		AddError(to->loc, "internal error: empty path");
		return false;
	}
	//String path_str;
	for (int i = path.GetCount()-1; i >= 0; i--) {
		AstNode* id = path[i];
		//if (!path_str.IsEmpty())
		//	path_str.Cat('.');
		ASSERT(id->name.GetCount());
		//path_str.Cat(id->name);
		script_id.parts.Add(id->name);
	}
	//DUMP(path_str);
	
	return true;
}

bool ScriptLoader::LoadCompilationUnit(AstNode* root) {
	loader.Clear();
	
	if (!LoadGlobalScope(cunit.glob, root))
		return false;
	
	loader = new ScriptSystemLoader(*this, 0, cunit.glob);
	
	return true;
}

bool ScriptLoader::LoadGlobalScope(Script::GlobalScope& def, AstNode* n) {
	ASSERT(n);
	if (!n) return false;
	
	//LOG(n->GetTreeString(0));
	
	Vector<AstNode*> items;
	n->FindAllNonIdEndpoints(items, (SemanticType)(SEMT_ECS_ANY | SEMT_MACH_ANY));
	
	if (items.IsEmpty()) {
		AddError(def.loc, "empty node");
		return false;
	}
	
	bool has_machine = false;
	for (AstNode* item : items) {
		if (item->src == SEMT_MACHINE) {
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			if (!LoadMachine(def.machs.Add(), block))
				return false;
			has_machine = true;
		}
		else if (item->src == SEMT_ENGINE) {
			TODO
		}
	}
	
	if (!has_machine) {
		Script::MachineDefinition& mach = def.machs.Add();
		return LoadMachine(mach, n);
	}
	
	return true;
}

bool ScriptLoader::LoadMachine(Script::MachineDefinition& def, AstNode* n) {
	Vector<AstNode*> items;
	n->FindAllNonIdEndpoints(items, (SemanticType)(SEMT_ECS_ANY | SEMT_MACH_ANY));
	
	if (items.IsEmpty()) {
		AddError(def.loc, "empty node");
		return false;
	}
	
	bool has_chain = false;
	for (AstNode* item : items) {
		if (item->src == SEMT_CHAIN) {
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			Vector<AstNode*> items;
			block->FindAllNonIdEndpoints(items, SEMT_CHAIN);
			if (items.IsEmpty()) {
				if (!LoadChain(def.chains.Add(), block))
					return false;
			} else {
				if (!LoadTopChain(def.chains.Add(), block))
					return false;
			}
			has_chain = true;
		}
		else if (item->src == SEMT_DRIVER) {
			TODO
		}
	}
	
	if (!has_chain) {
		Script::ChainDefinition& chain = def.chains.Add();
		return LoadChain(chain, n);
	}
	
	return true;
}

bool ScriptLoader::LoadEngine(Script::EngineDefinition& def, AstNode* n) {
	
	TODO
	/*
	EcsSysDefinition
	PoolDefinition
	*/
}

bool ScriptLoader::LoadDriver(Script::DriverDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadTopChain(Script::ChainDefinition& def, AstNode* n) {
	
	TODO
	/*
	ScriptLoopLoader
	ScriptStateLoader
	*/
}

bool ScriptLoader::LoadEcsSystem(Script::EcsSysDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadPool(Script::PoolDefinition& def, AstNode* n) {
	
	TODO
	/*
	ScriptEntityLoader
	ScriptPoolLoader
	*/
}

bool ScriptLoader::LoadState(Script::StateDeclaration& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadEntity(Script::EntityDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadChain(Script::ChainDefinition& chain, AstNode* root) {
	const auto& map = Parallel::Factory::AtomDataMap();
	Vector<AstNode*> loops, states, atoms, stmts, conns;
	
	//LOG(root->GetTreeString(0));
	
	root->FindAll(loops, SEMT_LOOP);
	root->FindAll(states, SEMT_STATE);
	
	//DUMP(loops.GetCount());
	
	chain.Clear();
	
	for (AstNode* loop : loops) {
		Script::LoopDefinition& def = chain.loops.Add();
		def.loc = loop->loc;
		
		if (!GetPathId(def.id, root, loop))
			return false;
		DUMP(def.id);
		
		//LOG(loop->GetTreeString(0));
		
		AstNode* stmt_block = loop->Find(SEMT_STATEMENT_BLOCK);
		if (!stmt_block) {
			AddError(loop->loc, "loop has no statement-block");
			return false;
		}
		
		atoms.SetCount(0);
		stmt_block->FindAll(atoms, SEMT_ATOM);
		if (atoms.IsEmpty()) {
			AddError(loop->loc, "no atoms in statement-block");
			return false;
		}
		
		for (AstNode* atom : atoms) {
			Script::AtomDefinition& atom_def = def.atoms.Add();
			
			if (!GetPathId(atom_def.id, loop, atom))
				return false;
			
			String loop_action = atom_def.id.ToString();
			const Parallel::Factory::AtomData* found_atom = 0;
			for (const Parallel::Factory::AtomData& atom_data : map.GetValues()) {
				bool match = false;
				for (const String& action : atom_data.actions) {
					if (action == loop_action) {
						match = true;
						break;
					}
				}
				if (!match)
					continue;
				found_atom = &atom_data;
			}
			
			if (!found_atom) {
				AddError(atom->loc, "could not find atom for '" + loop_action + "'");
				return false;
			}
			
			AtomTypeCls type = found_atom->cls;
			LinkTypeCls link = found_atom->link_type;
			ASSERT(type.IsValid());
			
			atom_def.iface.Realize(type);
			ASSERT(atom_def.iface.sink.GetCount());
			ASSERT(atom_def.iface.src.GetCount());
			atom_def.link = link;
			
			conns.SetCount(0);
			atom->FindAllStmt(conns, STMT_ATOM_CONNECTOR);
			if (!conns.IsEmpty()) {
				TODO
			}
			
			//DUMP(atom_def.id);
			
			stmts.SetCount(0);
			atom->FindAll(stmts, SEMT_STATEMENT);
			for (AstNode* stmt : stmts) {
				bool succ = false;
				if (stmt->stmt == STMT_EXPR) {
					//LOG(stmt->GetTreeString(0));
					if (stmt->rval) {
						if (stmt->rval->src == SEMT_EXPR) {
							if (stmt->rval->op == OP_ASSIGN) {
								AstNode* key = stmt->rval->arg[0];
								AstNode* value = stmt->rval->arg[1];
								//LOG(key->GetTreeString(0));
								//LOG(value->GetTreeString(0));
								if (key->src == SEMT_UNRESOLVED && key->str.GetCount()) {
									String key_str = key->str;
									if (value->src == SEMT_CONSTANT) {
										Object val_obj;
										value->CopyToObject(val_obj);
										atom_def.Set(key_str, val_obj);
										succ = true;
									}
								}
							}
						}
					}
				}
				if (!succ) {
					AddError(stmt->loc, "could not resolve statement in atom");
					return false;
				}
			}
		}
		
	}
	
	for (Script::LoopDefinition& src_loop : chain.loops) {
		for (Script::AtomDefinition& src_atom : src_loop.atoms) {
			int src_count = src_atom.iface.type.iface.src.GetCount();
			
			for(int src_i = 1; src_i < src_count; src_i++) {
				const ValDevTuple::Channel& src_ch = src_atom.iface.type.iface.src[src_i];
				const ValDevCls& src_vd = src_ch.vd;
				bool src_is_opt = src_ch.is_opt;
				IfaceConnLink& src_conn = src_atom.iface.src[src_i];
				
				bool connected = false;
				
				ASSERT(src_conn.conn < 0);
				
				for (Script::LoopDefinition& sink_loop : chain.loops) {
					if (&src_loop == &sink_loop)
						continue;
					
					for (Script::AtomDefinition& sink_atom : sink_loop.atoms) {
						int sink_count = sink_atom.iface.type.iface.sink.GetCount();
						
						for(int sink_i = 1; sink_i < sink_count; sink_i++) {
							const ValDevTuple::Channel& sink_ch = sink_atom.iface.type.iface.sink[sink_i];
							const ValDevCls& sink_vd = sink_ch.vd;
							bool sink_is_opt = sink_ch.is_opt;
							IfaceConnLink& sink_conn = sink_atom.iface.sink[sink_i];
							
							if (sink_conn.conn < 0 && src_vd == sink_vd) {
								int conn_id = GetLoader().NewConnectionId();
								
								src_conn.conn = conn_id;
								src_conn.local = src_i;
								src_conn.other = sink_i;
								
								sink_conn.conn = conn_id;
								sink_conn.local = sink_i;
								sink_conn.other = src_i;
								
								connected = true;
								break;
							}
						}
						
						if (connected)
							break;
					}
					
					if (connected)
						break;
				}
				
				if (!connected && !src_is_opt) {
					AddError(src_atom.loc, "could not connect source to any sink");
					return false;
				}
			}
		}
	}
	
	for (AstNode* state : states) {
		TODO
	}
	
	
	
	/*//if (loader->()) {
		LOG("TODO");
		if (!loader->LoadEcs()) {
			String e = "ecs loading failed: " + loader->GetErrorString();
			AddError(root->loc, e);
			//loader->SetError(e);
			return false;
		}
	//}
	*/
	LOG("TODO ecs, but no Load()");
	
	return true;
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

bool ScriptLoader::ConnectSides(ScriptLoopLoader& loop0, ScriptLoopLoader& loop1) {
	
	int dbg_i = 0;
	for (AtomBaseRef& sink : loop0.atoms) {
		LinkBaseRef sink_link = sink->GetLink()->AsRefT();
		const IfaceConnTuple& sink_iface = sink->GetInterface();
		for (int sink_ch = 1; sink_ch < sink_iface.type.iface.sink.GetCount(); sink_ch++) {
			const IfaceConnLink& sink_conn = sink_iface.sink[sink_ch];
			RTLOG("ScriptLoader::ConnectSides:	sink ch #" << sink_ch << " " << sink_conn.ToString());
			ASSERT(sink_conn.conn >= 0 || sink_iface.type.IsSinkChannelOptional(sink_ch));
			if (sink_conn.conn < 0 && sink_iface.type.IsSinkChannelOptional(sink_ch))
				continue;
			bool found = false;
			for (AtomBaseRef& src : loop1.atoms) {
				LinkBaseRef src_link = src->GetLink()->AsRefT();
				const IfaceConnTuple& src_iface = src->GetInterface();
				for (int src_ch = 1; src_ch < src_iface.type.iface.src.GetCount(); src_ch++) {
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
							AddError(loop0.def.loc, "Side-source refused linking to side-src");
							return false;
						}
						if (!sink_link->LinkSideSource(src_link, sink_ch_i, src_ch_i)) {
							AddError(loop1.def.loc, "Side-src refused linking to side-source");
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

/*Script::State* ScriptLoader::FindState(const Script::Id& id) {
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
}*/



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


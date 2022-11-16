#include "Internal.h"

NAMESPACE_SERIAL_BEGIN


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
	
}

void ScriptLoader::LogMessage(ProcMsg msg) {
	LOG(msg.ToString());
}

bool ScriptLoader::Initialize() {
	Machine& mach = GetMachine();
	
	if (!WhenMessage)
		WhenMessage << THISBACK(LogMessage);
	
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

bool ScriptLoader::Load(const String& content, const String& filepath) {
	RTLOG("ScriptLoader::Load: Loading \"" << filepath << "\"");
	
	WhenEnterScriptLoad(*this);
	
	Compiler c;
	AstNode* root = c.CompileAst(content, filepath);
	if (!root) {
		RTLOG(GetLineNumStr(content, 1));
		WhenLeaveScriptLoad();
		return false;
	}
	
	if (!LoadCompilationUnit(root)) {
		LOG("error dump:");
		if (loader) loader->Dump();
		
		Cleanup();
		WhenLeaveScriptLoad();
		return false;
	}
	
	if (!ImplementScript()) {
		Cleanup();
		WhenLeaveScriptLoad();
		return false;
	}
	
	
	if (!loader->LoadEcs()) {
		AddError(root->loc, "ecs loading failed: " + loader->GetErrorString());
		return false;
	}
	
	
	
	Cleanup();
	WhenLeaveScriptLoad();
	
	return true;
}

void ScriptLoader::Cleanup() {
	loader.Clear();
}

bool ScriptLoader::ImplementScript() {
	
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
	
	
	RTLOG("ScriptLoader::ImplementScript: loop post initialize");
	for (ScriptLoopLoader* ll : loops) {
		if (!ll->PostInitialize())
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
	Vector<Endpoint> path;
	
	if (from == to) {
		if (to->name.GetCount())
			path.Add(to);
	}
	else {
		AstNode* iter = to;
		while (iter && iter != from) {
			if (iter->name.GetCount() || iter == to) {
				path.Add(iter);
			}
			iter = iter->GetSubOwner();
		}
	}
	if (path.IsEmpty()) {
		AddError(to->loc, "internal error: empty path");
		return false;
	}
	for (int i = path.GetCount()-1; i >= 0; i--) {
		AstNode* id = path[i].n;
		ASSERT(id->name.GetCount());
		script_id.parts.Add(id->name);
	}
	
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
	
	
	// Serial machine part
	Vector<Endpoint> items;
	n->FindAllNonIdEndpoints(items, SEMT_MACH_ANY);
	Sort(items, AstNodeLess());
	
	bool has_machine = false;
	for (const Endpoint& ep : items) {
		AstNode* item = ep.n;
		if (item->src == SEMT_MACHINE) {
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			Script::MachineDefinition& mach_def = def.machs.Add();
			
			if (!GetPathId(mach_def.id, n, item))
				return false;
			
			ASSERT(!mach_def.id.IsEmpty());
			if (!LoadMachine(mach_def, block))
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
	
	
	// Entity machine / ecs-engine part
	items.SetCount(0);
	n->FindAllNonIdEndpoints(items, SEMT_ECS_ANY);
	Sort(items, AstNodeLess());
	
	bool has_world = false;
	for (const Endpoint& ep : items) {
		AstNode* item = ep.n;
		LOG(item->GetTreeString(0));
		if (item->src == SEMT_WORLD) {
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			Script::WorldDefinition& world_def = def.worlds.Add();
			
			if (!GetPathId(world_def.id, n, item))
				return false;
			
			ASSERT(!world_def.id.IsEmpty());
			if (!LoadWorld(world_def, block))
				return false;
			has_world = true;
		}
		else if (item->src == SEMT_SYSTEM) {
			TODO
		}
	}
	
	
	return true;
}

bool ScriptLoader::LoadMachine(Script::MachineDefinition& def, AstNode* n) {
	Vector<Endpoint> items;
	n->FindAllNonIdEndpoints(items, (SemanticType)(SEMT_ECS_ANY | SEMT_MACH_ANY));
	Sort(items, AstNodeLess());
	
	if (items.IsEmpty()) {
		AddError(def.loc, "empty node");
		return false;
	}
	
	Script::ChainDefinition* anon_chain = 0;
	
	bool has_chain = false;
	for (const Endpoint& ep : items) {
		AstNode* item = ep.n;
		if (item->src == SEMT_CHAIN) {
			Script::ChainDefinition& chain_def = def.chains.Add();
			
			if (!GetPathId(chain_def.id, n, item))
				return false;
			
			ASSERT(!chain_def.id.IsEmpty());
			
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			Vector<Endpoint> items;
			block->FindAllNonIdEndpoints(items, SEMT_CHAIN);
			if (items.IsEmpty()) {
				if (!LoadChain(chain_def, block))
					return false;
			} else {
				if (!LoadTopChain(chain_def, block))
					return false;
			}
			has_chain = true;
		}
		else if (item->src == SEMT_DRIVER || item->src == SEMT_LOOP) {
			if (!anon_chain)
				anon_chain = &def.chains.Add();
			
			if (!LoadChain(*anon_chain, item))
				return false;
			has_chain = true;
		}
	}
	
	if (!has_chain) {
		Script::ChainDefinition& chain = def.chains.Add();
		return LoadChain(chain, n);
	}
	
	return true;
}

bool ScriptLoader::LoadWorld(Script::WorldDefinition& def, AstNode* n) {
	Vector<Endpoint> items;
	n->FindAllNonIdEndpoints(items, SEMT_ECS_ANY);
	Sort(items, AstNodeLess());
	
	if (items.IsEmpty()) {
		AddError(def.loc, "empty node");
		return false;
	}
	
	Script::PoolDefinition* anon_pool = 0;
	
	bool has_chain = false;
	for (const Endpoint& ep : items) {
		AstNode* item = ep.n;
		if (item->src == SEMT_POOL) {
			Script::PoolDefinition& pool_def = def.pools.Add();
			
			if (!GetPathId(pool_def.id, n, item))
				return false;
			
			ASSERT(!pool_def.id.IsEmpty());
			
			AstNode* block = item->Find(SEMT_STATEMENT_BLOCK);
			if (!block) {AddError(n->loc, "internal error: no stmt block"); return false;}
			
			Vector<Endpoint> items;
			block->FindAllNonIdEndpoints(items, SEMT_POOL);
			if (items.IsEmpty()) {
				if (!LoadPool(pool_def, block))
					return false;
			} else {
				if (!LoadTopPool(pool_def, block))
					return false;
			}
			has_chain = true;
		}
		else if (item->src == SEMT_SYSTEM) {
			Script::EcsSysDefinition& sys_def = def.systems.Add();
			
			if (!GetPathId(sys_def.id, n, item))
				return false;
			
			ASSERT(!sys_def.id.IsEmpty());
			
			if (!LoadEcsSystem(sys_def, item))
				return false;
			has_chain = true;
		}
	}
	
	return true;
}

bool ScriptLoader::LoadDriver(Script::DriverDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadTopChain(Script::ChainDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadEcsSystem(Script::EcsSysDefinition& def, AstNode* n) {
	
	if (!LoadArguments(def.args, n))
		return false;
	
	return true;
}

bool ScriptLoader::LoadPool(Script::PoolDefinition& def, AstNode* n) {
	const auto& map = Parallel::Factory::AtomDataMap();
	Vector<Endpoint> items;
	
	n->FindAll(items, SEMT_ENTITY);
	n->FindAll(items, SEMT_POOL);
	Sort(items, AstNodeLess());
	
	for (Endpoint& ep : items) {
		AstNode* item = ep.n;
		if (item->src == SEMT_POOL) {
			Script::PoolDefinition& pool_def = def.pools.Add();
			pool_def.loc = item->loc;
			
			if (!GetPathId(pool_def.id, n, item))
				return false;
			
			if (!LoadPool(pool_def, item))
				return false;
		}
		else if (item->src == SEMT_ENTITY) {
			Script::EntityDefinition& ent_def = def.ents.Add();
			ent_def.loc = item->loc;
			
			if (!GetPathId(ent_def.id, n, item))
				return false;
			
			if (!LoadEntity(ent_def, item))
				return false;
		}
	}
	
	return true;
}

bool ScriptLoader::LoadTopPool(Script::PoolDefinition& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadState(Script::StateDeclaration& def, AstNode* n) {
	
	TODO
	
}

bool ScriptLoader::LoadEntity(Script::EntityDefinition& def, AstNode* n) {
	LOG(n->GetTreeString(0));
	
	const auto& map = Parallel::Factory::AtomDataMap();
	Vector<Endpoint> items;
	
	n->FindAll(items, SEMT_COMPONENT);
	Sort(items, AstNodeLess());
	
	for (Endpoint& ep : items) {
		AstNode* item = ep.n;
		Script::ComponentDefinition& comp_def = def.comps.Add();
		comp_def.loc = item->loc;
		
		if (!GetPathId(comp_def.id, n, item))
			return false;
		
		if (!LoadComponent(comp_def, item))
			return false;
	}
	
	if (!LoadArguments(def.args, n))
		return false;
	
	return true;
}

bool ScriptLoader::LoadComponent(Script::ComponentDefinition& def, AstNode* n) {
	
	if (!LoadArguments(def.args, n))
		return false;
	
	return true;
}

bool ScriptLoader::LoadChain(Script::ChainDefinition& chain, AstNode* n) {
	const auto& map = Parallel::Factory::AtomDataMap();
	Vector<Endpoint> loops, states, atoms, stmts, conns;
	
	n->FindAll(loops, SEMT_DRIVER); // subset of loops
	n->FindAll(loops, SEMT_LOOP);
	Sort(loops, AstNodeLess());
	
	for (Endpoint& ep : loops) {
		AstNode* loop = ep.n;
		bool is_driver = loop->src == SEMT_DRIVER;
		
		Script::LoopDefinition& loop_def = chain.loops.Add();
		loop_def.loc = loop->loc;
		loop_def.is_driver = is_driver;
		
		if (!GetPathId(loop_def.id, n, loop))
			return false;
		
		AstNode* stmt_block = loop->Find(SEMT_STATEMENT_BLOCK);
		if (!stmt_block) {
			AddError(loop->loc, "loop has no statement-block");
			return false;
		}
		
		atoms.SetCount(0);
		stmt_block->FindAll(atoms, SEMT_ATOM);
		Sort(atoms, AstNodeLess());
		
		if (atoms.IsEmpty()) {
			AddError(loop->loc, "no atoms in statement-block");
			return false;
		}
		
		if (is_driver && atoms.GetCount() > 1) {
			AddError(loop->loc, "only single atom is allowed in driver");
			return false;
		}
		
		if (atoms.GetCount() == 1 && !is_driver) {
			AddError(loop->loc, "only one atom in the loop");
			return false;
		}
		
		for (Endpoint& ep : atoms) {
			AstNode* atom = ep.n;
			Script::AtomDefinition& atom_def = loop_def.atoms.Add();
			
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
			
			if (!is_driver) {
				ASSERT(atom_def.iface.sink.GetCount());
				ASSERT(atom_def.iface.src.GetCount());
				atom_def.link = link;
				
				conns.SetCount(0);
				atom->FindAllStmt(conns, STMT_ATOM_CONNECTOR);
				Sort(conns, AstNodeLess());
				if (!conns.IsEmpty()) {
					int sink_conn_i = 0, src_conn_i = 0; // side ids start from 1, so this shouldn't be -1
					for (Endpoint& ep : conns) {
						AstNode* conn = ep.n;
						bool is_src = conn->i64 != 0;
						if (is_src)
							src_conn_i++;
						else
							sink_conn_i++;
						
						if (conn->sub.IsEmpty()) {
							// Empty connector is allowed
							continue;
						}
							
						AstNode* expr = conn->Find(SEMT_EXPR);
						if (!expr) {
							AddError(conn->loc, "internal error: no expression");
							return false;
						}
						
						bool succ = false;
						if (expr->op == OP_EQ) {
							Script::AtomDefinition::LinkCandidate& cand =
								is_src ?
									atom_def.src_link_cands.Add(src_conn_i) :
									atom_def.sink_link_cands.Add(sink_conn_i);
							
							AstNode* a0 = expr->arg[0];
							AstNode* a1 = expr->arg[1];
							while (a0->src == SEMT_RVAL && a0->rval) a0 = a0->rval;
							while (a1->src == SEMT_RVAL && a1->rval) a1 = a1->rval;
							String key;
							if (a0->src == SEMT_VARIABLE) {
								key = a0->name;
							}
							else if (a0->src == SEMT_UNRESOLVED) {
								key = a0->str;
							}
							if (key.GetCount()) {
								if (a1->src == SEMT_CONSTANT) {
									a1->CopyToObject(cand.req_args.GetAdd(key));
									succ = true;
								}
								else if (a1->src == SEMT_UNRESOLVED) {
									cand.req_args.GetAdd(key) = a1->str;
									succ = true;
								}
							}
						}
						
						if (!succ) {
							AddError(expr->loc, "invalid atom connector expression");
							return false;
						}
					}
				}
			}
			
			if (!LoadArguments(atom_def.args, atom))
				return false;
		}
		
		if (!LoadArguments(loop_def.args, loop))
			return false;
		
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
				
				int sink_cand_i = src_atom.src_link_cands.Find(src_i);
				Script::AtomDefinition::LinkCandidate* src_cand =
					sink_cand_i >= 0 ?
						&src_atom.src_link_cands[sink_cand_i] : 0;
				
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
							
							int sink_cand_i = sink_atom.sink_link_cands.Find(sink_i);
							Script::AtomDefinition::LinkCandidate* sink_cand =
								sink_cand_i >= 0 ?
									&sink_atom.sink_link_cands[sink_cand_i] : 0;
							
							// Only single fully optional is tried (so continue if connection exists)
							if ((sink_is_opt && !sink_cand) || (src_is_opt && !src_cand)) {
								if (src_atom.iface.HasCommonConnection(sink_atom.iface))
									continue;
							}
							
							if (sink_conn.conn < 0 && src_vd == sink_vd) {
								bool cond_prevents = false;
								
								if (src_cand) {
									for(int i = 0; i < src_cand->req_args.GetCount() && !cond_prevents; i++) {
										String key = src_cand->req_args.GetKey(i);
										if (key == "loop") {
											String loop_req = src_cand->req_args[i].ToString();
											Vector<String> parts = Split(loop_req, ".");
											if (!sink_loop.IsPathTrailMatch(parts))
												cond_prevents = true;
										}
										else {
											int j = sink_loop.args.Find(key);
											if (j >= 0) {
												const Object& src_obj = src_cand->req_args[i];
												const Object& sink_obj = sink_loop.args[j];
												if (src_obj != sink_obj)
													cond_prevents = true;
											}
											else cond_prevents = true;
										}
									}
								}
								
								if (sink_cand) {
									for(int i = 0; i < sink_cand->req_args.GetCount() && !cond_prevents; i++) {
										String key = sink_cand->req_args.GetKey(i);
										if (key == "loop") {
											String loop_req = sink_cand->req_args[i].ToString();
											Vector<String> parts = Split(loop_req, ".");
											if (!src_loop.IsPathTrailMatch(parts))
												cond_prevents = true;
										}
										else {
											int j = src_loop.args.Find(key);
											if (j >= 0) {
												const Object& sink_obj = sink_cand->req_args[i];
												const Object& src_obj = src_loop.args[j];
												if (sink_obj != src_obj)
													cond_prevents = true;
											}
											else cond_prevents = true;
										}
									}
								}
								
								if (!cond_prevents) {
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
						}
						
						if (connected)
							break;
					}
					
					if (connected)
						break;
				}
				
				if (!connected && !src_is_opt) {
					AddError(src_atom.loc, "could not connect source to any sink. Loop '" + src_loop.id.ToString() + "', atom '" + src_atom.id.ToString() + "'");
					return false;
				}
			}
		}
	}
	
	
	n->FindAll(states, SEMT_STATE);
	Sort(states, AstNodeLess());
	for (Endpoint& ep : states) {
		AstNode* state = ep.n;
		Script::StateDeclaration& state_def = chain.states.Add();
		state_def.loc = state->loc;
		
		if (!GetPathId(state_def.id, n, state))
			return false;
		
	}
	
	return true;
}

bool ScriptLoader::LoadArguments(ArrayMap<String, Object>& args, AstNode* n) {
	if (!n)
		return true; // only failed statements returns false
	
	if (n->src != SEMT_STATEMENT_BLOCK) {
		AstNode* block = n->Find(SEMT_STATEMENT_BLOCK);
		return LoadArguments(args, block);
	}
	
	AstNode* block = n;
	Vector<Endpoint> stmts;
	
	for (AstNode& stmt : block->sub) {
		if (stmt.src != SEMT_STATEMENT || stmt.stmt == STMT_ATOM_CONNECTOR) continue;
		
		static int dbg_i;
		bool succ = false;
		if (stmt.stmt == STMT_EXPR) {
			if (stmt.rval) {
				AstNode* r = stmt.rval;
				while (r->src == SEMT_RVAL && r->rval) r = r->rval;
				AstNode& rval = *r;
				
				if (rval.src == SEMT_EXPR) {
					if (rval.op == OP_ASSIGN) {
						dbg_i++;
						if (dbg_i == 15) {
							LOG("");
						}
						AstNode* key = rval.arg[0];
						AstNode* value = rval.arg[1];
						while (key->src == SEMT_RVAL && key->rval) key = key->rval;
						while (value->src == SEMT_RVAL && value->rval) value = key->rval;
						if (key->src == SEMT_UNRESOLVED && key->str.GetCount()) {
							String key_str = key->str;
							if (value->src == SEMT_CONSTANT) {
								Object val_obj;
								value->CopyToObject(val_obj);
								args.GetAdd(key_str) = val_obj;
								succ = true;
							}
							else if (value->src == SEMT_UNRESOLVED && value->str.GetCount()) {
								args.GetAdd(key_str) = value->str;
								succ = true;
							}
							else if (value->src == SEMT_EXPR) {
								Object val_obj = EvaluateAstNodeObject(*value);
								args.GetAdd(key_str) = val_obj;
								succ = true;
							}
							else {
								LOG(rval.GetTreeString(0));
								TODO
							}
						}
						else {
							LOG(rval.GetTreeString(0));
							TODO
						}
					}
					else {
						LOG(rval.GetTreeString(0));
						TODO
					}
				}
				else if (rval.src == SEMT_STATEMENT_BLOCK ||
						 rval.src == SEMT_SYMBOLIC_LINK) {
					if (!LoadArguments(args, &rval))
						return false;
					succ = true;
				}
				else {
					LOG(rval.GetTreeString(0));
					TODO
				}
			}
			else {
				LOG(stmt.GetTreeString(0));
				TODO
			}
		}
		else {
			LOG(stmt.GetTreeString(0));
			TODO
		}
		
		if (!succ) {
			DUMP(dbg_i);
			LOG(stmt.GetTreeString(0));
			AddError(stmt.loc, "could not resolve statement in atom");
			return false;
		}
	}
	
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
							AddError(loop0.def.loc, "Side-linking was refused");
							return false;
						}
						
						LOG(src->ToString() + "(" << HexStr(&*src) << "," << src_ch_i << ") side-linked to " + sink->ToString() + "(" << HexStr(&*sink) << "," << sink_ch_i << ")");
						
						
						loop0.UpdateLoopLimits();
						loop1.UpdateLoopLimits();
						break;
					}
				}
			}
			
			
			dbg_i++;
		}
	}
	
	
	return true;
}


NAMESPACE_SERIAL_END


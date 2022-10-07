#include "SerialScript.h"


NAMESPACE_SERIAL_BEGIN


ScriptChainLoader::ScriptChainLoader(ScriptTopChainLoader& parent, int id, Script::ChainDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::LoopDefinition& loop : def.loops) {
		ScriptLoopLoader& loader = loops.Add(new ScriptLoopLoader(*this, loops.GetCount(), loop));
	}
	
	for (Script::StateDeclaration& state : def.states) {
		ScriptStateLoader& loader = states.Add(new ScriptStateLoader(*this, states.GetCount(), state));
	}
	
}

bool ScriptChainLoader::Load() {
	TODO
}

String ScriptChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Chain " << id;
	s.Cat('\n');
	for (ScriptLoopLoader& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	//s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptChainLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptLoopLoader& loader : loops) {
		v.Add(&loader);
	}
}

void ScriptChainLoader::GetStates(Vector<ScriptStateLoader*>& v) {
	for (ScriptStateLoader& state : states) {
		v.Add(&state);
	}
}

/*void ScriptChainLoader::Forward() {
	if (iter == 0) {
		Index<String> loop_names;
		for (const ScriptLoopLoader& ll : loops) {
			String name = ll.def.id.ToString();
			if (loop_names.Find(name) >= 0) {
				AddError(def.loc, "duplicate loop with name '" + name + "'");
				return;
			}
			loop_names.Add(name);
		}
		RTLOG("ScriptChainLoader::Forward: chain '" << def.id.ToString() << "' duplicate loop check passed");
	}
	
	if (def.states.IsFilled() && states.IsEmpty()) {
		int id = 0;
		for (Script::StateDeclaration& decl : def.states) {
			ScriptStateLoader& loader = states.Add(new ScriptStateLoader(*this, id++, decl));
			loader.Forward();
		}
	}
	
	if (status == MAKE_OPTION_LINK_VECTOR) {
		MakeOptionLinkVector();
	}
	else if (status == PRUNE_OPTION_LINKS) {
		FindAcceptedLinks();
	}
	else if (status == LINK_PLANNER) {
		LinkPlanner();
	}
	else if (status == LINKER) {
		Linker();
	}
	else
		Base::Forward();
	
	iter++;
}*/

/*void ScriptChainLoader::ForwardLoops() {
	if (status == WAITING_CHILDREN) {
		for (ScriptLoopLoader& loader : loops) {
			loader.Forward();
		}
	}
	else TODO
}

void ScriptChainLoader::LoopStatus() {
	for (ScriptLoopLoader& loader : loops) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptChainLoader::CheckStatusDeep() {
	for (ScriptLoopLoader& loader : loops)
		loader.CheckStatusDeep();
	
	CheckFlags();
}*/

Script::Id ScriptChainLoader::GetDeepId() const {
	return parent.GetDeepId(); // chain & topchain has same id
}

/*
void ScriptChainLoader::MakeOptionLinkVector() {
	solver.Create();
	
	if (!solver->Initialize(this)) {
		SetError("Could not initialize ScriptConnectionSolver: " + solver->GetError());
		return;
	}
	
	if (!solver->MakeOptionLinkVector()) {
		SetError("Could not make option link vector: " + solver->GetError());
		return;
	}
	
	SetStatus(PRUNE_OPTION_LINKS);
}

void ScriptChainLoader::FindAcceptedLinks() {
	
	if (!solver->FindAcceptedLinks()) {
		SetError("Could not prune option links: " + solver->GetError());
		return;
	}
	
	SetStatus(LINK_PLANNER);
}

void ScriptChainLoader::LinkPlanner() {
	
	if (!solver->LinkPlanner()) {
		SetError("Could find linking plan: " + solver->GetError());
		return;
	}
	
	SetStatus(LINKER);
}*/

/*void ScriptChainLoader::Linker() {
	const Vector<ScriptLinkOption*>& result = solver->result;
	const Array<ScriptLoopOptions>& options = solver->loops;
	
	int& side_id_counter = GetLoader().GetSideIdCounter();
	
	for (ScriptLinkOption* link : result) {
		ScriptLoopLoader& src = *link->src_loop->ll;
		ScriptLoopLoader& sink = *link->sink_loop->ll;
		Script::ActionPlanner::State& src_node = link->src->state;
		Script::ActionPlanner::State& sink_node = link->sink->state;
		
		src.RealizeConnections(src_node);
		sink.RealizeConnections(sink_node);
		
		AtomTypeCls src_type = src_node.last->GetWorldState().GetAtom();
		AtomTypeCls sink_type = sink_node.last->GetWorldState().GetAtom();
		src.SetSideSourceConnected(src_type, src_node.ch_i, sink);
		sink.SetSideSinkConnected(sink_type, sink_node.ch_i, src);
		
		
		int conn_id = side_id_counter++;
		
		src_node.last->GetInterface().Realize(src_type);
		src_node.last->GetInterface().SetSource(conn_id,		src_node.ch_i,	sink_node.ch_i);
		
		sink_node.last->GetInterface().Realize(sink_type);
		sink_node.last->GetInterface().SetSink(conn_id,		sink_node.ch_i,	src_node.ch_i);
		
		LOG("Loop src " << src.GetId() << " ch " << src_node.ch_i << " accepted loop sink "
			<< sink.GetId() << " ch " << sink_node.ch_i << " with id " << conn_id);
		
	}
	
	// loops with incomplete iface links will be tried again until complete failure
	bool has_failures = false;
	for (ScriptLoopOptions& loop : options) {
		ScriptLoopLoader& ll = *loop.ll;
		if (ll.GetStatus() == WAITING_PARENT_SIDE_LINKS) {
			
			// for difficult debugging
			#if 0
			if (ll.GetAtomLinkCount() > 0) {
				static int counter = 0;
				RTLOG("ScriptChainLoader::Linker: ll.IsTopSidesConnected(): " << ll.def.id.ToString() << " counter=" << counter << ": " << (ll.IsTopSidesConnected() ? "true" : "false"));
				if (counter == 4) {
					ll.IsTopSidesConnected();
					TODO
				}
				counter++;
			}
			#endif
			
			if (ll.GetAtomLinkCount() > 0 && ll.IsTopSidesConnected()) {
				LOG("Loop " << ll.GetId() << " all sides connected");
				bool found = false;
				for (ScriptLinkOption* link : result) {
					if (link->src_loop->ll == &ll) {
						ll.AddSideConnectionSegment(link->src->state);
						found = true;
						break;
					}
					if (link->sink_loop->ll == &ll) {
						ll.AddSideConnectionSegment(link->sink->state);
						found = true;
						break;
					}
				}
				ASSERT(found);
				ll.SetStatus(WAITING_CHILDREN);
			}
			else
				has_failures = true;
		}
	}
	
	CheckStatusDeep();
	
	if (has_failures)
		SetStatus(WAITING_PARENT_SIDE_LINKS);
	else
		SetStatus(WAITING_CHILDREN);
	
}*/


NAMESPACE_SERIAL_END

#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptChainLoader::ScriptChainLoader(ScriptTopChainLoader& parent, int id, Script::ChainDefinition& def) :
	Base(parent, id, def)
{
	
	for (Script::LoopDefinition& loop : def.loops) {
		ScriptLoopLoader& loader = loops.Add(new ScriptLoopLoader(*this, loops.GetCount(), loop));
	}
	
}

String ScriptChainLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Chain " << id;
	s.Cat('\n');
	for (ScriptLoopLoader& loader : loops) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptChainLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptLoopLoader& loader : loops) {
		v.Add(&loader);
	}
}

void ScriptChainLoader::Forward() {
	
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
	
}

void ScriptChainLoader::ForwardLoops() {
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

void ScriptChainLoader::SetRetryDeep() {
	if (status == ScriptStatus::READY)
		return;
	
	SetStatus(ScriptStatus::IN_BEGINNING);
	
	for (ScriptLoopLoader& loader : loops)
		loader.SetRetryDeep();
}

void ScriptChainLoader::MakeOptionLinkVector() {
	solver = new ScriptConnectionSolver(GetLoader().GetSideIdCounter());
	
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
}

void ScriptChainLoader::Linker() {
	Vector<ScriptLinkOption*>& result = solver->result;
	
	for (ScriptLinkOption* link : result) {
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
		
	}
	
	// loops with incomplete iface links will be tried again until complete failure
	
	TODO
	
	SetStatus(WAITING_PARENT_SIDE_LINKS);
}


NAMESPACE_SERIAL_END

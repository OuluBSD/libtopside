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
	
	TODO
	
	// SetRetryDeep();
}


NAMESPACE_SERIAL_END

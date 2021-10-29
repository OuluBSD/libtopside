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

void ScriptChainLoader::ForwardLoops() {
	for (ScriptLoopLoader& loader : loops) {
		ScriptStatus s = loader.GetStatus();
		if (s != ScriptStatus::SINK_IS_WAITING &&
			s != ScriptStatus::SOURCE_IS_WAITING &&
			s != ScriptStatus::READY) {
			loader.Forward();
		}
	}
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


NAMESPACE_SERIAL_END

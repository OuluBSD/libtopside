#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptDriverLoader::ScriptDriverLoader(ScriptMachineLoader& parent, int id, Script::DriverDefinition& def) :
	Base(parent, id, def)
{
	
}

String ScriptDriverLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Driver " << id;
	s.Cat('\n');
	/*for (ScriptTopChainLoader& loader : chains) {
		s << loader.GetTreeString(indent+1);
	}*/
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptDriverLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	TODO
}

void ScriptDriverLoader::ForwardLoops() {
	TODO
}

void ScriptDriverLoader::LoopStatus() {
	TODO
}

void ScriptDriverLoader::SetRetryDeep() {
	TODO
}


NAMESPACE_SERIAL_END

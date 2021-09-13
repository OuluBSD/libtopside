#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptSystemLoader::ScriptSystemLoader(ScriptLoader& parent, int id, Script::GlobalScope& def) :
	Base(parent, id, def)
{
	
	for (Script::MachineDefinition& mach : def.machs) {
		ScriptMachineLoader& loader = machs.Add(new ScriptMachineLoader(*this, machs.GetCount(), mach));
	}
	
}

String ScriptSystemLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "System " << id;
	s.Cat('\n');
	for (ScriptMachineLoader& loader : machs) {
		s << loader.GetTreeString(indent+1);
	}
	s << GetScriptStatusLine(indent+1, status);
	
	return s;
}

void ScriptSystemLoader::ForwardLoops() {
	ASSERT(!IsReady() && !IsFailed());
	for (ScriptMachineLoader& loader : machs) {
		ScriptStatus s = loader.GetStatus();
		if (s != ScriptStatus::OUTPUT_IS_WAITING &&
			s != ScriptStatus::INPUT_IS_WAITING &&
			s != ScriptStatus::READY) {
			loader.Forward();
		}
	}
}

void ScriptSystemLoader::LoopStatus() {
	for (ScriptMachineLoader& loader : machs) {
		CheckStatus(loader.GetStatus());
	}
}

void ScriptSystemLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	for (ScriptMachineLoader& loader : machs) {
		loader.GetLoops(v);
	}
}

void ScriptSystemLoader::GetDrivers(Vector<ScriptDriverLoader*>& v) {
	for (ScriptMachineLoader& loader : machs) {
		loader.GetDrivers(v);
	}
}

void ScriptSystemLoader::SetRetryDeep() {
	if (status == ScriptStatus::READY)
		return;
	status = ScriptStatus::IN_BEGINNING;
	for (ScriptMachineLoader& loader : machs)
		loader.SetRetryDeep();
}


NAMESPACE_SERIAL_END

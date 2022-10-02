#include "SerialScript.h"

#if 0

NAMESPACE_SERIAL_BEGIN

ScriptEntityLoader::ScriptEntityLoader(ScriptPoolLoader& parent, int id, Script::EntityDefinition& def) :
	Base(parent, id, def) {
	
	for (Script::ComponentDefinition& sys : def.comps) {
		comps.Add(new ScriptComponentLoader(*this, comps.GetCount(), sys));
	}
	
}


NAMESPACE_SERIAL_END

#endif
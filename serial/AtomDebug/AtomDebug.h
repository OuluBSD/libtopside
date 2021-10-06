#ifndef _AtomDebug_AtomDebug_h_
#define _AtomDebug_AtomDebug_h_

#include <AtomNonGUI/AtomNonGUI.h>
#include <AtomLocal/AtomLocal.h>

#include "Verifier.h"


NAMESPACE_SERIAL_BEGIN

void DebugMain(String script_content, String eon_file, VectorMap<String,Object>& args, MachineVerifier* ver=0, bool dbg_ref_visits=false, uint64 dbg_ref=0);

NAMESPACE_SERIAL_END

#endif

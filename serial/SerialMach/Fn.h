#ifndef _SerialMach_Fn_h_
#define _SerialMach_Fn_h_


NAMESPACE_TOPSIDE_BEGIN

void DebugMain(String script_content, String eon_file, VectorMap<String,Object>& args, Parallel::MachineVerifier* ver=0, bool dbg_ref_visits=false, uint64 dbg_ref=0);

NAMESPACE_TOPSIDE_END


#endif

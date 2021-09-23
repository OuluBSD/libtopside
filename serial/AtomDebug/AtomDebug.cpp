#include "AtomDebug.h"


NAMESPACE_SERIAL_BEGIN


void DebugMain(String script_file, VectorMap<String,Object>& args, MachineVerifier* ver, bool dbg_ref_visits, uint64 dbg_ref) {
	SetCoutLog();
	//Serial::Factory::Dump();
	
	if (script_file.IsEmpty()) {
		LOG("No script file given");
		return;
	}
	
	if (dbg_ref)
		BreakRefAdd(dbg_ref);
	
	double time_limit = args.Get("MACHINE_TIME_LIMIT", 0).ToDouble();
	
	{
		Machine& mach = GetActiveMachine();
		
		if (ver)
			ver->Attach(mach);
		
		
		if (dbg_ref_visits)
			SetDebugRefVisits();
		RuntimeDiagnostics::Static().SetRoot(mach);
		
	    #ifdef flagSTDEXC
	    try {
	    #endif
			bool fail = false;
			{
				if (mach.IsStarted()) {
					RegistrySystemRef reg	= mach.FindAdd<RegistrySystem>();
					LoopStoreRef ls			= mach.FindAdd<LoopStore>();
					AtomStoreRef as			= mach.FindAdd<AtomStore>();
				    AtomSystemRef asys		= mach.FindAdd<AtomSystem>();
				    ScriptLoaderRef script	= mach.FindAdd<ScriptLoader>();
				    
				    mach.FindAdd<PacketTracker>();
				}
				
				LoopStoreRef ls			= mach.Find<LoopStore>();
				if (!ls) {
					LOG("No LoopStore added to machine and the machine is already started");
					return;
				}
				
				ScriptLoaderRef script	= mach.Find<ScriptLoader>();
				if (!script) {
					LOG("No ScriptLoader added to machine and the machine is already started");
					return;
				}
				
				LoopRef root = ls->GetRoot();
				
				String path;
				if (FileExists(script_file))
					path = script_file;
				else
					path = ShareDirFile(AppendFileName("eon", script_file));
				DUMP(path);
				String script_str = LoadFile(path);
				//script_str.DebugFollow();
				if (script_str.IsEmpty()) {
					LOG("No script file in " << path);
					return;
				}
				for(int i = 0; i < args.GetCount(); i++) {
					String key = "${" + args.GetKey(i) + "}";
					String value = args[i];
					script_str.Replace(key, value);
				}
				LOG(script_str);
				
		        script->PostLoadString(script_str);
		    }
		        
		    if (!fail) {
		        if (!mach.IsStarted())
					fail = !mach.Start();
		    }
		    
		    if (!fail) {
			    int iter = 0;
			    TimeStop t, total;
			    double sleep_dt_limit = 1.0 / 300.0;
			    while (mach.IsRunning()) {
			        double dt = ResetSeconds(t);
			        mach.Update(dt);
			        
			        if (!iter++)
						mach.Get<LoopStore>()->GetRoot()->Dump();
					
					if (dt < sleep_dt_limit)
						Sleep(1);
			        
			        double total_seconds = total.Seconds();
			        if (time_limit > 0 && total_seconds >= time_limit)
			            mach.SetNotRunning();
			    }
			    
			    RuntimeDiagnostics::Static().CaptureSnapshot();
		    }
		#ifdef flagSTDEXC
	    }
	    catch (Exc e) {
	        LOG("error: " << e);
	        Exit(1);
	    }
	    #endif
	    
	    mach.Stop();
	    mach.Clear();
	}
    
    //RefDebugVisitor::Static().DumpUnvisited();
}


NAMESPACE_SERIAL_END

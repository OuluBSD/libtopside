#include "AtomDebug.h"


NAMESPACE_SERIAL_BEGIN


void DebugMain(String script_file, VectorMap<String,Object>& args, MachineVerifier* ver, bool dbg_ref_visits, uint64 dbg_ref) {
	SetCoutLog();
	//Serial::Factory::Dump();
	
	if (dbg_ref)
		BreakRefAdd(0x80AE32468);
	
	double time_limit = args.Get("MACHINE_TIME_LIMIT", 0).ToDouble();
	
	{
		MAKE_STATIC(Machine, mach);
		
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
				RegistrySystemRef reg	= mach.Add<RegistrySystem>();
				LoopStoreRef ls			= mach.Add<LoopStore>();
				AtomStoreRef as			= mach.Add<AtomStore>();
			    AtomSystemRef asys		= mach.Add<AtomSystem>();
			    ScriptLoaderRef script	= mach.Add<ScriptLoader>();
			    
			    mach.Add<PacketTracker>();
				
				LoopRef root = ls->GetRoot();
				
				String path;
				if (FileExists(script_file))
					path = script_file;
				else
					path = ShareDirFile(AppendFileName("script", script_file));
				DUMP(path);
				String script_str = LoadFile(path);
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
			    mach.Start();
			    
			    int iter = 0;
			    TimeStop t, total;
			    while (mach.IsRunning()) {
			        double dt = ResetSeconds(t);
			        mach.Update(dt);
			        
			        if (!iter++)
						mach.Get<LoopStore>()->GetRoot()->Dump();
					
			        Sleep(1);
			        
			        if (time_limit > 0 && total.Seconds() >= time_limit)
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

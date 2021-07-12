#include "EcsDebug.h"


NAMESPACE_ECS_BEGIN



void DebugMain(String eon_file, VectorMap<String,Object>& args, MachineVerifier* ver, bool dbg_ref_visits, uint64 dbg_ref) {
	SetCoutLog();
	//Ecs::Factory::Dump();
	
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
				RegistrySystemRef reg		= mach.Add<RegistrySystem>();
				EntityStoreRef es			= mach.Add<EntityStore>();
				ComponentStoreRef compstore	= mach.Add<ComponentStore>();
			    ExtSystemRef cust			= mach.Add<ExtSystem>();
			    EonLoaderRef eon			= mach.Add<EonLoader>();
			    
			    mach.Add<PacketTracker>();
				
				PoolRef root = es->GetRoot();
				
				String path;
				if (FileExists(eon_file))
					path = eon_file;
				else
					path = ShareDirFile(AppendFileName("eon", eon_file));
				DUMP(path);
				String eon_str = LoadFile(path);
				if (eon_str.IsEmpty()) {
					LOG("No eon file in " << path);
					return;
				}
				for(int i = 0; i < args.GetCount(); i++) {
					String key = "${" + args.GetKey(i) + "}";
					String value = args[i];
					eon_str.Replace(key, value);
				}
				LOG(eon_str);
		        eon->PostLoadString(eon_str);
		    }
		        
		    if (!fail) {
			    mach.Start();
			    
			    int iter = 0;
			    TimeStop t, total;
			    while (mach.IsRunning()) {
			        double dt = ResetSeconds(t);
			        mach.Update(dt);
			        
			        if (!iter++)
			            mach.Get<EntityStore>()->GetRoot()->Dump();
			        
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



NAMESPACE_ECS_END

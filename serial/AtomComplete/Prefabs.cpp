#include "AtomComplete.h"

NAMESPACE_SERIAL_BEGIN


void SimpleSerialMain(String title, bool start_machine) {
	Machine& mach = GetActiveMachine();
	
	
	if (start_machine) {
		ASSERT(!mach.IsRunning());
		
		try {
		    RegistrySystem& reg = *mach.Add<RegistrySystem>();
			LoopStore& ents = *mach.Add<LoopStore>();
		    mach.Add<AtomStore>();
		    mach.Add<AtomSystem>();
		    
		    #if 0
		    
		    #if HAVE_SDL2
		    mach.Add<SDL2GUI3DSystem>();
		    #endif
		    
		    #ifdef flagOPENVR
		    mach.Add<OpenVR>();
		    #endif
		    
		    #endif
		    
		    reg.SetAppName(title);
		    
		    if (!mach.Start()) {
		        LOG("error: machine wouldn't start");
		        return;
		    }
		}
		catch (Exc e) {
			LOG("error: " << e);
			return;
		}
	}
	else if (!mach.IsRunning()) {
		LOG("error: machine is not running and start argument wasn't set");
		return;
	}
	
	try {
		Ref<LoopStore> ents = mach.Find<LoopStore>();
		if (ents.IsEmpty())
			throw Exc("LoopStore was not added to the ECS machine");
		
		LoopRef root = ents->GetRoot();
		
		#if 0
		
		#if HAVE_SDL2
			#ifdef flagGUI
				LoopRef app = root->Create<StandaloneWindow>();
			#else
				LoopRef app = root->Create<StandaloneConsole>
				();
			#endif
			app->Find<Connector>()->ConnectAll();
		#endif
		
		#ifdef flagVR
		LoopRef cam = root->Create<CameraPrefab>();
		cam->Find<Connector>()->ConnectAll(CONNAREA_POOL_CURRENT);
		#endif
		
		#endif
		
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	    }
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
	
	if (start_machine) {
		mach.Stop();
	}
	
}


NAMESPACE_SERIAL_END
